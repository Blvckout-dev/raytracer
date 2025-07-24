#include "geometry/shapes/sphere.h"
#include "lights/light.h"
#include "camera/camera.h"
#include "ui/MainWindow.h"
#include "scene/scene.h"
#include "render/renderer.h"
#include "timer/TickTimer.h"
#include "timer/Stopwatch.h"
#include <QApplication>
#include <QImage>

using vec::Vec3;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Resolution
    constexpr int width { 800 };
    constexpr int height { 600 };

    // Field of View
    constexpr float fovDegrees { 90.0f };

    // Camera setup
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        Vec3(0.f, 0.f, 6.f),
        Vec3(0.0f, 0.0f, -1.0f),
        width,
        height,
        fovDegrees
    );

    // Object
    Sphere sphere(Vec3(0.f, 0.f, 0.f), 0.5f);

    // Light
    std::shared_ptr<Light> light = std::make_shared<Light>(
        Vec3(1.0f, -1.0f, 0.0f)
    );

    MainWindow w;

    Scene scene;
    
    scene.addCamera(camera);
    scene.setLight(light);

    scene.Sphere = &sphere;

    Renderer renderer(&scene, width, height);

    QImage image(width, height, QImage::Format_ARGB32);

    std::atomic<bool> isRendering { false };
    float frameTimeMs {};

    TickTimer tickTimer;
    Stopwatch stopwatch;

    tickTimer.onTick = [&](double deltaTime) {
        if (isRendering.exchange(true)) return;

        stopwatch.restart();

        renderer.render();
        std::memcpy(image.bits(), renderer.getPixelBuffer().data(), renderer.getPixelBuffer().size() * sizeof(uint32_t));

        QMetaObject::invokeMethod(&w, [wPtr = &w, image]() {
            wPtr->setImage(image);
        }, Qt::QueuedConnection);

        qDebug() << "Frame render time [ms]:" << stopwatch.elapsedMs();

        isRendering.store(false);
    };

    tickTimer.start();

    w.show();

    return app.exec();
}
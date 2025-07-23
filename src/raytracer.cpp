#include "geometry/shapes/sphere.h"
#include "lights/light.h"
#include "camera/camera.h"
#include "ui/MainWindow.h"
#include "scene/scene.h"
#include "render/renderer.h"
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

    Scene scene;
    
    scene.addCamera(camera);
    scene.setLight(light);

    scene.Sphere = &sphere;

    Renderer renderer(&scene, width, height);
    renderer.render();

    MainWindow w;
    w.show();

    QImage image(
        reinterpret_cast<const uchar*>(renderer.getPixelBuffer().data()),
        width,
        height,
        width * sizeof(uint32_t),
        QImage::Format_ARGB32
    );

    w.setImage(image);

    return app.exec();
}
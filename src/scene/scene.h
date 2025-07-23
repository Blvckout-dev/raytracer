#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

class Sphere;
struct Light;
class Camera;

class Scene {
private:
    std::shared_ptr<Light> _light {};

    std::vector<std::shared_ptr<Camera>> _cameras {};
    std::shared_ptr<Camera> _activeCamera {};

public:
    // temporary, will be replaced by std::vector<std::shared_ptr<MeshObject>> _meshObjects;
    Sphere* Sphere {};

    void addCamera(std::shared_ptr<Camera> camera);
    bool removeCamera(std::shared_ptr<Camera> camera);

    std::shared_ptr<Camera> getActiveCamera() const { return _activeCamera; };
    void setActiveCamera(std::shared_ptr<Camera> camera);

    std::shared_ptr<Light> getLight() const { return _light; };
    void setLight(std::shared_ptr<Light> light);
};

#endif // SCENE_H
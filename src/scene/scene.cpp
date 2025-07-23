#include "scene.h"

void Scene::addCamera(std::shared_ptr<Camera> camera) {
    if (!_activeCamera)
        setActiveCamera(camera);

    auto it = std::find(_cameras.begin(), _cameras.end(), camera);
    if (it == _cameras.end()) {
        _cameras.push_back(std::move(camera));
    }
}

bool Scene::removeCamera(std::shared_ptr<Camera> camera)
{
    auto it = std::find(_cameras.begin(), _cameras.end(), camera);
    if (it != _cameras.end()) {
        _cameras.erase(it);
        
        if (_activeCamera == camera) {
            _activeCamera.reset();

            if (!_cameras.empty())
                setActiveCamera(_cameras.front());
        }
        
        return true;
    }
    return false;
}

void Scene::setActiveCamera(std::shared_ptr<Camera> camera)
{
    // Setting _activeCamera before addCamera avoids infinite recursion
    _activeCamera = std::move(camera);
    addCamera(_activeCamera);
}

void Scene::setLight(std::shared_ptr<Light> light)
{
    _light = std::move(light);
}

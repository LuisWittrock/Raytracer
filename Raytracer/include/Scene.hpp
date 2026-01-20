#pragma once
#include <vector>
#include <memory>
#include "Object.hpp"
#include "Light.hpp"

using std::vector;

class Scene
{
private:
    std::vector<std::unique_ptr<Object>> objects;
    vector<Light> lights;

    cv::Vec3f ambient;
    int index;
    int recursion;
public:
    Scene() = default;
    Scene(const Scene&) = delete; // Delete copy constructor
    Scene& operator=(const Scene&) = delete; // Delete copy assignment operator
    Scene(Scene&&) = default; // Allow move constructor
    Scene& operator=(Scene&&) = default; // Allow move assignment operator

    void setAmbient(int index, int recursion, cv::Vec3f ambient);

    void addObject(std::unique_ptr<Object> object) {
        objects.push_back(std::move(object));
    }

    void addLight(const Light& light) {
        lights.push_back(light);
    }

    cv::Vec3f calcDiffuse(const std::optional<Intersection>& intersectionObj, const Light& light) const;
    bool shadowed(const Ray& ray) const;

    cv::Vec3f trace(const Ray& ray) const;

    cv::Vec3f compose(cv::Vec3f E1, cv::Vec3f E2) const;
}; 
#pragma once
#include "Color.hpp"
#include "Ray.hpp"
#include "LineareAlgebra.hpp"
#include <optional>

struct Intersection 
{
    Eigen::Vector3d point; //intersection point
    Eigen::Vector3d normal; //normal of surface at intersection
    Color color; 
    double distance; //distance to intersection point
};

class Object
{
protected:
    Color color;
public:
    Object(const Color& color) : color(color){};
    virtual ~Object() = default; 

    virtual std::optional<Intersection> intersect(const Ray& ray) = 0;
};

class Sphere : public Object
{
private:
    Eigen::Vector3d position;
    double radius;
public:
    using Object::Object;

    Sphere(const Eigen::Vector3d& position, double radius, const Color& color)
        : Object(color), position(position), radius(radius){};

    std::optional<Intersection> intersect(const Ray& ray) override;

    Eigen::Vector3d getNormal(Eigen::Vector3d intersectionPoint);
};

class HalfSpace : public Object
{
private:
    Eigen::Vector3d position;
    Eigen::Vector3d normalVector;
public:
    using Object::Object;
    HalfSpace(const Eigen::Vector3d& position, Eigen::Vector3d& normalVector, const Color& color)
        : Object(color), position(position), normalVector(normalVector) {};

    std::optional<Intersection> intersect(const Ray& ray) override;
};
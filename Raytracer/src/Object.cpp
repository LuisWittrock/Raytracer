#include "Object.hpp"
#include <optional>
#include <iostream>

/*using Eigen::Vector3d;

Vector3d Halfspace::intersect(Ray ray){
    double lambda;
    if(GeradeEbene_Schnittpunkt(normalZuKoordinate(normalVector, position), ray.position, ray.direction, lambda)){
        Vector3d ret;
        ret = ray.position + lambda * ray.direction;
        return ret;
    }
}*/

//This function (Sphere::intersect) works as expected.
std::optional<Intersection> Sphere::intersect(const Ray& ray)
{
    Vector3d S = ray.getPosition();
    Vector3d d = ray.getDirection();

    Vector3d SC = position-S;

    double dSC_dot = d.dot(SC);
    double SC_norm2 = SC.squaredNorm();
    double delta = radius*radius + dSC_dot * dSC_dot - SC_norm2;

    if(delta<0)
    {
        return std::nullopt;
    }

    double sqrtDelta = std::sqrt(delta);
    double t1 = dSC_dot + sqrtDelta;
    double t2 = dSC_dot - sqrtDelta;

    // Find the smallest positive t value
    double t = std::numeric_limits<double>::max();
    if (t1 > 0) t = t1;
    if (t2 > 0 && t2 < t) t = t2;

    if (t == std::numeric_limits<double>::max()) 
    {
        return std::nullopt; // No positive intersection point found
    }

    Vector3d intersectionPoint = ray.pointAt(t);
    Vector3d normalAtIntersection = (intersectionPoint - position).normalized();
    return Intersection{intersectionPoint, normalAtIntersection, color, t};
}

Eigen::Vector3d Sphere::getNormal(Eigen::Vector3d intersectionPoint)
{
    return (intersectionPoint-position).normalized();
}

std::optional<Intersection> HalfSpace::intersect(const Ray& ray)
{
    double denom = normalVector.dot(ray.getDirection());

    // Check if the ray is parallel to the plane
    if (std::abs(denom) < 1e-8) {  // Floating point precision so ~0 is enough
        return std::nullopt;  // Ray is parallel to the plane or included in it
    }

    double t = (position.dot(normalVector) - normalVector.dot(ray.getPosition())) / denom;

    // Check if the intersection is behind the ray's origin
    if (t < 0) {
        return std::nullopt;  // No intersection
    }

    // Calculate the intersection point
    Eigen::Vector3d intersectionPoint = ray.pointAt(t);

    // The normal at the intersection point is the plane's normal
    Eigen::Vector3d normalAtIntersection = normalVector;

    // Return the intersection result
    return Intersection{intersectionPoint, normalAtIntersection, color, t};
}



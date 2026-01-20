#pragma once
#include <eigen3/Eigen/Dense>

using Eigen::Vector4d, Eigen::Vector3d;

class Ray
{
private:
    // Ray has a 4d position vector (x,y,z,1) and a 
    Vector3d position;
    Vector3d direction;
public:
    Ray(const Vector3d& position, Vector3d& direction) : position(position), direction(direction) {direction.normalize();};
    Vector3d pointAt(double t) const;
    Vector3d getPosition() const {return position;}
    Vector3d getDirection() const {return direction;}
};
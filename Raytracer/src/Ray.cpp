#include "Ray.hpp"

Vector3d Ray::pointAt(double t) const
{
    return position + t*direction;
}

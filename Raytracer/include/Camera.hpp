#pragma once
#include "Ray.hpp"
#include "Screen.hpp"

using Eigen::Vector3d;

class Camera
{
private:
    Screen screen;
    Vector3d position;
    double fov;
public:
    Camera() = default;
    Camera(Screen& screen, Vector3d& position) : screen(screen), position(position) {};
    Ray getRay(int x, int y);
};
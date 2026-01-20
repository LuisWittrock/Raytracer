#pragma once
#include <eigen3/Eigen/Dense>

using Eigen::Vector3d, Eigen::Vector2d;

struct Screen
{
    //The screen is always contained in the x,y plane.
    int dpi; //how many pixels per length unit in x and y direction.
    Vector2d dimension;
    Vector3d bottomLeftCorner;
    
    Screen(int dpi, const Vector2d& dimension, const Vector3d& bottomLeftCorner)
        : dpi(dpi), dimension(dimension), bottomLeftCorner(bottomLeftCorner) {};
    Screen() = default;
};
#pragma once
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

using Eigen::Vector3d;

class Light
{
private:
    Eigen::Vector3d position;
    cv::Vec3f intensity;
public:
    Light(Vector3d& position, cv::Vec3f& intensity) : position(position), intensity(intensity) {};

    Eigen::Vector3d getPosition() const
    {
        return position;
    }
    cv::Vec3f getIntensity() const
    {
        return intensity;
    }

};
#pragma once
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

using Eigen::Vector3d;

//You cant overload function using the return type alone so we do it with Structs used as id.
struct EigenTag {};
struct CVTag {};

class Color 
{
private:
    char red;
    char green;
    char blue;

    cv::Vec3f ambient;
    cv::Vec3f diffuse;
    cv::Vec3f specular;
    cv::Vec3f reflected;
    cv::Vec3f refracted;
    int shininess;
public:
    Color(char red, char green, char blue) : red(red), green(green), blue(blue) {};
    Color(cv::Vec3f& ambient, cv::Vec3f& diffuse, cv::Vec3f& specular, cv::Vec3f& reflected, cv::Vec3f& refracted)
        : ambient(ambient), diffuse(diffuse), specular(specular), reflected(reflected), refracted(refracted){red=ambient[0]; green=ambient[1]; blue=ambient[2];};

    cv::Vec3f getAmbient() const
    {
        return ambient;
    }
    cv::Vec3f getDiffuse() const 
    {
        return diffuse;
    }
    cv::Vec3f getSpecular() const
    {
        return specular;
    }
    cv::Vec3b getReflected() const
    {
        return reflected;
    }
    cv::Vec3f getRefracted() const
    {
        return refracted;
    }

    Eigen::Vector3d getColor(EigenTag)
    {
        return Eigen::Vector3d(red,green,blue);
    }

    cv::Vec3b getColor(CVTag)
    {
        return cv::Vec3b(static_cast<uchar>(red), static_cast<uchar>(green), static_cast<uchar>(blue));
    }
};
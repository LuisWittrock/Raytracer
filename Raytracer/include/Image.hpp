#pragma once
#include <vector>
#include "Color.hpp"
#include "Screen.hpp"

using std::vector, Eigen::Vector3d, Eigen::Vector2d;



class Image
{
private:
    Screen screen;
    vector<vector<Color>> pixels;
    cv::Mat picture;
public:
    Image() = default;
    Image(const Screen& screen);       
    void setPixel(int x, int y, cv::Vec3f color);
    void createImage();
    void testImage();
};
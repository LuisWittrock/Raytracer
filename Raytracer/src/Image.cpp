#include "Image.hpp"
#include <iostream>

Image::Image(const Screen& screen)
    : screen(screen),
        picture(static_cast<int>(screen.dimension[1] ),
                static_cast<int>(screen.dimension[0] ), CV_32FC3) {
    // Initialize the picture with black
    picture = cv::Scalar(0, 0, 0);
}

void Image::setPixel(int x, int y, cv::Vec3f color)
{
    picture.at<cv::Vec3f>(y, x) = color;
}

void Image::createImage()
{
    cv::imshow("Image", picture);
    cv::waitKey(0);

    // Convert to 8-bit format before saving
    cv::Mat image_8bit;
    picture.convertTo(image_8bit, CV_8UC3, 255.0); // Scale float to [0, 255]

    // Save the image
    cv::imwrite("colored_image.png", image_8bit);
}

void Image::testImage()
{
    // Define the image size and type
    int width = 512;
    int height = 512;
    cv::Mat image(height, width, CV_32FC3, cv::Scalar(0, 0, 0)); // Create a black image

    // Iterate through each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Define the color (BGR format)
            cv::Vec3b color;
            color[0] = x % 256; // Blue component
            color[1] = y % 256; // Green component
            color[2] = (x + y) % 256; // Red component

            // Set the pixel color
            image.at<cv::Vec3b>(y, x) = color;
        }
    }

    // Display the image
    cv::imshow("Image", image);
    cv::waitKey(0);

    // Save the image
    cv::imwrite("colored_image.png", image);
}

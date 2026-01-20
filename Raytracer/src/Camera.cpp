#include "Camera.hpp"

Ray Camera::getRay(int x, int y) //takes x and y coordinate representing pixels on the screen and return the ray from the camera to this specific pixel.
{
    // Calculate the point on the screen in world coordinates
    Vector3d pixelWorldCoord = screen.bottomLeftCorner
                               + x * Vector3d(1, 0, 0)
                               + y * Vector3d(0, 1, 0);

    // Calculate the direction from the camera position to the pixel world coordinate
    Vector3d direction = (pixelWorldCoord - position).normalized();

    // Return the ray from the camera position in the calculated direction
    return Ray(position, direction);
}

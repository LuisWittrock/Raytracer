#pragma once
#include <fstream>
#include <string>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "json.hpp"

using std::ifstream, std::string;

class Raytracer
{
private:
    Scene scene;
    Camera camera;
    Image image;
    Screen screen;
public:
    Raytracer() = default;
    //Raytracer(const Scene& scene, const Camera& camera, const Image& image, const Screen& screen) : scene(scene), camera(camera), image(image), screen(screen) {};
    
    bool readInputFile(const string& filename);
    void render();
    void test();
};
#include "Raytracer.hpp"

bool Raytracer::readInputFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) return false;

    nlohmann::json j;
    file >> j;

    file.close();

    // Access the data:
    std::cout << "Reading " << filename << "..." << std::endl;
    // Read in screen and camera variables:
    auto scr = j["screen"];
    int dpi = scr["dpi"];
    Eigen::Vector2d dimensions(scr["dimensions"][0], scr["dimensions"][1]);
    Eigen::Vector3d bottomLeftCorner(scr["position"][0], scr["position"][1], scr["position"][2]);
    Eigen::Vector3d observer(scr["observer"][0], scr["observer"][1], scr["observer"][2]);

    this->screen = Screen(dpi, dimensions, bottomLeftCorner);
    this->camera = Camera(this->screen, observer);
    this->image = Image(this->screen);

    // Read in Light Medium Parameters:
    auto medium = j["medium"];
    cv::Vec3f ambient(medium["ambient"][0], medium["ambient"][1], medium["ambient"][2]);
    double index = medium["index"];
    int recursion = medium["recursion"];
    scene.setAmbient(index, recursion, ambient);

    // Read in Light Source Parameters:
    auto sources = j["sources"];
    for (const auto& source : sources) 
    {
        Eigen::Vector3d srcPosition(source["position"][0], source["position"][1], source["position"][2]);
        cv::Vec3f intensity(source["intensity"][0], source["intensity"][1], source["intensity"][2]);

        Light light(srcPosition, intensity);
        scene.addLight(light);
    }

    // Read in objects:
    auto objects = j["objects"];
    int objCount = 0;
    for (const auto& obj : objects)
    {
        std::cout << "Processing object " << objCount << std::endl;

        
        if (obj.contains("halfSpace"))
        {
            auto hs = obj["halfSpace"];
            Eigen::Vector3d position(hs["position"][0], hs["position"][1], hs["position"][2]);
            Eigen::Vector3d normal(hs["normal"][0], hs["normal"][1], hs["normal"][2]);
            normal.normalize();

            auto color = hs["color"];
            cv::Vec3f ambient(color["ambient"][0], color["ambient"][1], color["ambient"][2]);
            cv::Vec3f diffuse(color["diffuse"][0], color["diffuse"][1], color["diffuse"][2]);
            cv::Vec3f specular(color["specular"][0], color["specular"][1], color["specular"][2]);
            cv::Vec3f reflected(color["reflected"][0], color["reflected"][1], color["reflected"][2]);
            cv::Vec3f refracted(color["refracted"][0], color["refracted"][1], color["refracted"][2]);
            double shininess = color["shininess"];

            int index = hs["index"];

            Color tmpColor(ambient, diffuse, specular, reflected, refracted);

            std::cout << "Adding halfSpace..." << std::endl;
            scene.addObject(std::make_unique<HalfSpace>(position, normal, tmpColor)); // Use unique_ptr
        }
        else if (obj.contains("sphere"))
        {
            auto sp = obj["sphere"];
            Eigen::Vector3d position(sp["position"][0], sp["position"][1], sp["position"][2]);
            double radius = sp["radius"];

            auto color = sp["color"];
            cv::Vec3f ambient(color["ambient"][0], color["ambient"][1], color["ambient"][2]);
            cv::Vec3f diffuse(color["diffuse"][0], color["diffuse"][1], color["diffuse"][2]);
            cv::Vec3f specular(color["specular"][0], color["specular"][1], color["specular"][2]);
            cv::Vec3f reflected(color["reflected"][0], color["reflected"][1], color["reflected"][2]);
            cv::Vec3f refracted(color["refracted"][0], color["refracted"][1], color["refracted"][2]);
            double shininess = color["shininess"];

            int index = sp["index"];

            Color tmpColor(ambient, diffuse, specular, reflected, refracted);

            std::cout << "Adding sphere..." << std::endl;
            scene.addObject(std::make_unique<Sphere>(position, radius, tmpColor)); // Use unique_ptr
        }
        else
        {
            std::cout << "Unknown object type." << std::endl;
        }
        objCount++;
    }
    std::cout << "object count: " << objCount << "\n";
    std::cout << "finished reading file\n";
    return true;
}


void Raytracer::render()
{
    std::cout << "start render...\n";
    
    for(int x = 0; x<screen.dimension[0]; x++)
    {
        for(int y = 0; y<screen.dimension[1]; y++)
        {
            Ray ray = camera.getRay(x,y);
            cv::Vec3f color = scene.trace(ray);
            image.setPixel(x, y, color);
        }
    }
    std::cout << "creating image...\n";
    image.createImage();
}

void Raytracer::test()
{
    std::cout << "test\n";
}

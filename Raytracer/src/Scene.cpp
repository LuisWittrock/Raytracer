#include "Scene.hpp"

void Scene::setAmbient(int index, int recursion, cv::Vec3f ambient)
{
    this->ambient = ambient;
    this->index = index;
    this->recursion = recursion;
}

bool Scene::shadowed(const Ray &ray) const
{
    std::optional<Intersection> res;
    for(auto& obj : objects)
    {
        res = obj->intersect(ray);

        if(res != std::nullopt) return true;
    }
    return false;
}

cv::Vec3f Scene::calcDiffuse(const std::optional<Intersection> &intersectionObj, const Light& light) const
{
    Eigen::Vector3d lightDirection = (intersectionObj->point-light.getPosition()).normalized();

    if(shadowed(Ray(intersectionObj->point+intersectionObj->normal*0.0001, lightDirection)))
    {
        return cv::Vec3f(0,0,0);
    }
    
    float scalar = std::max(lightDirection.dot(intersectionObj->normal), 0.0);
    return light.getIntensity().mul(intersectionObj->color.getDiffuse())*scalar;
}

// Das wird noch rekursiv und Phong Shader auf die Farben anwenden.
cv::Vec3f Scene::trace(const Ray &ray) const
{
    // Find first object we intersect using ray and return its color. (lamter we can add shading aswell to the color and recursive intersections.)
    std::optional<Intersection> intersectionObj = std::nullopt;
    std::optional<Intersection> currObj = std::nullopt;

    double distance = DBL_MAX;

    bool foundIntersection = false;

    int objCount = 0;


    //Find closest object
    for(auto& object : objects)
    {
        currObj = object->intersect(ray);

        if(currObj == std::nullopt) continue;
        

        foundIntersection = true;
            
        if(distance > currObj->distance) 
        {
            distance = currObj->distance;
            intersectionObj = currObj;
        }
        objCount++;
    }
    if(!foundIntersection) return cv::Vec3f(0,0,0);

    cv::Vec3f ambientComp = ambient.mul(intersectionObj->color.getAmbient());

    cv::Vec3f diffuseComp(0,0,0);

    for(auto& light : lights)
    {
        diffuseComp += calcDiffuse(intersectionObj, light);
    }
    
    
    cv::Vec3f finalColor = compose(diffuseComp, ambientComp);
    return finalColor;
}

cv::Vec3f Scene::compose(cv::Vec3f E1, cv::Vec3f E2) const
{
    cv::Vec3f a(1,1,1);
    return a-(a-E1).mul(a-E2);
}

#include "Raytracer.hpp"
#include <iostream>


int main() 
{
    Raytracer raytracer;
    if(!raytracer.readInputFile("input.json")) return -1;
    raytracer.render();
}

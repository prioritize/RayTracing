#include <iostream>
#include "vec3.h"

int main(){
    int width = 1920,  height = 1080;
    std::cout << "P3" << std::endl;
    std::cout << width << " " << height << std::endl;
    std::cout << "255" << std::endl;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            float r = float(x)/float(width);
            float g = float(y)/float(height);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
    
}
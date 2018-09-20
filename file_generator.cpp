#include <iostream>
#include <fstream>
#include "ray.h"
// #include "vec3.h"

vec3 color(const Ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    std::cout << "unit_direction.y(): " << unit_direction.y() << std::endl;
    std::cout << "Calculated t: " << t << std::endl;
    vec3 out = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    std::cout << "r: " << out[0] << "g: " << out[1] << "b: " << out[2];
    return out;
    
}
int main(){
    std::fstream write_file;
    write_file.open("test.ppm", std::ios::out | std::ios::trunc);
    // Generate the header information for the PPM file.
    int width = 400,  height = 200;
    write_file << "P3" << std::endl;
    write_file << width << " " << height << std::endl;
    write_file << "255" << std::endl;
    // End header information
    
    // Camera setup information
    vec3 lower_left_corner(-width/2, -height/2, -height/2);
    vec3 horizontal(width/2, 0.0, 0.0);
    vec3 vertical(0.0, width/2, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for(int j = height - 1; j >= 0; j--){
        for(int i = 0; i < width; i++){
            float u = float(i)/float(width);
            float v = float(j)/float(height);
            // float b = 0.2;
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 test = u*horizontal;
            std::cout << "test values: " << test[0] << " " << test[1] << " " << test[2];            
            if(ray.B[2] == 0){
                std::cout << "You're fucked" << std::endl;
            }
            std::cout << ray.B[0] << ray.B[1] << ray.B[2] << std::endl;
            std::cout << "(x: " << i << ", " << "y: "  << j << ")" << std::endl;
            vec3 col = color(ray);
            std::cout << "blue: "<< int(255.99*col[2]) << std::endl; 
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            write_file << ir << " " << ig << " " << ib << "\n";
            // write_file << ib << std::endl;
            // if(ib > 255){
            //     std::cout << "ib greater than 1"<< std::endl;
            //     std::cout << col[2] << std::endl;
            // }
        std::cout << std::endl;
        }
    }
    write_file.close();
    
}
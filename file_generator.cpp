#include <iostream>
#include <fstream>
#include "float.h"
#include "sphere.h"
#include "hitablelist.h"

#ifndef MAXFLOAT
#define MAXFLOAT FLT_MAX
#endif

Vector3 color(const Ray& ray, Hitable *world){
    HitRecord record;    
    if(world->Hit(ray, 0.0, MAXFLOAT, record)){
        return 0.5*Vector3(record.normal.x() + 1, record.normal.y() + 1, record.normal.z() + 1);
    }
    else{
        Vector3 unit_direction = unit_vector(ray.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
    }
}
int main(){
    std::fstream write_file;
    write_file.open("test.ppm", std::ios::out | std::ios::trunc);
    // Generate the header information for the PPM file.
    int width = 200;
    int height = 100;
    write_file << "P3" << std::endl << width << " " << height << " " << std::endl << "255" << std::endl;
    // write_file << width << " " << height << std::endl; 
    // write_file << "255" << std::endl;
    // End header information
    
    // Camera setup information
    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0);
    Hitable *list[2];
    list[0] = new Sphere(Vector3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vector3(0, -100.5, -1), 100);
    Hitable *world = new HitableList(list, 2);

    for(int j = height - 1; j >= 0; j--){
        for(int i = 0; i < width; i++){
            float u = float(i)/float(width);
            float v = float(j)/float(height);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
            Vector3 p = ray.point_at_parameter(2.0);
            Vector3 col = color(ray, world);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            write_file << ir << " " << ig << " " << ib << std::endl;
        }
    }
    write_file.close();
}
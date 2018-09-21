#include <iostream>
#include <fstream>
#include "ray.h"
// #include "vec3.h"
float HitSphere(const vec3& center, float radius, const Ray& ray){
    vec3 oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = 2.0 * dot(oc, ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discriminant))/(2.0*a);
    }
}
vec3 color(const Ray& r){
    float t = HitSphere(vec3(0,0, 1), .5, r);
    if(t > 0.0){
        vec3 normal = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5 * vec3(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    // Generate the background gradient
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    vec3 out = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
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
    vec3 lower_left_corner(-width/2, -height/2, -5);
    vec3 horizontal(width/2, 0.0, 0.0);
    vec3 vertical(0.0, width/2, 0.0);
    vec3 origin(0.0, 0.0, 10);

    for(int j = height - 1; j >= 0; j--){
        for(int i = 0; i < width; i++){
            float u = float(i)/float(width);
            float v = float(j)/float(height);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(ray);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            write_file << ir << " " << ig << " " << ib << std::endl;
        }
    }
    write_file.close();
    
}
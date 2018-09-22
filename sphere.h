#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
class Sphere: public Hitable{
    public:
    Sphere(){}
    Sphere(Vector3 cen, float r) : center(cen), radius(r) {};
    virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const;
    Vector3 center;
    float radius;
};

bool Sphere::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const{
    // Generate the vector from the center of the sphere to the surface of the sphere
    Vector3 oc = ray.origin() - center; 
    // Using the equation A + tB = p(t) and the equation t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0 
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - radius * radius;
    
    float discriminant = b*b - a * c;

    if(discriminant > 0){
        float temp = (-b - sqrt(b*b-a*c)/a);
        if(temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = ray.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(b*b-a*c) / a);
        if(temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = ray.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}
#endif
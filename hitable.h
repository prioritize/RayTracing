#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct HitRecord{
    float t;
    Vector3 p;
    Vector3 normal;
};

class Hitable{
    public:
        virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};
#endif
#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class Camera {
    public: 
        Camera(){
            lower_left_corner = Vector3(-2.0, -1.0, -1.0);
            horizontal = Vector3(4.0, 0.0, 0.0);
            vertical = Vector3(0.0, 2.0, 0.0);
            origin = Vector3(0.0, 0.0, 0.0);
        }
        Ray GetRay(float u, float v) {
            return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
        Vector3 lower_left_corner;
        Vector3 horizontal;
        Vector3 vertical;
        Vector3 origin;
};



#endif
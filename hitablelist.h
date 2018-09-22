#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class  HitableList: public Hitable{
    public:
    HitableList(){}
    HitableList(Hitable **l, int n){
        list = l; 
        list_size = n;
    }
    virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const;
    Hitable **list;
    int list_size;
};
bool HitableList::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list_size; i++){
        if(list[i]->Hit(ray, t_min, closest_so_far, temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif
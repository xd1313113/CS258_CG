#include "Object.h"


Object::~Object()
{
    //dtor
}

Object::Object(const Object& other)
{
    //copy ctor
}



float Object::findIntersection(Ray ray){

}

Sphere::Sphere(Vec3 ct, float r, Vec3 a,Vec3 rf,Vec3 s,Vec3 p, float pc, bool f):center(ct),R(r),Object(a,rf,s, p, pc,f){};


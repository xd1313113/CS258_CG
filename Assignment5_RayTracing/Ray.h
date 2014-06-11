#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

class Ray{
public:

    Vec3 origin, direction;

    Ray():origin(Vec3(0)),direction(Vec3(1,0,0)){}
    Ray(Vec3 o, Vec3 d):origin(o),direction(d.normalize()){}


    ~Ray(){};


};

#endif // _RAY_H_

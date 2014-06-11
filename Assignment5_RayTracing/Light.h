#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3.h"

class Light{
public:
    Vec3 color;
    Vec3 direction;

    Light(){};
    Light(Vec3 c, Vec3 d):color(c),direction(d.normalize()){};
    ~Light(){};
};

#endif // _LIGHT_H_

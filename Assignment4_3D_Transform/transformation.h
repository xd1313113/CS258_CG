#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "Command.h"


class Transformation{
public:
    Transformation();

    ~Transformation();

    void Push();

    void Pop();

    void Translate(float x,float y, float z);

    void Scale(float sx,float sy, float sz);

    void Rotate(float angle, float ax,float ay, float az);

    void Ortho(float l, float r,float b, float t,float n, float f);

    void Perspective(float angle, float a, float n, float f);

    void Lookat(float fx, float fy, float fz, float ax,float ay, float az, float ux, float uy, float uz);

    void Vertex(float x, float y, float z);

    void Reset();

    void Orient(float a, float b, float c, float d,float e, float f, float g, float h, float i);

    void getWH(int & w, int & h);

    int isLittleEndian();

    void writeImageMeta();
};

#endif // _TRANSFORMATION_H_

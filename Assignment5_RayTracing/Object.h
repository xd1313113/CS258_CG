#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include <vector>

class Object;

struct Intersection {          // Records all info at ray-object intersection.
    Object *object; // The object that was hit (set by Intersect).
    float  distance;     // Distance to hit (used & reset by Intersect).
    Vec3    point;        // ray-object intersection point (set by Intersect).
    Vec3    normal;       // Surface normal (set by Intersect).
    //bool    isHit;
    };

typedef std::vector<Intersection> IntersectionList;

class Object
{
public:
    Object();
    virtual ~Object();

    virtual int getDept() = 0;

    virtual Vec3 getAmbient() = 0;

    virtual Vec3 getReflect() = 0;

    virtual Vec3 getSpecular() = 0;

    virtual Vec3 getPhong() = 0;

    virtual float getPC() = 0;

    virtual bool isRef() = 0;

    virtual float getTransparency(){return 0.0;};

    virtual bool getF() = 0;

    virtual bool findIntersections(Ray ray, IntersectionList & list) = 0;
};





class Sphere: public Object
{
public:
    Vec3 center;
    float R;

    Vec3 ambient;
    Vec3 reflect;
    Vec3 specular;
    Vec3 phong;
    float phcoff;
    bool F;

    float transparency;

    Sphere();
    Sphere(Vec3 ct, float r);
    Sphere(Vec3 ct, float r, Vec3 a,Vec3 rf,Vec3 s,Vec3 p, float pc, bool f,float trans);
    ~Sphere();

    virtual bool findIntersections(Ray ray, IntersectionList & list);


    virtual int getDept(){return 0;}

    virtual Vec3 getAmbient(){return ambient;}

    virtual Vec3 getReflect(){return reflect;}

    virtual Vec3 getSpecular(){ return specular;}

    virtual Vec3 getPhong(){return phong;}

    virtual float getPC( ){return phcoff;}

    virtual bool getF(){return F;};

    virtual bool isRef(){return !(specular.x == 0 && specular.y == 0 && specular.z == 0);}

    virtual float getTransparency(){   return transparency; }
};


class CTriangle: public Object
{
public:
    Vec3 u,v,w;

    Vec3 normal;

    Vec3 ambient;
    Vec3 reflect;
    Vec3 specular;
    Vec3 phong;
    float phcoff;
    bool F;

    CTriangle();
    CTriangle(Vec3 u, Vec3 v, Vec3 w);
    CTriangle(Vec3 u, Vec3 v, Vec3 w,Vec3 a,Vec3 rf,Vec3 s,Vec3 p, float pc, bool f);
    ~CTriangle();

    virtual bool findIntersections(Ray ray, IntersectionList & list);

    virtual int getDept(){return 0;}

    virtual Vec3 getAmbient(){return ambient;}

    virtual Vec3 getReflect(){return reflect;}

    virtual Vec3 getSpecular(){ return specular;}

    virtual Vec3 getPhong(){return phong;}

    virtual float getPC( ){return phcoff;}

    virtual bool getF(){return F;};

    virtual bool isRef(){return !(specular.x == 0 && specular.y == 0 && specular.z == 0);};

};

class CBox: public Object
{
public:
    Vec3 llb;
    Vec3 urt;

    Vec3 ambient;
    Vec3 reflect;
    Vec3 specular;
    Vec3 phong;
    float phcoff;
    bool F;

    float transparency;

    CBox();
    CBox(Vec3 u,Vec3 v);
    CBox(Vec3 u,Vec3 v, Vec3 a,Vec3 rf,Vec3 s,Vec3 p, float pc, bool f,float trans);
    ~CBox();

    virtual bool findIntersections(Ray ray, IntersectionList & list);

    bool equal(float x, float y);

    virtual int getDept(){return 0;}

    virtual Vec3 getAmbient(){return ambient;}

    virtual Vec3 getReflect(){return reflect;}

    virtual Vec3 getSpecular(){ return specular;}

    virtual Vec3 getPhong(){return phong;}

    virtual float getPC( ){return phcoff;}

    virtual bool getF(){return F;};

    virtual bool isRef(){return !(specular.x == 0 && specular.y == 0 && specular.z == 0);};

    virtual float getTransparency(){return transparency; };

};

class Plane: public Object
{
public:
    Vec3 norm;
    Vec3 passing;

    Vec3 ambient;
    Vec3 reflect;
    Vec3 specular;
    Vec3 phong;
    float phcoff;
    bool F;

    Plane();
    Plane(Vec3 n, Vec3 pass);
    Plane(Vec3 n, Vec3 pass, Vec3 a,Vec3 rf,Vec3 s,Vec3 p, float pc, bool f);
    ~Plane();

    virtual bool findIntersections(Ray ray, IntersectionList & list);

    virtual int getDept(){return 0;}

    virtual Vec3 getAmbient(){return ambient;}

    virtual Vec3 getReflect(){return reflect;}

    virtual Vec3 getSpecular(){ return specular;}

    virtual Vec3 getPhong(){return phong;}

    virtual float getPC( ){return phcoff;}

    virtual bool getF(){return F;};

    virtual bool isRef(){return !(specular.x == 0 && specular.y == 0 && specular.z == 0);}

};

#endif // _OBJECT_H

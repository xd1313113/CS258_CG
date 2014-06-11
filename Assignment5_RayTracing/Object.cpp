#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{

}

Object::~Object()
{

}

bool Object::findIntersections(Ray ray, IntersectionList & list)
{
}

Sphere::Sphere()
{

}

Sphere::Sphere(Vec3 ct, float r):center(ct),R(r)
{

}

Sphere::Sphere(Vec3 ct, float r, Vec3 a, Vec3 rf, Vec3 s, Vec3 p, float pc, bool f, float trans):center(ct),R(r),
    ambient(a),reflect(rf),specular(s),phong(p),phcoff(pc),F(f), transparency(trans)
{

}

Sphere::~Sphere()
{

}

bool Sphere::findIntersections(Ray ray, IntersectionList & list)
{
    const Vec3 displacement = ray.origin - center;
    const float a = ray.direction.magnitude();
    const float b = 2 * ray.direction.dot(displacement);
    const float c = displacement.magnitude() - R * R;

    const float radicand = b*b - 4.0*a*c;

    if (radicand < 0)
    {
        return false;
    }
    else
    {
        const float root = sqrt(radicand);
        const float denom = 2.0 * a;
         float r1 = (-b - root) / denom;
        float r2 = (-b + root) / denom;

//        Intersection inter;
//        if(r1 < -1e-4 ){
//                r1 = r2;
//        }
//        if(r2 < -1e-4){
//            return false;
//        }else{
//                inter.distance = r2;
//                inter.object = this;
//                inter.point = ray.origin + ray.direction * r2;
//                inter.normal = (inter.point - center).normalize();
//                list.push_back(inter);
//                return true;
//        }


        if(r2 > 1e-4 && r1 > 1e-4)
        {
            if( root == 0)
            {
                Intersection inter;
                inter.distance = r1;
                inter.object = this;
                inter.point = ray.origin + ray.direction * r1;
                inter.normal = (inter.point - center).normalize();
                list.push_back(inter);
            }
            else
            {
                Intersection inter1;
                inter1.distance = r1;
                inter1.object = this;
                inter1.point = ray.origin + ray.direction * r1;
                inter1.normal = (inter1.point - center).normalize();
                list.push_back(inter1);
                Intersection inter2;
                inter2.distance = r2;
                inter2.object = this;
                inter2.point = ray.origin + ray.direction * r2;
                inter2.normal = (inter2.point - center).normalize();
                list.push_back(inter2);
            }

            return true;
        }
        else
        {
            return false;
        }
    }
}

CBox::CBox()
{

}

CBox::CBox(Vec3 u, Vec3 v):llb(u),urt(v)
{

}

CBox::CBox(Vec3 u, Vec3 v, Vec3 a, Vec3 rf, Vec3 s, Vec3 p, float pc, bool f,float trans):llb(u),urt(v),
    ambient(a),reflect(rf),specular(s),phong(p),phcoff(pc),F(f),transparency(trans)
{

}

CBox::~CBox()
{

}

bool CBox::findIntersections(Ray ray, IntersectionList & list)
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    tmin = (llb.x - ray.origin.x) / ray.direction.x;
    tmax = (urt.x - ray.origin.x) / ray.direction.x;

    if(tmin > tmax)
    {
        swap(tmin, tmax);
    }

    tymin = (llb.y - ray.origin.y) / ray.direction.y;
    tymax = (urt.y - ray.origin.y) / ray.direction.y;

    if(tymin > tymax)
    {
        swap(tymin, tymax);
    }
    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (llb.z - ray.origin.z) / ray.direction.z;
    tzmax = (urt.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) swap(tzmin, tzmax);
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    float ttmax = 1e30;
    float ttmin = 0.001;
    if ((tmin > ttmax) || (tmax < ttmin))
        return false;
    if (ttmin < tmin) ttmin = tmin;
    if (ttmax > tmax) ttmax = tmax;

    Intersection inter;
    inter.distance = ttmin;
    inter.object = this;
    inter.point = ray.origin + ray.direction * ttmin;
//
    if(equal(inter.point.y, urt.y)) inter.normal = Vec3(0,1,0);
    else if(equal(inter.point.y, llb.y)) inter.normal = Vec3(0,-1,0);
    else if(equal(inter.point.x, urt.x)) inter.normal = Vec3(1,0,0);
    else if(equal(inter.point.x, llb.x)) inter.normal = Vec3(-1,0,0);
    else if(equal(inter.point.z, urt.z)) inter.normal = Vec3(0,0,1);
    else if(equal(inter.point.z, llb.z)) inter.normal = Vec3(0,0,-1);

    list.push_back(inter);
}

bool CBox::equal(float x, float y)
{

    if(abs(x - y) < 0.0001)
        return true;
    else
        return false;

}


CTriangle::CTriangle()
{

}

CTriangle::CTriangle(Vec3 u, Vec3 v, Vec3 w):u(u),v(v),w(w)
{

}

CTriangle::CTriangle(Vec3 u, Vec3 v, Vec3 w, Vec3 a, Vec3 rf, Vec3 s, Vec3 p, float pc, bool f):u(u),v(v),w(w),
    ambient(a),reflect(rf),specular(s),phong(p),phcoff(pc),F(f)
{
    Vec3 edge1 = v - u;
    Vec3 edge2 = w - u;
    normal = edge1.cross(edge2).normalize();
}

CTriangle::~CTriangle()
{

}

bool CTriangle::findIntersections(Ray ray, IntersectionList & list)
{
    float a = u.x - v.x; //a
    float b = u.y - v.y; //b
    float c = u.z - v.z; //c

    float d = u.x - w.x; //d
    float e = u.y - w.y; //e
    float f = u.z - w.z; //f

    float g = ray.direction.x; //g
    float h = ray.direction.y; //h
    float i = ray.direction.z; //i

    float j = u.x - ray.origin.x; //j
    float k = u.y - ray.origin.y; //k
    float l = u.z - ray.origin.z; //l

    //float numer_t = a * (e * ii - ff*h) - b * (d * ii - ff * g) + cc * (d * h - e * g);
    //float denom_t = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    float denom_t = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
    float numer_t = f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c);
    //cout<<"denom"<<denom_t<<endl;
    float t = - numer_t / denom_t;
    //cout<<t<<endl;
    if(t < 1e-3 || t > 1e20)
    {
        return false;
    }
    //cout <<"t"<< t<<endl;

    //float numer_a = cc * (e * -i - (-f)*h) - b * (ff * -i - (-f) * ii) + -c * (ff * h - e * ii);
    float numer_a = i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c);
    float triangle_a = numer_a / denom_t;

    if (triangle_a < 0 || triangle_a > 1)
    {
        return false;
    }
    //cout <<"a"<< triangle_a<<endl;

    //float numer_b = a * (ff * -i - (-f) * ii) - cc * (d * -i - (-f) * g) + (-c) * (d * ii - (-f) * ii);
    float numer_b  = j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g);
    float triangle_b = numer_b / denom_t;

    if (triangle_b < 0 || triangle_b > (1 - triangle_a))
    {
        return false;
    }
    //cout <<"b"<< triangle_b<<endl;

    Intersection inter;
    inter.distance = t;
    inter.object = this;



    if(normal.dot(ray.direction) < 0)
        inter.normal = normal;
    else
        inter.normal = normal.negate();
    inter.point = ray.origin + ray.direction * t;
    list.push_back(inter);

}

Plane::Plane()
{

}

Plane::Plane(Vec3 n, Vec3 pass):norm(n.normalize()),passing(pass)
{

}

Plane::Plane(Vec3 n, Vec3 pass, Vec3 a, Vec3 rf, Vec3 s, Vec3 p, float pc, bool f):norm(n.normalize()),passing(pass),
    ambient(a),reflect(rf),specular(s),phong(p),phcoff(pc),F(f)
{

}

Plane::~Plane()
{

}

bool Plane::findIntersections(Ray ray, IntersectionList & list)
{
    Intersection inter;
    //(p0−l0)⋅n/(l⋅n)
    float denom = ray.direction.dot(norm);
    if(denom < 0)
    {
        Vec3 n = passing - ray.origin;
        float d = n.dot(norm) / denom;
        //if(d > 0){
        inter.distance = d;
        inter.object = this;
        inter.point = ray.origin + ray.direction * d;
        inter.normal = norm;
        list.push_back(inter);
        //}
    }
    return false;
}

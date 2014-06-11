#ifndef _VECfloatOR3_H_
#define _VECfloatOR3_H_

#include <cmath>
#include <iostream>

class Vec3
{
public:
    float x, y, z;

    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3(float xx) : x(xx), y(xx), z(xx) {}

    Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

    void setXYZ(float xx,float yy,float zz){
        x = xx;
        y = yy;
        z = zz;
    }
    Vec3 negate()
    {
        return Vec3(-x,-y,-z);
    }


    Vec3 normalize()
    {
        float nor2 = magnitude();
        if (nor2 > 0)
        {
            float invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return Vec3(x,y,z);
    }// nofloatice floathe return floatype of sqrt



    Vec3 operator * (const float &f) const
    {
        return Vec3(x * f, y * f, z * f);
    }
    Vec3 operator * (const Vec3 &v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }
    float dot(const Vec3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    Vec3 cross(const Vec3 &v) const{
        return Vec3(y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x);
    }
    Vec3 operator - (const Vec3 &v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    Vec3 operator + (const Vec3 &v) const
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3& operator += (const Vec3 &v)
    {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    Vec3& operator *= (const Vec3 &v)
    {
        x *= v.x, y *= v.y, z *= v.z;
        return *this;
    }
    Vec3 operator - () const
    {
        return Vec3(-x, -y, -z);
    }
    float magnitude() const
    {
        return x * x + y * y + z * z;
    }
    float length() const
    {
        return sqrt(magnitude());
    }
    friend std::ostream & operator << (std::ostream &os, const Vec3 &v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

#endif // _VECfloatOR3_H_

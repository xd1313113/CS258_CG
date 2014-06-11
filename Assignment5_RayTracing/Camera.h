#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"
#include "Ray.h"
#include <iostream>

using namespace std;


class Camera{
public:

    Vec3 eye;
    Vec3 gaze;
    Vec3 up;
    Vec3 right;
    float s;
    float l, r;
    float t, b;

    int type; // Perpective 0, Orhtocamera 1;

    Vec3 backgound;
    bool whIsSet;
    bool bgIsSet;

    float widthpp;
    float heightpp;

    int width;
    int height;

    Camera(){}
    Camera(Vec3 e, Vec3 g, Vec3 u, float s, float au, float av, float bu, float bv):
                        eye(e),gaze(g),up(u),s(s),l(au),r(av),t(bu),b(bv){}

    ~Camera(){}

    void setCamera(Vec3 e, Vec3 g, Vec3 u, float _s, float au, float av, float bu, float bv,int w, int h){
        eye = e;
        gaze = g.normalize();
        up = u.normalize();
        right = gaze.cross(up);
        right = right.normalize();

        //cout<<eye<<gaze<<up<<right<<endl;
        s = _s;
        l = au;
        b = av;
        r = bu;
        t = bv;

        width = w;
        height =h;

        widthpp = (r - l) / width;
        heightpp = (t - b) / height;

        //cout<<"wid"<<widthpp<<" hpp"<<heightpp<<endl;
    }

    Ray generateRay(int h, int w){
        if(type == 0){
            float u = l + widthpp * (w + 0.5);
            float v = b + heightpp * (h + 0.5);
            Vec3 direction = gaze * s + right * u  + up * v;
            return Ray(eye,direction);
        }else{
            return Ray(Vec3(h,w,0),Vec3(0,0,-1));
        }
    }
};

#endif

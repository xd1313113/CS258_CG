#ifndef _SCENE_H_
#define _SCENE_H_
#include "Object.h"
#include "Light.h"
#include <vector>
#include "Camera.h"

using namespace std;

class RayTracer{
public:
    void trace();
    void setScreen(float x,float y);
    void setOrthocamera();
    void setCamera(float ex, float ey, float ez,
                    float gx, float gy, float gz,
                    float ux, float uy, float uz,float s,
                    float au, float av, float bu, float bv);
    void setBackground(float r, float g, float b);
    void addSphere(float R,float cx, float cy, float cz,
                    float ar, float ag, float ab,
                    float rr, float rg, float rb,
                    float sr = 0, float sg = 0, float sb = 0,
                    float pr = 0, float pg = 0, float pb = 0,
                    float pc = 0, bool F = false, float trans = 0);
    void addTriangle(float ux, float uy, float uz,
                     float vx, float vy, float vz,
                     float wx, float wy, float wz,
                     float ar, float ag, float ab,
                     float rr, float rg, float rb,
                     float sr = 0, float sg = 0, float sb = 0,
                     float pr = 0, float pg = 0, float pb = 0,
                     float pc = 0, bool F = false);
    void addBox(float ux, float uy, float uz,
                     float vx, float vy, float vz,
                     float ar, float ag, float ab,
                     float rr, float rg, float rb,
                     float sr = 0, float sg = 0, float sb = 0,
                     float pr = 0, float pg = 0, float pb = 0,
                     float pc = 0, bool F = false, float trans = 0);
    void addIlight(float lr, float lg, float lb,
                    float dx, float dy, float dz);
    void addPlane(   float nx, float ny, float nz,
                     float px, float py, float pz,
                     float ar, float ag, float ab,
                     float rr, float rg, float rb,
                     float sr = 0, float sg = 0, float sb = 0,
                     float pr = 0, float pg = 0, float pb = 0,
                     float pc = 0, bool F = false);

    Intersection pickClosetIntersection(IntersectionList & list);

    Vec3 rayTraceRecursive(Ray & ray, int depth);

    bool intersectLights(Light * light, Vec3 pos);

    float clampColor(float c);

    float mix(float a, float b, float mix);

    void clear();

private:
    int height;
    int width;

    Camera camera;
    vector<Object*> objects;
    vector<Light*> iLights;
    Vec3 background;

};

#endif // _SCENE_H_

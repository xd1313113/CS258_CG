#include "RayTracer.h"
#include <GL/glut.h>
#include <iostream>
#include "AppContext.h"
#include "tiff.h"
#include <limits>
#include <math.h>
#include <time.h>
#include <iomanip>



extern Context *ctx;
extern GLubyte checkImage[1024][1024][3];
extern void makeCheckImage(void);
extern void display(void);
extern Tiff *img;
extern int width_W, height_W;

void RayTracer::setScreen(float x, float y)
{
    glutReshapeWindow(x, y);
    width_W = width = int(x);
    height_W = height = int(y);

    cout<<"Set the screen to "<<width<<" "<<height<<endl;
    camera.whIsSet = true;

}


void RayTracer::setOrthocamera()
{
    cout<<"Set the camera to Orthocamera."<<endl;
    camera.type = 1;
}

void RayTracer::setCamera(float ex, float ey, float ez, float gx, float gy, float gz, float ux, float uy, float uz, float s, float au, float av, float bu, float bv)
{
    camera.setCamera(Vec3(ex,ey,ez),Vec3(gx,gy,gz),Vec3(ux,uy,uz),s,au,av,bu,bv,width,height);
    camera.type = 0;
    cout<<"Set the camera"<<endl;
}

void RayTracer::setBackground(float r, float g, float b)
{
    background.setXYZ(r,g,b);
    cout<<"Set the background"<<endl;
}

void RayTracer::addSphere(float R, float cx, float cy, float cz, float ar, float ag, float ab, float rr, float rg, float rb, float sr, float sg, float sb, float pr, float pg, float pb, float pc, bool F, float trans)
{
    Sphere* sphere  = new Sphere(Vec3(cx,cy,cz), R, Vec3(ar,ag,ab), Vec3(rr,rg,rb), Vec3(sr,sg,sb), Vec3(pr,pg,pb),pc,F,trans);
    objects.push_back(sphere);
    cout<<"Add a Sphere"<<endl;
}

void RayTracer::addTriangle(float ux, float uy, float uz, float vx, float vy, float vz, float wx, float wy, float wz, float ar, float ag, float ab, float rr, float rg, float rb, float sr, float sg, float sb, float pr, float pg, float pb, float pc, bool F)
{
    CTriangle* triangle  = new CTriangle(Vec3(ux,uy,uz), Vec3(vx,vy,vz),Vec3(wx,wy,wz), Vec3(ar,ag,ab), Vec3(rr,rg,rb), Vec3(sr,sg,sb), Vec3(pr,pg,pb),pc,F);
    objects.push_back(triangle);
    cout<<"Add a Triangle"<<endl;
}

void RayTracer::addBox(float ux, float uy, float uz, float vx, float vy, float vz, float ar, float ag, float ab, float rr, float rg, float rb, float sr, float sg, float sb, float pr, float pg, float pb, float pc, bool F, float trans)
{
    CBox* box  = new CBox(Vec3(ux,uy,uz), Vec3(vx,vy,vz), Vec3(ar,ag,ab), Vec3(rr,rg,rb), Vec3(sr,sg,sb), Vec3(pr,pg,pb),pc,F,trans);
    objects.push_back(box);
    cout<<"Add a Box"<<endl;
}

void RayTracer::addIlight(float lr, float lg, float lb, float dx, float dy, float dz)
{
    Light *ilight = new Light(Vec3(lr,lg,lb), Vec3(dx,dy,dz));
    iLights.push_back(ilight);
    cout<<"Add Light"<<endl;
}

void RayTracer::clear()
{

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; ++j)
        {
//            checkImage[img->mImageLength - i][j][0] = img->mImageData[i][j][0] = 0.0;
//            checkImage[img->mImageLength - i][j][1] = img->mImageData[i][j][1] = 0.0;
//            checkImage[img->mImageLength - i][j][2] = img->mImageData[i][j][2] = 0.0;
            checkImage[height - i][j][0] = 0.0;
            checkImage[height - i][j][1] = 0.0;
            checkImage[height - i][j][2] = 0.0;
        }
    }
    objects.clear();
    iLights.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0,0);
    glFlush();

}

void RayTracer::addPlane(float nx, float ny, float nz, float px, float py, float pz, float ar, float ag, float ab, float rr, float rg, float rb, float sr, float sg, float sb, float pr, float pg, float pb, float pc, bool F)
{
    Plane * plane = new Plane(Vec3(nx,ny,nz),Vec3(px,py,pz), Vec3(ar,ag,ab), Vec3(rr,rg,rb), Vec3(sr,sg,sb), Vec3(pr,pg,pb),pc,F);
    objects.push_back(plane);
    cout<<"Add a Plane"<<endl;
}

Intersection RayTracer::pickClosetIntersection(IntersectionList& list)
{
    float min = std::numeric_limits<float>::infinity();

    Intersection inter;
    for(int i = 0; i < list.size(); i++)
    {
        //cout<<list[i].distance<<endl;
        //cout<<"min"<<min<<endl;
        if( list[i].distance < min)
        {
            min = list[i].distance;
            inter = list[i];
        }
    }
    return inter;

}



void RayTracer::trace()
{

    cout<<"Rendering the scene"<<endl;
    if(!camera.whIsSet)
    {
        cout<<"Screen Dimension is not set";
        return;
    }

    clock_t start, end;

    start = clock();


    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            Vec3 color(0);
            Ray ray(camera.generateRay(height - i, j));
            //cout<<i<<","<<j<<endl;
            color = rayTraceRecursive(ray, 4);
            if(color.x - 0 > 0.00001)
            {
                //cout<<i<<","<<j<<endl;
                //cout<<color<<endl;
            }
//                checkImage[img->mImageLength - i][j][0] = img->mImageData[i][j][0] = 255 * clampColor(color.x);
//                checkImage[img->mImageLength - i][j][1] = img->mImageData[i][j][1] = 255 * clampColor(color.y);
//                checkImage[img->mImageLength - i][j][2] = img->mImageData[i][j][2] = 255 * clampColor(color.z);

            checkImage[height - i][j][0] = GLubyte(255 * clampColor(color.x));
            checkImage[height - i][j][1] = GLubyte(255 * clampColor(color.y));
            checkImage[height - i][j][2] = GLubyte(255 * clampColor(color.z));

        }
    }
    end = clock();

    cout<<"The process takes "<<setprecision(5)<< (float)(end -start)/CLOCKS_PER_SEC<<"s"<<endl;
    display();
}

Vec3 RayTracer::rayTraceRecursive(Ray& ray, int depth)
{

    IntersectionList intersections;

    Vec3 color;

    for(int i =0; i < objects.size(); i++)
    {
        //cout<<intersections.size()<<endl;
        objects[i]->findIntersections(ray, intersections);

        //cout<<intersections.size()<<endl;
    }

    Intersection closet;

    bool hasIntersection = false;
    if (intersections.size() > 0)
    {
        closet = pickClosetIntersection(intersections);
        hasIntersection = true;
        //cout<<"closet"<<closet.distance<<endl;
    }

    if(hasIntersection)
    {
        color = closet.object->getAmbient() * closet.object->getReflect();


        for(int i = 0; i < iLights.size(); i++)
        {
            if(!intersectLights(iLights[i],closet.point))
            {
                Vec3 lcnld = iLights[i]->color * closet.normal.dot(iLights[i]->direction.negate());
                Vec3 rdld = ray.direction.negate() + iLights[i]->direction.negate();
                rdld = rdld.normalize();

                color = color + lcnld * closet.object->getReflect() +
                        iLights[i]->color * closet.object->getPhong() * pow(rdld.dot(closet.normal), closet.object->getPC());

            }
        }

        bool inside = false;
        if (ray.direction.dot(closet.normal) > 0)
            closet.normal = closet.normal.negate(), inside = true;
        if((closet.object->getTransparency() > 1e-4||closet.object->isRef())&&depth > 0)
        {
            float facingratio = -ray.direction.dot(closet.normal);
            float fresneleffect = mix(pow(1 - facingratio, 5), 1, 0.5);


            Ray reflray(closet.point, ray.direction + closet.normal * ray.direction.dot(closet.normal) * -2);
            Vec3 reflection = closet.object->getSpecular() * rayTraceRecursive(reflray, depth - 1);

            Vec3 refraction(0.0);
            if(closet.object->getTransparency() > 1e-4)
            {
                float ior = 1.1, eta = (inside) ? ior : 1 / ior;
                float cosi = -closet.normal.dot(ray.direction);
                float k = 1 - eta * eta * (1 - cosi * cosi);
                Ray refractionray(closet.point, ray.direction * eta + closet.normal * (eta *  cosi - sqrt(k)));
                refraction = rayTraceRecursive(refractionray, depth -1);
            }

            if(closet.object->getF())
            {
                reflection = reflection * fresneleffect;
            }



            color = color + reflection + refraction * (1 - fresneleffect) * closet.object->getTransparency() * closet.object->getSpecular();
        }


        return color;
    }
    else if (depth == 4)
    {

        return background;
    }
    else
    {
        return Vec3(0);

    }
}


bool RayTracer::intersectLights(Light* light, Vec3 pos)
{
    Ray ray(pos, light->direction.negate());
    IntersectionList intersections;

    for(int i =0; i < objects.size(); i++)
    {
        objects[i]->findIntersections(ray, intersections);
    }

    if( intersections.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


float RayTracer::clampColor(float c)
{
    if(c > 1.0) return 1.0;
    else if(c < 0.0) return 0.0;
    else return c;
}

float RayTracer::mix(float a, float b, float mix)
{
    return b * mix + a * (1.0 - mix);
}





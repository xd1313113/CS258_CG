#include "transformation.h"
#include "AppContext.h"
#include <iostream>
#include "3D.h"
#include "tiff.h"

extern Context *ctx;
extern GLubyte checkImage[1024][1024][3];
extern void makeCheckImage(void);
using namespace std;


Transformation::Transformation()
{
    top = 0;
    matrix_unit * p = new matrix_unit;
    Copy_mat(&I,p);
    stack[top] = p;
    //printMatrix44(stack[top]);
}

Transformation::~Transformation()
{
    for(int i = top; i >= 0; i--)
        delete stack[i];
}

void Transformation::Push()
{
    if(top == 49)
    {
        printf("Over exceed the size of the stack, nothing will be done!\n");
        return;
    }
    matrix_unit * p = new matrix_unit;
    //printMatrix44(stack[top]);
    Copy_mat(stack[top], p);
    stack[++top] = p;
    //printMatrix44(stack[top]);
    //cout<<"The current stack has been pushed one level down with copy of previous top on top"<<endl;
}

void Transformation::Pop()
{
    if(top == 0)
    {
        cout<<"Reach stack bottom with Identify Matrix."<<endl;
        Copy_mat(&I, stack[top]);
    }
    else
    {
        delete stack[top--];
    }
}

void Transformation::Translate(float x, float y, float z)
{
    matrix_unit MatrixT =
    {
        {   {1., 0., 0., x},
            {0., 1., 0., y},
            {0., 0., 1., z},
            {0., 0., 0., 1.}
        },
    };
    matrix_unit temp;
    //printMatrix44(stack[top]);
    Mult_mat(stack[top], &MatrixT, &temp);
    Copy_mat(&temp, stack[top]);

}

void Transformation::Scale(float sx, float sy, float sz)
{
    matrix_unit MatrixT =
    {
        {   {sx, 0., 0., 0.},
            {0., sy, 0., 0.},
            {0., 0., sz, 0.},
            {0., 0., 0., 1.}
        },
    };
    matrix_unit temp;
    //printMatrix44(stack[top]);
    Mult_mat(stack[top], &MatrixT, &temp);
    Copy_mat(&temp, stack[top]);

}

void Transformation::Rotate(float angle, float ax, float ay, float az)
{

    float theta = angle * 3.14159 / 180.0;
    float c = cos(theta);
    float s = sin(theta);
    matrix_unit temp;
    Vector unit_a;
    Unitvec(ax, ay, az, &unit_a);

    float x = unit_a.i;
    float y = unit_a.j;
    float z = unit_a.k;

    matrix_unit MatrixT =
    {
        {   {x * x *(1 - c) + c,     x * y * (1 - c) - z * s, x * z *(1 - c) + y * s, 0.},
            {x * y *(1 - c) + z * s, y * y * (1 - c) + c,     y * z *(1 - c) - x * s, 0.},
            {x * z *(1 - c) - y * s, y * z * (1 - c) + x * s, z * z *(1 - c) + c, 0.},
            {0., 0., 0., 1.}
        },
    };
    Mult_mat(stack[top], &MatrixT, &temp);
    Copy_mat(&temp, stack[top]);
    //printMatrix44(stack[top]);

}

void Transformation::Ortho(float l, float r, float b, float t, float n, float f)
{
    //writeImageMeta();
    getWH(width_W,height_W);

    matrix_unit MatrixT
    {
        {   {2.0f /(r - l) , 0.f, 0.f, -1.0f * (r + l )/(r - l)},
            {0., 2.f /(t - b), 0.,  -1.0f * (t + b )/(t - b)},
            {0., 0., -2.f /(f - n), -1.0f * (f + n)/(f - n)},
            {0., 0., 0., 1.}
        },
    };
    matrix_unit MatrixV
    {
        {   {width_W/ 2.f, 0., 0., (width_W - 1) / 2.f},
            {0., height_W/ 2.f, 0., (height_W - 1) / 2.f},
            {0., 0., 1., 0.},
            {0., 0., 0., 1.}
        },
    };

    perspflag = 0;
    Near = n, Far = f;

    matrix_unit temp;
    Mult_mat(&MatrixV, &MatrixT, &temp);
    Copy_mat(&temp, &orth);
    //printMatrix44(&orth);
}


void Transformation::Perspective(float angle, float a, float n, float f)
{
    //writeImageMeta();
    float fov = angle * 3.14159 / 180.0;
    float c = 1. / tan(fov / 2.);
    perspflag = 1;
    Near = -n;
    Far = -f;

    getWH(width_W,height_W);

    matrix_unit MatrixT
    {
        {   {c / a, 0., 0., 0.},
            {0., c, 0., 0.},
            {0., 0., -1.0f * (f + n)/(n - f), -2.0f*f * n /(f - n)},
            {0., 0., 1., 0.}
        },
    };
    matrix_unit MatrixV
    {
        {   {width_W/ 2.0f, 0., 0., (width_W - 1) / 2.0f },
            {0., height_W/ 2.0f, 0., (height_W - 1) / 2.0f },
            {0., 0., 0., 0.},
            {0., 0., 0., 1.}
        },
    };
    matrix_unit temp;
    Mult_mat(&MatrixV, &MatrixT, &temp);
    Copy_mat(&temp, &perspect);
    //printMatrix44(&perspect);
}

void Transformation::Lookat(float fx, float fy, float fz, float ax, float ay, float az, float ux, float uy, float uz)
{
    gtLookAt(fx, fy, fz, ax, ay, az, ux, uy, uz);
}

void Transformation::Vertex(float x, float y, float z)
{
    gtVertex3f(x, y, z);
}

void Transformation::Reset()
{
    for(int i = top; i > 0; i--)
        delete stack[i];
    top = 0;
    Copy_mat(&I, stack[top]);
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0,0);
    glFlush();

    makeCheckImage();
}


void Transformation::Orient(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    matrix_unit MatrixT =
    {
        {   {a, b, c, 0.},
            {d, e, f, 0.},
            {g, h, i, 0.},
            {0., 0., 0., 1.}
        },
    };
    matrix_unit temp;
    Mult_mat(stack[top], &MatrixT, &temp);
    Copy_mat(&temp, stack[top]);

}


void Transformation::getWH(int& w, int& h)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    width_W = abs(viewport[2]-viewport[0]);
    height_W = abs(viewport[3]-viewport[1]);

    //printMatrix44(stack[0]);
    cout<<width_W<<","<<height_W<<endl;

}

int Transformation::isLittleEndian()
{
    short int one = 1;
    char *byte = (char *) &one;
    return(byte[0] ? TIFF_LITTLE_ENDIAN : TIFF_BIG_ENDIAN);
}
void Transformation::writeImageMeta()
{
//    for(int i = 0; i < 1024; i++)
//    {
//        for(int j = 0; j < 1024; j++)
//        {
//            img->mImageData[i][j][0] = img->mImageData[i][j][1] = img->mImageData[i][j][2] = 0;
//        }
//    }
//
//    if(isLittleEndian() == 1)
//    {
//        img->header.tiff_endian = 18761;
//    }
//    else
//    {
//        img->header.tiff_endian = 19789;
//    }
//
//
//    img->header.tiff_magic = 42;
//
//    img->mImageWidth = width_W;
//    img->mImageLength = height_W;
//
//    img->mPhotoMetric = 1;
//    img->mCompressed = 1;
//    unsigned int resolution[2];
//    resolution[0] = 72;
//    resolution[1] = 1;
//
//    img->mXResolution = (unsigned long long )&resolution;
//    img->mYResolution = (unsigned long long )&resolution;
//    img->mResolutionUnit = 2;
//    img->mEndian_Convert = false;
//    img->mBitsPerSample = 8;
//    img->mSamplePerPixel = 1;

}


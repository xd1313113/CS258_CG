#ifndef _IMAGERESIZER_H_
#define _IMAGERESIZER_H_

#include <math.h>
#include "Command.h"
#include <string.h>


#define PI  3.14159265359
#define E   2.7182818284
using namespace std;

class Filter
{
public:

    virtual float compute(float x, float r = 2) = 0;

};

class Lanczos: public Filter
{
public:

    float sinc(float x)
    {
        return sin(PI * x) / (PI * x);
    }

    float compute(float x, float r = 2)
    {
        if(x == 0.0)
            return 1.0;
        else if(fabs(x) < r)
            return sinc(x) * sinc(x / r);
        else
            return 0.0;
    }
};

class Gaussian: public Filter
{
public:
    float compute(float x, float r = 1)
    {
        return pow(E, -(x * x) / (2.0 * r * r)) / (sqrt(2 * PI) * r);
    }
};

class Mitchell: public Filter
{
public:
    float compute(float x, float r = 2)
    {
        if(fabs(x) <= 1)
            return 1.0/18 * (-21.0 * pow((1 - fabs(x)), 3) + 27.0 * (pow(1 - fabs(x), 2)) + 9.0 * (1 - fabs(x)) + 1.0);
        else if(fabs(x) >= 1 && fabs(x) < 2)
            return 1.0/18 * (7.0 * pow(2.0 - fabs(x), 3) - 6.0 * pow(2.0 - fabs(x), 2));
        else
            return 0.0;
    }
};

class Hamming: public Filter
{
public:
    float compute(float x, float r = 2)
    {
        if(fabs(x) < 2.0)
        {
            return (0.54 + 0.46 * cos((2 * PI * x) / 2.0));
        }
        else
            return 0.0;
    }
};

class Hann: public Filter
{
public:
    float compute(float x, float r = 2)
    {
        if(fabs(x) < 2.0)
            return  (0.5 + 0.5 * cos((2 * PI * x) / 2.0));
        else
            return 0.0;
    }
};

class Triangle: public Filter
{
public:
    float compute(float x, float r = 2)
    {
        if(fabs(x) < r)
            return (1.0 - fabs(x / r)) / r;
        else
            return 0.0;
    }
};

class Box: public Filter
{
public:
    float compute(float x, float r = 2)
    {
        if(x < r && x >= -r)
            return 1.0 / (2.0 * r);
        else
            return 0.0;
    }
};


class Resize: public Command
{
public:

    Resize();
    Resize(float x, float y, float width = 2.0);
    ~Resize();
    int clamp(float value);
    void execute();
private:
    float mx;
    float my;
    float mWidth;
    Filter * mFilter;
    int mBorder;
};


class Border: public Command
{
public:
    Border(string type);
    ~Border();
    void execute();
private:
    string border_type;
};

class Select: public Command
{
public:
    Select(string type);
    Select(string type, float width);
    ~Select();
    void execute();
private:
    string filter_type;
    float width;
};

#endif // _IMAGERESIZER_H_

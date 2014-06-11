#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <GL/glut.h>
#include <string.h>
using namespace std;

class Context{

public:
    Context():read_level(0),tiff_hold(0),border_type("zero"),filter_type("lanczos"),filterwidth(2.0){}
    ~Context(){}
    //Assignment 2
    int read_level; //flag for read command recursive
    int tiff_hold; //flag for read before write

    //Assignment 3
    string border_type;
    //0 zero border
    //1 border freeze
    //2 border circular

    string filter_type;
    //0 Lanczos
    //1 Gaussian
    //2 mitchell
    //3 hamming
    //4 hann
    //5 triangle
    //6 box

    float filterwidth;
    //default 2
};

#endif // _APPCONTEXT_H

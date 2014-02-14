#ifndef _APPCONTEXT_H_
#define _APPCONTEXT_H_

#include <GL/glut.h>

class Context{

public:
    Context():read_level(0),tiff_hold(0){}
    ~Context();
    int read_level;
    int tiff_hold;
};

#endif // _APPCONTEXT_H

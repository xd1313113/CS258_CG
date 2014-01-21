#include "CMDDraw.h"
#include <iostream>

using namespace std;

CMDDraw::CMDDraw(float x = 0.0, float y = 0.0 , float z = 0.0):x(x),y(y),z(z){}

CMDDraw::~CMDDraw(){}

void CMDDraw::execute(){
    cout<<"Draw to ("<<x<<", "<<y<<", "<<z<<");"<<endl;
}


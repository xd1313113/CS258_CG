#include "CMDMove.h"
#include <iostream>

using namespace std;

CMDMove::CMDMove(float x = 0, float y = 0 , float z =0):x(x),y(y),z(z) {}

CMDMove::~CMDMove() {}

void CMDMove::execute()
{
    cout<<"Moving to ("<<x<<", "<<y<<", "<<z<<");"<<endl;
}

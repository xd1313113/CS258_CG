#include "CMDMove.h"
#include <iostream>

using namespace std;

CMDMove::CMDMove(int x = 0, int y = 0 , int z =0):x(x),y(y),z(z){}

CMDMove::~CMDMove(){}

void CMDMove::execute(){
    cout<<"Moving to ("<<x<<", "<<y<<", "<<z<<");"<<endl;
}

#include "CMDColor.h"
#include <iostream>
#include "Command.h"

using namespace std;

CMDColor::CMDColor(int v = 0, int h = 0 , int s =0):v(v),h(h),s(s) {}

CMDColor::~CMDColor() {}

void CMDColor::execute()
{
    cout<<"Color with("<<v<<", "<<h<<", "<<s<<");"<<endl;
}


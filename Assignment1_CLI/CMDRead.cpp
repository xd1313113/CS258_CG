#include "CMDRead.h"
#include <string>
#include <iostream>

using namespace std;

CMDRead::CMDRead(string file):filename(file){}

CMDRead::~CMDRead(){}

void CMDRead::execute(){
    cout<<"Read command"<<endl;
}

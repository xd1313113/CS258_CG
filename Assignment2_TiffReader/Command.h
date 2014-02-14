#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>

using namespace std;

class Command{
public:
    virtual void execute(){
        cout<<"This is the default command!"<<endl;
    }
};

#endif

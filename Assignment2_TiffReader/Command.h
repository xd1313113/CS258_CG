#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>

using namespace std;

class Command{
public:
    Command(){}
    virtual ~Command(){}
    virtual void execute(){
        cout<<"This is the default command!"<<endl;
    }
};

#endif

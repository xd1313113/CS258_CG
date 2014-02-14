#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "AppContext.h"

using namespace std;

class Dispatcher
{
private:
    char * input;
    string currentCommand;
    set<string> commands;
    vector<string> parameters;
    Context* mContext;
public:
    Dispatcher(char* line);
    ~Dispatcher();
    void CLI_Dispatch();
    bool CLI_StringPar();
    bool checkString(char* str);
    void run();
    void registerCmd(string cmd);
    void unRegisterCmd(string cmd);
};

#endif

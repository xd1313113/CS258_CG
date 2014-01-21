#include "Dispatcher.h"
#include "Command.h"
#include "CMDRead.h"
#include "CMDMove.h"
#include "CMDDraw.h"
#include "CMDColor.h"
#include <algorithm>


Dispatcher::Dispatcher(char * line):input(0),currentCommand("")
{
    input = line;
    registerCmd("read");
    registerCmd("move");
    registerCmd("draw");
    registerCmd("color");
}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::CLI_Dispatch()
{
    transform(currentCommand.begin(), currentCommand.end(), currentCommand.begin(), ::tolower);

    Command* cmd;
    if(currentCommand == "")
    {
        cout<<"Blank Command;"<<endl;
    }
    else if(commands.find(currentCommand) == commands.end())
    {
        cout<<"No such command exits!"<<endl;
    }
    else if (currentCommand == "read")
    {
        if(parameters.size() == 1)
        {
            cmd = new CMDRead(parameters[0]);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: Read filename"<<endl;
        }
    }
    else if (currentCommand == "move")
    {
        int paras[3] = {0,0,0};
        for(unsigned i = 0; i < parameters.size(); i++)
        {
            paras[i] = atoi(parameters.at(i).c_str());
        }
        cmd = new CMDMove(paras[0],paras[1],paras[2]);
        cmd->execute();

    }
    else if (currentCommand == "draw")
    {
        float paras[3] = {0.0,0.0,0.0};
        for(unsigned i = 0; i < parameters.size(); i++)
        {
            paras[i] = atof(parameters.at(i).c_str());
        }
        cmd = new CMDDraw(paras[0],paras[1],paras[2]);
        cmd->execute();

    }
    else if (currentCommand == "color")
    {
        int paras[3] = {0,0,0};
        for(unsigned i = 0; i < parameters.size(); i++)
        {
            paras[i] = atoi(parameters.at(i).c_str());
        }
        cmd = new CMDColor(paras[0],paras[1],paras[2]);
        cmd->execute();
    }
    else
    {
        cout<<"unknown error"<<endl;
    }
}

bool Dispatcher::checkString(char* str)
{
    for(int i = 0; str[i]!='\0'; i++)
    {
        if(!(isdigit(str[i])||isalpha(str[i])||str[i]=='.'||str[i]=='-'))
        {
            return false;
        }
    }
    return true;
}

bool Dispatcher::CLI_StringPar()
{
    char * pch;
    pch = strtok (input," ,");
    currentCommand = string(pch);
    if(!checkString(pch))
    {
        return false;
    }
    else
    {
        while (pch != NULL)
        {
            pch = strtok (NULL, " ,");
            if(pch !=0)
            {

                if(!checkString(pch))
                    return false;
                else
                {
                    string para = string(pch);
                    parameters.push_back(para);
                }
            }
        }
    }
    return true;
}

void Dispatcher::run()
{
    CLI_StringPar();
    CLI_Dispatch();
}

void Dispatcher::registerCmd(string cmd)
{
    commands.insert(cmd);
}

void Dispatcher::unRegisterCmd(string cmd)
{
    set<string>::iterator it;
    it = commands.find(cmd);
    commands.erase(it);
}

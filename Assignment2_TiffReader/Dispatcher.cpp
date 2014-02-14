#include "Dispatcher.h"
#include "Command.h"
#include "CMDRead.h"
#include "tiff.h"
#include <algorithm>


Dispatcher::Dispatcher(char * line):input(0),currentCommand("")
{
    input = line;
    registerCmd("read");
    registerCmd("tiffread");
    registerCmd("tiffstat");
    registerCmd("tiffwrite");
}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::CLI_Dispatch()
{
    transform(currentCommand.begin(), currentCommand.end(), currentCommand.begin(), ::tolower);

    Command* cmd = 0;
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
    else if (currentCommand == "tiffread")
    {
        if(parameters.size() == 1)
        {
            cmd = new TiffRead(parameters[0]);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: Read filename"<<endl;
        }
    }
    else if (currentCommand == "tiffstat")
    {
        if(parameters.size() == 1)
        {
            cmd = new TiffStat(parameters[0]);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: Read filename"<<endl;
        }
    }
    else if (currentCommand == "tiffwrite")
    {
        if(parameters.size() < 1)
        {
            cout<<"Usage: tiffwrite filename x ,y , xx, yy"<<endl;
        }
        else
        {
            int paras[4] = {0,0,0,0};

            for(unsigned i = 1; i < parameters.size(); i++)
            {
                paras[i-1] = atoi(parameters.at(i).c_str());
            }
            //cmd = new TiffRead("1.tif");
            //cmd->execute();
            cmd = new TiffWrite(parameters[0],paras[0],paras[1],paras[2],paras[3]);
            cmd->execute();
        }
    }
    else
    {
        cout<<"unknown error"<<endl;
    }
    if(cmd != 0)
        delete cmd;
}

bool Dispatcher::checkString(char* str)
{
    for(int i = 0; str[i]!='\0'; i++)
    {
        if(!(isdigit(str[i])||isalpha(str[i])||str[i]=='.'||str[i]=='-'||str[i]=='_'))
        {
            return false;
        }
    }
    return true;
}

bool Dispatcher::CLI_StringPar()
{
    //char temp[] = "tiffwrite test5.tif 10,20,100,150";
    //input = temp;
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

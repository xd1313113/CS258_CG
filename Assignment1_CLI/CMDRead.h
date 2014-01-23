#include "Command.h"
#include<string>

class CMDRead: public Command
{
private:
    string filename;
public:
    CMDRead(string filename);
    ~CMDRead();
    void execute();
};


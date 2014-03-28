#include "Command.h"
#include<string>
#include "AppContext.h"
extern Context* ctx;

class CMDRead: public Command
{
private:
    string filename;
public:
    CMDRead(string filename);
    ~CMDRead();
    void execute();
};


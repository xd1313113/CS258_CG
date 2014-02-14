#include "Command.h"

class CMDDraw:public Command
{
private:
    float x, y ,z;
public:
    CMDDraw(float x, float y, float z);
    ~CMDDraw();
    void execute();
};


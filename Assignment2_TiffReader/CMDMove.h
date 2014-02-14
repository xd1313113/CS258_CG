#include "Command.h"

class CMDMove:public Command
{
private:
    float x, y ,z;
public:
    CMDMove(float x, float y, float z);
    ~CMDMove();
    void execute();
};

#include "Command.h"

class CMDMove:public Command{
private:
    int x, y ,z;
public:
    CMDMove(int x, int y, int z);
    ~CMDMove();
    void execute();
};

#include "Command.h"

class CMDColor:public Command{
private:
    int v, h ,s;
public:
    CMDColor(int v, int h, int s);
    ~CMDColor();
    void execute();
};


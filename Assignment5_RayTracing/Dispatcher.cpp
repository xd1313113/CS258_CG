#include "Dispatcher.h"
#include "Command.h"
#include "CMDRead.h"
#include "tiff.h"
#include "ImageResizer.h"
#include "transformation.h"
#include "RayTracer.h"
#include <algorithm>

extern Context *ctx;
Transformation *trns = new Transformation();
RayTracer * raytracer = new RayTracer();

Dispatcher::Dispatcher(char * line):input(0),currentCommand("")
{
    input = line;
    registerCmd("read");
    registerCmd("tiffread");
    registerCmd("tiffstat");
    registerCmd("tiffwrite");
    registerCmd("select");
    registerCmd("border");
    registerCmd("resize");
    registerCmd("zoom");

    //assignment 4
    registerCmd("push");
    registerCmd("pop");
    registerCmd("translate");
    registerCmd("scale");
    registerCmd("rotate");
    registerCmd("ortho");
    registerCmd("perspective");
    registerCmd("lookat");
    registerCmd("vertex");
    registerCmd("reset");
    registerCmd("orient");


    //assignment 5
    registerCmd("screen");
    registerCmd("orthocamera");
    registerCmd("camera");
    registerCmd("background");
    registerCmd("sphere");
    registerCmd("triangle");
    registerCmd("box");
    registerCmd("ilight");
    registerCmd("clear");
    registerCmd("trace");
    registerCmd("plane");
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
            cout<<"Usage: tiffread filename"<<endl;
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
            cout<<"Usage: tiffstat filename"<<endl;
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
    else if (currentCommand == "border")
    {
        if(parameters.size() == 1 &&
           (parameters[0]=="zero"||parameters[0]=="freeze"||parameters[0]=="circular"))
        {
            cmd = new Border(parameters[0]);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: border zero||freeze||circular"<<endl;
        }
    }
    else if (currentCommand == "select")
    {
        if(parameters.size() == 0){
            cout<<"The current filter is "<< ctx->filter_type << " with width "<<ctx->filterwidth<<";"<<endl;
        }
        else if(parameters.size() == 1&&(parameters[0]=="lanczos"||
                                    parameters[0]=="gaussian"||
                                    parameters[0]=="mitchell"||
                                    parameters[0]=="hamming"||
                                    parameters[0]=="hann"||
                                    parameters[0]=="triangle"||
                                    parameters[0]=="box"
                                    ))
        {
            cmd = new Select(parameters[0]);
            cmd->execute();
        }else if(parameters.size() == 2&&(parameters[0]=="lanczos"||
                                    parameters[0]=="gaussian"||
                                    parameters[0]=="triangle"||
                                    parameters[0]=="box"
                                    ))
        {
            float width = atof(parameters[1].c_str());
            cmd = new Select(parameters[0],width);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: select filtername"<<endl;
        }
    }
    else if (currentCommand == "resize")
    {
        if(parameters.size() == 2)
        {
            float x = atof(parameters[0].c_str());
            float y = atof(parameters[1].c_str());
            cmd = new Resize(x,y);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: resize x_scale, y_scale"<<endl;
        }
    }
    else if (currentCommand == "zoom")
    {
        if(parameters.size() == 1)
        {
            float s = atof(parameters[0].c_str());
            cmd = new Resize(s,s);
            cmd->execute();
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: zoom scale"<<endl;
        }
    }
    //assignment 4
    else if (currentCommand == "push")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: push"<<endl;
        }
        else
        {
           trns->Push();
        }
    }else if (currentCommand == "pop")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: pop"<<endl;
        }
        else
        {
            trns->Pop();
        }
    }else if (currentCommand == "translate")
    {
        if(parameters.size() == 3)
        {
            float x = atof(parameters[0].c_str());
            float y = atof(parameters[1].c_str());
            float z = atof(parameters[2].c_str());
            trns->Translate(x,y,z);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: translate x ,y, z"<<endl;
        }
    }else if (currentCommand == "scale")
    {
        if(parameters.size() == 3)
        {
            float sx = atof(parameters[0].c_str());
            float sy = atof(parameters[1].c_str());
            float sz = atof(parameters[2].c_str());
            trns->Scale(sx,sy,sz);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: scale x, y, z"<<endl;
        }
    }else if (currentCommand == "rotate")
    {
        if(parameters.size() == 4)
        {
            float paras[4] = {0.0,0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            trns->Rotate(paras[0],paras[1],paras[2],paras[3]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: rotate angle, x, y, z"<<endl;
        }
    }else if (currentCommand == "ortho")
    {
        if(parameters.size() == 6)
        {
            float paras[6] = {0.0,0.0,0.0,0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            trns->Ortho(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: ortho l, r, b, t, n, f"<<endl;
        }
    }else if (currentCommand == "perspective")
    {
        if(parameters.size() == 4)
        {
            float paras[4] = {0.0,0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            trns->Perspective(paras[0],paras[1],paras[2],paras[3]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: perspective f, a, n, f"<<endl;
        }
    }else if (currentCommand == "lookat")
    {
        if(parameters.size() == 9)
        {
            float paras[9] = {  0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            trns->Lookat(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: lookat "<<endl;
        }
    }else if (currentCommand == "vertex")
    {
        if(parameters.size() == 3)
        {
            float x = atof(parameters[0].c_str());
            float y = atof(parameters[1].c_str());
            float z = atof(parameters[2].c_str());
            trns->Vertex(x,y,z);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: vertex x,y,z"<<endl;
        }
    }else if (currentCommand == "reset")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: reset"<<endl;
        }
        else
        {
            trns->Reset();
        }
    }else if (currentCommand == "orient")
    {
        if(parameters.size() == 9)
        {
            float paras[9] = {  0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            trns->Orient(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: orient "<<endl;
        }
    }else if (currentCommand == "screen")
    {
        if(parameters.size() == 2)
        {
            float paras[2] = { 0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->setScreen(paras[0],paras[1]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: screen x, y"<<endl;
        }
    }else if (currentCommand == "orthocamera")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: orthocamera"<<endl;
        }
        else
        {
            raytracer->setOrthocamera();
        }
    }else if (currentCommand == "camera")
    {
        if(parameters.size() == 14)
        {
            float paras[14] = { 0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0 };

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->setCamera(paras[0],paras[1],paras[2],paras[3],paras[4],
                                    paras[5],paras[6],paras[7],paras[8],
                                    paras[9],paras[10],paras[11],paras[12],paras[13]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: camera "<<endl;
        }
    }else if (currentCommand == "background")
    {
        if(parameters.size() == 3)
        {
            float paras[3] = { 0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->setBackground(paras[0],paras[1],paras[2]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: background "<<endl;
        }
    }else if (currentCommand == "sphere")
    {
        if(parameters.size() == 10 ||parameters.size() == 13||parameters.size() == 17||parameters.size() == 18||parameters.size() == 19)
        {
            float paras[19] = { 0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->addSphere(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8],
                                    paras[9],paras[10],paras[11],paras[12],paras[13],paras[14],paras[15],paras[16],paras[17],paras[18]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: sphere "<<endl;
        }
    }else if (currentCommand == "triangle")
    {
        if(parameters.size() == 15||parameters.size() == 18||parameters.size() == 22||parameters.size() == 23)
        {
            float paras[23] = { 0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0 };

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->addTriangle(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8],
                                    paras[9],paras[10],paras[11],paras[12],paras[13],paras[14],paras[15],paras[16],paras[17],
                                    paras[18],paras[19],paras[20],paras[21],paras[22]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: triangle "<<endl;
        }
    }else if (currentCommand == "box")
    {
        if(parameters.size() == 12||parameters.size() == 15||parameters.size() == 19||parameters.size() == 20||parameters.size() == 21)
        {
            float paras[21] = { 0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->addBox(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8],
                                    paras[9],paras[10],paras[11],paras[12],paras[13],paras[14],paras[15],paras[16],
                                    paras[17],paras[18],paras[19],paras[20]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: box "<<endl;
        }
    }else if (currentCommand == "ilight")
    {
        if(parameters.size() == 6)
        {
            float paras[6] = {  0.0,0.0,0.0,
                                0.0,0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->addIlight(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: ilight "<<endl;
        }
    }else if (currentCommand == "clear")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: clear"<<endl;
        }
        else
        {
            raytracer->clear();
        }
    }else if (currentCommand == "trace")
    {
        if(parameters.size() != 0)
        {
            cout<<"no parameters needed!"<<endl;
            cout<<"Usage: trace"<<endl;
        }
        else
        {
            raytracer->trace();
        }
    }else if (currentCommand == "plane")
    {
        if(parameters.size() == 12 ||parameters.size() == 15 ||parameters.size() == 19||parameters.size() == 20)
        {
            float paras[20] = { 0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0,0.0,
                                0.0,0.0};

            for(unsigned i = 0; i < parameters.size(); i++)
            {
                paras[i] = atof(parameters.at(i).c_str());
            }
            raytracer->addPlane(paras[0],paras[1],paras[2],paras[3],paras[4],paras[5],paras[6],paras[7],paras[8],
                                    paras[9],paras[10],paras[11],paras[12],paras[13],paras[14],paras[15],paras[16],
                                    paras[17],paras[18],paras[19]);
        }
        else
        {
            cout<<"Incorrect parameters!"<<endl;
            cout<<"Usage: plane "<<endl;
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
    string s(str);
    //cout<<"str"<<s.length()<<endl;
    for(int i = 0; i < s.length(); i++)
    {
        if(!(isdigit(s[i])||isalpha(s[i])||s[i]=='.'||s[i]=='-'||s[i]=='_'))
        {
            //cout<<"str"<<s[i]<<endl;
            return false;
        }
    }
    return true;
}

bool Dispatcher::CLI_StringPar()
{
//    char temp[] = "read cube_test_1.cli";
//    input = temp;
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

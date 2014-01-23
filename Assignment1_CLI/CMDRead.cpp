#include "CMDRead.h"
#include "Dispatcher.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CMDRead::CMDRead(string file):filename(file) {}

CMDRead::~CMDRead() {}

void CMDRead::execute()
{
    std::string line;

    std::ifstream input(filename.c_str());
    if(!input)
    {
        std::cout << "Could not open the given file, please check and try again" << std::endl;
    }
    else
    {
        while(std::getline(input, line))
        {
            Dispatcher* dispatcher = new Dispatcher(const_cast<char*>(line.c_str()));
            dispatcher->run();
        }
    }

    input.close();
}

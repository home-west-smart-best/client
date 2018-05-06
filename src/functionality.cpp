//
// Created by jamie on 3/28/18.
//

#include <iostream>
#include "functionality.h"

Functionality::Functionality(const std::string &appname,
                             const std::string &clientname,
                             const std::string &host,
                             int port) :
        CommandProcessor(appname, clientname, host, port)
{

}

Functionality::~Functionality()
{
    stop();
}

void Functionality::start()
{
    if(_thread.joinable())
    {
        std::cerr << "---- ** Functionality already started, restarting...\n";
        _thread.detach();
    }

    _thread = std::thread(_routine);
    loop();

    std::cerr << "---- ** Started " << clientname_.c_str() <<"\n";
}

void Functionality::stop()
{
    if(_thread.joinable()) _thread.detach();
    loop_stop();

    std::cerr << "---- ** Stopped " << appname_ <<"\n";
}

#include "MQTTconfig.h"
#include "application.h"
#include <iostream>

Switch::Switch(const std::string &appname,
               const std::string &clientname,
               const std::string &host,
               int port)
        : Functionality(appname, clientname, host, port)
{
    registerCommand("set_state", std::bind(&Switch::setState, this, std::placeholders::_1));
    registerCommand("get_state", std::bind(&Switch::getState, this, std::placeholders::_1));

    std::cerr << "---- ** Created " << clientname << ": " << topicRoot_.c_str() << "\n";
}

Switch::~Switch()
= default;

void Switch::setState(const Switch::parameters_t &commandParameters)
{
    json j = json::parse(commandParameters[0]);

    std::cerr << "switch set to " << j["state"].get<bool>() << "\n";
}

void Switch::getState(const Switch::parameters_t &commandParameters)
{
    json j;

    j["state"] = _currentState;

    publishReturn("get_state", j.dump());
}

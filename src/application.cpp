#include "MQTTconfig.h"
#include "application.h"
#include <iostream>

AppController::AppController(const std::string &appname,
                             const std::string &clientname,
                             const std::string &host,
                             int port)
        : CommandProcessor(appname, clientname, host, port)
{
    registerCommand("set_functionality", std::bind(&AppController::setFunctionality, this, std::placeholders::_1));
    registerCommand("get_functionality", std::bind(&AppController::getFunctionality, this, std::placeholders::_1));

    // create functionalities
    _functionalities.emplace("thermostat", std::make_unique<Thermostat>(appname, "thermostat", host, port));

    setFunctionality({R"([{"name" : "thermostat", "value" : true}])"});

    std::cerr << "---- ** Application started: " << topicCommandRoot_.c_str() << std::endl;
}

AppController::~AppController()
{
    std::cerr << "---- ** Destroy AppController" << std::endl;
}

void AppController::setFunctionality(const std::vector<std::string> &commandParameters)
{
    json j = json::parse(commandParameters[0]);

    for(const auto &func : j)
    {
        auto it = _functionalities.find(func["name"]);

        if (it != _functionalities.end())
        {
            if(func["value"].get<bool>()) it->second->start();
        }
        else
        {
            std::cerr << "---- ** Invalid functionality '" << func["name"] << "'" << std::endl;
            return;
        }
    }
}

void AppController::getFunctionality(const std::vector<std::string> &commandParameters)
{

}

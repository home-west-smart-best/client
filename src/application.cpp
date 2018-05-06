#include "MQTTconfig.h"
#include "application.h"
#include <iostream>

AppController::AppController(const std::string &appname,
                             const std::string &clientname,
                             const std::string &host,
                             int port)
        : CommandProcessor(appname, clientname, host, port)
{
    // create functionalities
    _thermostat =  std::make_unique<Thermostat>(appname, "thermostat", host, port);

    // deprecated
//    setFunctionality({R"([{"name" : "thermostat", "value" : true}])"});

    std::cerr << "---- ** Application started: " << topicRoot_.c_str() << std::endl;
}

AppController::~AppController()
{
    std::cerr << "---- ** Destroy AppController" << std::endl;
}


//
// Created by jamie on 3/28/18.
//

#include <iostream>

#include "thermostat.h"

Thermostat::Thermostat(const std::string& appname,
                 const std::string& clientname,
                 const std::string& host,
                 int port):
        CommandProcessor(appname, clientname, host, port)
{
    std::cerr << "---- ** Started thermostat\n";

    _thread = std::thread(std::bind(&Thermostat::routine, this));
}

Thermostat::~Thermostat()
{
    _thread.detach();
    std::cerr << "---- ** Stopped thermostat\n";
}

void Thermostat::routine()
{
    std::cerr << "---- ** Started thermostat\n";

    for (;;)
    {
        // TBD
        publishAddition("temperature/celsius", "21");
        publishAddition("temperature/fahrenheit", "83");
        delay(1000);
    }
}

void Thermostat::start(const parameters_t &commandParameters)
{
    //TBD
    _targetTemperature = 50;
}

int Thermostat::stop(const parameters_t &commandParameters) const
{
    return _targetTemperature;
}

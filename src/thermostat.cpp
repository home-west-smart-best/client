//
// Created by jamie on 3/28/18.
//

#include <iostream>

#include "thermostat.h"

Thermostat::Thermostat(const std::string& appname,
                 const std::string& clientname,
                 const std::string& host,
                 int port):
        Functionality(appname, clientname, host, port)
{
    setRoutine(std::bind(&Thermostat::routine, this));

    std::cerr << "---- ** Created app: " << appname <<"\n";
}

Thermostat::~Thermostat()
= default;

void Thermostat::routine()
{
    for (;;)
    {
        // TBD
        publishAddition("temperature/celsius", "21");
        publishAddition("temperature/fahrenheit", "83");
        delay(1000);
    }
}

void Thermostat::setTargetTemperature(const parameters_t &commandParameters)
{
    //TBD
    _targetTemperature = 50;
}

int Thermostat::getTargetTemperature(const parameters_t &commandParameters) const
{
    return _targetTemperature;
}

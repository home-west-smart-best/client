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

    registerCommand("set_target_temperature", std::bind(&Thermostat::setTargetTemperature, this, std::placeholders::_1));
    registerCommand("get_target_temperature", std::bind(&Thermostat::getTargetTemperature, this, std::placeholders::_1));

    std::cerr << "---- ** Created functionality " << clientname << ": " << topicCommandRoot_.c_str() <<"\n";
}

Thermostat::~Thermostat()
= default;

void Thermostat::routine()
{
    for (;;)
    {
        // TODO: real sensor data
        publishAddition("temperature/celsius", "21");
        publishAddition("temperature/fahrenheit", "83");
        delay(1000);
    }
}

void Thermostat::setTargetTemperature(const parameters_t &commandParameters)
{
    json j = json::parse(commandParameters[0]);

    _targetTemperature = j["value"];
}

void Thermostat::getTargetTemperature(const parameters_t &commandParameters)
{
    publishAddition("target_temperature", std::to_string(_targetTemperature));
}

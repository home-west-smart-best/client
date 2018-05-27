//
// Created by jamie on 3/28/18.
//

#include <iostream>

#include "thermostat.h"

Thermostat::Thermostat(const std::string &appname,
                       const std::string &clientname,
                       const std::string &host,
                       int port) :
    Functionality(appname, clientname, host, port)
{
  setRoutine(std::bind(&Thermostat::routine, this));

  registerCommand("set_target_temperature", std::bind(&Thermostat::setTargetTemperature, this, std::placeholders::_1));
  registerCommand("get_target_temperature", std::bind(&Thermostat::getTargetTemperature, this, std::placeholders::_1));

  std::cerr << "---- ** Created " << clientname << ": " << topicRoot_.c_str() << "\n";

  start();
}

Thermostat::~Thermostat()
= default;

void Thermostat::routine()
{
  int currentTemp = 20;

  for (;;)
  {
    json j;

    if(currentTemp - _targetTemperature < 0) currentTemp += 1;
    else if(currentTemp - _targetTemperature > 0) currentTemp -= 1;

    // TODO: real sensor data
    j["id"] = std::atoi(appname_.c_str());
    j["unit"]["celsius"] = currentTemp;
    j["unit"]["fahrenheit"] = 88;

    publishAddition("temperature", j.dump());
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
  json j;

  j["id"] = std::atoi(appname_.c_str());
  j["unit"]["celsius"] = _targetTemperature;
  j["unit"]["fahrenheit"] = _targetTemperature;

  publishReturn("get_target_temperature", j.dump());
}

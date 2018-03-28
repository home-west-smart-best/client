#include "MQTTconfig.h"
#include "TemperatureConverter.h"
#include "Topic.h"
#include <string>
#include <iostream>

TemperatureConverter::TemperatureConverter(const std::string& appname,
                                           const std::string& clientname,
                                           const std::string& host,
                                           int port)
   : CommandProcessor(appname, clientname, host, port)
{
   std::cerr << "---- ** CTOR TemperatureConverter" << std::endl;
   registerCommand("c2f", std::bind(&TemperatureConverter::c2f, this,
                                    std::placeholders::_1));
    registerCommand("f2c", std::bind(&TemperatureConverter::f2c, this,
                                    std::placeholders::_1));
}

TemperatureConverter::~TemperatureConverter()
{
   std::cerr << "---- ** DTOR TemperatureConverter" << std::endl;
}

void TemperatureConverter::c2f(const std::vector<std::string>& commandParameters)
{
   if (commandParameters.size() == 1)
   {
      double temp_celsius{std::stod(commandParameters[0])};
      std::string temp_fahrenheit {"c2f " +
                                   std::to_string(temp_celsius * 9.0 / 5.0 + 32.0)};
      publishReturn("c2f", temp_fahrenheit);
   }
   else
   {
      publishError("c2f", "number of parameters != 1");
   }
}

void TemperatureConverter::f2c(const std::vector<std::string>& commandParameters)
{
   if (commandParameters.size() == 1)
   {
      double temp_fahrenheit{std::stod(commandParameters[0])};
      std::string temp_celsius {"f2c " +
                                   std::to_string((temp_fahrenheit - 32) / 1.8)};
      publishReturn("f2c", temp_celsius);
   }
   else
   {
      publishError("f2c", "number of parameters != 1");
   }
}

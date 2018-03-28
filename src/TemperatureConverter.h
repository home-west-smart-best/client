#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "CommandProcessor.h"
#include <string>
#include <vector>

class TemperatureConverter : public CommandProcessor
{
public:
   TemperatureConverter(const std::string& appname,
                        const std::string& clientname,
                        const std::string& host,
                        int port);
   virtual ~TemperatureConverter();
private:
   void c2f(const std::vector<std::string>& commandParameters);
   void f2c(const std::vector<std::string>& commandParameters);
};

#endif

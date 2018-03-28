#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "_libMQTT/CommandProcessor.h"
#include <string>
#include <vector>

#include "thermostat.h"

class CommandInterface : public CommandProcessor
{
public:
    CommandInterface(const std::string &appname,
                const std::string &clientname,
                const std::string &host,
                int port);

    virtual ~CommandInterface();

private:
    void c2f(const std::vector<std::string> &commandParameters);

    void f2c(const std::vector<std::string> &commandParameters);
};

#endif

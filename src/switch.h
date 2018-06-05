#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "CommandProcessor.h"
#include <string>
#include <vector>

#include "json.hpp"
#include "thermostat.h"

class Switch : public Functionality
{
    using parameters_t = std::vector<std::string>;
    using json = nlohmann::json;

public:
    Switch(const std::string &appname, const std::string &clientname, const std::string &host, int port,
               std::string id);

    ~Switch() override;

    void setState(const parameters_t &commandParameters);

    void getState(const parameters_t &commandParameters);

private:
    int _currentState{};
};

#endif

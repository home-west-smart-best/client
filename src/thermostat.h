//
// Created by jamie on 3/28/18.
//

#ifndef CLIENT_THERMOSTAT_H
#define CLIENT_THERMOSTAT_H

#include <thread>
#include <memory>

#include "functionality.h"

using parameters_t = std::vector<std::string>;

class Thermostat : public Functionality
{
public:
    Thermostat(const std::string &appname,
            const std::string &clientname,
            const std::string &host,
            int port);

    ~Thermostat() override;

    void setTargetTemperature(const parameters_t &commandParameters);

    int getTargetTemperature(const parameters_t &commandParameters) const;

    void routine();

private:
    int _targetTemperature;
};

#endif //CLIENT_THERMOSTAT_H

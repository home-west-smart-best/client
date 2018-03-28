//
// Created by jamie on 3/28/18.
//

#ifndef CLIENT_THERMOSTAT_H
#define CLIENT_THERMOSTAT_H

#include <thread>
#include <memory>

#include "_libMQTT/CommandProcessor.h"

using parameters_t = std::vector<std::string>;

class Thermostat : public CommandProcessor
{
public:
    Thermostat(const std::string &appname,
            const std::string &clientname,
            const std::string &host,
            int port);

    ~Thermostat() override;

    void start(const parameters_t &commandParameters);

    int stop(const parameters_t &commandParameters) const;

    void routine();

    void delay(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

private:
    std::thread _thread;
    int _targetTemperature;
};

#endif //CLIENT_THERMOSTAT_H

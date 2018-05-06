#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "CommandProcessor.h"
#include <string>
#include <vector>

#include "json.hpp"
#include "thermostat.h"

class AppController : public CommandProcessor
{
    using functionality_t = std::unique_ptr<Functionality>;
    using json = nlohmann::json;

public:
    AppController(const std::string &appname,
                const std::string &clientname,
                const std::string &host,
                int port);

    ~AppController() override;

private:
    std::unique_ptr<Thermostat> _thermostat;
};

#endif

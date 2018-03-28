#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "CommandProcessor.h"
#include <string>
#include <vector>

class Application : public CommandProcessor
{
public:
    Application(const std::string &appname,
                const std::string &clientname,
                const std::string &host,
                int port);

    virtual ~Application();

private:
    void c2f(const std::vector<std::string> &commandParameters);

    void f2c(const std::vector<std::string> &commandParameters);
};

#endif

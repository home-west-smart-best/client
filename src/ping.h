//
// Created by jamie on 5/24/18.
//

#ifndef CLIENT_PING_H
#define CLIENT_PING_H

#include "functionality.h"
#include <nlohmann/json.hpp>

class Ping : public Functionality
{
    using parameters_t = std::vector<std::string>;
    using json = nlohmann::json;

public:
    Ping(const std::string &appname, const std::string &clientname, const std::string &host, int port,
             std::string id);

    ~Ping() override;

    void routine();

private:

};

#endif //CLIENT_PING_H

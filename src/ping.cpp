//
// Created by jamie on 5/24/18.
//

#include <iostream>
#include "ping.h"

Ping::Ping(const std::string &appname, const std::string &clientname, const std::string &host, int port,
           std::string id) :
        Functionality(appname, clientname, host, port, id)
{
    setRoutine(std::bind(&Ping::routine, this));

    auto msg = std::string("{\"id\":") + clientname + "}";

    set_lwt("hwsb/disconnect", msg.size(), msg.c_str(), 0, false);

    std::cerr << "---- ** Created " << appname << ": " << topicRoot_.c_str() <<"\n";

    start();
}

Ping::~Ping() {
  auto msg = std::string("{\"id\":") + clientname_ + "}";

  publish(nullptr, "hwsb/disconnect", msg.size(), msg.c_str(), 0, false);
}

void Ping::routine()
{
    for (;;)
    {
        json j;

        // TODO: real sensor data
        j["id"] = std::atoi(clientname_.c_str());

        publishAddition("pong", j.dump());
        delay(500);
    }
}
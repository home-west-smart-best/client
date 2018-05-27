//
// Created by jamie on 5/24/18.
//

#include <iostream>
#include "ping.h"

Ping::Ping(const std::string& appname,
                       const std::string& clientname,
                       const std::string& host,
                       int port):
        Functionality(appname, clientname, host, port)
{
    setRoutine(std::bind(&Ping::routine, this));

    std::cerr << "---- ** Created " << clientname << ": " << topicRoot_.c_str() <<"\n";

    start();
}

Ping::~Ping()
= default;

void Ping::routine()
{
    for (;;)
    {
        json j;

        // TODO: real sensor data
        j["id"] = std::atoi(appname_.c_str());

        publishAddition("pong", j.dump());
        delay(500);
    }
}
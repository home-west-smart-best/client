#include "MQTTconfig.h"
#include "switch.h"
#include <iostream>
#include <random>

Switch::Switch(const std::string &appname,
               const std::string &clientname,
               const std::string &host,
               int port)
    : Functionality(appname, clientname, host, port)
{
  registerCommand("set_state", std::bind(&Switch::setState, this, std::placeholders::_1));
  registerCommand("get_state", std::bind(&Switch::getState, this, std::placeholders::_1));

  json j;

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

  j["id"] = std::atoi(appname.c_str());
  j["state"] = (bool)(dist(rng));

  publishAddition("state", j.dump());

  std::cerr << "---- ** Created " << clientname << ": " << topicRoot_.c_str() << "\n";
}

Switch::~Switch()
= default;

void Switch::setState(const Switch::parameters_t &commandParameters)
{
  json j = json::parse(commandParameters[0]);

  std::cerr << "switch set to " << j["state"].get<bool>() << "\n";
}

void Switch::getState(const Switch::parameters_t &commandParameters)
{
  json j;

  j["id"] = std::atoi(appname_.c_str());
  j["state"] = _currentState;

  publishReturn("get_state", j.dump());
}

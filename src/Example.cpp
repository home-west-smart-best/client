#include "Example.h"
#include <iostream>

Example::Example(const std::string& appname,
                 const std::string& clientname,
                 const std::string& host,
                 int port):
   CommandProcessor(appname, clientname, host, port)
{
   std::cerr << "---- ** CTOR CommandProcessor" << std::endl;
   // Register C++-functions by MQTT topics/messages
   registerCommand("start", bind(&Example::start, this, std::placeholders::_1));
   registerCommand("stop", bind(&Example::stop, this, std::placeholders::_1));
}

Example::~Example()
{
   std::cerr << "---- ** DTOR Example" << std::endl;
}

// Class member function
void Example::start(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError(__func__, "number of parameters != 0");
   }
   else
   {
      std::cerr << "Example::start() " ;
      for (const auto& s: commandParameters)
      {
         std::cerr << s << " ";
      }
      std::cerr << std::endl;
   }
}

// Class member function
void Example::stop(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("stop", "number of parameters != 0");
   }
   else
   {
      std::cerr << "-- Command: stop ";
      for (const auto& s: commandParameters)
      {
         std::cerr << s << " ";
      }
      std::cerr << std::endl;
   }
}

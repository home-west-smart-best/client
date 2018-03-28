#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "CommandProcessor.h"

#include <string>
#include <vector>

using parameters_t = std::vector<std::string>;

class Example: public CommandProcessor
{
public:
   Example(const std::string& appname,
           const std::string& clientname,
           const std::string& host,
           int port);
   virtual ~Example();
   // class member functions
   void start(const parameters_t& commandParameters);
   void stop(const parameters_t& commandParameters);
};

#endif // EXAMPLE_H

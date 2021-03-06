#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "Topic.h"
#include "mosquittopp.h"
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <mutex>

class CommandProcessor;

using commandfunction =
std::function<void(const std::vector<std::string> &commmandParameters)>;

/// CommandProcessor is a base class for connecting a command name to a 
/// related member function in the derived class by calling the #registerCommand
/// function.
///  
/// The definition of the member function for handling the received command 
/// topic: #commandfunction.
///
/// THe topic syntax for a command is: 
/// #MQTT_TOPIC_ROOT / <appname> / <clientname> /command"
/// The related command name and parameters are part of the message. 
///
/// Every command can have >=0 parameters separated by one or more spaces. 
/// The receiving client (derived class) is responsible for 
/// checking the number of parameters and the conversion of the strings to 
/// the correct type (int, double, etc.).
class CommandProcessor : public mosqpp::mosquittopp
{
public:
    CommandProcessor(const std::string &appname, const std::string &clientname,
                         const std::string &host, int port, const std::string &id);

    CommandProcessor(const CommandProcessor &other) = delete;

    CommandProcessor &operator=(const CommandProcessor &other) = delete;

    virtual ~CommandProcessor();

    void registerCommand(const std::string &command, commandfunction cfunction);

    void executeCommand(const std::string &command);

    void executeCommands(const std::vector<std::string> &commands);

    bool commandIsRegistered(const std::string &command) const;

    void publishAddition(const std::string &topicAddition,
                         const std::string &message);

    void publishReturn(const std::string &command, const std::string &message);

    void publishInfo(const std::string &command, const std::string &message);

    void publishWarning(const std::string &command, const std::string &message);

    void publishError(const std::string &command, const std::string &message);

    void set_lwt(const char *topic, int payloadlen=0, const void *payload=NULL, int qos=0, bool retain=false);

protected:
    std::string appname_;
    std::string clientname_;
    Topic topicRoot_;
    Topic topicCommandRoot_;

    virtual void on_message(const mosquitto_message *message) override;

    virtual void on_connect(int rc) override;

    //virtual void on_disconnect(int rc) override {}
    virtual void on_log(int level, const char *str) override;
    //virtual void on_error() override;
private:
    std::mutex mut_;
    std::map<std::string, commandfunction>
            commands_;
};

#endif // COMMANDPROCCESSOR_H


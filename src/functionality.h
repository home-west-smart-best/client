//
// Created by jamie on 3/28/18.
//

#ifndef CLIENT_FUNCTIONALITY_H
#define CLIENT_FUNCTIONALITY_H

#include <CommandProcessor.h>
#include <thread>
#include <utility>

class Functionality : public CommandProcessor
{
public:
    using routine_t = std::function<void()>;

    Functionality(const std::string &appname, const std::string &clientname, const std::string &host,
                      int port, std::string id);

    ~Functionality() override;

    void start();

    void stop();

    void delay(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

protected:
    void setRoutine(routine_t routine) { _routine = std::move(routine); }

private:
    routine_t _routine;
    std::thread _thread;
};

#endif //CLIENT_FUNCTIONALITY_H

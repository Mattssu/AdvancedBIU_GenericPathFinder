//
// Created by lab on 1/15/19.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H


#include <vector>
#include <thread>
#include "ClientHandler.h"

#include "Server.h"

class MyParallelServer : public Server {
private:
    /* Holds all the opened threads. */
    std::vector<thread> threads;
    bool stopRunning = false;

public:
    virtual void open(int port, ClientHandler *c) override;

    virtual void stop() override;

    ~MyParallelServer() = default;
};


#endif //MILESTONE2_MYPARALLELSERVER_H

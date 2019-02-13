//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H


#include "Server.h"

class MySerialServer : public Server {
private:
    bool stopRunning;
public:
    MySerialServer() {
        stopRunning = false;
    }

    virtual void open(int port, ClientHandler *c) override;

    virtual void stop() override {
        stopRunning = true;
    }
};


#endif //MILESTONE2_MYSERIALSERVER_H

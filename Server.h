//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"

class Server {
public:
    virtual void open(int port, ClientHandler *ch) = 0;

    virtual void stop() = 0;

    ~Server() = default;
};


#endif //MILESTONE2_SERVER_H

//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

#include <iostream>

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int socketInfo) = 0;

    virtual ~ClientHandler() = default;
};


#endif //MILESTONE2_CLIENTHANDLER_H

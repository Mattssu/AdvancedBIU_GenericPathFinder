//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler : public ClientHandler {
private:
    Solver<string, string> *solver;
    CacheManager<string, string> *manager;
public:
    MyTestClientHandler(Solver<string, string> *solver, CacheManager<string, string> *manager);

    void handleClient(int socketInfo) override;
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H

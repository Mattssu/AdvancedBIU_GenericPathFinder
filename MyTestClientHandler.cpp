//
// Created by lab on 1/9/19.
//

#include "MyTestClientHandler.h"
#include <string>
//
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solver, CacheManager<string, string> *manager) {
    this->manager = manager;
    this->solver = solver;
}

void MyTestClientHandler::handleClient(int socketInfo) {
    //init param
    bool stopRule = true;
    string solution;
    char buffer[1024];
    int n;
    string temp;
    while (stopRule) {
        /* If connection is established then start communicating */
        bzero(buffer, 1024);
        n = read(socketInfo, buffer, 1023);
        string line = string(buffer);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        if (line == "end" || line == "end\n" || line == "end\r\n") {
            stopRule = false;
        } else {
            //Checks if there's an already solution and sends to the client
            if (manager->isSolutionExists(line)) {
                solution = manager->getSolution(line);
                //
                std::cout << line + " 1" << std::endl;
                std::cout << solution + " 1" << std::endl;

            } else {
                temp = line;
                solution = solver->solve(&line);
                line = temp;
                manager->saveSolutionFor(line, solution);
                //
                std::cout << line + " 2" << std::endl;
                std::cout << solution + " 2" << std::endl;
            }
            /* Write a response to the client */
            n = write(socketInfo, solution.c_str(), solution.size());

            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
    }

}

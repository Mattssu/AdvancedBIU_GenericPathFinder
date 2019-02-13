//
// Created by lab on 1/13/19.
//

#include <strings.h>
#include <zconf.h>
#include "PathSearchAlgoHandler.h"

//handles clients
void PathSearchAlgoHandler::handleClient(int socketInfo) {
//init param
    bool stopRule = true;
    string solution;
    char buffer[10240];
    int n;
    string line;
    string temp;
    vector<string> lines;
    int endline;;
    //
    while (stopRule) {
        /* If connection is established then start communicating */
        while (true) {
            bzero(buffer, 10240);
            int n = read(socketInfo, buffer, 10024);
            if (n < 0) {
                perror("other error");
                exit(3);
            }
            temp = string(buffer);
            while (temp.size() != 0) {
                endline = temp.find("\n");
                lines.push_back(temp.substr(0, endline));
                temp.erase(0, endline + 1);
            }
            if (lines[lines.size() - 1] == "end") {
                lines.pop_back();
                break;
            }
        }
        for (string &x : lines) {
            line += x + "\n";
        }
        //cout << line << endl;
        stopRule = false;
        //Checks if there's an already solution and sends to the client
        auto *m = new MatrixProblem(line);
        if (cManager->isSolutionExists(*m)) {
            solution = cManager->getSolution(*m);
            std::cout << line << std::endl;
            std::cout << solution << std::endl;
        } else {
            //cout << "Im in" << endl;
            solution = solver->solve(m);
            cManager->saveSolutionFor(*m, solution);
            //
            std::cout << line << std::endl;
            std::cout << solution << std::endl;
        }
        /* Write a response to the client */
        n = write(socketInfo, solution.c_str(), solution.size());
        delete (m);
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

    }
}
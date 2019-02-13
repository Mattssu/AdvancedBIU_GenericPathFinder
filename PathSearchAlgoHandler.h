//
// Created by lab on 1/13/19.
//

#ifndef MILESTONE2_PATHSEARCHALGOHANDLER_H
#define MILESTONE2_PATHSEARCHALGOHANDLER_H


#include "ClientHandler.h"
#include "MatrixProblem.h"
#include "Solver.h"
#include "CacheManager.h"

class PathSearchAlgoHandler : public ClientHandler {
private:
    Solver<ISearchable<Cell>, string> *solver;
    CacheManager<MatrixProblem, string> *cManager;
public:
    PathSearchAlgoHandler(Solver<ISearchable<Cell>, string> *solver,
                          CacheManager<MatrixProblem, string> *cManager) {
        this->solver = solver;
        this->cManager = cManager;
    }

    void handleClient(int socketInfo) override;

    ~PathSearchAlgoHandler() {
        delete (solver);
        delete (cManager);
    }
};


#endif //MILESTONE2_PATHSEARCHALGOHANDLER_H

#include <iostream>
#include <vector>
#include <zconf.h>
//
#include "ClientHandler.h"
#include "MySerialServer.h"
#include "PathSearchAlgoHandler.h"
#include "SearcherSolver.h"
//
#include "BFS.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "AStar.h"
#include "StringReverser.h"
//
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "SearcherAlgoFactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: <Prog> <Port>" << std::endl;
        return 1;
    }
    int port = atoi(argv[1]);
    //MySerialServer mSS;
    MyParallelServer mSS;
    //client handler
    auto factory = new SearcherAlgoFactory<Cell, string>("AStar");
    auto solver = new SearcherSolver<Cell, string>(factory);
    auto manager = new FileCacheManager<MatrixProblem, string>();
    ClientHandler *cH = new PathSearchAlgoHandler(solver, manager);
    mSS.open(port, cH);
    sleep(5);
    mSS.stop();
    delete (factory);
    //delete (solver);
    //delete (manager);
    delete (cH);
}
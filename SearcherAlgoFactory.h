//
// Created by lab on 1/15/19.
//

#ifndef MILESTONE2_SEARCHERALGOFACTORY_H
#define MILESTONE2_SEARCHERALGOFACTORY_H


#include <string>
#include "ISearcher.h"
#include "AStar.h"
#include "BFS.h"
#include "BestFirstSearch.h"
#include "DFS.h"

template<class Problem, class Solution>
class SearcherAlgoFactory {
private:
    std::string type;
    ISearcher<Problem, Solution> *algo = nullptr;
public:
    SearcherAlgoFactory(std::string type) {
        this->type = type;
    }

    ISearcher<Problem, Solution> *getSearcher() {
        if (type == "AStar") {
            algo = new AStar<Problem, Solution>();
            return algo;
        }
        if (type == "BFS") {
            algo = new BFS<Problem, Solution>();
            return algo;
        }
        if (type == "BestFirstSearch") {
            algo = new BestFirstSearch<Problem, Solution>();
            return algo;
        }
        if (type == "DFS") {
            algo = new DFS<Problem, Solution>();
            return algo;
        }
    }

    ~SearcherAlgoFactory() {
        delete (algo);
    }
};


#endif //MILESTONE2_SEARCHERALGOFACTORY_H

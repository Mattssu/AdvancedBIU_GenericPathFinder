//
// Created by Elinor on 12/01/2019.
//

#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "ISearcher.h"
#include "PathSearchAlgo.h"
#include <queue>
#include <vector>

using namespace std;

template<class StateType, class Solution>
class BFS : public PathSearchAlgo<StateType, Solution> {
private :
    int counter = 0;
public:
    BFS() = default;

    Solution Search(ISearchable<StateType> *searchable) override {
        State<StateType> *initState = searchable->getInitialState();
        State<StateType> *goal = searchable->getGoalState();
        counter++;
        //TODO check if need as pointer .
        queue<State<StateType> *> theQueue;
        initState->hasVisited();
        theQueue.push(initState);
        while (!theQueue.empty()) {
            State<StateType> *node = theQueue.front();
            theQueue.pop();
            //TODO fix it
            if (searchable->equals(goal, node)) {
                return PathSearchAlgo<StateType, Solution>::backTrace(node);
            }
            vector<State<StateType> *> *vec = searchable->getAllPossibleStates(node);
            if (vec == nullptr) {
                continue;
            }
            for (State<StateType> *state: *vec) {
                if (!state->getVisited()) {
                    counter++;
                    state->hasVisited();
                    state->setCameFrom(node);
                    searchable->locateDirection(state, node);
                    theQueue.push(state);
                }
            }
        }
        // if we get to here we will return nullptr.
        return "-1";
    }

    int getNumberOfNodesEvaluated() override {
        return counter;
    }

    ~BFS() = default;
};


#endif //MILESTONE2_BFS_H

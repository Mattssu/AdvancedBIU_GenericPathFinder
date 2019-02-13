//
// Created by Elinor on 11/01/2019.
//

#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "ISearcher.h"
#include "PathSearchAlgo.h"
#include <stack>

using namespace std;

template<class StateType, class Solution>
class DFS : public PathSearchAlgo<StateType, Solution> {
    int counter = 0;
public:

    DFS() = default;

    Solution Search(ISearchable<StateType> *searchable) override {
        State<StateType> *initState = searchable->getInitialState();
        State<StateType> *goal = searchable->getGoalState();
        counter++;
        //TODO check if need as pointer .
        stack<State<StateType> *> theStack;
        initState->hasVisited();
        theStack.push(initState);
        while (!theStack.empty()) {
            State<StateType> *node = theStack.top();
            theStack.pop();
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
                    theStack.push(state);
                }
            }
        }
        // if we get to here we will return nullptr.
        return "-1";
    }

    int getNumberOfNodesEvaluated() override {
        return counter;
    }

    ~DFS() = default;
};


#endif //MILESTONE2_DFS_H

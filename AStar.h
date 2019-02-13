//
// Created by lab on 1/12/19.
//

#ifndef MILESTONE2_ASTARALGO_H
#define MILESTONE2_ASTARALGO_H


#include <unordered_set>
#include <queue>
#include <math.h>
#include "ISearcher.h"
#include "PathSearchAlgo.h"


using namespace std;

template<class StateType>
struct compareHeur {
    bool operator()(const State<StateType> *a, const State<StateType> *b) {
        return (a->getFScore() + a->getParentCost() + a->getCost() >
                (b->getFScore() + b->getParentCost() + b->getCost()));
    }
};

template<class StateType, class Solution>
class AStar : public PathSearchAlgo<StateType, Solution> {
private :
    //OPEN - Priority queue , CLOSED - Hash set
    priority_queue<State<StateType> *, vector<State<StateType> *>, compareHeur<StateType>> *
            openQueue = new std::priority_queue<State<StateType> *, vector<State<StateType> *>,
                    compareHeur<StateType>>();
    unordered_set<State<StateType> *> *closed = new unordered_set<State<StateType> *>();
    int nodesCounter = 0;

    double getHeuristic(State<StateType> *curr, State<StateType> *finish) {
        return curr->getHeuristic(*finish);
    }

public:
    AStar() = default;

    Solution Search(ISearchable<StateType> *searchable) {
        //Algorithm
        openQueue->push(searchable->getInitialState());
        State<StateType> *goal = searchable->getGoalState();
        //goes till queue is empty
        while (!openQueue->empty()) {
            State<StateType> *n = getOpenTop();
            //nodesCounter++;
            //n->setHeuristic(heuristic(n, searchable->getGoalState()));
            n->setHeuristic(*goal);
            //add one more to counter
            closed->insert(n);
            if (searchable->IsGoalState(n)) {
                //if is goal
                return PathSearchAlgo<StateType, Solution>::backTrace(n);
            }
            //creates the son nodes
            vector<State<StateType> *> *succerssors = searchable->getAllPossibleStates(n);
            if (succerssors == nullptr) {
                continue;
            }
            for (State<StateType> *state : *succerssors) {
                //number of nodes
                //nodesCounter++;
                //if is not in CLOSED && not in OPEN
                if (!openContains(state) && !closedContains(state)) {
                    //sets where it came from and insert to OPEN
                    state->setCameFrom(n);
                    searchable->locateDirection(state, n);
                    openQueue->push(state);
                } else {
                    //if is in CLOSED
                    if (closedContains(state)) {
                        continue;
                    }
                    //if new state cost is less then top cost
                    auto temp = getOpenTop();
                    nodesCounter++;
                    if (temp->getCost() + temp->getParentCost() <
                        n->getCost() + n->getParentCost()) {
                        state->setCameFrom(n);
                        searchable->locateDirection(state, n);
                        openQueue->push(state);
                        openQueue->push(temp);
                    } else {
                        openQueue->push(temp);
                    }
                }
            }
        }
        //could not find
        return "-1";
    }

    int getNumberOfNodesEvaluated() {
        return nodesCounter;
    }

    //UTILS

    State<StateType> *getOpenTop() {
        auto temp = openQueue->top();
        openQueue->pop();
        return temp;
    }

    bool openContains(State<StateType> *s) {
        auto temp = *openQueue;
        while (!temp.empty()) {
            if (s == temp.top()) {
                return true;
            }
            temp.pop();
        }
        return false;
    }

    void updateOpenList(State<StateType> *s, double val) {
        s->setParentCost(val);
        openQueue->push(s);
    }

    //set funcs

    bool closedContains(State<StateType> *s) {
        return closed->count(s) > 0;
    }

    ~AStar() {
        delete (openQueue);
        delete (closed);
    }
};


#endif //MILESTONE2_ASTARALGO_H

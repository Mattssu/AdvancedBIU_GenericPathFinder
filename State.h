//
// Created by Elinor on 09/01/2019.
//

#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

#include <string>

using namespace std;

template<class T>
class State {
    T state;
    double cost = 0;
    double parentCost = 0;
    double fScore = 0;
    State<T> *cameFrom = nullptr;
    bool visited;
    string direction;
public :

    State(T state, double cost, State<T> *cameFrom) :
            state(state),
            cost(cost),
            cameFrom(cameFrom) {
        if (cameFrom != nullptr) {
            parentCost = cameFrom->getCost();
        }
        visited = false;
    }

    //BASICS

    T getState() const {
        return state;
    }


    double getCost() const {
        return cost;
    }


    State<T> *getCameFrom() {
        return cameFrom;
    }

    void setState(T state) {
        State::state = state;
    }

    void setCost(double cost) {
        State::cost = cost;
    }

    void setParentCost(double cost) {
        State::parentCost = cost;
    }

    double getFScore() const {
        return fScore;
    }

    void setHeuristic(const State<T> &other) {
        fScore = state.getHeuristic(other.getState()) + cost;
    }

    double getHeuristic(const State<T> &other) const {
        return state.getHeuristic(other.getState());
    }


    void setCameFrom(State<T> *cameFrom) {
        this->cameFrom = cameFrom;
        if (cameFrom != nullptr) {
            parentCost = cameFrom->getCost() + cameFrom->getParentCost();
        }
    }

    //ADDONS


    string getDirection() {
        return direction;
    }

    void setDirection(string newDirection) {
        this->direction = newDirection;
    }

    bool getVisited() {
        return visited;
    }

    void hasVisited() {
        visited = true;
    }

    double getParentCost() const {
        return parentCost;
    }

    //OVERLOADS

    bool operator>(const State<T> &other) const {
        return cost + parentCost > other.cost + other.parentCost;
    }

    bool operator<(const State<T> &other) const {
        return cost + parentCost < other.cost + other.parentCost;
    }

    //Destructor

    ~State() = default;

};

#endif //MILESTONE2_STATE_H
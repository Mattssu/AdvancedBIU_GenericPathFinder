//
// Created by Elinor on 09/01/2019.
//

#ifndef MILESTONE2_SEARVHABLE_H
#define MILESTONE2_SEARVHABLE_H

#include "State.h"
#include <vector>

// TODO Check if we need template for ISearchable. <State<T>>
// TODO CHECK IT BECAUSE THE TEMPLATE IS USED IN STATE.
template<class T>
class ISearchable {
    // the search method.
public:
    virtual State<T> *getInitialState() = 0;

    virtual State<T> *getGoalState() = 0;

    virtual bool IsGoalState(State<T> *state) = 0;

    virtual std::vector<State<T> *> *getAllPossibleStates(State<T> *state) = 0;

    virtual bool equals(State<T> *s1, State<T> *s2) = 0;

    virtual void locateDirection(State<T> *child, State<T> *parent) = 0;
};

#endif //MILESTONE2_SEARVHABLE_H

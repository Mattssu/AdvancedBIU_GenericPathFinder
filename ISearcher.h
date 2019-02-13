//
// Created by Elinor on 09/01/2019.
//

#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H

#include "ISearchable.h"

// TODO CHECK THE TEMPLATE .
template<class StateType, class Solution>
class ISearcher {
    // The Algo
public :
    //TODO check if need pointer.
    virtual Solution Search(ISearchable<StateType> *searchable) = 0;

    virtual int getNumberOfNodesEvaluated() = 0;

    virtual ~ISearcher() = default;
};


#endif //MILESTONE2_SEARCHER_H

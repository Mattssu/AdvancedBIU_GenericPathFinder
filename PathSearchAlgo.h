//
// Created by Elinor on 10/01/2019.
//

#ifndef MILESTONE2_ABSEARCHABLE_H
#define MILESTONE2_ABSEARCHABLE_H

#include "ISearcher.h"

template<class StateType, class Solution>
class PathSearchAlgo : public ISearcher<StateType, Solution> {
public:
    virtual Solution Search(ISearchable<StateType> *searchable) = 0;

    virtual int getNumberOfNodesEvaluated() = 0;

    string backTrace(State<StateType> *v) {
        vector<string> vec;
        double cash = 0;
        string result;
        while (v != nullptr) {
            vec.push_back(v->getDirection());
            cash += v->getCost();
            v = v->getCameFrom();
        }
        // now we need to rev the vec.
        while (!vec.empty()) {
            result += vec.back() + ",";
            vec.pop_back();
        }
        result = result.substr(1, result.size() - 1);
        cout << this->getNumberOfNodesEvaluated() << endl;
        cout << cash << endl;
        return result;
    }

    virtual ~PathSearchAlgo() = default;
};


#endif //MILESTONE2_ABSEARCHABLE_H

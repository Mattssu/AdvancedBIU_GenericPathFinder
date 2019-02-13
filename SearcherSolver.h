//
// Created by lab on 1/13/19.
//

#ifndef MILESTONE2_SOLVERSEARCHER_H
#define MILESTONE2_SOLVERSEARCHER_H


#include "Solver.h"
#include "ISearcher.h"
#include "SearcherAlgoFactory.h"

template<class Problem, class Solution>
class SearcherSolver : public Solver<ISearchable<Problem>, Solution> {
private:
    SearcherAlgoFactory<Problem, Solution> *s;
public:
    SearcherSolver(SearcherAlgoFactory<Problem, Solution> *i) {
        this->s = i;
    }

    Solution solve(ISearchable<Problem> *problem) override {
        return s->getSearcher()->Search(problem);
    }

    ~SearcherSolver() = default;
};


#endif //MILESTONE2_SOLVERSEARCHER_H

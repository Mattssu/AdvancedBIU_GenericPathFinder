//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

//we want them to be generic
template<class Problem, class Solution>

class Solver {
public:
    virtual Solution solve(Problem *problem) = 0;

    virtual ~Solver() = default;
};

#endif //MILESTONE2_SOLVER_H

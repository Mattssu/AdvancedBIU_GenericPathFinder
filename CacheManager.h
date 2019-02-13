//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

template<class Problem, class Solution>
class CacheManager {
public:

    virtual bool isSolutionExists(Problem p) = 0;

    virtual Solution getSolution(Problem p) = 0;

    virtual void saveSolutionFor(Problem p, Solution s) = 0;

    virtual ~CacheManager() = default;
};


#endif //MILESTONE2_CACHEMANAGER_H

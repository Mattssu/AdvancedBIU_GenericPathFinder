//
// Created by lab on 1/9/19.
//

#include "StringReverser.h"
#include <algorithm>

string StringReverser::solve(string *problem) {
    reverse(problem->begin(), problem->end());
    return *problem;
}

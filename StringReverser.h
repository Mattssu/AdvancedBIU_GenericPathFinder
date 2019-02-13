//
// Created by lab on 1/9/19.
//

#ifndef MILESTONE2_STRINGREVERSER_H
#define MILESTONE2_STRINGREVERSER_H

#include <iostream>
#include "Solver.h"

using namespace std;


class StringReverser : public Solver<string, string> {
public:
    StringReverser() = default;

    ~StringReverser() = default;

    string solve(string *problem);
};


#endif //MILESTONE2_STRINGREVERSER_H

//
// Created by Elinor on 10/01/2019.
//

#ifndef MILESTONE2_MATRIXPROBLEM_H
#define MILESTONE2_MATRIXPROBLEM_H

#include "ISearchable.h"
#include <vector>
#include <math.h>

using namespace std;


//Matrix Cell/Block
class Cell {
private:
    int i;
    int j;
public :
    Cell(int i, int j) {
        this->i = i;
        this->j = j;
    }

    int getI() const {
        return i;
    }

    int getJ() const {
        return j;
    }

    //OVERLOADS

    bool operator==(const Cell &other) const {
        return this->i == other.i && this->j == other.j;
    }

    double getHeuristic(const Cell &other) const {
        return sqrt(pow(j - other.getJ(), 2) + pow(i + other.getI(), 2));
    }

    //
    ~Cell() = default;

};


class MatrixProblem : public ISearchable<Cell> {
private:
    vector<vector<State<Cell>>> arr;
    State<Cell> *beginState;
    State<Cell> *goalState;
    int length;
    int height;
public:
    MatrixProblem() = default;

    MatrixProblem(string &clientInput) {
        MatrixCreator(clientInput);
    }

    void MatrixCreator(string maze);

    State<Cell> *getInitialState() override;

    State<Cell> *getGoalState() override;

    bool IsGoalState(State<Cell> *state) override;

    std::vector<State<Cell> *> *getAllPossibleStates(State<Cell> *state) override;

    bool equals(State<Cell> *s1, State<Cell> *s2) override;

    void locateDirection(State<Cell> *child, State<Cell> *parent) override;

    //OVERLOADS

    bool operator<(const MatrixProblem &other) const {
        return length < other.length;
    }


    bool operator==(const MatrixProblem &other) const {
        if (this->height == other.height && this->length == other.length) {
            if (beginState == other.beginState && goalState == other.goalState) {
                return true;
            }
        }
        return false;
    }

    friend istream &operator>>(istream &in, MatrixProblem &mat);

    friend ostream &operator<<(ostream &out, MatrixProblem &mat);

    //destructor

    ~MatrixProblem() = default;
};


#endif //MILESTONE2_MATRIXPROBLEM_H

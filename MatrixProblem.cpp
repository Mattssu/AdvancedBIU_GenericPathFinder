//
// Created by Elinor on 10/01/2019.
//

#include <string>
#include <sstream>
#include "MatrixProblem.h"

State<Cell> *MatrixProblem::getInitialState() {
    return beginState;
}

State<Cell> *MatrixProblem::getGoalState() {
    return goalState;
}

vector<string> split(string s, char delim) {
    vector<string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void MatrixProblem::MatrixCreator(string maze) {
    //init matrix
    vector<vector<State<Cell>>> matrix;
    //get each line
    vector<string> lines = split(maze, '\n');
    vector<string> temp;
    vector<State<Cell>> row;
    bool inFlag = false;
    int i = 0;
    //takes a string line -> to a vector row
    for (string &line : lines) {
        //matrix value
        temp = split(line, ',');
        int j = 0;
        //matrix in and out states
        if (temp.size() == 2) {
            State<Cell> *c = new State<Cell>(Cell(stoi(temp[0]), stoi(temp[1])),
                                             matrix[stoi(temp[0])][stoi(temp[1])].getCost(), nullptr);
            //sets the in and out states
            if (!inFlag) {
                //sets the init State and its location

                beginState = c;
                inFlag = true;
                //
                //delete (c1);
            } else {
                //TODO add error msg if wrong index
                //sets the goal State and its location

                goalState = c;
                //
            }
            //delete (c);
            continue;
        }
        for (string &x : temp) {
            Cell *cell = new Cell(i, j);
            auto *curr = new State<Cell>(*cell, stod(x), nullptr);
            row.push_back(*curr);
            ++j;
            //clean up
            //delete (cell);
            //delete (curr);
        }
        //
        matrix.push_back(row);
        row.clear();
        ++i;
    }
    this->arr = matrix;
    // row length
    length = static_cast<int>(arr[0].size());
    height = static_cast<int>(arr.size());
}

bool MatrixProblem::IsGoalState(State<Cell> *state) {
    return (equals(state, this->getGoalState()));
}

vector<State<Cell> *> *MatrixProblem::getAllPossibleStates(State<Cell> *state) {
    int row = static_cast<int>(arr[0].size() - 1); // N-1
    int col = height - 1;
    //TODO
    int i = state->getState().getI();
    int j = state->getState().getJ();
    auto *vec = new vector<State<Cell> *>;
    bool bugFlag = false;
    //bug fix
    if (state->getCameFrom() == nullptr) {
        //do it temporary
        state->setCameFrom(state);
        state->setParentCost(0);
        bugFlag = true;
    }
    // up
    if (i != 0) {
        if (arr[i - 1][j].getCost() == -1) {
            //get out
        } else if (!equals(state->getCameFrom(), &arr[i - 1][j])) {
            //arr[x - 1][y].setDirection("UP");
            vec->push_back(&arr[i - 1][j]);
        }
    }
    // down
    if (i != col) {
        if (arr[i + 1][j].getCost() == -1) {
            //get out
        } else if (!equals(state->getCameFrom(), &arr[i + 1][j])) {
            //arr[x + 1][y].setDirection("DOWN");
            vec->push_back(&arr[i + 1][j]);
        }
    }
    //left
    if (j != 0) {
        if (arr[i][j - 1].getCost() == -1) {
            //get out
        } else if (!equals(state->getCameFrom(), &arr[i][j - 1])) {
            //arr[x][y - 1].setDirection("LEFT");
            vec->push_back(&arr[i][j - 1]);
        }
    }
    // right
    if (j != row) {
        if (arr[i][j + 1].getCost() == -1) {
            //get out
        } else if (!equals(state->getCameFrom(), &arr[i][j + 1])) {
            //arr[x][y + 1].setDirection("RIGHT");
            vec->push_back(&arr[i][j + 1]);
        }
    }
    //return to regular
    if (bugFlag) {
        state->setCameFrom(nullptr);
    }
    //dead end
    if (vec->empty()) {
        return nullptr;
    }
    auto *newVec = vec;
    //delete (vec);
    return newVec;
}

bool MatrixProblem::equals(State<Cell> *s1, State<Cell> *s2) {
    return ((s1->getState() == s2->getState()));
}

//DIRECTION

void MatrixProblem::locateDirection(State<Cell> *child, State<Cell> *parent) {
    if (child->getState().getI() == parent->getState().getI()) {
        if (child->getState().getJ() < parent->getState().getJ()) {
            child->setDirection("LEFT");
        } else {
            child->setDirection("RIGHT");
        }
    } else {
        if (child->getState().getI() < parent->getState().getI()) {
            child->setDirection("UP");
        } else {
            child->setDirection("DOWN");
        }
    }
}

//OVERLOADING for CACHE

std::istream &operator>>(std::istream &in, MatrixProblem &mat) {
    string temp;
    in >> temp;
    mat.length = stoi(temp);
    in >> temp;
    mat.height = stoi(temp);
    //
    int mLength = mat.length;
    int mHeight = mat.height;
    //mLength *= mHeight;
    int row, column;
    double cost;
    vector<State<Cell>> v;
    //Read each state
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mLength; ++j) {
            in >> temp;
            column = stoi(temp);
            in >> temp;
            row = stoi(temp);
            in >> temp;
            cost = stod(temp);
            Cell *c = new Cell(column, row);
            //
            State<Cell> *s = new State<Cell>(*c, cost, nullptr);
            v.push_back(*s);
            //leaks
            delete (c);
            delete (s);
        }
        mat.arr.push_back(v);
        v.clear();
    }
    //the init state
    in >> temp;
    column = stoi(temp);
    in >> temp;
    row = stoi(temp);
    in >> temp;
    cost = stod(temp);
    State<Cell> *c1 = new State<Cell>(Cell(column, row), cost, nullptr);
    mat.beginState = c1;
    delete (c1);
    //the goal state
    in >> temp;
    column = stoi(temp);
    in >> temp;
    row = stoi(temp);
    in >> temp;
    cost = stod(temp);
    State<Cell> *c2 = new State<Cell>(Cell(column, row), cost, nullptr);
    mat.goalState = c2;
    delete (c2);

    return in;
}

ostream &operator<<(ostream &out, MatrixProblem &mat) {
    //Save the length for the reader to check how much to read
    out << mat.length << endl;
    out << mat.height << endl;
    //saves states in matrix
    for (vector<State<Cell>> &c : mat.arr) {
        for (State<Cell> &cell : c) {
            out << cell.getState().getI() << endl;
            out << cell.getState().getJ() << endl;
            out << cell.getCost() << endl;
            //out << cell.getParentCost() << endl;
        }
    }
    // in state
    out << mat.beginState->getState().getI() << endl;
    out << mat.beginState->getState().getJ() << endl;
    out << mat.beginState->getCost() << endl;
    //out state
    out << mat.goalState->getState().getI() << endl;
    out << mat.goalState->getState().getJ() << endl;
    out << mat.goalState->getCost() << endl;
    return out;
}

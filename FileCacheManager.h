//
// Created by lab on 1/13/19.
//

#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H


#include "CacheManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <mutex>

//mutex
std::mutex mtx;
using namespace std;

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    map<Problem, Solution> cache;
public:
    FileCacheManager() {
        cache = map<Problem, Solution>();
        ifstream data;
        string problem;
        string solution;
        string changeString;
        string temp;
        int counter = 0;
        data.open("fileCache.txt");

        if (data.is_open()) {
            while (getline(data, temp)) {
                changeString += temp + "\n";
                if (temp == "$") {
                    ++counter;
                }
            }
            istringstream prob(changeString);
            Problem pr;
            Solution sl;
            for (int i = 0; i < counter; ++i) {
                prob >> pr;
                prob >> sl;
                prob >> temp;
                cache.insert(pair<Problem, Solution>(pr, sl));
            }
            data.close();
        }
    }

    bool isSolutionExists(Problem p) {
        mtx.lock();
        //check if the problem is in the map
        typename map<Problem, Solution>::iterator it = cache.begin();
        while (it != cache.end()) {
            if (it->first == p) {
                mtx.unlock();
                return true;
            }
            it++;
        }
        mtx.unlock();
        return false;
    }

    Solution getSolution(Problem problem) {
        mtx.lock();
        std::cout << "Used Saved Solution" << std::endl;
        Solution sol = cache.find(problem)->second;
        mtx.unlock();
        return sol;
    }

    void saveSolutionFor(Problem p, Solution s) {
        //
        mtx.lock();
        cache.insert(std::pair<Problem, Solution>(p, s));
        //
        ofstream myfile;
        myfile.open("fileCache.txt", std::ios_base::app);
        //insert into map
        //myfile << "\n";
        myfile << p << s << "\n$" << endl;
        myfile.close();
        mtx.unlock();
    }

    ~FileCacheManager() = default;
};


#endif //MILESTONE2_FILECACHEMANAGER_H

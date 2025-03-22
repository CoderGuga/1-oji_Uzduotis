#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <exception>
#include <random>
#include <sstream>
#include <list>
#include <deque>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::getline;
using namespace std::chrono;
using std::sort;
using std::optional;
using std::stringstream;
using std::list;
using std::deque;

extern int MAX_GRADES;

struct Stud {
    std::string pavarde;
    std::string vardas;
    int egz;
    vector<int> ndVector;
    int* nd;
    int nd_count;
    float galutinisVid;
    float galutinisMed;

    Stud();
    ~Stud();
};

#endif // HELPER_H
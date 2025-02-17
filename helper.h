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

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std:: ofstream;
using std::cerr;
using std::getline;
using namespace std::chrono;

int MAX_GRADES = 10;

struct Stud {
    std::string pavarde = "Pavardenis";
    std::string vardas = "Vardenis";
    int egz = 10;
    vector <int> ndVector;
    int* nd; // dynamically allocated array for grades
    int nd_count = 0;
    float galutinisVid;
    float galutinisMed;
};



#endif // HELPER_H
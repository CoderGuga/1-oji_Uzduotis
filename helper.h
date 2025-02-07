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

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct Stud {
    std::string pavarde = "Pavardenis";
    std::string vardas = "Vardenis";
    int egz = 10;
    std::vector<int> nd;
};

template <typename T>
std::optional<T> string_to(const std::string & s)
{
    T value;
    std::istringstream ss(s);
    if ((ss >> value) && (ss >> std::ws).eof()) { // attempt the conversion
        return value; // success
    } else {
        return std::nullopt; // failure
    }
}

int TypeInt(const std::string& text, int max = 0);
std::string TypeString(const std::string& prompt);

#endif // HELPER_H
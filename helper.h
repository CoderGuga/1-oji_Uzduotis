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

int MAX_GRADES = 10;

struct Stud {
    std::string pavarde = "Pavardenis";
    std::string vardas = "Vardenis";
    int egz = 10;
    vector <int> ndVector;
    int* nd; // dynamically allocated array for grades
    int nd_count = 0;
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


string GenName()
{
    const std::string names[] = {"Jonas", "Petras", "Antanas", "Kazys", "Vytautas", "Tomas", "Marius", "Andrius", "Darius", "Saulius"};
    int index = rand() % (sizeof(names) / sizeof(names[0]));
    return names[index];
}

string GenSurname()
{
    const std::string surnames[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Takelis", "Tomaitis", "Andraitis"};
    int index = rand() % (sizeof(surnames) / sizeof(surnames[0]));
    return surnames[index];
}

int RandInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

#endif // HELPER_H
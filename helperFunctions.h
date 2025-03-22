#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "helper.h"

template <typename T>
optional<T> string_to(const string & s);

int RandInt(int min, int max);
int RandIntWSeed(int min, int max, std::mt19937 generator);
int CheckInt(const string& text, int max = 0);
int TypeInt(const string& text, int max = 0);
string TypeString(const string& prompt);
double Median(vector<int> numbers);
double Average(vector<int> numbers);
string GenName();
string GenSurname();
void GenFile(string filename, int amount);
void GenFiles();
int CountWordsInLine(const string& line);
void Pause();

#endif // HELPFUNCTIONS_H
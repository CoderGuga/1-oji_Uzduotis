#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "helper.h"

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

int RandInt(int min, int max)
{
    // Use the current time as a seed for the random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister engine
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int CheckInt(const string& text, int max = 0)
{
    cout << text;
    while (true)
    {
        //cout << "Iveskite sveikaji skaiciu: ";
        string input;
        cin >> input;
        try {
            auto result = string_to<int>(input);
            if (result) {
                if (max == 0 || result <= max)
                    return *result;
                else
                    cout<< "Per didelis skaicius"<<endl;
            } else {
                throw std::invalid_argument("Neteisinga ivestis");
            }
        } catch (const std::invalid_argument&) {
            cout << "Ivestas ne sveikas skaicius. Bandykite dar karta." << endl;
        } catch (const std::exception& e) {
            cerr << "Klaida: " << e.what() << endl;
        }
    }
}

int TypeInt(const string& text, int max = 0)
{
    cout << text;
    string input;
    while (true)
    {
        cin >> input;
        auto result = string_to<int>(input);
        if (result) {
            if (max == 0 || result <= max)
                return *result;
            else
                cout<< "Per didelis skaicius"<<endl;
        } else {
            cout << "Irasykite sveika skaiciu" << endl;
        }
    }
}

std::string TypeString(const string& prompt)
{
    string output;
    cout << prompt;
    while (!(cin >> output)) {
        cin.clear(); // clear the error flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a valid string: ";
    }
    return output;
}

double Median(vector<int> numbers)
{
    vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    double median;
    if (sorted.size() % 2 == 0)
        median = (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
    else
        median = sorted[sorted.size() / 2];

    return median;
}

double Average(vector<int> numbers)
{
    double sum = 0;
    for (int grade : numbers) {
        sum += grade;}
    double average = sum / numbers.size();

    return average;
}

#endif
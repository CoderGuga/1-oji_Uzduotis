#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

int CountWordsInLine(const std::string& line)
{
    std::istringstream stream(line);
    std::string word;
    int count = 0;
    while (stream >> word) {
        ++count;
    }
    return count;
}

void ReadFromFile(vector<Stud>& students, const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    // Skip the first line
    if (std::getline(file, line)) {
        // First line is skipped
    }

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        Stud student;
        stream >> student.vardas >> student.pavarde;

        int grade;
        student.ndVector.clear();
        while (stream >> grade) {
            student.ndVector.push_back(grade);
        }

        // The last element in ndVector is actually the egz score
        if (!student.ndVector.empty()) {
            student.egz = student.ndVector.back();
            student.ndVector.pop_back();
            students.push_back(student);
        }

        
    }

    file.close();

}

void WriteToFile(const vector<Stud>& students, const string& filename)
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Write the header line
    file << std::left << std::setw(15) << "Vardas"
         << std::setw(15) << "Pavarde"
         << std::setw(15) << "Galutinis (Vid.)"
         << std::setw(15) << "Galutinis (Med.)"
         << endl;
    file << "-------------------------------------------------------------" << endl;

    // Write each student's data
    for (const auto& student : students) {
        file << std::left << std::setw(15) << student.vardas
             << std::setw(15) << student.pavarde;

        file << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisVid
             << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisMed
             << endl;
    }

    file.close();
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
    double sum = 0, average;
    for (int grade : numbers) {
    sum += grade; 
    }
    average = sum / numbers.size();
}

void SortOutput(string sortType, vector<Stud> students)
{
    if (sortType == "vardas") {
        std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
            return a.vardas < b.vardas;
        });
    } else if (sortType == "pavarde") {
        std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
            return a.pavarde < b.pavarde;
        });
    } else if (sortType == "vidurkis") {
        std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
            return a.galutinisVid < b.galutinisVid;
        });
    } else if (sortType == "mediana") {
        std::sort(students.begin(), students.end(), [](const Stud& a, const Stud& b) {
            return a.galutinisMed < b.galutinisMed;
        });
    }
}



#endif
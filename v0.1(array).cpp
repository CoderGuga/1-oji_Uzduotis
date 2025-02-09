#include "helper.h"

using namespace std;

const int MAX_STUDENTS = 10;

int TypeInt(const string& text, int max)
{
    cout << text;
    string input;
    while (true)
    {
        cin >> input;
        auto result = string_to<int>(input);
        if (result) {
            if (max == 0 || (result <= max && result > 0))
                return *result;
            else
                cout<< "Per didelis skaicius"<<endl;
        } else {
            cout << "Irasykite sveika skaiciu" << endl;
        }
    }
}

string TypeString(const string& prompt)
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
    return rand() % max + min;
}

int main()
{
    srand(time(0)); // Initialize random seed

    int stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba: ", 4);
    Stud students[MAX_STUDENTS];
    int student_count = 0;

    while ((stCon == 1 || stCon == 2 || stCon == 3) && student_count < MAX_STUDENTS)
    {
        Stud student;
        student.vardas = (stCon == 3) ? GenName() : TypeString("Studento vardas: ");
        student.pavarde = (stCon == 3) ? GenSurname() : TypeString("Studento pavarde: ");
        student.egz = (stCon == 1) ? TypeInt("Egzamino pazymys: ", 10) : RandInt(1, 10);
        student.nd_count = 0;

        string ndCon = TypeString("sukurti nauja namu darbo pazymi? Iveskite 'y', kad sukurtumete ");
        while (ndCon == "y" && student.nd_count < MAX_GRADES)
        {
            student.nd[student.nd_count++] = (stCon == 1) ? TypeInt("Namu darbo pazymys: ", 10) : RandInt(1, 10);
            ndCon = TypeString("sukurti nauja namu darbo pazymi? Iveskite 'y', kad sukurtumete ");
        }
        students[student_count++] = student;

        stCon = TypeInt("1 - ranka irasyti, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba: ");
    }

    string type;
    cout << "Pazymio isvedimo tipas? (Vidurkis - v / Mediama - m): ";
    cin >> type;
    while (type != "v" && type != "m")
    {
        cout << "Iveskite 'v' arba 'm': ";
        cin >> type;
    }

    string galutinisTipas;
    if (type == "v")
        galutinisTipas = "Galutinis (Vid.)";
    else
        galutinisTipas = "Galutinis (Med.)";

    cout << std::left << std::setw(15) << "Vardas" 
         << std::setw(15) << "Pavarde" 
         << std::setw(10) << galutinisTipas << endl;
    cout << "-------------------------------------------------------------" << endl;

    // Print the student data
    for (int i = 0; i < student_count; ++i) {
        const Stud& student = students[i];
        double average = 0;
        if (student.nd_count > 0) {
            if (type == "v") {
                double sum = 0;
                for (int j = 0; j < student.nd_count; ++j) {
                    sum += student.nd[j];
                }
                average = sum / student.nd_count;
            } else {
                int sorted_nd[MAX_GRADES];
                std::copy(student.nd, student.nd + student.nd_count, sorted_nd);
                std::sort(sorted_nd, sorted_nd + student.nd_count);
                if (student.nd_count % 2 == 0) {
                    average = (sorted_nd[student.nd_count / 2 - 1] + sorted_nd[student.nd_count / 2]) / 2.0;
                } else {
                    average = sorted_nd[student.nd_count / 2];
                }
            }
        }

        double galutinis = student.egz * 0.6 + average * 0.4;

        cout << std::left << std::setw(15) << student.vardas 
             << std::setw(15) << student.pavarde 
             << std::setw(10) << std::fixed << std::setprecision(2) << galutinis << endl;
    }

    return 0;
}
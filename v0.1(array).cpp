#include "helper.h"

const int INITIAL_STUDENT_CAPACITY = 2;

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

int main()
{
    srand(time(0)); // Initialize random seed

    int stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba: ", 4);
    int student_capacity = INITIAL_STUDENT_CAPACITY;
    Stud* students = new Stud[student_capacity];
    int student_count = 0;

    while ((stCon == 1 || stCon == 2 || stCon == 3))
    {
        if (student_count >= student_capacity) {
            student_capacity *= 2;
            Stud* new_students = new Stud[student_capacity];
            for (int i = 0; i < student_count; ++i) {
                new_students[i] = students[i];
            }
            delete[] students;
            students = new_students;
        }

        Stud student;
        student.vardas = (stCon == 3) ? GenName() : TypeString("Studento vardas: ");
        student.pavarde = (stCon == 3) ? GenSurname() : TypeString("Studento pavarde: ");
        student.egz = (stCon == 1) ? TypeInt("Egzamino pazymys: ", 10) : RandInt(1, 10);
        student.nd_count = TypeInt("Kiek namu darbu pazymiu norite ivesti? ");
        student.nd = new int[student.nd_count];

        for (int i = 0; i < student.nd_count; ++i) {
            student.nd[i] = (stCon == 1) ? TypeInt("Namu darbo pazymys: ", 10) : RandInt(1, 10);
        }

        // Deep copy the student object
        students[student_count].vardas = student.vardas;
        students[student_count].pavarde = student.pavarde;
        students[student_count].egz = student.egz;
        students[student_count].nd_count = student.nd_count;
        students[student_count].nd = new int[student.nd_count];
        for (int i = 0; i < student.nd_count; ++i) {
            students[student_count].nd[i] = student.nd[i];
        }
        student_count++;

        delete[] student.nd; // Free the temporary student's nd array

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
                int* sorted_nd = new int[student.nd_count];
                std::copy(student.nd, student.nd + student.nd_count, sorted_nd);
                std::sort(sorted_nd, sorted_nd + student.nd_count);
                if (student.nd_count % 2 == 0) {
                    average = (sorted_nd[student.nd_count / 2 - 1] + sorted_nd[student.nd_count / 2]) / 2.0;
                } else {
                    average = sorted_nd[student.nd_count / 2];
                }
                delete[] sorted_nd;
            }
        }

        double galutinis = student.egz * 0.6 + average * 0.4;

        cout << std::left << std::setw(15) << student.vardas 
             << std::setw(15) << student.pavarde 
             << std::setw(10) << std::fixed << std::setprecision(2) << galutinis << endl;

        // Free the dynamically allocated memory for nd
        delete[] student.nd;
    }

    // Free the dynamically allocated memory for students
    delete[] students;

    return 0;
}
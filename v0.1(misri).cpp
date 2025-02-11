#include "helper.h"

int TypeInt(const string& text, int max)
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

int main()
{
    srand(time(0)); // Initialize random seed

    int stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba: ", 4);
    vector<Stud> students;
    while (stCon == 1 || stCon == 2 || stCon == 3)
    {
        Stud student;
        student.vardas = (stCon == 3) ? GenName() : TypeString("Studento vardas: ");
        student.pavarde = (stCon == 3) ? GenSurname() : TypeString("Studento pavarde: ");
        student.egz = (stCon == 1) ? TypeInt("Egzamino pazymys: ", 10) : RandInt(1, 10);
        student.nd_count = TypeInt("Kiek namu darbu pazymiu norite ivesti? ");
        student.nd = new int[student.nd_count];
        for (int i = 0; i < student.nd_count; ++i) {
            student.nd[i] = (stCon == 1) ? TypeInt("Namu darbo pazymys: ", 10) : RandInt(1, 10);
        }
        students.push_back(student);  

        stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba: ", 4);
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
    for (const auto& student : students) {
        double average = 0;
        if (!student.ndVector.empty()) {
            if (type == "v") {
                double sum = 0;
                for (int grade : student.ndVector) {
                    sum += grade;
                }
                average = sum / student.ndVector.size();
            } else {
                vector<int> sorted_nd = student.ndVector;
                std::sort(sorted_nd.begin(), sorted_nd.end());
                if (sorted_nd.size() % 2 == 0) {
                    average = (sorted_nd[sorted_nd.size() / 2 - 1] + sorted_nd[sorted_nd.size() / 2]) / 2.0;
                } else {
                    average = sorted_nd[sorted_nd.size() / 2];
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
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
    string stCon = TypeString("sukurti nauja studenta? Iveskite 'y', kad sukurtumete ");
    vector<Stud> students;
    while (stCon == "y")
    {
        Stud student;
        student.vardas = TypeString("Studento vardas: ");
        student.pavarde = TypeString("Studento pavarde: ");
        student.egz = TypeInt("Egzamino pazymys: ", 10);
        string ndCon = TypeString("sukurti nauja namu darbo pazymi? Iveskite 'y', kad sukurtumete ");
        while (ndCon =="y")
        {
            student.ndVector.push_back(TypeInt("Namu darbo pazymys: ", 10));
            ndCon = TypeString("sukurti nauja namu darbo pazymi? Iveskite 'y', kad sukurtumete ");
        }
        students.push_back(student);  

        stCon = TypeString("sukurti nauja studenta? Iveskite 'y', kad sukurtumete ");
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
                for (int grade : student.nd) {
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
#include "helper.h"

int main()
{
    srand(time(0)); // Initialize random seed

    int stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - irasyti duomenis is failo 5 - baigti darba: ", 5);
    vector<Stud> students;

    while (stCon != 5)
    {

        if (stCon == 4){
            string filename;
            cout << "Iveskite failo pavadinima: ";
            cin >> filename;
            ReadFromFile(students, filename);
        }
        
        if (stCon == 1 || stCon == 2 || stCon == 3)
        {
            Stud student;
            student.vardas = (stCon == 3) ? GenName() : TypeString("Studento vardas: ");
            student.pavarde = (stCon == 3) ? GenSurname() : TypeString("Studento pavarde: ");
            student.egz = (stCon == 1) ? TypeInt("Egzamino pazymys: ", 10) : RandInt(1, 10);
            cout << "egzaminas: " << student.egz << endl;
            int nd_count = TypeInt("Kiek namu darbu pazymiu norite ivesti? ");
            student.ndVector.clear();
            student.ndVector.resize(nd_count);
            for (int i = 0; i < nd_count; ++i) {
                int nd = (stCon == 1) ? TypeInt("Namu darbo pazymys: ", 10) : RandInt(1, 10);
                student.ndVector.push_back(nd);
                cout << "namu darbo: " << nd << endl;
            }
            students.push_back(student);  
            student.ndVector.clear();
        }
        
        stCon = TypeInt("1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - irasyti duomenis is failo 5 - baigti darba: ", 5);
        
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
                std::vector<int> sorted_nd = student.ndVector;
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
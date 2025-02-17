#include "functions.h"

int main()
{
    srand(time(0)); // Initialize random seed
    string menu = "1 - ranka irasyti viska, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - irasyti duomenis is failo 5 - baigti darba: ";

    int stCon = TypeInt(menu, 5);
    vector<Stud> students;

    while (stCon != 5)
    {
        if (stCon == 4) {
            string filename;
            cout << "Iveskite failo pavadinima: ";
            cin >> filename;

            auto start = high_resolution_clock::now();
            ReadFromFile(students, filename);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "ReadFromFile function took " << duration.count() << " milliseconds." << endl;
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
                student.ndVector[i] = nd;
                cout << "namu darbo: " << nd << endl;
            }
            students.push_back(student);  
        }
        
        stCon = TypeInt(menu, 5);
    }

    string sortType;
    cout << "Rikiavimo tipas? (Vardas - vardas / Pavarde - pavarde / Galutinis pagal vidurki - vidurkis / Galutinis pagal mediana - mediana): ";
    cin >> sortType;
    while (sortType != "vardas" && sortType != "pavarde" && sortType != "vidurkis" && sortType != "mediana")
    {
        cout << "Iveskite 'vardas', 'pavarde', 'vidurkis' arba 'mediana': ";
        cin >> sortType;
    }

    // Calculate final grades
    for (auto& student : students) {
        double average = 0;
        double median = 0;
        if (!student.ndVector.empty()) {
 
            average = Average(student.ndVector);
            median = Median(student.ndVector);
        }

        student.galutinisVid = student.egz * 0.6 + average * 0.4;
        student.galutinisMed = student.egz * 0.6 + median * 0.4;
    }

    // Sort students based on the user's choice
    SortOutput(sortType, students);

    string outputType;
    cout << "Isvesti i terminala 't', ar faila 'f': ";
    cin >> outputType;
    while (outputType != "t" && outputType != "f")
    {
        cout << "Iveskite 't' arba 'f': ";
        cin >> outputType;
    }
    auto start = high_resolution_clock::now();
    if (outputType == "t")
    {
        string galutinisTipasVid = "Galutinis (Vid.)";
        string galutinisTipasMed = "Galutinis (Med.)";
            
        cout << std::left << std::setw(15) << "Vardas" 
            << std::setw(15) << "Pavarde" 
            << std::setw(15) << galutinisTipasVid 
            << std::setw(15) << galutinisTipasMed << endl;
        cout << "-------------------------------------------------------------" << endl;

        // Print the student data
        for (const auto& student : students) {
            cout << std::left << std::setw(15) << student.vardas 
                << std::setw(15) << student.pavarde 
                << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisVid 
                << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisMed << endl;
        }
    }
    else
        WriteToFile(students, "output.txt");

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Output took " << duration.count() << " milliseconds." << endl;

    return 0;
}
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "helpFunctions.h"

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
    auto start = high_resolution_clock::now();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo (ar teisingai ivedete pavadinima?): " << filename << endl;
        return;
    }

    string line;
    // Skip the first line
    if (std::getline(file, line)) {
        // First line is skipped
    }

    const size_t bufferSize = 8192; // 8 KB buffer size
    vector<char> buffer(bufferSize);
    stringstream ss;

    while (file.read(buffer.data(), bufferSize) || file.gcount() > 0) {
        ss.write(buffer.data(), file.gcount());
    }

    while (std::getline(ss, line)) {
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
            student.galutinisVid = student.egz * 0.6 + Average(student.ndVector) * 0.4;
            student.galutinisMed = student.egz * 0.6 + Median(student.ndVector) * 0.4;
            students.push_back(student);
        }
        
    }

    file.close();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Failo nuskaitymas uztruko " << duration.count() << " sekundes." << endl;
}

void WriteToFile(const vector<Stud>& students, const string& filename)
{
    ofstream file(filename);
    std::ostringstream output;

    auto start = high_resolution_clock::now();

    // Write the header line
    output << std::left << std::setw(15) << "Vardas"
         << std::setw(15) << "Pavarde"
         << std::setw(15) << "Galutinis (Vid.)"
         << std::setw(15) << "Galutinis (Med.)"
         << endl;
    output << "-------------------------------------------------------------" << endl;

    // Write each student's data
    for (const auto& student : students) {
        output << std::left << std::setw(15) << student.vardas
             << std::setw(15) << student.pavarde;

        output << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisVid
             << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisMed
             << endl;
    }

    

    file << output.str();
    file.close();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Irasymas i faila uztruko " << duration.count() << " sekundes." << endl;
}

vector<Stud> SortOutput(string sortType, vector<Stud> students)
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

    return students;
}

void PrintToTerminal(vector<Stud> students)
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

Stud CreateStudent(int stCon)
{
    Stud student;
    student.vardas = (stCon == 3) ? GenName() : TypeString("Studento vardas: ");
    student.pavarde = (stCon == 3) ? GenSurname() : TypeString("Studento pavarde: ");
    student.egz = (stCon == 1) ? CheckInt("Egzamino pazymys: ", 10) : RandInt(1, 10);
    cout << "egzaminas: " << student.egz << endl;
    string con = TypeString("Prideti namu darbp pazymi? y/n  ");
    student.ndVector.clear();
    while (con == "y")
    {
        int nd = RandInt(1, 10);
        nd = (stCon == 1) ? CheckInt("Namu darbu pazymys: ", 10) : RandInt(1, 10);
        if (stCon != 1) cout<<"Pazymis: "<< nd<<endl;
        student.ndVector.push_back(nd);
        con = TypeString("Prideti namu darbp pazymi? y/n  ");
    }
    return student;
}

void GenFile(string filename, int amount)
{
    int ndCount = 15;
    std::ostringstream output;

    auto start = high_resolution_clock::now();

    output << std::left << std::setw(15) << "Vardas"
           << std::setw(15) << "Pavarde";
    for (int i = 1; i <= ndCount; i++)
    {
        output << std::setw(10) << ("ND" + std::to_string(i));
    }
    output << std::setw(10) << "Egz." << endl;
    output << "-------------------------------------------------------------" << endl;
    for (int i = 1; i <= amount; i++)
    {
        output << std::left << std::setw(15) << ("Vardas" + std::to_string(i))
               << std::setw(15) << ("Pavarde" + std::to_string(i));
        for (int j = 1; j <= ndCount; j++)
        {
            output << std::setw(10) << RandInt(1, 10);
        }
        output << std::setw(10) << RandInt(1, 10) << endl;
    }

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Failo generavimas uztruko " << duration.count() << " sekundes." << endl;

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo (ar teisingai ivedete pavadinima?): " << filename << endl;
        return;
    }

    start = high_resolution_clock::now();

    file << output.str();
    file.close();

    duration = high_resolution_clock::now() - start;
    cout << "Irasymas i faila uztruko " << duration.count() << " sekundes." << endl;
}

void SortStudent(vector<Stud>& students, vector<Stud>& islaike, vector<Stud>& neislaike)
{
    auto start = high_resolution_clock::now();
    for (const auto& student : students)
    {
        float galutinis = student.egz * 0.6 + Average(student.ndVector) * 0.4;
        if (galutinis < 5.0)
            neislaike.push_back(student);
        else
            islaike.push_back(student);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << endl;
}

void GenFiles()
{
    cout<<"1 000 studentu"<<endl;
    auto start = high_resolution_clock::now();
    GenFile("1 000 studentu.txt",1000);
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "viskas bendrai uztruko " << duration.count() << " sekundes." << endl;

    cout<<"10 000 studentu"<<endl;
    start = high_resolution_clock::now();
    GenFile("10 000 studentu.txt",10000);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "viskas bendrai uztruko " << duration.count() << " sekundes." << endl;

    cout<<"100 000 studentu"<<endl;
    start = high_resolution_clock::now();
    GenFile("100 000 studentu.txt",100000);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "viskas bendrai uztruko " << duration.count() << " sekundes." << endl;

    cout<<"1 000 000 studentu"<<endl;
    start = high_resolution_clock::now();
    GenFile("1 000 000 studentu.txt",1000000);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "viskas bendrai uztruko " << duration.count() << " sekundes." << endl;

    cout<<"10 000 000 studentu"<<endl;
    start = high_resolution_clock::now();
    GenFile("10 000 000 studentu.txt",10000000);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "viskas bendrai uztruko " << duration.count() << " sekundes." << endl;
}

void DataProccess(string filename)
{
    vector<Stud> students;
    vector<Stud> islaike;
    vector<Stud> neislaike;

    cout<<filename<<endl;

    auto start = high_resolution_clock::now();

    ReadFromFile(students, filename);
    SortStudent(students, islaike, neislaike);
    string islaikeFile = "Islaike" + std::to_string(students.size()) + ".txt";
    string neislaikeFile = "Neislaike" + std::to_string(students.size()) + ".txt";
    WriteToFile(islaike, islaikeFile);
    WriteToFile(neislaike, neislaikeFile);

    students.clear();
    islaike.clear();
    neislaike.clear();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai uztruko " << duration.count() << " sekundes." << endl;
}

void FullDataProccess(string filename1, string filename2, string filename3, string filename4, string filename5)
{
    DataProccess(filename1);
    DataProccess(filename2);
    DataProccess(filename3);
    //DataProccess(filename4);
    //DataProccess(filename5);
}

#endif
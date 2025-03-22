#include "helper.h"
#include "helperFunctions.h"
#include "cFunctions.h"

template <typename Container>
void ReadFromFile(Container& students, const string& filename)
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

template <typename Container>
void WriteToFile(const Container& students, const string& filename)
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
    cout << "Irasymas i faila "<<filename<<" uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
auto SortOutput(const std::string& sortType, Container students) -> Container
{
    if constexpr (std::is_same_v<typename std::iterator_traits<typename Container::iterator>::iterator_category, std::random_access_iterator_tag>) {
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
    } else {
        if (sortType == "vardas") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.vardas < b.vardas;
            });
        } else if (sortType == "pavarde") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.pavarde < b.pavarde;
            });
        } else if (sortType == "vidurkis") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.galutinisVid < b.galutinisVid;
            });
        } else if (sortType == "mediana") {
            students.sort([](const Stud& a, const Stud& b) {
                return a.galutinisMed < b.galutinisMed;
            });
        }
    }

    return students;
}

template <typename Container>
void PrintToTerminal(Container students)
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

template <typename Container>
void SortStudent(Container& students, Container& islaike, Container& neislaike)
{
    auto start = high_resolution_clock::now();
    for (const auto& student : students)
    {
        if (student.galutinisVid < 5.0)
            neislaike.push_back(student);
        else
            islaike.push_back(student);
    }
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Rusiavimas uztruko " << duration.count() << " sekundes." << endl;
}

template <typename Container>
void DataProccess(string filename, string sortType, bool writeToFile = true)
{
    Container students;
    Container islaike;
    Container neislaike;

    cout<<filename<<endl;

    auto start = high_resolution_clock::now();

    ReadFromFile(students, filename);
    SortStudent(students, islaike, neislaike);

    string islaikeFile = "Islaike" + std::to_string(students.size()) + ".txt";
    string neislaikeFile = "Neislaike" + std::to_string(students.size()) + ".txt";

    auto start2 = high_resolution_clock::now();
    islaike = SortOutput(sortType, islaike);
    neislaike = SortOutput(sortType, neislaike);
    std::chrono::duration<double> duration2 = high_resolution_clock::now() - start2;
    cout << "Rikiavimas uztruko " << duration2.count() << " sekundes." << endl;

    if (writeToFile){
    WriteToFile(islaike, islaikeFile);
    WriteToFile(neislaike, neislaikeFile);}

    students.clear();
    islaike.clear();
    neislaike.clear();

    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai uztruko " << duration.count() << " sekundes." << endl;
}

void FullDataProccess(string filename1, string filename2, string filename3, string filename4, string filename5)
{
    string sortType;
    cout << "Rikiavimo tipas? (Vardas - vardas / Pavarde - pavarde / Galutinis pagal vidurki - vidurkis / Galutinis pagal mediana - mediana): ";
    cin >> sortType;
    while (sortType != "vardas" && sortType != "pavarde" && sortType != "vidurkis" && sortType != "mediana")
    {
        cout << "Iveskite 'vardas', 'pavarde', 'vidurkis' arba 'mediana': ";
        cin >> sortType;
    }
    DataProccess<vector<Stud>>(filename1, sortType);
    DataProccess<vector<Stud>>(filename2, sortType);
    DataProccess<vector<Stud>>(filename3, sortType);
    DataProccess<vector<Stud>>(filename4, sortType);
    DataProccess<vector<Stud>>(filename5, sortType);
}

void FullContainerTest(string filename1, string filename2, string filename3, string filename4, string filename5)
{
    string sortType = "vidurkis";
    double vectorTime, listTime, dequeTime = 0;
    int times = 5;

    for (int i = 0; i <= times; i++){
    //vector test
    cout<<"Vector konteinerio testavimas\n ---------------------------------------------------------------------------\n";
    auto start = high_resolution_clock::now();
    DataProccess<vector<Stud>>(filename1, sortType, false);
    DataProccess<vector<Stud>>(filename2, sortType, false);
    DataProccess<vector<Stud>>(filename3, sortType, false);
    DataProccess<vector<Stud>>(filename4, sortType, false);
    DataProccess<vector<Stud>>(filename5, sortType, false);
    std::chrono::duration<double> duration = high_resolution_clock::now() - start;
    cout << "Bendrai vector uztruko " << duration.count() << " sekundes.\n" << endl;
    vectorTime+=duration.count();

    //list test
    cout<<"List konteinerio testavimas\n ---------------------------------------------------------------------------\n";
    start = high_resolution_clock::now();
    DataProccess<list<Stud>>(filename1, sortType, false);
    DataProccess<list<Stud>>(filename2, sortType, false);
    DataProccess<list<Stud>>(filename3, sortType, false);
    DataProccess<list<Stud>>(filename4, sortType, false);
    DataProccess<list<Stud>>(filename5, sortType, false);
    duration = high_resolution_clock::now() - start;
    cout << "Bendrai list uztruko " << duration.count() << " sekundes.\n" << endl;
    listTime+=duration.count();

    //deque test
    cout<<"Deque konteinerio testavimas\n ---------------------------------------------------------------------------\n";
    start = high_resolution_clock::now();
    DataProccess<deque<Stud>>(filename1, sortType, false);
    DataProccess<deque<Stud>>(filename2, sortType, false);
    DataProccess<deque<Stud>>(filename3, sortType, false);
    DataProccess<deque<Stud>>(filename4, sortType, false);
    DataProccess<deque<Stud>>(filename5, sortType, false);
    duration = high_resolution_clock::now() - start;
    cout << "Bendrai deque uztruko " << duration.count() << " sekundes." << endl;
    dequeTime+=duration.count();

    }

    cout << "Vidutiniskai vector uztruko " << vectorTime/times << " sekundes." << endl;
    cout << "Vidutiniskai list uztruko " << listTime/times << " sekundes." << endl;
    cout << "Vidutiniskai deque uztruko " << dequeTime/times << " sekundes." << endl;


}
#include "helper.h"
#include "helperFunctions.h"

template <typename T>
optional<T> string_to(const string & s) {
    stringstream ss(s);
    T result;
    if (ss >> result)
        return result;
    return std::nullopt;
}

int RandInt(int min, int max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int RandIntWSeed(int min, int max, std::mt19937 generator) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int CheckInt(const string& text, int max) {
    cout << text;
    while (true) {
        string input;
        cin >> input;
        try {
            auto result = string_to<int>(input);
            if (result) {
                if (max == 0 || result <= max)
                    return *result;
                else
                    cout << "Per didelis skaicius" << endl;
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

int TypeInt(const string& text, int max) {
    cout << text;
    string input;
    while (true) {
        cin >> input;
        auto result = string_to<int>(input);
        if (result) {
            if (max == 0 || result <= max)
                return *result;
            else
                cout << "Per didelis skaicius" << endl;
        } else {
            cout << "Irasykite sveika skaiciu" << endl;
        }
    }
}

string TypeString(const string& prompt) {
    string output;
    cout << prompt;
    while (!(cin >> output)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid string: ";
    }
    return output;
}

double Median(vector<int> numbers) {
    vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    double median;
    if (sorted.size() % 2 == 0)
        median = (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
    else
        median = sorted[sorted.size() / 2];
    return median;
}

double Average(vector<int> numbers) {
    double sum = 0;
    for (int grade : numbers) {
        sum += grade;
    }
    double average = sum / numbers.size();
    return average;
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

void GenFile(string filename, int amount)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed); // Mersenne Twister engine
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
            output << std::setw(10) << RandIntWSeed(1, 10, generator);
        }
        output << std::setw(10) << RandIntWSeed(1, 10, generator) << endl;
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

void Pause()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
# 1-oji_Uzduotis

v1.0

Pirmojo release rezultatai, naudojant skirtingo tipo konteinerius.

Pirmoji strategija - studentai iš pagrindinio konteinerio išskirstomi į du skirtingus - vieną išlaikiusiems, kitą neišlaikiusiems, tada jie surikiuojami.

![image](https://github.com/user-attachments/assets/9db9261d-3065-4918-8519-ee8cd3256a4a)


Rezultatai gauti naudojant kompiuterį su šiais komponentais:
Processor:	Intel(R) Core(TM) i5-9300H CPU @ 2.40GHz
Memory:   Speed: 2667 MHz, Size: 32 GB
Storage: HDD


Galutinio release rezultatai, naudojant skirtingo tipo konteinerius.

Antroji strategija - iš pagrindinio konteinerio neišlaikiusieji studentai perkeliami į atskirą konteinerį ir ištrinami iš pirmojo naudojant delete funkciją, tokiu būdu išvengiant perteklinio atminties naudojimo ir nereikalingų veiksmų

![image](https://github.com/user-attachments/assets/bd492c4d-6f21-4dc3-b9ab-79384170b1a3)

Trečioji strategija - ta pati, kaip antroji, tačiau studentai skirstomi naudojant partition funkciją, vietoj paprasto if

![image](https://github.com/user-attachments/assets/be7e285a-67b7-4e6d-85be-893f421626ce)


1. Sistemos Reikalavimai

Įsitikinkite, kad turite šias priemones:

Operacinė sistema: Windows, Linux arba macOS

C++ kompiliatorius: GCC (MinGW Windows sistemai), Clang arba MSVC

CMake: 3.10 ar naujesnė versija

Git: 2.0 ar naujesnė versija

Patikrinkite, ar įrankiai įdiegti:

    cmake --version
    gcc --version
    git --version


2. Projekto Atsisiuntimas

  1. Atidarykite terminalą (arba "Command Prompt" Windows sistemoje).

  2. Nukeliaukite į katalogą, kuriame norite atsisiųsti projektą.

    cd /kelias/iki/katalogo

  3. Nukopijuokite projektą iš GitHub naudodami komandą:

    git clone https://github.com/vartotojas/projektas.git

  4. Pereikite į projekto katalogą:
   
    cd projektas


3. Programos Kompiliavimas

  1. Sukurkite "build" katalogą ir pereikite į jį:

    mkdir build && cd build

  2. Paleiskite "CMake" komandą:

    cmake ..

  3. Kompiliuokite programą:

  Windows (naudojant MinGW):

    mingw32-make

  Linux / macOS:
  
    make



4. Programos Paleidimas

  1. Po sėkmingo kompiliavimo, galite paleisti programą:

  Windows:

    ./MyExecutable.exe

  Linux / macOS:
  
    ./MyExecutable

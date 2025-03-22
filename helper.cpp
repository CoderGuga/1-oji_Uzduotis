#include "helper.h"

int MAX_GRADES = 10;

Stud::Stud() : pavarde("Pavardenis"), vardas("Vardenis"), egz(10), nd(nullptr), nd_count(0), galutinisVid(0.0f), galutinisMed(0.0f) {
    // Initialization code (if any)
}

Stud::~Stud() {
    delete[] nd; // Cleanup dynamically allocated array
}
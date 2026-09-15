#pragma once // that the compiler doesn't copy the structure (repeatedly)

#include <cmath>

// Create structure
struct Params {
    double m;
    double z1;
    double z2;
};

void calc(Params& params);

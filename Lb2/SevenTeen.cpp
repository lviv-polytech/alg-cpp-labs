#include "Params.h"

#include <cmath>

using namespace std;

void calc(Params& params) {

    // Part 1
    double BLOCK_1 = std::pow((3 * params.m + 2), 2);
    double BLOCK_2 = 24 * params.m;

    double MERGE_1_B1_B2 = std::sqrt(BLOCK_1 - BLOCK_2);

    // Part 2
    double BLOCK_3 = 3 * std::sqrt(params.m);
    double BLOCK_4 = 2 / std::sqrt(params.m);

    double MERGE_2_B1_B2 = BLOCK_3 - BLOCK_4;

    params.z1 = MERGE_1_B1_B2 / MERGE_2_B1_B2;
    params.z2 = std::sqrt(params.m);
}
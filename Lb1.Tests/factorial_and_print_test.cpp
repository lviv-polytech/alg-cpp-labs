#include <cassert>
#include <sstream>
#include <string>

void runFactorialLogic(std::istream& input, std::ostream& output);

void test_calculate_factorial_output_is_correct() {
    std::stringstream fake_input("");
    std::stringstream fake_output;

    runFactorialLogic(fake_input, fake_output);

    std::string actual_result = fake_output.str();
    std::string expected_result = "Hello, World!\nP: 3628800 i: 11\n";

    assert(actual_result == expected_result);
}
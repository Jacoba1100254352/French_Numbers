#include <set>
#include <catch2/catch.hpp>
#include "../french_numbers.h"

#include <sstream>


TEST_CASE("Test RandomOption function")
{
    constexpr double maxVal = 10;
    const unsigned long long result = RandomOption(maxVal);
    CHECK(result >= 1);
    CHECK(result <= maxVal);

    // Test randomness properties over multiple calls
    set<unsigned long long> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(RandomOption(maxVal));
    }
    CHECK(values.size() > 1);  // Check if it produces more than one unique value
}

TEST_CASE("Test StartingScript function")
{
    unsigned desiredPracticeForm;
    std::stringstream ss;
    ss.str("1\n100\n");  // simulate user input
    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf(output.rdbuf());

    unsigned result = StartingScript(desiredPracticeForm);

    std::cin.rdbuf(orig_cin);  // restore original cin
    std::cout.rdbuf(orig_cout); // restore original cout

    CHECK(result == 1);
    CHECK(desiredPracticeForm == 1);
    CHECK(output.str().find("Welcome to Number Practice!") != std::string::npos);
}

TEST_CASE("Test NumToWritten function")
{
    bool practiceEnd = false;
    std::stringstream ss;
    ss.str("0\n");  // simulate user input to end the practice
    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf(output.rdbuf());

    NumToWritten(practiceEnd);

    std::cin.rdbuf(orig_cin);  // restore original cin
    std::cout.rdbuf(orig_cout); // restore original cout

    CHECK(practiceEnd == true);
    CHECK(output.str().find("Correct!") == std::string::npos); // Expect no "Correct!" since user quits immediately
}


TEST_CASE("Test WrittenFrenchNum0to99 function")
{
    std::string result;

    // Test for 0
    unsigned long long number = 0;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "zéro-");
    result.clear();

    // Test for 1
    number = 1;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "un-");
    result.clear();

    // Test for 21
    number = 21;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "vingt-et-un-");
    result.clear();

    // Test for 71
    number = 71;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "soixante-et-onze-");
    result.clear();

    // Test for 80
    number = 80;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "quatre-vingts-");
    result.clear();

    // Test for 99
    number = 99;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "quatre-vingt-dix-neuf-");
    result.clear();
}

TEST_CASE("Test WrittenFrenchNumbers function")
{
    std::string result;

    // Test for 100
    unsigned long long number = 100;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent");
    result.clear();

    // Test for 101
    number = 101;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-un");
    result.clear();

    // Test for 111
    number = 111;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-onze");
    result.clear();

    // Test for 200
    number = 200;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "deux-cents");
    result.clear();

    // Test for 201
    number = 201;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "deux-cent-un");
    result.clear();

    // Test for 999
    number = 999;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "neuf-cent-quatre-vingt-dix-neuf");
    result.clear();

    // Test for 1000
    number = 1000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "mille");
    result.clear();

    // Test for 1001
    number = 1001;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "mille-un");
    result.clear();

    // Test for 1100
    number = 1100;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "mille-cent");
    result.clear();

    // Test for 10000
    number = 10000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "dix-mille");
    result.clear();

    // Test for 100000
    number = 100000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-mille");
    result.clear();

    // Test for 1000000
    number = 1000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "un-million");
    result.clear();

    // Test for 10000000
    number = 10000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "dix-millions");
    result.clear();

    // Test for 100000000
    number = 100000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-millions");
    result.clear();

    // Test for 1000000000
    number = 1000000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "un-milliard");
    result.clear();

    // Test for 200000
    number = 200000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "deux-cent-mille");
    result.clear();

    // Test for 80000
    number = 80000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "quatre-vingt-mille");
    result.clear();
}

/*TEST_CASE("Edge Cases for WrittenFrenchNumbers function")
{
    // Test for very large numbers
    unsigned long long number = 999999999999;
    std::string result = WrittenFrenchNumbers(number);
    CHECK(result == "neuf-cent-quatre-vingt-dix-neuf-milliard-neuf-cent-quatre-vingt-dix-neuf-million-neuf-cent-quatre-vingt-dix-neuf-mille-neuf-cent-quatre-vingt-dix-neuf");
    result.clear();

    // Test for zero
    number = 0;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "zéro");
    result.clear();

    // Test for negative numbers
    CHECK(WrittenFrenchNumbers(0) == "zéro");
    CHECK_THROWS_AS(WrittenFrenchNumbers(-1), std::exception);  // if negatives should throw
    CHECK(WrittenFrenchNumbers(999999999999) == "Expected Output for 999999999999");
}*/

/*TEST_CASE("Edge Cases for RandomOption function")
{
    CHECK_THROWS_AS(RandomOption(0), std::exception);
    CHECK_THROWS_AS(RandomOption(-1), std::exception);
}*/

/*TEST_CASE("Boundary and Error Handling in StartingScript")
{
    unsigned desiredPracticeForm;
    std::stringstream ss;
    ss.str("5\n1\n100\n");  // Test with an out-of-range followed by valid input
    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf(output.rdbuf());

    unsigned result = StartingScript(desiredPracticeForm);

    std::cin.rdbuf(orig_cin);
    std::cout.rdbuf(orig_cout);

    CHECK(desiredPracticeForm == 1);
    CHECK(output.str().find("Invalid choice") != std::string::npos);  // Assuming you add this message
}

TEST_CASE("Continuous Interaction in DaysAndMonths")
{
    bool practiceEnd = false;
    std::stringstream ss;
    ss.str("Lundi\nMardi\n0\n");  // Simulate multiple correct inputs followed by exit command
    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf(output.rdbuf());

    DaysAndMonths(practiceEnd);

    std::cin.rdbuf(orig_cin);
    std::cout.rdbuf(orig_cout);

    CHECK(practiceEnd == true);
    CHECK(output.str().find("Correct!") != std::string::npos);
}

TEST_CASE("Handling Incorrect and Extreme Inputs in NumToWritten")
{
    bool practiceEnd = false;
    std::stringstream ss;
    ss.str("incorrect\n999999999999\n0\n");  // Incorrect answer followed by extreme number and exit
    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf(output.rdbuf());

    NumToWritten(practiceEnd);

    std::cin.rdbuf(orig_cin);
    std::cout.rdbuf(orig_cout);

    CHECK(output.str().find("Incorrect") != std::string::npos);
    CHECK(output.str().find("Correct!") == std::string::npos); // No correct since the session ended early
}*/


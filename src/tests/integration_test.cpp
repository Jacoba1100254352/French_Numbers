#include <catch2/catch.hpp>
#include "../french_numbers.h"

TEST_CASE("test empty input")
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

    // Test for 99
    number = 99;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "quatre-vingt-dix-neuf-");
    result.clear();

    // Test for 100
    number = 100;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-");
    result.clear();

    // Test for 101
    number = 101;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "cent-un-");
    result.clear();

    // Test for 111
    number = 111;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "cent-onze-");
    result.clear();

    // Test for 200
    number = 200;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "deux-cents-");
    result.clear();

    // Test for 201
    number = 201;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "deux-cent-un-");
    result.clear();

    // Test for 999
    number = 999;
    WrittenFrenchNum0to99(result, number);
    CHECK(result == "neuf-cent-quatre-vingt-dix-neuf-");
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
    CHECK(result == "un-millon");
    result.clear();

    // Test for 10000000
    number = 10000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "dix-millon");
    result.clear();

    // Test for 100000000
    number = 100000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "cent-millon");
    result.clear();

    // Test for 1000000000
    number = 1000000000;
    result = WrittenFrenchNumbers(number);
    CHECK(result == "un-millard");
    result.clear();
}

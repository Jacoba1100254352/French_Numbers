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
}

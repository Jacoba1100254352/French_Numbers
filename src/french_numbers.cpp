#include "french_numbers.h"

#include <cstdint>
#include <random>
#include <stdexcept>

namespace {

void WrittenFrenchNum0to99Impl(string& writNumbers, unsigned long long& number, const bool isTerminal)
{
	const string writ0to9[10] = {
		"zéro-", "un-", "deux-", "trois-", "quatre-", "cinq-", "six-", "sept-", "huit-", "neuf-"
	};
	const string writ10to19[10] = {
		"dix-", "onze-", "douze-", "treize-", "quatorze-", "quinze-", "seize-", "dix-sept-", "dix-huit-", "dix-neuf-"
	};
	const string writ20to60[7] = {
		"", "", "vingt-", "trente-", "quarante-", "cinquante-", "soixante-"
	};

	if (number < 10) {
		writNumbers += writ0to9[number];
		number = 0;
		return;
	}

	if (number < 20) {
		writNumbers += writ10to19[number - 10];
		number = 0;
		return;
	}

	if (number < 70) {
		const unsigned long long tens = number / 10;
		const uint8_t ones = number % 10;

		writNumbers += writ20to60[tens];
		if (ones == 1)
			writNumbers += "et-";
		if (ones != 0)
			writNumbers += writ0to9[ones];

		number = 0;
		return;
	}

	if (number < 80) {
		if (number == 71)
			writNumbers += "soixante-et-onze-";
		else
			writNumbers += "soixante-" + writ10to19[number - 70];

		number = 0;
		return;
	}

	if (number == 80) {
		writNumbers += isTerminal ? "quatre-vingts-" : "quatre-vingt-";
		number = 0;
		return;
	}

	writNumbers += "quatre-vingt-";

	const unsigned long long remainder = number - 80;
	if (remainder < 10)
		writNumbers += writ0to9[remainder];
	else
		writNumbers += writ10to19[remainder - 10];

	number = 0;
}

void WrittenFrenchNumHundredsPlaceImpl(string& writNumbers, unsigned long long number, const bool isTerminal)
{
	constexpr unsigned ONE_HUNDRED = 100;

	if (number >= ONE_HUNDRED) {
		unsigned long long tempNumber = number / ONE_HUNDRED;
		if (tempNumber > 1)
			WrittenFrenchNum0to99Impl(writNumbers, tempNumber, false);

		const bool hasRemainder = number % ONE_HUNDRED != 0;
		if (tempNumber == 1 || hasRemainder || !isTerminal)
			writNumbers += "cent-";
		else
			writNumbers += "cents-";
	}

	number %= ONE_HUNDRED;
	if (number > 0)
		WrittenFrenchNum0to99Impl(writNumbers, number, isTerminal);
}

void AppendScaleChunk(
	string& writNumbers,
	unsigned long long& number,
	const unsigned long long divisor,
	const string& scale,
	const bool pluralizeScale,
	const bool omitOne,
	const bool isTerminalChunk)
{
	if (number < divisor)
		return;

	const unsigned long long chunk = number / divisor;
	if (!(omitOne && chunk == 1))
		WrittenFrenchNumHundredsPlaceImpl(writNumbers, chunk, isTerminalChunk);

	writNumbers += scale;
	if (pluralizeScale && chunk > 1)
		writNumbers += "s";

	number %= divisor;
	if (number > 0)
		writNumbers += "-";
}

} // namespace

/************************
*   General Functions   *
************************/
unsigned long long RandomOption(const double maxVal)
{
	const auto upperBound = maxVal >= 1 ? static_cast<unsigned long long>(maxVal) : rangeMax;
	if (upperBound < 1)
		throw invalid_argument("RandomOption maxVal must be positive");

	random_device rd;
	mt19937_64 mt(rd());
	uniform_int_distribution<unsigned long long> randomDistribution(1, upperBound);

	return randomDistribution(mt);
}

unsigned StartingScript(unsigned& desiredPracticeForm)
{
	cout << "Welcome to Number Practice!" << endl
		<< "What would you like to practice: " << endl
		<< "1) Written to Number" << endl
		<< "2) Numbers to Letters" << endl
		<< "3) Days and Months" << endl
		<< "4) Random" << endl
		<< "Enter choice (1, 2, 3, or 4): ";
	cin >> desiredPracticeForm;

	while (cin.fail() || (desiredPracticeForm < 1 || desiredPracticeForm > 4)) {
		//system("clear");
		cout << "Enter choice (1, 2, 3, or 4): ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> desiredPracticeForm;
	}

	if (desiredPracticeForm != 3) {
		cout << "\nEnter maximum number to practice with: ";
		cin >> rangeMax;

		if (!rangeMax)
			rangeMax = 999999999999;

		while (cin.fail()) {
			//system("clear");
			cout << "Enter maximum number to practice with: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> rangeMax;
		}
	} else rangeMax = 19; // Hardcoded for the number of days + months

	cout << "\nGreat! Let's Get Started!" << endl
		<< "Note: Enter '0' at any time to end the practice." << endl;

	return desiredPracticeForm;
}

/*unsigned Timer()
{
    using namespace literals::chrono_literals;
    chrono::time_point<chrono::steady_clock> start, end;

    start = chrono::high_resolution_clock::now();

    end = chrono::high_resolution_clock::now();

    chrono::duration<float> duration = end - start;
    cout << duration.count() << "s " << endl;
}*/

/*****************************************
*   Days and Months Practice Functions   *
*****************************************/

void DaysAndMonths(bool& practiceEnd)
{
	const string DaysAndMonthsFrench[] = {
		"", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche",
		"janvier", "février", "mars", "avril", "mai", "juin", "juillet",
		"août", "septembre", "octobre", "novembre", "décembre"
	};

	const string DaysAndMonthsEnglish[] = {
		"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"
	};

	//Timer timer;
	const unsigned long long randomNumber = RandomOption();
	const string answer = DaysAndMonthsFrench[randomNumber];
	const string prompt = DaysAndMonthsEnglish[randomNumber];
	string userAnswer;

	do {
		cout << prompt << endl;
		userAnswer = UserInputWritten();

		if (userAnswer == "0") {
			practiceEnd = true;
			break;
		} else if (userAnswer == "?") {
			cout << "The Answer is: " << answer << endl;
			hintsGiven++;
		} else if (userAnswer == answer) {
			cout << "Correct!\n" << endl;
			correctAnswers++;
		} else {
			cout << "Incorrect Answer, Please try again. Hint: Make sure your capitalization is right" << endl;
			incorrectAnswers++;
		}
	} while (userAnswer == "?" || userAnswer != answer);
}


/*******************************
*   Written Number Functions   *
*******************************/

string UserInputWritten()
{
	///   Initialize Variable(s)   ///
	string userAnswer;

	///   Input User Decision   ///
	cout << "Enter Answer: ";
	cin >> userAnswer;
	cout << endl;

	///   Failsafe for correct user Input   ///
	while (cin.fail()) {
		cout << "Enter Answer: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> userAnswer;
		cout << endl;
	}

	return userAnswer;
}

void NumToWritten(bool& practiceEnd)
{
	const unsigned long long randomNumber = RandomOption();
	const string answer = WrittenFrenchNumbers(randomNumber);
	string userAnswer;

	do {
		cout << randomNumber << endl;
		userAnswer = UserInputWritten();

		if (userAnswer == "0") {
			practiceEnd = true;
			break;
		} else if (userAnswer == "?") {
			cout << "The Answer is: " << answer << endl;
			hintsGiven++;
		} else if (userAnswer == answer) {
			cout << "Correct!" << endl << endl;
			correctAnswers++;
		} else {
			cout << "Incorrect Answer, Please try again" << "   Hint: Remember to use \"-\" in between each word" <<
				endl;
			incorrectAnswers++;
		}
	} while (userAnswer == "?" || userAnswer != answer);
}


/**********************************
*   Enumerated Number Functions   *
**********************************/

// UserInputEnumerated function
unsigned long long UserInputEnumerated()
{
	string userAnswer;

	while (true) {
		// Input user decision
		cout << "Enter Answer: ";
		cin >> userAnswer;
		cout << endl;

		// Failsafe for correct user input
		try {
			if (userAnswer != "?") {
				size_t processedCharacters = 0;
				const auto parsedValue = stoull(userAnswer, &processedCharacters);
				if (processedCharacters == userAnswer.size())
					return parsedValue;
			}
		} catch (...) {
		}

		if (userAnswer != "?")
			cout << "Invalid input, please try again." << endl;

		if (userAnswer == "?") {
			constexpr unsigned ASCII_Q_Mark = 00101111;
			return ASCII_Q_Mark;
		}
	}
}

// WrittenToNum function
void WrittenToNum(bool& practiceEnd)
{
	constexpr unsigned ASCII_Q_Mark = 00101111;
	unsigned long long userAnswer;
	const unsigned long long randomNumber = RandomOption();

	do {
		cout << "\n" << WrittenFrenchNumbers(randomNumber) << endl;
		userAnswer = UserInputEnumerated();

		if (!userAnswer) {
			practiceEnd = true;
		} else if (userAnswer == ASCII_Q_Mark) {
			cout << "The Answer is: " << randomNumber << endl;
			hintsGiven++;
		} else {
			while (userAnswer != randomNumber) {
				incorrectAnswers++;
				cout << "Incorrect Answer, Please try again" << endl;
				cout << WrittenFrenchNumbers(randomNumber) << endl;
				userAnswer = UserInputEnumerated();
			}

			cout << "Correct!\n" << endl;
			correctAnswers++;
		}
	} while (userAnswer == ASCII_Q_Mark);
}


/****************************
*   Calculation Functions   *
****************************/

string WrittenFrenchNumbers(unsigned long long number)
{
	string WritNumbers;

	constexpr unsigned long long ONE_BILLION = 1000000000;
	constexpr unsigned long long ONE_MILLION = 1000000;
	constexpr unsigned long long ONE_THOUSAND = 1000;

	AppendScaleChunk(WritNumbers, number, ONE_BILLION, "milliard", true, false, true);
	AppendScaleChunk(WritNumbers, number, ONE_MILLION, "million", true, false, true);
	AppendScaleChunk(WritNumbers, number, ONE_THOUSAND, "mille", false, true, false);

	// Process remaining numbers (0 to 999)
	if (number > 0)
		WrittenFrenchNumHundredsPlaceImpl(WritNumbers, number, true);

	// If the result is empty, the number is zero
	if (WritNumbers.empty())
		WritNumbers = "zéro";
	// Remove the trailing hyphen, if any
	else if (WritNumbers.back() == '-')
		WritNumbers.pop_back();

	return WritNumbers;
}

void WrittenFrenchNum0to99(string& WritNumbers, unsigned long long& number)
{
	WrittenFrenchNum0to99Impl(WritNumbers, number, true);
}

void WrittenFrenchNumHundredsPlace(string& WritNumbers, unsigned long long number)
{
	WrittenFrenchNumHundredsPlaceImpl(WritNumbers, number, true);
}

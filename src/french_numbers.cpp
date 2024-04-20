#include "french_numbers.h"

#include <random>

/************************
*   General Functions   *
************************/
unsigned long long RandomOption(const double maxVal = static_cast<double>(rangeMax))
{
	///   Use random library to effectively randomize the dice rolls   ///
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<> randomDistribution(1, maxVal + 1); // Add one to make it inclusive

	return static_cast<unsigned long long>(randomDistribution(mt));
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
				return stoi(userAnswer);
			}
		} catch (...) {
			cout << "Invalid input, please try again." << endl;
		}

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
	const string Writ100to1Billion[5] = {"cent", "cents", "mille", "million", "milliard"};

	// Process billions
	if (constexpr unsigned ONE_BILLION = 1000000000; number >= ONE_BILLION) {
		if (unsigned long long tempNumber = number / ONE_BILLION; tempNumber > 1) // avoids "un-cent-..." which is not a number
			WrittenFrenchNum0to99(WritNumbers, tempNumber);
		WritNumbers += Writ100to1Billion[4];
		number %= ONE_BILLION;
		if (number > 0) WritNumbers += "-";
	}

	// Process millions
	if (constexpr unsigned ONE_MILLION = 1000000; number >= ONE_MILLION) {
		if (unsigned long long tempNumber = number / ONE_MILLION; tempNumber > 1) // avoids "un-mille-..." which is not a number
			WrittenFrenchNum0to99(WritNumbers, tempNumber);
		WritNumbers += Writ100to1Billion[3];
		number %= ONE_MILLION;
		if (number > 0) WritNumbers += "-";
	}

	// Process thousands
	if (constexpr unsigned ONE_THOUSAND = 1000; number >= ONE_THOUSAND) {
		if (unsigned long long tempNumber = number / ONE_THOUSAND; tempNumber > 1) // avoids "un-mille-..." which is not a number
			WrittenFrenchNum0to99(WritNumbers, tempNumber);
		WritNumbers += Writ100to1Billion[2];
		number %= ONE_THOUSAND;
		if (number > 0) WritNumbers += "-";
	}

	// Process remaining numbers (0 to 999)
	if (number > 0) {
		WrittenFrenchNumHundredsPlace(WritNumbers, number);
	}

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
	const string Writ0to9[10] = {
		"zéro-", "un-", "deux-", "trois-", "quatre-", "cinq-", "six-", "sept-", "huit-", "neuf-"
	};
	const string Writ11to19[10] = {
		"", "onze-", "douze-", "treize-", "quatorze-", "quinze-", "seize-", "dix-sept-", "dix-huit-", "dix-neuf-"
	};
	const string Writ10to90[10] = {
		"", "dix-", "vingt-", "trente-", "quarante-", "cinquante-", "soixante-", "soixante-dix-", "quatre-vingt-", "quatre-vingt-dix-"
	};

	if (number < 10) {
		// 1 to 9
		WritNumbers += Writ0to9[number];
	} else {
		// 10 to 99
		const unsigned long long tens = number / 10;
		const uint8_t ones = number % 10;

		if ((11 <= number && number <= 19) || (71 <= number && number <= 79) || (91 <= number && number <= 99)) {
			if (number >= 71 && number <= 79 || number >= 91 && number <= 99)
				WritNumbers += Writ10to90[tens - 1]; // Subtract 1 from tens to avoid appending "dix-" twice
			WritNumbers += Writ11to19[ones];
		} else if (!ones) { // TENS: 10, 20, 30, ..., 90
			WritNumbers += Writ10to90[tens];
		} else { ///   Add "et-" to numbers 21-71 that have "1"   ///
			WritNumbers += Writ10to90[tens];
			if (ones == 1 && 20 < number && number <= 71)
				WritNumbers += "et-";
			WritNumbers += Writ0to9[ones];
		}
		number = 0;
	}
}

void WrittenFrenchNumHundredsPlace(string& WritNumbers, unsigned long long number)
{
	constexpr unsigned ONE_HUNDRED = 100;

	if (number >= ONE_HUNDRED) {
		unsigned long long tempNumber = number / ONE_HUNDRED;
		if (tempNumber > 1) // avoids "un-cent-..." which is not a number
			WrittenFrenchNum0to99(WritNumbers, tempNumber);

		///   Add Hundred's prefix   ///
		if (tempNumber == 1 || number % ONE_HUNDRED >= 1)
			WritNumbers += "cent-";
		else if (!(number % ONE_HUNDRED))
			WritNumbers += "cents-";
	}

	///   Output the other numbers   ///  // (834 becomes 34)
	number %= ONE_HUNDRED;
	WrittenFrenchNum0to99(WritNumbers, number);
}

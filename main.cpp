#include <iostream>
#include <random>
#include <map>
#include <string>
#include <chrono>

using namespace std;
using namespace literals::chrono_literals;

///   General Functions   ///
unsigned long long RandomOption(double maxVal);
unsigned StartingScript( unsigned& );
//unsigned Timer();
struct Timer
{
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<float> duration{};

    Timer()
    {
        start = chrono::high_resolution_clock::now();
    }

/*    float startTimer()
    {
        start = chrono::high_resolution_clock::now();
    }*/

    //~Timer()
    float endTimer()
    {
        end = chrono::high_resolution_clock::now();
        duration = end - start;

        //float ms = duration.count() * 1000.0f;
        return duration.count(); // seconds
        //cout << "Timer took " << ms << "ms" << endl;
    }
};

///   Days and Months Practice Functions   ///
void DaysAndMonths( bool& );

///   Written Number Functions   ///
string UserInputWritten();
void WrittenToNum( bool& );

///   Enumerated Number Functions   ///
unsigned long long  UserInputEnumerated();
void NumToWritten( bool& );

///   Calculation Functions   ///
string WrittenFrenchNumbers( unsigned long long );
void WrittenFrenchNum0to99( string&, unsigned long long& );
void WrittenFrenchNumHundredsPlace(string&, unsigned long long);

///   Global Variable   ///
unsigned long long rangeMax;
unsigned correctAnswers;
unsigned incorrectAnswers;
unsigned hintsGiven;


/***********
*   Main   *
************/

int main() {
    ///   Initialize Variables   ///
    enum PracticeForm { WritToNum = 1, NumToWrit = 2, DaysMonths = 3, Random = 4 };
    unsigned percentCorrect, desiredPracticeForm, randomOption, userRandMax;
    bool practiceEnd = false;

    map<string, float> time;
    Timer timer;
    time["total"] = timer.endTimer();

    ///   Welcome the User   ///
    StartingScript(desiredPracticeForm);
    userRandMax = rangeMax;

    ///   Global Variables   ///
    correctAnswers = incorrectAnswers = hintsGiven = 0;

    //chrono::time_point<chrono::steady_clock> times = chrono::high_resolution_clock::now();
    //time["total"] = times;
    do {
        if (desiredPracticeForm == Random)
            randomOption = RandomOption(3);

        // Continues rangeMax hardcoding for the Days and the Months option (see note in StartingScript function)
        rangeMax = (randomOption == 3) ? 19 : userRandMax;

        if (desiredPracticeForm == WritToNum || randomOption == 1)
            do WrittenToNum(practiceEnd);
            while (!practiceEnd && desiredPracticeForm != Random);
        else if (desiredPracticeForm == NumToWrit || randomOption == 2)
            do NumToWritten(practiceEnd);
            while (!practiceEnd && desiredPracticeForm != Random);
        else if (desiredPracticeForm == DaysMonths || randomOption == 3)
            do DaysAndMonths(practiceEnd);
            while (!practiceEnd && desiredPracticeForm != Random);
        else throw invalid_argument("Error: Invalid practice form passed");
    } while (desiredPracticeForm == Random && !practiceEnd);

    //chrono::duration<float> totalDuration = end - start;

    percentCorrect = (correctAnswers * 100) / (correctAnswers + incorrectAnswers);

    cout << "Congrats! You finished." << endl
         << "Incorrect Answers: " << incorrectAnswers << endl
         << "Correct Answers: " << correctAnswers << endl;
    if (hintsGiven > 0)
        cout << "Hints Given: " << hintsGiven << endl;
    cout << "Percent Correct: " << percentCorrect << endl
         << "Time taken on the correct questions: " << time["correct"] << "s " << endl
         << "Time taken on the incorrect questions: " << time["incorrect"] << "s " << endl
         << "Total duration: " << time["total"] << "s " << endl;

    return 0;
}


/************************
*   General Functions   *
************************/
unsigned long long RandomOption(double maxVal = static_cast<double>(rangeMax))
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

    while (cin.fail() || (desiredPracticeForm < 1 || desiredPracticeForm > 4))
    {
        //system("clear");
        cout << "Enter choice (1, 2, 3, or 4): ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> desiredPracticeForm;
    }

    if (desiredPracticeForm != 3)
    {
        cout << "\nEnter maximum number to practice with: ";
        cin >> rangeMax;

        if (!rangeMax)
            rangeMax = 999999999999;

        while (cin.fail())
        {
            //system("clear");
            cout << "Enter maximum number to practice with: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> rangeMax;
        }
    }
    else rangeMax = 19; // Hardcoded for the number of days + months

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

void DaysAndMonths(bool &practiceEnd) {
    string DaysAndMonthsFrench[] = {"", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche",
                                    "janvier", "février", "mars", "avril", "mai", "juin", "juillet",
                                    "août", "septembre", "octobre", "novembre", "décembre"};

    string DaysAndMonthsEnglish[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                     "January", "February", "March", "April", "May", "June", "July",
                                     "August", "September", "October", "November", "December"};

    //Timer timer;
    unsigned long long randomNumber = RandomOption();
    string answer = DaysAndMonthsFrench[randomNumber];
    string prompt = DaysAndMonthsEnglish[randomNumber];
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

string UserInputWritten() {
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

void NumToWritten(bool& practiceEnd) {
    unsigned long long randomNumber = RandomOption();
    string answer = WrittenFrenchNumbers(randomNumber);
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
            cout << "Incorrect Answer, Please try again" << "   Hint: Remember to use \"-\" in between each word" << endl;
            incorrectAnswers++;
        }
    } while (userAnswer == "?" || userAnswer != answer);
}


/**********************************
*   Enumerated Number Functions   *
**********************************/

// UserInputEnumerated function
unsigned long long UserInputEnumerated() {
    const unsigned ASCII_Q_Mark = 00101111;
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
            return ASCII_Q_Mark;
        }
    }
}

// WrittenToNum function
void WrittenToNum(bool &practiceEnd) {
    const unsigned ASCII_Q_Mark = 00101111;
    unsigned long long userAnswer = 0;
    unsigned long long randomNumber = RandomOption();

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

string WrittenFrenchNumbers(unsigned long long number) {
    const unsigned ONE_BILLION = 1000000000;
    const unsigned ONE_MILLION = 1000000;
    const unsigned ONE_THOUSAND = 1000;

    string WritNumbers;
    string Writ100to1Billion[5] = {"cent-", "cents-", "mille-", "millon-", "millard-"};

    // Process billions
    if (number >= ONE_BILLION) {
        unsigned long long tempNumber = number / ONE_BILLION;
        WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
        WritNumbers += Writ100to1Billion[4];
        number %= ONE_BILLION;
    }

    // Process millions
    if (number >= ONE_MILLION) {
        unsigned long long tempNumber = number / ONE_MILLION;
        WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
        WritNumbers += Writ100to1Billion[3];
        number %= ONE_MILLION;
    }

    // Process thousands
    if (number >= ONE_THOUSAND) {
        if (number != ONE_THOUSAND)
            WrittenFrenchNumHundredsPlace(WritNumbers, number / ONE_THOUSAND);
        WritNumbers += Writ100to1Billion[2];
        number %= ONE_THOUSAND;
    }

    // Process remaining numbers (0 to 999)
    WrittenFrenchNumHundredsPlace(WritNumbers, number);

    // If the result is empty, the number is zero
    if (WritNumbers.empty())
        WritNumbers = "zéro";
        // Remove the trailing hyphen, if any
    else if (WritNumbers.back() == '-')
        WritNumbers.pop_back();

    return WritNumbers;
}

void WrittenFrenchNum0to99(string& WritNumbers, unsigned long long& number) {
    string Writ0to9[10] = {"zéro-", "un-", "deux-", "trois-", "quatre-", "cinq-", "six-", "sept-", "huit-", "neuf-"};
    string Writ11to19[10] = {"", "onze-", "douze-", "treize-", "quatorze-", "quinze-", "seize-", "dix-sept-", "dix-huit-", "dix-neuf-"};
    string Writ10to90[10] = {"", "dix-", "vingt-", "trente-", "quarante-", "cinquante-", "soixante-", "soixante-", "quatre-vingt-", "quatre-vingt-"};

    if (number < 10) { // 1 to 9
        WritNumbers += Writ0to9[number];
    } else { // 10 to 99
        unsigned long long tens = number / 10;
        uint8_t ones = number % 10;

        if ((11 <= number && number <= 19) || (70 <= number && number <= 79) || (90 <=number && number <= 99)) {
            if (number >= 70 && number <= 79 || number >= 90 && number <= 99)
                WritNumbers += Writ10to90[tens];
            WritNumbers += Writ11to19[ones];
        } else if (!ones) { // TENS: 10, 20, 30, ..., 90
            WritNumbers += Writ10to90[tens];
        } else { ///   Add "et-" to numbers 21-71 that have "1"   ///
            WritNumbers += Writ10to90[tens];
            if (ones == 1 && 20 < number && number <= 71)
                WritNumbers += "et-";
            WritNumbers += Writ0to9[ones];
        }
    }
    number = 0;
}

void WrittenFrenchNumHundredsPlace(string& WritNumbers, unsigned long long number)
{
    const unsigned ONE_HUNDRED = 100;

    if (number >= ONE_HUNDRED)
    {
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


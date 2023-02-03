#include <iostream>
#include <random>
#include <map>
#include <string>
#include <chrono>

using namespace std;
using namespace literals::chrono_literals;

///   General Functions   ///
unsigned long long RandomOption();
unsigned long long RandomPathOption();
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


int main()
{
    ///   Initialize Variables   ///
    enum PracticeForm { WritToNum = 1, NumToWrit = 2, DaysMonths = 3, Random = 4 };
    unsigned percentCorrect, desiredPracticeForm, randomOption, userRandMax;
    bool practiceEnd = false;

    map<string, float> time;
    Timer timer;
    time["total"] = timer.endTimer();

    ///   Welcome the User   ///
    StartingScript( desiredPracticeForm );
    userRandMax = rangeMax;

    ///   Global Variables   ///
    correctAnswers = 0, incorrectAnswers = 0, hintsGiven = 0;

    //chrono::time_point<chrono::steady_clock> times = chrono::high_resolution_clock::now();
    //time["total"] = times;
    do {
        if (desiredPracticeForm == Random)
            randomOption = RandomPathOption();

        // Continues rangeMax hardcoding for the Days and the Months option (see note in StartingScript function)
        if (randomOption == 3)
            rangeMax = 19;
        else rangeMax = userRandMax;

        if (desiredPracticeForm == WritToNum || randomOption == 1)
            do {
                WrittenToNum(practiceEnd);
            } while (!practiceEnd && desiredPracticeForm != Random );
        else if (desiredPracticeForm == NumToWrit || randomOption == 2)
            do {
                NumToWritten(practiceEnd);
            } while (!practiceEnd && desiredPracticeForm != Random );
        else if (desiredPracticeForm == DaysMonths || randomOption == 3)
            do {
                DaysAndMonths(practiceEnd);
            } while (!practiceEnd && desiredPracticeForm != Random );
        else throw invalid_argument("Error: Invalid practice form passed");
    } while (desiredPracticeForm == Random && !practiceEnd);

    //chrono::duration<float> totalDuration = end - start;

    percentCorrect = (correctAnswers*100)/(correctAnswers + incorrectAnswers);

    cout << "Congrats! You finished." << endl
         << "Incorrect Answers: " << incorrectAnswers << endl
         << "Correct Answers: " << correctAnswers << endl;
    if (hintsGiven > 0)
        cout << "Hints Given: " << hintsGiven << endl;
    cout << "Percent Correct: " << percentCorrect << endl;
    cout << "Time taken on the correct questions: " << time["correct"] << "s " << endl;
    cout << "Time taken on the incorrect questions: " << time["incorrect"] << "s " << endl;
    cout << "Total duration: " << time["total"] << "s " << endl;

    return 0;
}


/************************
*   General Functions   *
************************/
unsigned long long RandomOption()
{
    ///   Use random library to effectively randomize the dice rolls   ///
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<> randomDistribution(1, static_cast<double>(rangeMax) + 1); // Add one to make it inclusive

    return static_cast<unsigned long long>(randomDistribution(mt));
}

unsigned long long RandomPathOption()
{
    ///   Use random library to effectively randomize the dice rolls   ///
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<> randomDistribution(1, 4); // Add one to make it inclusive

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
void DaysAndMonths( bool& practiceEnd )
{
    //Timer timer;
    string userAnswer;
    unsigned long long randomNumber = RandomOption(); // Assign it each time to provide random numbers

    string DaysAndMonthsFrench[] = { "", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche",
                                      "janvier", "février", "mars", "avril", "mai", "juin", "juillet",
                                      "août", "septembre", "octobre", "novembre", "décembre"}; // position 0 is blank because of the random option hard-coding

    string DaysAndMonthsEnglish[] = { "", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
                                      "January", "February", "March", "April", "May", "June", "July",
                                      "August", "September", "October", "November", "December"};// position 0 is blank because of the random option hard-coding

    do
    {
        cout << "\n" << DaysAndMonthsEnglish[randomNumber] << endl;
        userAnswer = UserInputWritten();

        while ((userAnswer != DaysAndMonthsFrench[randomNumber]) && (userAnswer != "0") && (userAnswer != "?")) {
            incorrectAnswers++;
            cout << "Incorrect Answer, Please try again" << "   Hint: Make sure your capitalization is right"
                 << endl;
            cout << DaysAndMonthsEnglish[randomNumber] << endl;
            userAnswer = UserInputWritten();
        }

        if (userAnswer == "0")
            practiceEnd = true;
        else if (userAnswer == "?")
        {
            cout << "The Answer is: " << DaysAndMonthsFrench[randomNumber] << endl;
            hintsGiven++;
        }
        else if (userAnswer == DaysAndMonthsFrench[randomNumber]) {
            cout << "Correct!" << "\n" << endl;
            correctAnswers++;
            //system("clear");
        }
        else throw invalid_argument("Error: Invalid Argument was passed"); // Theoretically this should never be thrown

    } while (userAnswer == "?");
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
    string userAnswer;

    do {
        cout << randomNumber << endl;
        userAnswer = UserInputWritten();

        if (userAnswer == "0")
            practiceEnd = true;
        else if (userAnswer == "?") {
            cout << "The Answer is: " << WrittenFrenchNumbers(randomNumber) << endl;
            hintsGiven++;
        } else if (userAnswer == WrittenFrenchNumbers(randomNumber)) {
            cout << "Correct!" << endl << endl;
            correctAnswers++;
        } else {
            incorrectAnswers++;
            cout << "Incorrect Answer, Please try again" << "   Hint: Remember to use \"-\" in between each word" << endl << randomNumber << endl;
        }
    } while (userAnswer == "?");
}


/**********************************
*   Enumerated Number Functions   *
**********************************/

unsigned long long UserInputEnumerated() {
    const unsigned ASCII_Q_Mark = 00101111;
    string userAnswer;

    while (true) {
        cout << "Enter Answer: ";
        cin >> userAnswer;
        cout << endl;

        try {
            if (userAnswer != "?")
                return stoi(userAnswer);
        } catch (...) { cout << "Invalid input, please try again." << endl; }

        if (userAnswer == "?")
            return ASCII_Q_Mark;
    }
}

void WrittenToNum(bool& practiceEnd) {
    const unsigned ASCII_Q_Mark = 00101111;
    unsigned long long userAnswer = 0;
    unsigned long long randomNumber = RandomOption();

    do {
        cout << '\n' << WrittenFrenchNumbers(randomNumber) << endl;
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

            cout << "Correct!" << '\n' << endl;
            correctAnswers++;
        }
    } while (userAnswer == ASCII_Q_Mark);
}


/****************************
*   Calculation Functions   *
****************************/

string WrittenFrenchNumbers(unsigned long long number)
{
    const unsigned ONE_BILLION = 1000000000;
    const unsigned ONE_MILLION = 1000000;
    const unsigned ONE_THOUSAND = 1000;
    unsigned long long tempNumber = 0;

    string WritNumbers;
    string Writ100to1Billion[5] = { "cent-", "cents-", "mille-", "millon-", "millard-" };

    while (number)
    {
        if (number >= ONE_BILLION)
        {
            tempNumber = number / ONE_BILLION;
            WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
            WritNumbers += Writ100to1Billion[4];
            number %= ONE_BILLION;
        }
        else if (number >= ONE_MILLION)
        {
            tempNumber = number / ONE_MILLION;
            WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
            WritNumbers += Writ100to1Billion[3];
            number %= ONE_MILLION;
        }
        else if (number >= ONE_THOUSAND)
        {
            tempNumber = number / ONE_THOUSAND;
            if (tempNumber != 1)
                WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
            WritNumbers += Writ100to1Billion[2];
            number %= ONE_THOUSAND;
        }
        else
        {
            WrittenFrenchNumHundredsPlace(WritNumbers, number);
            number = 0;
        }
    }

    if (WritNumbers.empty())
        WritNumbers = "zéro-";

    if (WritNumbers.back() == '-')
        WritNumbers.pop_back();

    return WritNumbers;
}

void WrittenFrenchNum0to99(string& WritNumbers, unsigned long long& number) {
    string Writ0to9[10] = {"zéro-", "un-", "deux-", "trois-", "quatre-", "cinq-", "six-", "sept-", "huit-", "neuf-"};
    string Writ11to19[10] = {"", "onze-", "douze-", "treize-", "quatorze-", "quinze-", "seize-", "dix-sept-", "dix-huit-", "dix-neuf-"}; // [0] is empty so there is less confusion later
    string Writ10to90[10] = {"", "dix-", "vingt-", "trente-", "quarante-", "cinquante-", "soixante-", "soixante-", "quatre-vingt-", "quatre-vingt-"}; // [0] is empty so there is less confusion later

    if (number >= 10 && number <= 99) { // 10 to 99
        if ((number >= 11 && number <= 19) || (number >= 70 && number <= 79) || (number >= 90 && number <= 99)) { // 11-19 and 71-79 or 91-99
            if (number >= 70 && number <= 79 || number >= 90 && number <= 99)
                for (unsigned i = 1; i <= 9; i++)
                    if (i == (number / 10))
                        WritNumbers += Writ10to90[i];

            for (int i = 1; i < 10; i++)
                if ((number % 10) == i)
                    WritNumbers += Writ11to19[i];

            number = 0; // End the loop

            ///   Write Ten's Place   ///
        } else if (number == 10 || number >= 20) {
            for (unsigned i = 1; i < 10; i++)
                if (i == (number / 10))
                    WritNumbers += Writ10to90[i];

            ///   Add "et-" to numbers 21-71 that have "1"   ///
            if (number > 20 && number <= 71 && (number % 10) == 1) // 21-71 add et- to work
                WritNumbers += "et-";
            number %= 10; // Modulate down
            if (number > 0) // 1 to 9
                for (unsigned i = 1; i < 10; i++)
                    if ((number % 10) == i)
                        WritNumbers += Writ0to9[i];
            number = 0; // End the loop
        } else {
            number %= 10; // Modulate down
            if (number > 0) // 1 to 9
                for (unsigned i = 1; i < 10; i++)
                    if ((number % 10) == i)
                        WritNumbers += Writ0to9[i];
            number = 0; // End the loop
        }
    } else { // 1 to 9
        for (int i = 1; i < 10; i++)
            if ((number % 10) == i)
                WritNumbers += Writ0to9[i];
        number = 0; // End the loop
    }
}
void WrittenFrenchNumHundredsPlace(string& WritNumbers, unsigned long long number)
{
    const unsigned ONE_HUNDRED = 100;
    unsigned long long tempNumber = 0;

    if (number >= ONE_HUNDRED)
    {
        if (number >= 200) // avoids "un-cent-..." which is not a number
        {
            tempNumber = number / ONE_HUNDRED; // of 903, make it 9
            WrittenFrenchNum0to99(WritNumbers, tempNumber);
        }

        ///   Add Hundred's prefix   ///
        if (number / ONE_HUNDRED == 1 || number % ONE_HUNDRED >= 1)
            WritNumbers += "cent-";
        else if (number % ONE_HUNDRED == 0)
            WritNumbers += "cents-";
    }

    ///   Output the other numbers   ///  // (834 becomes 34)
    number %= ONE_HUNDRED;
    WrittenFrenchNum0to99(WritNumbers, number);
}

#include <iostream>
#include <random>
#include <string>
//#include <chrono>

using namespace std;

///   General Functions   ///
unsigned long long RandomOption();
unsigned long long RandomPathOption();
unsigned StartingScript( unsigned& );
//unsigned Timer();

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
    unsigned percentCorrect = 0;
    unsigned desiredPracticeForm = 0;
    unsigned randomOption = 0;
    bool practiceEnd = false;
    unsigned userRandMax = 0;


    ///   Welcome the User   ///
    StartingScript( desiredPracticeForm );
    userRandMax = rangeMax;

    ///   Global Variables   ///
    correctAnswers = 0;
    incorrectAnswers = 0;
    hintsGiven = 0;

    do {
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

    percentCorrect = (correctAnswers*100)/(correctAnswers + incorrectAnswers);

    cout << "Congrats! You finished." << endl
         << "Incorrect Answers: " << incorrectAnswers << endl
         << "Correct Answers: " << correctAnswers << endl;
    if (hintsGiven > 0)
        cout << "Hints Given: " << hintsGiven << endl;
    cout << "Percent Correct: " << percentCorrect << endl;

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

    return static_cast<unsigned long long int>(randomDistribution(mt));
}
unsigned long long RandomPathOption()
{
    ///   Use random library to effectively randomize the dice rolls   ///
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<> randomDistribution(1, 4); // Add one to make it inclusive

    return static_cast<unsigned long long int>(randomDistribution(mt));
}
unsigned StartingScript( unsigned& desiredPracticeForm )
{

    cout << "Welcome to Number Practice!" << endl
         << "What would you like to practice," << endl
         << "Written to Number (1), Numbers to Letters (2), Days and Months (3), or Random (4)?" << endl
         << "Enter 1, 2, 3, or 4: ";
    cin >> desiredPracticeForm;

    while ( cin.fail() || ( desiredPracticeForm != 1 && desiredPracticeForm != 2 && desiredPracticeForm != 3 && desiredPracticeForm != 4 ) )
    {
        //system("clear");
        cout << "Enter 1, 2, 3, or 4: ";
        cin.clear();
        cin.ignore ( 256, '\n' );
        cin >> desiredPracticeForm;
    }

    if ( desiredPracticeForm != 3 )
    {
        cout << "\n" << "Also, Enter the number you'd like to practice til: ";
        cin >> rangeMax;

        if (rangeMax == 0)
            rangeMax = 999999999999;

        while ( cin.fail() )
        {
            //system("clear");
            cout << "Enter the number you'd like to practice til: ";
            cin.clear();
            cin.ignore ( 256, '\n' );
            cin >> rangeMax;
        }
    }
    else rangeMax = 19; // Hardcoded for the number of days + months

    cout << "\n" << "Great! Let's Get Started!" << endl
         << "Note: Enter '0' at any time to end the practice." << endl;

    return desiredPracticeForm;
}
//struct Timer
//{
//    chrono::time_point<chrono::steady_clock> start, end;
//    chrono::duration<float> duration{};
//
//    Timer()
//    {
//        start = chrono::high_resolution_clock::now();
//    }
//
//    ~Timer()
//    {
//        end = chrono::high_resolution_clock::now();
//        duration = end - start;
//
//        float ms = duration.count() * 1000.0f;
//        cout << "Timer took " << ms << "ms" << endl;
//    }
//};
//unsigned Timer()
//{
//    using namespace literals::chrono_literals;
//
//    auto start = chrono::high_resolution_clock::now();
//
//    auto end = chrono::high_resolution_clock::now();
//
//    chrono::duration<float> duration = end - start;
//    cout << duration.count() << "s " << endl;
//}

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

string UserInputWritten()
{
    ///   Initialize Variable(s)   ///
    string userAnswer;

    ///   Input User Decision   ///
    cout << "Enter Answer: ";
    cin >> userAnswer;
    cout << endl;

    ///   Failsafe for correct user Input   ///
    while ( cin.fail() )
    {
        //system("clear");
        cout << "Enter Answer: ";
        cin.clear();
        cin.ignore ( 256, '\n' );
        cin >> userAnswer;
        cout << endl;
    }

    return userAnswer;
}
void NumToWritten( bool& practiceEnd )
{
    string userAnswer;
    unsigned long long randomNumber = RandomOption(); // Assign it each time to provide random numbers

    do
    {
        cout << randomNumber << endl;
        userAnswer = UserInputWritten();

        while ((userAnswer != WrittenFrenchNumbers(randomNumber)) && (userAnswer != "0") && (userAnswer != "?")) {
            incorrectAnswers++;
            cout << "Incorrect Answer, Please try again" << "   Hint: Remember to use \"-\" in between each word"
                 << endl;
            cout << randomNumber << endl;
            userAnswer = UserInputWritten();
        }
        if (userAnswer == "0")
            practiceEnd = true;
        else if (userAnswer == "?")
        {
            cout << "The Answer is: " << WrittenFrenchNumbers(randomNumber) << endl;
            hintsGiven++;
        }
        else if (userAnswer == WrittenFrenchNumbers(randomNumber)) {
            cout << "Correct!" << "\n" << endl;
            correctAnswers++;
            //system("clear");
        }
        else throw invalid_argument("Error: Invalid Argument was passed"); // Theoretically this should never be thrown

    } while (userAnswer == "?");
}


/**********************************
*   Enumerated Number Functions   *
**********************************/

unsigned long long UserInputEnumerated() {
    ///   Initialize Variable(s)   ///
    const unsigned ASCII_Q_Mark = 00101111;
    string userAnswer;
    bool stoiFunctioning = false;
    //int testVariable = 0;

    do
    {
        ///   Input User Decision   ///
        cout << "Enter Answer: ";
        cin >> userAnswer;
        cout << endl;

        try
        {
            if (userAnswer != "?")
                stoi(userAnswer);
            stoiFunctioning = true; // Note: stoiFunctioning is only set to true when stoi(...) was successfull
        }
        catch (...)
        {
            stoiFunctioning = false;
        }

        ///   Failsafe for correct user Input   ///
        while ( cin.fail() && (userAnswer != "?"))
        {

            //system("clear");
            cout << "Enter Answer: ";
            cin.clear();
            cin.ignore ( 256, '\n' );
            cin >> userAnswer;
            cout << endl;
        }

    } while (!stoiFunctioning);

    if (userAnswer == "?")
        return ASCII_Q_Mark;
    else return stoi(userAnswer);
}
void WrittenToNum( bool& practiceEnd )
{
    const unsigned ASCII_Q_Mark = 00101111;
    unsigned long long userAnswer = 0;
    unsigned long long randomNumber = RandomOption();

    do
    {
        cout << "\n" << WrittenFrenchNumbers(randomNumber) << endl;
        userAnswer = UserInputEnumerated();

        if (userAnswer == 0)
            practiceEnd = true;
        else if (userAnswer == ASCII_Q_Mark)
        {
            cout << "The Answer is: " << randomNumber << endl;
            hintsGiven++;
        }

        while ((userAnswer != randomNumber) && (userAnswer != 0) && (userAnswer != ASCII_Q_Mark)) {
            incorrectAnswers++;
            cout << "Incorrect Answer, Please try again" << endl;
            cout << WrittenFrenchNumbers(randomNumber) << endl;
            userAnswer = UserInputEnumerated();
        }
        if (userAnswer == randomNumber) {
            cout << "Correct!" << "\n" << endl;
            correctAnswers++;
            //system("clear");
        }
    } while (userAnswer == ASCII_Q_Mark);
}


/****************************
*   Calculation Functions   *
****************************/

string WrittenFrenchNumbers( unsigned long long number )
{
    const unsigned ONE_BILLION = 1000000000;
    const unsigned ONE_MILLION = 1000000;
    const unsigned ONE_THOUSAND = 1000;
    unsigned long long tempNumber = 0;

    bool moreNumbers = true;

    string WritNumbers;

    string Writ100to1Billion[5] = { "cent-", "cents-", "mille-", "millon-", "millard-" };

    ///   Handles 100 to 1000000000   ///
    while (moreNumbers)
    {
        if (number == 0)
        {
            WritNumbers = "zéro-";
        }
        else if (number >= ONE_BILLION) // add "mille" to numbers between 1000 and 900000
        {
            tempNumber = number/ONE_BILLION;
            WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);

            WritNumbers += Writ100to1Billion[4];

            number %= ONE_BILLION; // Modulate down
        }
        else if (number >= ONE_MILLION) // add "mille" to numbers between 1000 and 900000
        {
            tempNumber = number/ONE_MILLION;
            WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);

            WritNumbers += Writ100to1Billion[3];

            number %= ONE_MILLION; // Modulate down
        }
        else if (number >= ONE_THOUSAND) // add "mille" to numbers between 1000 and 900000
        {
            if ( (number/ONE_THOUSAND) != 1) // avoids writing a single "un-mille" (It should, if not just find and replace in string)
            {
                tempNumber = number / ONE_THOUSAND;
                WrittenFrenchNumHundredsPlace(WritNumbers, tempNumber);
            }

            WritNumbers += Writ100to1Billion[2];

            number %= ONE_THOUSAND; // Modulate down
        }
        else
        {
            WrittenFrenchNumHundredsPlace(WritNumbers, number);
            number = 0; // end the program
        }

        if ( number == 0 )
            moreNumbers = false;
    }

    // Keep at End of function
    if ( WritNumbers.at(WritNumbers.size() - 1) == '-' ) // Get rid of the last '-' in the word
        WritNumbers.pop_back();

    return WritNumbers;
}

void WrittenFrenchNum0to99(string& WritNumbers, unsigned long long& number)
{
    string Writ0to9[10] = { "zéro-", "un-", "deux-", "trois-", "quatre-", "cinq-", "six-", "sept-", "huit-", "neuf-" };
    string Writ11to19[10] = { "", "onze-", "douze-", "treize-", "quatorze-", "quinze-", "seize-", "dix-sept-", "dix-huit-", "dix-neuf-" }; // [0] is empty so there is less confusion later
    string Writ10to90[10] = { "", "dix-", "vingt-", "trente-", "quarante-", "cinquante-", "soixante-", "soixante-", "quatre-vingt-", "quatre-vingt-" }; // [0] is empty so there is less confusion later

    if ( (number >= 10) && (number <= 99) ) // 10 to 99
    {
        if ( ((number >= 11) && (number <= 19)) || ((number >= 70) && (number <= 79)) || ((number >= 90) && (number <= 99))) // 11-19 and 71-79 or 91-99
        {
            if (((number >= 70) && (number <= 79)) || ((number >= 90) && (number <= 99)))
                for (int i = 1; i <= 9; i++)
                    if (i == (number / 10))
                        WritNumbers += Writ10to90[i];

            for (int i = 1; i <= 9; i++)
                if ( (number % 10) == i)
                    WritNumbers += Writ11to19[i];

            number = 0; // End the loop
        }
        ///   Write Ten's Place   ///
        else if (number == 10 || number >= 20)
        {
            for (int i = 1; i <= 9; i++)
                if (i == (number / 10))
                    WritNumbers += Writ10to90[i];

            ///   Add "et-" to numbers 21-71 that have "1"   ///
            if ( ( number > 20 ) && ( number <= 71 ) && ( (number % 10) == 1 ) ) // 21-71 add et- to work
                WritNumbers += "et-";

            number %= 10; // Modulate down
            if ( number > 0 ) // 1 to 9
                for (int i = 1; i < 10; i++)
                    if ((number % 10) == i)
                        WritNumbers += Writ0to9[i];

            number = 0; // End the loop
        }
        else
        {
            number %= 10; // Modulate down
            if ( number > 0 ) // 1 to 9
                for (int i = 1; i < 10; i++)
                    if ((number % 10) == i)
                        WritNumbers += Writ0to9[i];

            number = 0; // End the loop
        }
    }
    else // 1 to 9
    {
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
        if (((number / ONE_HUNDRED) == 1) || ((number % ONE_HUNDRED) >= 1)) // If 100 or #0#
            WritNumbers += "cent-";
        else if ((number % ONE_HUNDRED) == 0)
            WritNumbers += "cents-";
    }

    ///   Output the other numbers   ///  // (834 becomes 34)
    number %= ONE_HUNDRED;
    WrittenFrenchNum0to99(WritNumbers, number);
}

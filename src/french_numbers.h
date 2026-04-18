#ifndef FRENCH_NUMBERS_H
#define FRENCH_NUMBERS_H

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace literals::chrono_literals;

///   General Functions   ///
unsigned long long RandomOption(double maxVal = 0);
unsigned StartingScript(unsigned&);

//unsigned Timer();
struct Timer {
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
void DaysAndMonths(bool&);

///   Written Number Functions   ///
string UserInputWritten();
void WrittenToNum(bool&);

///   Enumerated Number Functions   ///
unsigned long long UserInputEnumerated();
void NumToWritten(bool&);

///   Calculation Functions   ///
string WrittenFrenchNumbers(unsigned long long);
void WrittenFrenchNum0to99(string&, unsigned long long&);
void WrittenFrenchNumHundredsPlace(string&, unsigned long long);

///   Global Variable   ///
inline unsigned long long rangeMax;
inline unsigned correctAnswers;
inline unsigned incorrectAnswers;
inline unsigned hintsGiven;

#endif //FRENCH_NUMBERS_H

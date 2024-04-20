#include "french_numbers.h"

#include <map>

/***********
*   Main   *
************/

int main()
{
	///   Initialize Variables   ///
	enum PracticeForm { WritToNum = 1, NumToWrit = 2, DaysMonths = 3, Random = 4 };
	unsigned desiredPracticeForm, randomOption = 0;
	bool practiceEnd = false;

	map<string, float> time;
	Timer timer;
	time["total"] = timer.endTimer();

	///   Welcome the User   ///
	StartingScript(desiredPracticeForm);
	const unsigned userRandMax = rangeMax;

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

	const unsigned percentCorrect = (correctAnswers * 100) / (correctAnswers + incorrectAnswers);

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

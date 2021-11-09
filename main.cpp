#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <string>
#include "timer.hpp"

struct Score {
	double total;
	double average;
};

bool score_dump(Score& score, FILE* file);
bool score_load(Score& score, FILE* file);

inline bool exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}


int main() {
	using std::cout;
	using std::endl;
	using std::cin;
	srand(time(NULL));

	static const char operations[] = {'+', '-'};
	std::string score_filename = "score.data";
	int level;
	int num1, num2, result;
	int limit;
	int uAnswer; /* user answer */

	cout << "Welcome to the Math In Mind\nChoose your level:\n";
	cout << "1. Easy: 10-100\n"
		 << "2. Medium: 10 - 1000\n"
		 << "3. Hard: 10 - 10000\n";
	cin >> level;

	while (level > 3 || level < 1) {
		cout << "Please, enter a number from 1 to 3: ";
		cin >> level;
	}

	switch (level) {
		case 1: /* easy level */
			limit = 100;
			break;
		case 2: /* Medium level*/
			limit = 1000;
			break;
		case 3: /* Hard level */
			limit = 10000;
	}

	Timer t;
	for (int i = 1; i <= 10; i++) {
		// generate numbers between 10 and $limit
		num1 = (rand() % limit - 11) + 10;
		num2 = (rand() % limit - 11) + 10;
		char curr_operation = operations[rand() % 2];
		switch (curr_operation) {
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
		}
		cout << i << "/10) " << num1 << " " << curr_operation << " " << num2 << " = ";
		cin >> uAnswer;
		while (uAnswer != result) {
			cout << "Wrong answer, try again\n";
			cout << num1 << " " << curr_operation << " " << num2 << " = ";
			cin >> uAnswer;
		}
	}
	double left = t.elapsed();
	double average = left * 0.1;
	cout << "Total time for 10 tasks: " << left << endl;
	cout << "Average for 1 task: " << average << endl;
	Score score_current{left, average};
	Score temp;
	// calculate and dump best result
	if (exists(score_filename)) {
		FILE* score_file = fopen(score_filename.c_str(), "rb");
		if (score_file == NULL) {
			perror("opening score_file");
			exit(EXIT_FAILURE);
		}
		score_load(temp, score_file);
		if (left < temp.total) { // this result is better than previous
			cout << "Wow! That result is better then previous\n";
			cout << "previous:\n" << temp.total << endl << temp.average << endl;
			freopen(score_filename.c_str(), "wb", score_file);
			if (!score_dump(score_current, score_file)) {
				std::cout << "error while dumping your best result.\n";
			}
		}
		else { // this result is worse than previous
			cout << "Best result:\n";
			cout << "total: " << temp.total << endl;
			cout << "average: "<< temp.average << endl;
		}
		fclose(score_file);
	}
	else {
		FILE* score_file = fopen(score_filename.c_str(), "wb");
		if (score_file == NULL) {
			perror("opening score_file");
			exit(EXIT_FAILURE);
		}
		if (!score_dump(score_current, score_file)) {
			std::cout << "error while dumping your first result.\n";
		}
		fclose(score_file);
	}

	return 0;
}

bool score_dump(Score &score, FILE* file) {
	if (!fwrite(&score, sizeof(Score), 1, file)) {
		perror("score_dump");
		return false;
	}
	return true;
}


bool score_load(Score& score, FILE* file) {
	if (!fread(&score, sizeof(Score), 1, file)) {
		perror("score_load");
		return false;
	}
	return true;
}


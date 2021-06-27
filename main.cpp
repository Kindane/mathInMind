#include <iostream>
#include <ctime>
#include "timer.hpp"

using std::cout;
using std::endl;
using std::cin;

int main() {
	srand(time(NULL));
	const char operations[] = {'+', '-'};
	int level = 1;
	int num1, num2, result;
	int div1, div2;
	int uAnswer; /* user answer */
	cout << "Welcome to the Math In Mind\nChoose your level:\n";
	cout << "1. Easy: 10-99\n"
		 << "2. Medium: 100 - 999\n"
		 << "3. Hard: 1000 - 9999\n";
	cin >> level;
	while (level > 3 || level < 1) {
		cout << "Please, enter a number from 1 to 3: ";
		cin >> level;
	}

	switch (level) {
		case 1: /* easy level */
			div1 = 10;
			div2 = 99;
			break;
		case 2: /* Medium level*/
			div1 = 100;
			div2 = 999;
			break;
		case 3: /* Hard level */
			div1 = 1000;
			div2 = 9999;
	}

	Timer t;
	for (int i = 1; i <= 10; i++) {
		num1 = rand() % div2 + div1;
		num2 = rand() % div2 + div1;
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
	cout << "Total time for 10 tasks: " << left << endl;
	cout << "Average for 1 task: " << left/10 << endl;
	return 0;
}

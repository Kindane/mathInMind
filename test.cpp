#include <iostream>

struct Score {
	double total;
	double average;
};

int main() {
	bool write = 0;

	Score score;
	FILE* file = fopen("score.data", "rb+");
	if (file == NULL) {
		perror("opening file");
		return EXIT_FAILURE;
	}

	if (write) { // write
		score.total = 100;
		score.average = 10;
		fwrite(&score, sizeof(Score), 1, file);
	}

	else { // read
		fread(&score, sizeof(Score), 1, file);
		std::cout << "total: " << score.total << std::endl;
		std::cout << "average: " << score.average << std::endl;
	}
	fclose(file);
	return 0;
}

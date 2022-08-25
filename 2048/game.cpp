#include "game.h"

using namespace std;


const int SIDE_LENGTH = 4;


int main() {
	Grid gameGrid = Grid::getInstance();


	return 0;
}


Grid::Grid() {
	gridContent_.resize(16);
}


int Square::getRank() {
	return SIDE_LENGTH * (verticalPosition_ - 1) + horizontalPosition_;
}


bool Square::isPossibleToMerge(Square other) {
	if (*this != other) {
		if (isOnTheSameLine(other)) {
			return true;
		}

	}
}

bool Square::operator!=(Square other) {
	return getRank() != other.getRank();
}

bool Square::isOnTheSameLine(Square other) {
	int rank = getRank();
	int otherRank = other.getRank();


	if (abs(rank - otherRank) % SIDE_LENGTH == 0) {
		return true;
	}

	else if (abs(rank - otherRank) < SIDE_LENGTH) {
		return rank / (SIDE_LENGTH + 1) == otherRank / (SIDE_LENGTH + 1);
	}

	return false;
}
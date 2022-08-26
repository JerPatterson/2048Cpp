#include <iostream>
#include "game.h"

using namespace std;


const int SIDE_LENGTH = 4;


int main() {
	//Grid gameGrid = Grid::getInstance();

	Square firstSquare = Square(1, 3, 4);
	Square sencondSquare = Square(1, 2, 4);
	Square thirdSquare = Square(4, 3, 0);

	cout << firstSquare.getRank() << ' ' 
		<< sencondSquare.getRank() << ' ' 
		<< thirdSquare.getRank() << endl;

	cout << firstSquare.isPossibleToMerge(sencondSquare) << ' '
		<< firstSquare.isPossibleToMerge(thirdSquare);


	return 0;
}

Grid::Grid() {
	gridContent_.resize(16);
}


Square::Square(int x, int y, int value) :
	horizontalPosition_(x),
	verticalPosition_(y),
	value_(value)
{
}

int Square::getRank() {
	return SIDE_LENGTH * (verticalPosition_ - 1) + horizontalPosition_;
}


bool Square::isPossibleToMerge(Square other) {
	if (*this != other) {
		if (getValue() == 0) {
			return true;
		}
		else if (isOnTheSameLine(other)) {
			return value_ == other.value_;
		}
	}

	return false;
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
		if (rank / SIDE_LENGTH == otherRank / SIDE_LENGTH) {
			return true;
		}
		else {
			return max(rank, otherRank) % SIDE_LENGTH == 0;
		}
	}

	return false;
}


void Square::merge(Square other) {
	if (isPossibleToMerge(other)) {
		value_ += other.value_;
		other.value_ = 0;
	}
}
#include <iostream>
#include <algorithm>
#include <random>
#include "game.h"

using namespace std;


const int SIDE_LENGTH = 4;
const int MOST_COMMON_SPAWN = 2;
const int OTHER_SPAWN = 4;


int main() {
	Grid gameGrid = Grid::getInstance();

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


int Square::getRank() const {
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


void Square::setNewValue() {
	if (isGettingNewValue()) {
		if (rand() % 3 == 0) {
			value_ = OTHER_SPAWN;
		}
		else {
			value_ = MOST_COMMON_SPAWN;
		}
	}
}

bool Square::isGettingNewValue() const {
	return value_ == 0 && rand() > rand();
}



void Grid::sortValues() {
	sort(gridContent_.begin(), gridContent_.end(), 
		[](const Square& first, const Square& second) { return first.getRank() < second.getRank(); });
}


void Grid::generateStartValues() {
	for (Square& square : gridContent_) {
		square.setNewValue();
	}
}
#include <iostream>
#include <algorithm>
#include <random>
#include "game.h"

using namespace std;


const int SIDE_LENGTH = 4;
const int MOST_COMMON_SPAWN = 2;
const int OTHER_SPAWN = 4;

const char UP_KEY = 'w';
const char DOWN_KEY = 's';
const char RIGHT_KEY = 'a';
const char LEFT_KEY = 'd';


int main() {
	Grid gameGrid = Grid::getInstance();

	gameGrid.print();

	return 0;
}

Grid::Grid() {
	gridContent_.resize(16);

	srand(static_cast<int>(time(NULL)));
	generateStartValues();
}


Square::Square() :
	value_(0)
{
	static int nbOfSquaresGenerated = 0;
	++nbOfSquaresGenerated;

	setPosition(nbOfSquaresGenerated);
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

void Square::setPosition(int rank) {
	if (rank % SIDE_LENGTH == 0) 
		verticalPosition_ = rank / SIDE_LENGTH;
	else
		verticalPosition_ = (rank / SIDE_LENGTH) + 1;
	
	horizontalPosition_ = rank - SIDE_LENGTH * (verticalPosition_ - 1);
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


void Square::print() const {
	cout << value_;
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


void Grid::print() const {
	int i = 0;
	for (const Square& square : gridContent_) {
		if (i++ >= SIDE_LENGTH) {
			i = 1;
			cout << '\n';
		}

		square.print();
		cout << " ";
	}
}


void Grid::makeMove(char keyPressed) {
	if (keyPressed == UP_KEY) {
		upShift();
	}

	else if (keyPressed == DOWN_KEY) {
		downShift();
	}

	else if (keyPressed == RIGHT_KEY) {
		rightShift();
	}

	else if (keyPressed == LEFT_KEY) {
		leftShift();
	}
}

void Grid::upShift() {
	// TODO : if (unsorted) { ...
	sortValues();

	for (int k = SIDE_LENGTH; k > 1; --k) {
		for (int i = 0; i < SIDE_LENGTH; ++i) {
			for (int j = k - 1; j > 0; --j) {
				Square& top = gridContent_[i + SIDE_LENGTH * (SIDE_LENGTH - k)];
				Square& under = gridContent_[i + SIDE_LENGTH * j];

				if (top.getValue() == 0) {
					top.merge(under);
				}
				else if (top.isPossibleToMerge(under)) {
					top.merge(under);
					break;
				}
			}

		}
	}
}

void Grid::downShift() {
	// TODO : if (unsorted) { ...
	sortValues();
}

void Grid::rightShift() {
	// TODO : if (unsorted) { ...
	sortValues();
}

void Grid::leftShift() {
	// TODO : if (unsorted) { ...
	sortValues();
}
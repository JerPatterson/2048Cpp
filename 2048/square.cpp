#include "2048.h"


using std::max, std::cout;
using namespace _2048Game;


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


void Square::merge(Square& other) {
	if (isPossibleToMerge(other)) {
		value_ += other.value_;
		other.value_ = 0;
	}
}


void Square::setNewValue(int percentageOfSpawn) {
	if (isGettingNewValue(percentageOfSpawn)) {
		if (rand() % 3 == 0) {
			value_ = OTHER_SPAWN;
		}
		else {
			value_ = MOST_COMMON_SPAWN;
		}
	}
}

bool Square::isGettingNewValue(int percentageOfSpawn) const {
	return value_ == 0 && rand() < RAND_MAX * percentageOfSpawn / 100;
}


void Square::print() const {
	cout << value_;
}
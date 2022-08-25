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
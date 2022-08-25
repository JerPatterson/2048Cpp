#include "game.h"

using namespace std;


const int sideLength = 4;


int main() {
	Grid gameGrid = Grid::getInstance();


	return 0;
}


Grid::Grid() {
	gridContent_.resize(16);
}


int Square::getRank() {
	return sideLength * (verticalPosition_ - 1) + horizontalPosition_;
}
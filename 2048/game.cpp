#include "game.h"

using namespace std;


int main() {
	Grid gameGrid = Grid::getInstance();


	return 0;
}


Grid::Grid() {
	gridContent_.resize(16);
}
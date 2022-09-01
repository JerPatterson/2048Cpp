#include "2048.h"

using std::cin, std::cout;
using namespace _2048Game;


void Grid::sortValues() {
	if (!isSorted()) {
		sort(gridContent_.begin(), gridContent_.end(),
			[](const Square& first, const Square& second) { return first.getRank() < second.getRank(); });
	}
}

bool Grid::isSorted() const {
	for (int i = 0; i < SIDE_LENGTH * SIDE_LENGTH; ) {
		if (gridContent_[i++].getRank() != i) {
			return false;
		}
	}

	return true;
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

	cout << "\n\n";
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
	sortValues();

	for (int k = 0; k < SIDE_LENGTH; ++k) {
		for (int i = 0; i < SIDE_LENGTH; ++i) {
			for (int j = i + 1; j < SIDE_LENGTH; ++j) {
				Square& top = gridContent_[k + SIDE_LENGTH * i];
				Square& under = gridContent_[k + SIDE_LENGTH * j];

				if (top.getValue() == 0) {
					top.merge(under);
				}
				else if (under.getValue() != 0) {
					top.merge(under);
					break;
				}
			}
		}
	}

	spawnNewValues();
}

void Grid::downShift() {
	sortValues();

	for (int k = 0; k < SIDE_LENGTH; ++k) {
		for (int i = SIDE_LENGTH - 1; i > 0; --i) {
			for (int j = i - 1; j >= 0; --j) {
				Square& bottom = gridContent_[SIDE_LENGTH * i + k];
				Square& above = gridContent_[SIDE_LENGTH * j + k];

				if (bottom.getValue() == 0) {
					bottom.merge(above);
				}
				else if (above.getValue() != 0) {
					bottom.merge(above);
					break;
				}
			}
		}
	}

	spawnNewValues();
}

void Grid::rightShift() {
	sortValues();

	for (int k = 1; k <= SIDE_LENGTH; ++k) {
		for (int i = 1; i < SIDE_LENGTH; ++i) {
			for (int j = i + 1; j <= SIDE_LENGTH; ++j) {
				Square& right = gridContent_[SIDE_LENGTH * k - i];
				Square& left = gridContent_[SIDE_LENGTH * k - j];

				if (right.getValue() == 0) {
					right.merge(left);
				}
				else if (left.getValue() != 0) {
					right.merge(left);
					break;
				}
			}
		}
	}

	spawnNewValues();
}

void Grid::leftShift() {
	sortValues();

	for (int k = 1; k <= SIDE_LENGTH; ++k) {
		for (int i = SIDE_LENGTH; i > 1; --i) {
			for (int j = i - 1; j >= 1; --j) {
				Square& left = gridContent_[SIDE_LENGTH * k - i];
				Square& right = gridContent_[SIDE_LENGTH * k - j];

				if (left.getValue() == 0) {
					left.merge(right);
				}
				else if (right.getValue() != 0) {
					left.merge(right);
					break;
				}
			}
		}
	}

	spawnNewValues();
}


void Grid::spawnNewValues() {
	for (Square& square : gridContent_) {
		if (square.getValue() == 0) {
			square.setNewValue(DEFAULT_SPAWN_PERCENTAGE / 2);
		}
	}
}


void Grid::play() {
	print();

	char keyPressed;
	while (true) {
		cin >> keyPressed;
		makeMove(keyPressed);
		print();
	}
}
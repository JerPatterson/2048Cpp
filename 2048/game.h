#pragma once
#include <vector>


class Square {
public:
	Square() = default;

	//int getRank();
	int getValue() { return value_; };

	//void merge(Square);
	//bool isPossibleToMerge(Square);

private:
	int value_ = 0;
	int horizontalPosition_ = -1;
	int verticalPosition_ = -1;
};


class Grid {
public:
	static Grid getInstance() {
		static Grid theInstance = Grid();
		return theInstance;
	};

private:
	Grid();

	std::vector<Square> gridContent_;
};
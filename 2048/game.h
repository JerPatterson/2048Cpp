#pragma once
#include <vector>


class Square {
public:
	Square() = default;
	Square(int, int, int = 0);

	int getRank() const;
	int getValue() { return value_; };

	void merge(Square);
	bool operator!=(Square);
	bool isPossibleToMerge(Square);

private:
	int value_ = 0;
	int horizontalPosition_ = -1;
	int verticalPosition_ = -1;

	bool isOnTheSameLine(Square);
};


class Grid {
public:
	static Grid getInstance() {
		static Grid theInstance = Grid();
		return theInstance;
	};

	//void spawnNewValues();
	//void makeMove(char keyPressed);
	//void generateStartValues();

private:
	Grid();
	void sortValues();

	std::vector<Square> gridContent_;
};
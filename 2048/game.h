#pragma once
#include <vector>


class Square {
public:
	Square();
	Square(int, int, int = 0);

	int getRank() const;
	int getValue() { return value_; };

	void print() const;
	void setNewValue();
	void merge(Square);
	bool operator!=(Square);
	bool isPossibleToMerge(Square);

private:
	int value_ = 0;
	int horizontalPosition_ = -1;
	int verticalPosition_ = -1;

	bool isOnTheSameLine(Square);
	bool isGettingNewValue() const;
};


class Grid {
public:
	static Grid getInstance() {
		static Grid theInstance = Grid();
		return theInstance;
	};

	void print() const;
	//void spawnNewValues();
	//void makeMove(char keyPressed);

private:
	Grid();
	void sortValues();
	void generateStartValues();

	std::vector<Square> gridContent_;
};
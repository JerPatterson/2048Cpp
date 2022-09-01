#pragma once
#include <vector>


class Square {
public:
	Square();
	Square(int, int, int = 0);

	int getRank() const;
	int getValue() { return value_; };

	void print() const;
	void setNewValue(int);
	void merge(Square&);
	bool operator!=(Square);
	bool isPossibleToMerge(Square);

private:
	int value_ = 0;
	int horizontalPosition_ = -1;
	int verticalPosition_ = -1;

	void setPosition(int);
	bool isOnTheSameLine(Square);
	bool isGettingNewValue(int) const;
};


class Grid {
public:
	static Grid getInstance() {
		static Grid theInstance = Grid();
		return theInstance;
	};

	void play();
	void print() const;
	void spawnNewValues();
	void makeMove(char keyPressed);

private:
	Grid();

	void sortValues();
	bool isSorted() const;
	void generateStartValues();

	void upShift();
	void downShift();
	void rightShift();
	void leftShift();

	std::vector<Square> gridContent_;
};
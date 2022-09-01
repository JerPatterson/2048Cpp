#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <QObject>


namespace _2048Game {
	const int SIDE_LENGTH = 4;
	const int DEFAULT_SPAWN_PERCENTAGE = 30;
	const int MOST_COMMON_SPAWN = 2;
	const int OTHER_SPAWN = 4;

	const char UP_KEY = 'w';
	const char DOWN_KEY = 's';
	const char RIGHT_KEY = 'd';
	const char LEFT_KEY = 'a';
}


class Square {
public:
	Square();
	Square(int, int, int = 0);

	int getRank() const;
	int getValue() const { return value_; };

	void print() const;
	void setNewValue(int = _2048Game::DEFAULT_SPAWN_PERCENTAGE);
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


class Grid : public QObject {
	Q_OBJECT

public:
	static Grid* getInstance() {
		static Grid theInstance = Grid();
		return &theInstance;
	};

	void play();
	void print() const;
	void spawnNewValues();
	void makeMove(char keyPressed);

public slots:
	void generateStartValues();

signals:
	void contentHasChanged(const std::vector<Square>&);

private:
	Grid();

	void sortValues();
	bool isSorted() const;

	void upShift();
	void downShift();
	void rightShift();
	void leftShift();

	std::vector<Square> gridContent_;
};
#include "Qt2048.h"

using _2048Game::SIDE_LENGTH;
using std::vector, std::to_string, std::map, std::string;


Qt2048::Qt2048() :
	interfaceGrid_(new QGridLayout()) 
{
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setStyleSheet("background-color: #ECF0F1");
	mainWidget->setLayout(interfaceGrid_);
	setCentralWidget(mainWidget);


	for (int i = 0; i < SIDE_LENGTH; ++i) {
		for (int j = 0; j < SIDE_LENGTH; ++j) {
			QPushButton* newSquare = new QPushButton(this);
			newSquare->setFixedSize(QSize(100, 100));
			squares_.push_back(newSquare);
			interfaceGrid_->addWidget(newSquare, i, j, Qt::AlignCenter);
		}
	}

	connect(this, SIGNAL(startGame()), Grid::getInstance(), 
		SLOT(generateStartValues()), Qt::UniqueConnection);
	connect(Grid::getInstance(), SIGNAL(contentHasChanged(const std::vector<Square>&)),
		this, SLOT(changeContent(const std::vector<Square>&)));

	KeyReceiver* receiver = new KeyReceiver();
	mainWidget->installEventFilter(receiver);

	emit startGame();
}


void Qt2048::changeContent(const vector<Square>& gridContent) {
	int i = 0;

	for (const Square& square : gridContent) {
		setAppropriateColor(i, square.getValue());
		squares_[i++]->setText(QString::number(square.getValue()));
	}
}

void Qt2048::setAppropriateColor(int rank, int number) {
	const map<int, string> NUMBER_AND_COLOR_ASSOCIATION{
		{ 0, "#ECF0F1" },   { 2, "#FFFF66" },   { 4, "#FF9933" },
		{ 8, "#80FF00" },   { 16, "#009900" },  { 32, "#009999" },
		{ 64, "#0000CC" },  { 128, "#9933FF" }, { 256, "#FF66FF" }, 
		{ 512, "#FF99CC" }, { 1024, "#CC0066" }, { 2048, "#990099" },
	};

	squares_[rank]->setStyleSheet(QString::fromStdString("background-color: "
		+ NUMBER_AND_COLOR_ASSOCIATION.at(number)));
}


bool KeyReceiver::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_W) {
			Grid::getInstance()->makeMove('w');
		}
		else if (keyEvent->key() == Qt::Key_S) {
			Grid::getInstance()->makeMove('s');
		}
		else if (keyEvent->key() == Qt::Key_D) {
			Grid::getInstance()->makeMove('d');
		}
		else if (keyEvent->key() == Qt::Key_A) {
			Grid::getInstance()->makeMove('a');
		}

		return true;
	}
	else {
		return QObject::eventFilter(obj, event);
	}

	return false;
}
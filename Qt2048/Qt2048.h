#pragma once
#include "2048.h"
#include <vector>
#include <QGridLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>


class Qt2048 : public QMainWindow {
    Q_OBJECT

public:
    Qt2048();
    ~Qt2048() = default;

public slots:
    void changeContent(const std::vector<Square>&);

    signals:
        void startGame();

private:
    QGridLayout* interfaceGrid_;
    std::vector<QAbstractButton*> squares_;
};


class KeyReceiver : public QObject {
    Q_OBJECT
protected:
    bool eventFilter(QObject* obj, QEvent* event);
};
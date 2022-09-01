#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt2048.h"

class Qt2048 : public QMainWindow
{
    Q_OBJECT

public:
    Qt2048(QWidget *parent = nullptr);
    ~Qt2048();

private:
    Ui::Qt2048Class ui;
};

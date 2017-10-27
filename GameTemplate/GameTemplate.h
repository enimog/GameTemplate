#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameTemplate.h"

class GameTemplate : public QMainWindow
{
    Q_OBJECT

public:
    GameTemplate(QWidget *parent = Q_NULLPTR);

private:
    Ui::GameTemplateClass ui;
};

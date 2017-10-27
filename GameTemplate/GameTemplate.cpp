#include "stdafx.h"
#include "GameTemplate.h"

GameTemplate::GameTemplate(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    LOG_TRACE(L"Creating main window");
}

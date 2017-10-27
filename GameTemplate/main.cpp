#include "stdafx.h"
#include "GameTemplate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameTemplate w;
    w.show();
    return a.exec();
}

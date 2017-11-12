#include "stdafx.h"
#include "MainWindow.h"
#include "Logger.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow )
{
    CLogger logger;
    MainWindow window;

    return window.exec();
}

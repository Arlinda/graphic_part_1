#include "MainWindow.h"
#include <iostream>

using namespace std;


int main( int argc, char *argv[] )
{
    MainWindow mainWindow;

    if(!mainWindow.isValid()) {
        cout << "Error creating main window" << endl;
        exit(0);
    }

    mainWindow.exec();

	return 0;
}

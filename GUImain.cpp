#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include "Netflix.h"
#include "login.h"

using namespace std;

int main (int argc, char *argv[]){

	QApplication app (argc, argv);

	Netflix *netflix = new Netflix(argv[1]);
	//Netflix netflix (argv[1]);
	
	//loginClass *loginwindow = new loginClass(netflix);
	loginClass *loginwindow = new loginClass();
	//loginwindow->show();

	return app.exec();
}

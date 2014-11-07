#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTextStream>
#include "newUserClass.h"
#include "login.h"

using namespace std;

newUserClass::newUserClass(Netflix *N, QWidget *parent):QWidget(parent){
	netflix = N;

	QVBoxLayout *newUserScreen = new QVBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;

	newUserScreen->addWidget(new QLabel("Create a New User"));

	usernameText = new QLineEdit;
	fullNameText = new QLineEdit;

	QFormLayout *form = new QFormLayout;
	form -> addRow("Login", usernameText);
	form -> addRow("Name", fullNameText);
	newUserScreen -> addLayout(form);

	confirmB = new QPushButton (tr("Confirm"), this);
	cancelB = new QPushButton(tr("Cancel"), this);

	connect (confirmB, SIGNAL(clicked()), this, SLOT(confirmFunc()));
	connect (cancelB, SIGNAL(clicked()), this, SLOT(cancelFunc()));

	buttonLayout -> addWidget(confirmB);
	buttonLayout -> addWidget(cancelB);

	newUserScreen->addLayout(buttonLayout);
	setLayout(newUserScreen);
}

newUserClass::~newUserClass(){}

void newUserClass::confirmFunc(){
	std::cout << "Confirm" << endl;
	QString usernameString = usernameText -> text();
	std::cout << "Username: ";
	QTextStream(stdout) << usernameString << endl;

	QString fullnameString = fullNameText -> text();
	std::cout << "Full Name ";
	QTextStream(stdout) << fullnameString << endl;

	this -> hide();
	loginClass *loginwindow = new loginClass(netflix);
	loginwindow->show();
}

void newUserClass::cancelFunc(){
	std::cout << "Cancel" << endl;
	this -> hide();
	loginClass *loginwindow = new loginClass(netflix);
	loginwindow->show();		
}
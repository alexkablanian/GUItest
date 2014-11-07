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
#include "login.h"

using namespace std;

loginClass::loginClass(QWidget *parent):QWidget(parent){
//loginClass::loginClass (QWidget *parent):QWidget(parent){
	QVBoxLayout *loginScreen = new QVBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;

	loginScreen->addWidget(new QLabel("CSC104 Netflix"));

	loginText = new QLineEdit("Enter text here");

	QFormLayout *form = new QFormLayout;
	form -> addRow("Login", loginText);
	loginScreen -> addLayout(form);

	quitB = new QPushButton (tr("Quit"), this);
	newUserB = new QPushButton(tr("New User"), this);
	loginB = new QPushButton (tr("Login"), this);

	connect (loginB, SIGNAL(clicked()), this, SLOT(login()));
	//connect (newUserB, SIGNAL(clicked()), qApp, SLOT(clickNewUser()));
	connect (newUserB, SIGNAL(clicked()), this, SLOT(clickNewUser()));

	//only one that does not need to be changed --> writeOut delete memory 
	connect(quitB, SIGNAL(clicked()), this, SLOT(quit()));

	buttonLayout -> addWidget(loginB);
	buttonLayout -> addWidget(newUserB);
	buttonLayout -> addWidget(quitB);

	loginScreen->addLayout(buttonLayout);
	setLayout(loginScreen);
}

loginClass::~loginClass(){}

void loginClass::clickNewUser(){
	//get taken to the new user window
	cout << "new user" << endl;
	//newUserClass *newUserWindow = new newUserClass();
	this -> hide();
	//newUserWindow -> show();	
}

void loginClass::login(){
	//check user and if exists log in, if not pop up message saying incorrect username, try again!
	QString username = loginText -> text();
	cout << "it worked!" << endl;
	QTextStream(stdout) << username << endl;
	//run netflix login
	//take qline edit and input as string 
	//userMenuClass *newUserMenu = new userMenuClass();
	this -> hide();
	//newUserMenu -> show();
}

void loginClass::quit(){
	//write out files and deallocate memory when quit clicked
	//end program
	cout << "Leaving program" << endl;
	this -> close();
	//connect (quitB, SIGNAL(clicked()), qAPP, SLOT (quit()));
}
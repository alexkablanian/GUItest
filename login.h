#ifndef LOGIN_H
#define LOGIN_H

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

class loginClass:public QWidget{
Q_OBJECT

public:
	loginClass(QWidget *parent=0);
	//loginClass(QWidget *parent = 0);
	~loginClass();

private slots:
	void clickNewUser();
	void login();
	//should take input from the bar and use it as the string "username" and run the function login when clicked
	void quit();

private:
	QPushButton *quitB;
	QPushButton *newUserB;
	QPushButton *loginB;

	QLineEdit *loginText;
//
	//Netflix *netflix; 
};

#endif
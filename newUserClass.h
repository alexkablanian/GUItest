#ifndef NEWUSERCLASS_H
#define NEWUSERCLASS_H

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include "Netflix.h"

using namespace std;

class newUserClass:public QWidget{
	Q_OBJECT

public:
	newUserClass(Netflix *N, QWidget *parent = 0);
	~newUserClass();

private slots:
	void confirmFunc();
	void cancelFunc();

private:
	QPushButton *confirmB;
	QPushButton *cancelB;

	QLineEdit *usernameText;
	QLineEdit *fullNameText;

	Netflix *netflix;
};

#endif
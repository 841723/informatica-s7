/* Description */
/* ***************************************************
 * Dieser Header-File dient dazu die Klasse 'Window'
 * zu definieren. Objekte der Klasse 'Window'besitzen
 * diverse Bedienelemente in Form von qt-Widgets und 
 * Methoden, die bei Bedienung der einzelnen Widgets
 * ausgeloest werden.
 * **************************************************/

/* Includeguard */
#ifndef WINDOW_H
#define WINDOW_H

/* Libraries */
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QSlider>
#include <QSpacerItem>
#include <QGridLayout>
#include <QSize>
#include <QComboBox>
#include <string>
#include <iostream>
#include "Sender.h"

/* Class */
class Window : public QMainWindow
{
    Q_OBJECT
	public:
		QPushButton *startBtn; 
		QPushButton *quitBtn;
		QPushButton *devBtn;
		QSlider *sld;
		QWidget *wdg;
		QComboBox *modeDropdown;
		QVBoxLayout *mainLayout;
		Sender *mainSender;
		Window();
		void send();
		std::string order;
	
	public slots:
		void OnSliderMoved(int i);
		void StartRun();
		void Devmode();
		void Usermode();
};

#endif


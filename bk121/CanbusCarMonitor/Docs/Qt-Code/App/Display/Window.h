/* Description */
/* ***************************************************
 * 
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
		QLabel *lab;
		QWidget *wdg;
		QComboBox *modeDropdown;
		QVBoxLayout *mainLayout;
		Sender *mainSender;
		Window();
		void send(QString str);
	
	public slots:
		void OnSliderMoved(int i);
		//void OnClick();
		void StartRun();
		void Devmode();
		void Usermode();
};

#endif


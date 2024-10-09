/* Description */
/* ***************************************************
 * Hier wird der Standardkonstruktor fuer ein Objekt
 * vom Typ 'Window' definiert und desssen Methoden
 * ausformuliert.
 * **************************************************/
 
 /* Libraries */
#include "Window.h"

/* Constructors */
Window::Window()
{
	setWindowState(Qt::WindowFullScreen);
	mainSender=new Sender();
	wdg = new QWidget(this);
	
	/* Button-Options */
	
	//Start-Button
	startBtn = new QPushButton("START");
	startBtn->setMinimumHeight(300);
	QFont startBtn_fontsize = startBtn->font();
	startBtn_fontsize.setPointSize(150);
	startBtn->setFont(startBtn_fontsize);
	
	//Quit-Button
	quitBtn = new QPushButton("QUIT");
	quitBtn->setMinimumHeight(100);
	QFont quitBtn_fontsize = quitBtn->font();
	quitBtn_fontsize.setPointSize(50);
	quitBtn->setFont(quitBtn_fontsize);
	
	//Dev-Button
	devBtn = new QPushButton("DEVMODE");
	devBtn->setMinimumHeight(100);
	QFont devBtn_fontsize = devBtn->font();
	devBtn_fontsize.setPointSize(50);
	devBtn->setFont(devBtn_fontsize);
	
	/* Slider-Options */
	
	//Step-Count
	sld= new QSlider(Qt::Horizontal);
	sld->setMinimumHeight(150);
	QFont sld_fontsize = sld->font();
	sld_fontsize.setPointSize(100);
	sld->setFont(sld_fontsize);
	sld->setTickInterval(50);
	sld->setMinimum(50);
	sld->setMaximum(1000);
	
	/* Layout Setup */
	
	mainLayout = new QVBoxLayout(wdg);
	
	/* Dropdown-Options */
	
	//Mode-Dropdown
	modeDropdown = new QComboBox();
	modeDropdown->setMinimumHeight(150);
	QFont modeDropdown_fontsize = modeDropdown->font();
	modeDropdown_fontsize.setPointSize(100);
	modeDropdown->setFont(modeDropdown_fontsize);
	
	modeDropdown->addItem("Forward");
	modeDropdown->addItem("Backward");
	modeDropdown->addItem("Left Turn");
	modeDropdown->addItem("Right Turn");
	
	mainLayout->addWidget(startBtn);
	mainLayout->addWidget(modeDropdown);
	mainLayout->addWidget(sld);
	mainLayout->addWidget(devBtn);
	mainLayout->addWidget(quitBtn);
	
	wdg->setLayout(mainLayout);
	this->setCentralWidget(wdg);

	QObject::connect(startBtn, SIGNAL (clicked()), this, SLOT(StartRun()));
	QObject::connect(sld, SIGNAL (valueChanged(int)),this, SLOT(OnSliderMoved(int)));
	QObject::connect(quitBtn, SIGNAL (clicked()), qApp, SLOT(quit()));
	QObject::connect(devBtn, SIGNAL (clicked()), this, SLOT(Devmode()));
	
	QSize mysize = wdg->frameSize();
	printf("Höhe: %d Breite: %d", mysize.height(), mysize.width());
	
}

/* Methods */

//Send String via UART
void Window::send()
{
	mainSender->send("$F5000*");
}

//Start programmed run
void Window::StartRun()
{
	send();
}

//Programm steps
void Window::OnSliderMoved(int i)
{
	
}

//Windowed mode
void Window::Usermode()
{
	setWindowState(Qt::WindowFullScreen);
	devBtn->setText("DEVMODE");
	QObject::connect(devBtn, SIGNAL (clicked()), this, SLOT(Devmode()));
}

//Fullscreenmode
void Window::Devmode()
{
	setWindowState(Qt::WindowMaximized);
	devBtn->setText("USERMODE");
	QObject::connect(devBtn, SIGNAL (clicked()), this, SLOT(Usermode()));
}


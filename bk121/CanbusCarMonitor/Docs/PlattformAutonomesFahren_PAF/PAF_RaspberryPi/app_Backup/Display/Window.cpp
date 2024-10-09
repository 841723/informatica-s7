/* Description */
/* ***************************************************
 * 
 * **************************************************/
 
 /* Libraries */
#include "Window.h"

/* Constructors */
Window::Window()
{
	//setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);
	//setWindowState(Qt::WindowMaximized);
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
	//const QSize quitBtn_size = QSize(2*120, 2*120);
	//quitBtn->setFixedSize(quitBtn_size);
	
	//Dev-Button
	devBtn = new QPushButton("DEVMODE");
	devBtn->setMinimumHeight(100);
	QFont devBtn_fontsize = devBtn->font();
	devBtn_fontsize.setPointSize(50);
	devBtn->setFont(devBtn_fontsize);
	//const QSize devBtn_size = QSize(2*120, 2*120);
	//devBtn->setFixedSize(devBtn_size);
	
	/* Slider-Options */
	
	//Step-Count
	sld= new QSlider(Qt::Horizontal);
	sld->setMinimumHeight(150);
	QFont sld_fontsize = sld->font();
	sld_fontsize.setPointSize(100);
	sld->setFont(sld_fontsize);
	//sld->triggerAction(QSlider::TicksBelow);
	
	/* Layout Setup */
	
	//mainLayout = new QGridLayout(wdg);
	mainLayout = new QVBoxLayout(wdg);
	//Grid Dimensions (16:9)
	/*for(int i=0; i<=15; i++) {
		mainLayout->setColumnMinimumWidth(i,120);
	}
	for(int i=0; i<=8; i++) {
		mainLayout->setRowMinimumHeight(i,120);
	}*/
	
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
	
	
	//mainLayout->addWidget(startBtn, 0, 0, 1, 15);
	//mainLayout->addWidget(sld, 3, 1, 1, 12);
	//mainLayout->addWidget(quitBtn, 6, 13, 2, 2);
	//mainLayout->addWidget(devBtn, 6, 0, 2, 2);
	
	mainLayout->addWidget(startBtn);
	mainLayout->addWidget(modeDropdown);
	mainLayout->addWidget(sld);
	mainLayout->addWidget(devBtn);
	mainLayout->addWidget(quitBtn);
	
	//debuSize(startBtn);
	
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
void Window::send()
{
	mainSender->send("$F5000*");
}

void Window::StartRun()
{
	printf("Click\n");
	send();
}
    
void Window::OnSliderMoved(int i)
{
	printf("Wert ist %d\n",i);
}
   
void Window::Usermode()
{
	setWindowState(Qt::WindowFullScreen);
	devBtn->setText("DEVMODE");
	QObject::connect(devBtn, SIGNAL (clicked()), this, SLOT(Devmode()));
}

void Window::Devmode()
{
	setWindowState(Qt::WindowMaximized);
	devBtn->setText("USERMODE");
	QObject::connect(devBtn, SIGNAL (clicked()), this, SLOT(Usermode()));
}

/*void debugSize(QWidget *mywdg)
{
	QSize mysize = mywdg->frameSize();
	printf("Höhe: %d Breite: %d", mysize.height(), mysize.width());
}*/

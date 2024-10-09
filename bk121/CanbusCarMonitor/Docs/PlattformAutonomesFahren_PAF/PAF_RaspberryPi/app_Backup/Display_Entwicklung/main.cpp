/* Description */
/* ***************************************************
 * In der main Funktion wird eine qt-übliche
 * Initialisierung der Applikation vorgenommen,
 * ein Objekt vom Typ Window erstellt und dieses
 * aufgerufen.
 * **************************************************/
 
/* Libraries */
#include "Window.h"
#include <QLineEdit>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Window *wnd=new Window();
   wnd->show();
   QSize mysize = wnd->frameSize();
   return a.exec();
}

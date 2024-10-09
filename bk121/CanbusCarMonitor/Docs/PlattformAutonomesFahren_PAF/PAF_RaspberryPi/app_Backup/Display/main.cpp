/* Description */
/* ***************************************************
 * 
 * **************************************************/
 
/* Libraries */
#include "Window.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Window *wnd=new Window();
   wnd->show();
   QSize mysize = wnd->frameSize();
   return a.exec();
}

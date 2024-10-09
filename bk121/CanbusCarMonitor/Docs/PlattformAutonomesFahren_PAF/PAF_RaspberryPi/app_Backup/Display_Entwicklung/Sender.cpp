/* Description */
/* ***************************************************
 * Hier wird der Standardkonstruktor fuer ein Objekt
 * vom Typ 'sender' definiert und die Methode 'send'
 * ausformuliert. Dieser Code basiert auf Beispielen
 * aus Internet Recherchen.
 * **************************************************/

/* Libraries */
#include "Sender.h"

/* Constructors */
Sender::Sender()
{
	uart0_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (uart0_filestream == -1) {
		printf("[ERROR] UART open()\n");
	}

	/* UART Options */
	struct termios options;

	tcgetattr(uart0_filestream, &options);
	
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; 
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	tcflush(uart0_filestream, TCIFLUSH);

	tcsetattr(uart0_filestream, TCSANOW, &options);
}

/* Methods */
void Sender::send(const std::string daten)
{
	uart0_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

	if (uart0_filestream != -1)	{ 
		int out = write(uart0_filestream, daten,daten.length()+1); 
			if (out < 0) {
				printf("[ERROR] UART TX\n");
			} else {
				//printf("[STATUS: TX %i Bytes] %s\n", out, BUF_TX);
			}
	} 
	close(uart0_filestream);	
}

		

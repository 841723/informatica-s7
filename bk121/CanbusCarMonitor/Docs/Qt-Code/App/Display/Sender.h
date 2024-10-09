/* Description */
/* ***************************************************
 * Dieser Header-File dient dazu die Klasse 'sender'
 * zu definieren. Objekte der Klasse 'sender' koennen
 * den UART Kanal des Raspberry Pi's oeffnen und
 * ueber diesen einen 'string' senden.
 * **************************************************/

/* Includeguard */
#ifndef SENDER_H
#define SENDER_H

/* Libraries */
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

/* Class */
class Sender
{  
  public:
    int uart0_filestream = -1;
    Sender();
    void send(const char daten[20]);
};

#endif



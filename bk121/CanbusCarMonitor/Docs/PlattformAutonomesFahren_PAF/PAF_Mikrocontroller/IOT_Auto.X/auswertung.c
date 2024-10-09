
#include <xc.h>
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"
#include "motorcontrol.h"
#include "uart.h"
#include "uart_dsPIC.h"
#include "defines.h"

#include <stdlib.h> // für atoi()


/*
 *      CAN Auswertung (für Motoren PIC)
 */

int receivedMessageFlag = 0;
uint8_t test[8] = {0};
CAN_MSG_OBJ message;

void CanRxBufferInterruptHandler() {
    receivedMessageFlag = 1;
}

void CanMessageAuswertung() {
    // Überprüfe ob wirklich Nachrichten im Buffer liegen
    if(CAN1_ReceivedMessageCountGet() == 0) {
        receivedMessageFlag = 0;
        return;
    }
    
    // Speicherplatz für CAN_MSG_OBJ Daten
    message.data = test;
    
    // Hole Datensatz aus Buffer
    if(CAN1_Receive(&message) == true) {
        // checke ob ID NOTSTOP ID ist
        if(message.msgId == 0x1) {   // STOP ID
            stopMotor();
        }
        // Werte andere ID aus
        else {
            char befehl = *message.data;
            int schritte = 0;
            schritte += (*(message.data + 1)) << 8;
            schritte += (*(message.data + 2));
            // Führe Befehl aus und addiere ggf Restschritte zu aktuellem Stand
            befehlAusfuehren(befehl);
            addiereRestSchritte(schritte);
        }
    }
}



/*
 *      UART Auswertung (für Raspberry PIC)
 */

// sende per UART empfangene Daten auf den CAN Bus
void sendCAN(char befehl, int schritte) {
    CAN_MSG_OBJ message;
    uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char befehlLinks;
    char befehlRechts;
    
    // erstelle spezifische Befehle für die Motorseiten
    if(befehl == 'L') {
        befehlLinks = 'B';
        befehlRechts = 'F';
    }
    else if(befehl == 'R') {
        befehlLinks = 'F';
        befehlRechts = 'B';
    }
    else if(befehl == 'E') {
        // Sende eine leere Nachricht mit der ID 0x01 -> Notstop!
        message.msgId = 0x1;
        message.field.idType = CAN_FRAME_STD;
        message.field.frameType = CAN_FRAME_DATA;
        message.field.dlc = CAN_DLC_8;
        message.data = data;
        // starte CAN Transmission
        CAN1_Transmit(CAN_PRIORITY_NONE,&message);
        while(!C1INTFbits.TBIF);
        C1INTFbits.TBIF = 0;
        return;
    }
    else {
        befehlLinks = befehl;
        befehlRechts = befehl;
    }
    
    // Teile Schritte auf 3 mal 8 Byte auf
    data[1] = schritte >> 8;
    schritte &= 0x0000FF;
    data[2] = schritte;
    
    /* CAN Nachricht für MotorLinks */
    data[0] = befehlLinks;  // erstes Byte für Befehlszeichen
    // Zuweisung der Daten zum CAN Objekt
    message.msgId = 0x2;    // ID 0x02 für Motoren Links
    message.field.idType = CAN_FRAME_STD;
    message.field.frameType = CAN_FRAME_DATA;
    message.field.dlc = CAN_DLC_8;
    message.data = data;
    // starte CAN Transmission
    CAN1_Transmit(CAN_PRIORITY_NONE,&message);
    while(!C1INTFbits.TBIF);
    C1INTFbits.TBIF = 0;
    
    /* CAN Nachricht für MotorRechts */
    data[0] = befehlRechts; // erstes Byte für Befehlszeichen
    // Zuweisung der Daten zum CAN Objekt
    message.msgId = 0x3;    // ID 0x03 für Motoren Rechts
    message.field.idType = CAN_FRAME_STD;
    message.field.frameType = CAN_FRAME_DATA;
    message.field.dlc = CAN_DLC_8;
    message.data = data;
    // starte CAN Transmission    
    CAN1_Transmit(CAN_PRIORITY_NONE,&message);
    while(!C1INTFbits.TBIF);
    C1INTFbits.TBIF = 0;
}

// setze UART String zusammen und werte diesen aus
void UartAuswertung() {
    static char teststring[20];
    static int i = 0;
    static int keep = 0;
    
    // einlesen des nächsten Characters
    teststring[i] = UART1_Read();
    // Startzeichen eines Befehlsstrings
    if(teststring[i] == '$')
        keep = 1;
    // Endzeichen eines Befehlsstrings
    else if(teststring[i] == '*') {
        // Zerlege String in Befehlszeichen und Schrittanzahl
        char befehl = teststring[1];
        int schritte = atoi(teststring + 2);
        // starte CAN Transmission
        sendCAN(befehl, schritte);
        // leere String für den nöchsten Befehlsstring
        keep = 0;
        i = 0;
    }
    // String zu lang evtl Zeichenfehler
    if(i >= 19) {
        keep = 0;
        i = 0;
    }
    // wenn Befehlsstring erkannt zähle index hoch
    if(keep)
        i++;
}


#include <xc.h>
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"

#include <stdlib.h> // für atoi()

/*
 *      UART Auswertung (für Raspberry PIC)
 */

// Fahrzeugbefehle: F(orward) B(ackward) S(top) L(eft) R(ight) E(mergency Break)
// Motorbefehle:    F(orward) B(ackward) S(top)
// NOTSTOP SID 0x01
// MotorLinks SID 0x02
// MotorRechts SID 0x03

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

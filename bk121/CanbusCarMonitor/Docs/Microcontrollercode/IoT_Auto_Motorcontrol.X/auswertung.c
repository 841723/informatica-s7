
#include <xc.h>
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"
#include "motorcontrol.h"

#include <stdlib.h> // für atoi()


/*
 *      CAN Auswertung (für Motoren PIC)
 */

// Fahrzeugbefehle: F(orward) B(ackward) S(top) L(eft) R(ight) E(mergency Break)
// Motorbefehle:    F(orward) B(ackward) S(top)
// NOTSTOP SID 0x01
// MotorLinks SID 0x02
// MotorRechts SID 0x03

extern int motordef;
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
        else if((message.msgId == 0x2 && motordef == 2) || (message.msgId == 0x3 && motordef == 1) || motordef == 0)
            return;
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

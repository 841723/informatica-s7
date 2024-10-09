
#define FCY 40000000

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "defines.h"
#include "auswertung.h"
#include "motorcontrol.h"

#include <libpic30.h>
#include <stdlib.h> // für atoi()

// Testroutine zur CAN Übertragung mit Motorsteuerung
void transmitMessage() {
    CAN_MSG_OBJ message;
    int schritte = 5000;
    char befehl = 'F';
    uint8_t testdata[8];
    
    testdata[0] = befehl;
    
    testdata[1] = schritte >> 8;
    schritte &= 0x0000FF;
    testdata[2] = schritte;
    
    message.msgId = 0x2;
    message.field.idType = CAN_FRAME_STD;
    message.field.frameType = CAN_FRAME_DATA;
    message.field.dlc = CAN_DLC_8;
    message.data = testdata;
    
    CAN1_Transmit(CAN_PRIORITY_NONE,&message);
    while(!C1INTFbits.TBIF);
    C1INTFbits.TBIF = 0;
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
   
    CAN_STDBY_SetLow();     // Pull Low to enable CAN-IC, High to disable
    
#if defined(MOTOR_LINKS) || defined(MOTOR_RECHTS)
    // Initialisiere den Motor und aktiviere den CAN Empfänger
    initMotor();
    CAN1_ReceiveEnable();
    CAN1_SetRxBufferInterruptHandler(CanRxBufferInterruptHandler);
#endif
    
#ifdef RASPBERRY
    // Aktiviere den CAN Sender und UART Empfänger
    CAN1_TransmitEnable();
    UART1_Enable();
#endif
     
#ifdef CAN_TX_TEST
    // Teste das senden des CAN Bus
    CAN1_TransmitEnable();
    transmitMessage();
    transmitMessage();
    transmitMessage();
    transmitMessage();
#endif
        
#ifdef MOTOR_TEST
    // Teste den Motor mit x Schritten
    addiereRestSchritte(5000);
#endif
 
#ifdef UART_TEST
    // Test zum Empfangen von UART Nachrichten
    UART1_Enable();
    unsigned char test[] = "Test";
    int i;
    for(i=0;i<4;i++) {
        while(!UART1_IsTxReady());
        UART1_Write(test[i]);
        while(!UART1_IsTxDone());
    }
    char teststring[20];
    char befehl;
    int schritte;
    i = 0;
    int keep = 0;
#endif
    
    while(1) {
#if defined(MOTOR_LINKS) || defined(MOTOR_RECHTS)
        // checke ob CAN Nachrichten vorhanden sind und werte diese aus
        if(receivedMessageFlag)
            CanMessageAuswertung();
#endif
        
#ifdef RASPBERRY
        // checke ob UART Nachrichten ankommen und werte diese aus
        if(UART1_IsRxReady()) {
            UartAuswertung();
        }
#endif
        
#ifdef UART_TEST
        // Test zum Empfangen von UART Nachrichten
        if(UART1_IsRxReady()) {
            teststring[i] = UART1_Read();
            if(teststring[i] == '$')
                keep = 1;
            if(teststring[i] == '*') {
                keep = 0;
                befehl = teststring[0];
                schritte = atoi(teststring + 1);
                int debug = 0;
                debug = 1;
            }
            if(keep)
                i++;
        }
#endif        
    }
    
    return 1; 
}
/**
 End of File
*/


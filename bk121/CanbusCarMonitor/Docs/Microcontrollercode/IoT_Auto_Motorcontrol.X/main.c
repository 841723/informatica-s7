
#define FCY 40000000

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "auswertung.h"
#include "motorcontrol.h"

#include <libpic30.h>
#include <stdlib.h> // für atoi()

int motordef = 0;   // 0 - undefiniert; 1 - Motor-Links; 2 - Motor-Rechts

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // Motorauswahl per DIP Schalter
    // Motor-Links -> DIP 1 (dominant)
    // Motor-Rechts -> DIP 2
    if(DIP_SWITCH_1_GetValue() == true)
        motordef = 1;
    else if(DIP_SWITCH_2_GetValue() == true)
        motordef = 2;
    
    // Initialisiere CAN und DMA
    CAN1_Initialize();
    DMA_Initialize();
    
    // Initialisiere den Motor und aktiviere den CAN Empfänger
    initMotor();
    CAN1_ReceiveEnable();
    CAN1_SetRxBufferInterruptHandler(CanRxBufferInterruptHandler);
        
    // Teste den Motor mit x Schritten
//    addiereRestSchritte(2000);
    
    while(1) {
        // checke ob CAN Nachrichten vorhanden sind und werte diese aus
        if(receivedMessageFlag)
            CanMessageAuswertung();
    }
    
    return 1; 
}
/**
 End of File
*/


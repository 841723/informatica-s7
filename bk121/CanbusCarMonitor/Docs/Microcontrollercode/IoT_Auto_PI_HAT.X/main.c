
#define FCY 40000000

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "auswertung.h"

#include <libpic30.h>
#include <stdlib.h> // für atoi()

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // Aktiviere den CAN Sender und UART Empfänger
    CAN1_TransmitEnable();
    UART1_Enable();
    
    while(1) {
        // checke ob UART Nachrichten ankommen und werte diese aus
        if(UART1_IsRxReady()) {
            UartAuswertung();
        }      
    }
    
    return 1; 
}
/**
 End of File
*/


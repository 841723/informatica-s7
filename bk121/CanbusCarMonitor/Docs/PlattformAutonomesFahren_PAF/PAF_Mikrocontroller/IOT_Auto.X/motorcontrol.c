
#include <xc.h>
#include "defines.h"
#include "mcc_generated_files/pin_manager.h"
#include "motorcontrol.h"

volatile uint32_t restSchritte = 0;
volatile int anhaltenFlag = 0;
volatile int flag = 0;
volatile int changeDirection = 0;

// Initialisiere den Motor mit Timer
void initMotor() {
    T1CONbits.TON = 0;
    
                    // Timereinstellungen
    T1CONbits.TCS = 0;
    T1CONbits.TGATE = 0;
    T1CONbits.TCKPS = 0b11;     // Prescaler 1:256
    
    TMR1 = 0x00;
    
    PR1 = MOTOR_MIN_SPEED;  
    
                    // Interrupteinstellungen
    IPC0bits.T1IP = 0x01;
    IFS0bits.T1IF = 0;
    
    
    // Initialisiere Steuerpins (GPIOs)
    MOTOR_ENABLE_SetHigh();     // Enable L297, Pull Low to disable
    MOTOR_RESET_SetHigh();      // Pull Low to Reset L297 to HOME Position
    MOTOR_HALF_FULL_SetLow();   // Pull Low for FULL-STEP, High for HALF-STEP
    // Vorwärtsdefinition
#ifdef MOTOR_LINKS
    MOTOR_CW_CCW_SetHigh();     // Pull Low for CounterClockWise, High for ClockWise Rotation
#endif
#ifdef MOTOR_RECHTS
    MOTOR_CW_CCW_SetLow();      // Pull Low for CounterClockWise, High for ClockWise Rotation
#endif
    MOTOR_CONTROL_SetHigh();    // Pull High for Chopping on ABCD, Low for INH1/2
}

// Timer Interrupt Routine
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {
    // Toggle CLOCK Pin of L297
    MOTOR_CLOCK_Toggle();
    // Step at every Low->High Transition
    // only every 2nd Interrupt is a step
    if(flag) {
        schrittAuswertung();
        flag = 0;
    }
    else
        flag = 1;
    
    // Reset Timercounter and Interruptflag
    TMR1 = 0;
    IFS0bits.T1IF = 0;
}

// Auswertung der Restschritte und Steuerung des Periodenregisters -> Geschwindigkeit
void schrittAuswertung() {
    // Bei Richtungswechsel abbremsen, Richtung ändern und wieder anfahren
    if(changeDirection != 0) {
        if(PR1 < MOTOR_MIN_SPEED)
            PR1 += MOTOR_ACCELERATION;
        else {
            PR1 = MOTOR_MIN_SPEED;
            MOTOR_CW_CCW_Toggle();
            changeDirection = 0;
        }
    }
    // Zum anhalten abbremsen dann stoppen
    else if(anhaltenFlag != 0) {
        if(PR1 < MOTOR_MIN_SPEED)
            PR1 += MOTOR_ACCELERATION;
        else {
            stopMotor();
            PR1 = MOTOR_MIN_SPEED;
        }
    }
    // wenn Schritte aufgebraucht stoppen
    else if(restSchritte <= 0) {
        stopMotor();
        PR1 = MOTOR_MIN_SPEED;
        anhaltenFlag = 0;
    }
    // abbremsen wenn nur noch genug Restschritte zum gerade eben anhalten
    else if(restSchritte <= ((MOTOR_MIN_SPEED - PR1) / MOTOR_ACCELERATION) && PR1 < MOTOR_MIN_SPEED) {
        PR1 += MOTOR_ACCELERATION;
    }
    // beschleunigen solange noch nicht full speed
    else if(PR1 > MOTOR_MAX_SPEED) {
        PR1 -= MOTOR_ACCELERATION;
    }
    // Restschritte reduzieren
    restSchritte--;
    
    // Test zum anhalten (einkommentieren)
//    if(restSchritte <= 3990 && restSchritte >= 3980)
//        anhalten();
    
    // Test zum Richtungswechsel (einkommentieren)
//    if(restSchritte <= 3990 && restSchritte >= 3980)
//        changeDirection = 1;
}

// addiere neue Restschritte zum akteullem Stand hinzu und starte Motor falls noch nicht läuft
void addiereRestSchritte(uint32_t schritte) {
    restSchritte += schritte;
    if(T1CONbits.TON == 0 && restSchritte > 0) {
        startMotor();
    }
}

// Starte Motor (Timer)
void startMotor() {
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
}

// Stoppe Motor (Timer)
void stopMotor() {
    IEC0bits.T1IE = 0;
    T1CONbits.TON = 0;
    anhaltenFlag = 0;
}

// Starte Abbremsvorgang und verwerfe Restschritte
void anhalten() {
    anhaltenFlag = 1;
    restSchritte = 0;
}

// Auswertung des Befehls
void befehlAusfuehren(uint8_t befehl) {
    // ggf Richtungswechsel einleiten
    if(befehl == 'F') {         // forward
#ifdef MOTOR_LINKS
        if(MOTOR_CW_CCW_GetValue() == 0) {
            changeDirection = 1;
        }
#endif
#ifdef MOTOR_RECHTS
        if(MOTOR_CW_CCW_GetValue() != 0) {
            changeDirection = 1;
        }
#endif
    }
    // ggf Richtungswechsel einleiten
    else if(befehl == 'B') {    // backward
#ifdef MOTOR_LINKS
        if(MOTOR_CW_CCW_GetValue() != 0) {
            changeDirection = 1;
        }
#endif
#ifdef MOTOR_RECHTS
        if(MOTOR_CW_CCW_GetValue() == 0) {
            changeDirection = 1;
        }
#endif
    }
    // leite Abbremsvorgang ein
    else if(befehl == 'S') {    // stop
        anhalten();
    }
}

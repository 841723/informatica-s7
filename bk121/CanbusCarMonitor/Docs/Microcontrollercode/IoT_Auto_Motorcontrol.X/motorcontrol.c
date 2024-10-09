
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "motorcontrol.h"

volatile uint32_t restSchritte = 0;
volatile int anhaltenFlag = 0;
volatile int flag = 0;
volatile int changeDirection = 0;
   
volatile int T_Steps = MOTOR_MIN_SPEED;
volatile int StepCounter = 0;
volatile int AccCounter = 0;
volatile int StepAccCounter = 0;

extern int motordef;

// Initialisiere den Motor mit Timer
void initMotor() {
    T1CONbits.TON = 0;
    
                    // Timereinstellungen
    T1CONbits.TCS = 0;
    T1CONbits.TGATE = 0;
    T1CONbits.TCKPS = 0b10;// 1:64
    
    TMR1 = 0x00;
    
    PR1 = 25;// alle 20us  
    
                    // Interrupteinstellungen
    IPC0bits.T1IP = 0x01;
    IFS0bits.T1IF = 0;
    
    
    // Initialisiere Steuerpins (GPIOs)
    MOTOR_ENABLE_SetHigh();     // Enable L297, Pull Low to disable
    MOTOR_HALF_FULL_SetHigh();   // Pull Low for FULL-STEP, High for HALF-STEP
    // Vorwärtsdefinition
    if(motordef == 1)
        MOTOR_CW_CCW_SetHigh();     // Pull Low for CounterClockWise, High for ClockWise Rotation
    if(motordef == 2)
        MOTOR_CW_CCW_SetLow();      // Pull Low for CounterClockWise, High for ClockWise Rotation
}

// Timer Interrupt Routine
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {
    
    schrittAuswertung();
    
    // Reset Timercounter and Interruptflag
    TMR1 = 0;
    IFS0bits.T1IF = 0;
}

// Neues Anfahrverhalten Timer konstant bei 20us 
void schrittAuswertung() {
    // Schritte ausführen
    StepCounter++;
    if(StepCounter >= T_Steps) {
        MOTOR_CLOCK_Toggle();
        StepCounter = 0;
        // Jeden zweiten Toggle einen Schritt
        if(flag) {
            if(T_Steps > MOTOR_MAX_SPEED) {
                if(anhaltenFlag != 0 || changeDirection != 0)
                    StepAccCounter--;
                else
                    StepAccCounter++;
            }
            if(StepAccCounter >= restSchritte)
                anhalten();
            restSchritte--;
            flag = 0;
        }
        else
            flag = 1;
        // wenn Schritte aufgebraucht stoppen
        if(restSchritte <= 0) {
            stopMotor();
            T_Steps = MOTOR_MIN_SPEED;
            anhaltenFlag = 0;
        }
    }
    
    // Beschleunigung ausführen
    AccCounter++;
    if(AccCounter >= MOTOR_PERIOD_ACCELERATION) {
        // Bei Richtungswechsel abbremsen, Richtung ändern und wieder anfahren
        if(changeDirection != 0) {
            if(T_Steps < MOTOR_MIN_SPEED)
                T_Steps += MOTOR_ACCELERATION;
            else {
                T_Steps = MOTOR_MIN_SPEED;
                if(MOTOR_CW_CCW_GetValue() == 0)
                    MOTOR_CW_CCW_SetHigh();
                else
                    MOTOR_CW_CCW_SetLow();
                changeDirection = 0;
            }
        }
        // Zum anhalten abbremsen dann stoppen
        else if(anhaltenFlag != 0) {
            if(T_Steps < MOTOR_MIN_SPEED)
                T_Steps += MOTOR_ACCELERATION;
            else {
                stopMotor();
                T_Steps = MOTOR_MIN_SPEED;
            }
        }
        // beschleunigen solange noch nicht full speed
        else if(T_Steps > MOTOR_MAX_SPEED) {
            T_Steps -= MOTOR_ACCELERATION;
        }
        AccCounter = 0;
    }
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
    changeDirection = 0;
    restSchritte = 0;
    StepAccCounter = 0;
}

// Starte Abbremsvorgang und verwerfe Restschritte
void anhalten() {
    anhaltenFlag = 1;
}

// Auswertung des Befehls
void befehlAusfuehren(uint8_t befehl) {    
    // ggf Richtungswechsel einleiten
    if(befehl == 'F') {         // forward
        if(motordef == 1) {
            if(MOTOR_CW_CCW_GetValue() == 0) {
                if(restSchritte > 0)
                    changeDirection = 1;
                else
                    MOTOR_CW_CCW_SetHigh();
            }
        }
        if(motordef == 2) {
            if(MOTOR_CW_CCW_GetValue() != 0) {
                if(restSchritte > 0)
                    changeDirection = 1;
                else
                    MOTOR_CW_CCW_SetLow();
            }
        }
    }
    // ggf Richtungswechsel einleiten
    else if(befehl == 'B') {    // backward
        if(motordef == 1) {
            if(MOTOR_CW_CCW_GetValue() != 0) {
                if(restSchritte > 0)
                    changeDirection = 1;
                else
                    MOTOR_CW_CCW_SetLow();
            }
        }
        if(motordef == 2) {
            if(MOTOR_CW_CCW_GetValue() == 0) {
                if(restSchritte > 0)
                    changeDirection = 1;
                else
                    MOTOR_CW_CCW_SetHigh();
            }
        }
    }
    // leite Abbremsvorgang ein
    else if(befehl == 'S') {    // stop
        anhalten();
    }
}

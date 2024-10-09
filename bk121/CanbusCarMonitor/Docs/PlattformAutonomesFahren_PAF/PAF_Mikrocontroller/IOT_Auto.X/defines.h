
// Definiere welche Platine programmiert werden soll
#define MOTOR_LINKS
//#define MOTOR_RECHTS
//#define RASPBERRY

// Aktiviere Testfunktionen
//#define MOTOR_TEST
//#define UART_TEST
//#define CAN_TX_TEST

// Geschwindigkeits- und Beschleunigungsparameter für die Motoren
#define MOTOR_ACCELERATION 10
#define MOTOR_MAX_SPEED 150
#define MOTOR_MIN_SPEED 1150

// Fahrzeugbefehle: F(orward) B(ackward) S(top) L(eft) R(ight) E(mergency Break)
// Motorbefehle:    F(orward) B(ackward) S(top)
// NOTSTOP SID 0x01
// MotorLinks SID 0x02
// MotorRechts SID 0x03

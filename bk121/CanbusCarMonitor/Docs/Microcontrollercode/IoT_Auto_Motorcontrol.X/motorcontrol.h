
// Geschwindigkeits- und Beschleunigungsparameter für die Motoren
#define MOTOR_ACCELERATION 1//5
#define MOTOR_MAX_SPEED 12//75
#define MOTOR_MIN_SPEED 92 //575

#define MOTOR_PERIOD_ACCELERATION 200

extern void initMotor();
extern void schrittAuswertung();
extern void addiereRestSchritte(uint32_t);
extern void startMotor();
extern void stopMotor();
extern void befehlAusfuehren(uint8_t befehl);
extern void anhalten();



#include <Servo.h>

const int PIN_S1 =10;
const int PIN_S2 = 6;

const int POS_A = 0;
const int POS_B = 120;
const int PAUSA_INICIAL = 5000;
const int PAUSA_1 = 3000;
const int PAUSA_2 = 5000;

Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(PIN_S1);
  servo2.attach(PIN_S2);
  //posicion inicial
  servo1.write(POS_A);
  servo2.write(POS_A);
  delay (PAUSA_INICIAL);
}

void loop() {
//ir a posocion B
  servo1.write(POS_B);
  servo2.write(POS_B);
  delay(PAUSA_1);
// vuelta a A
  servo1.write(POS_A);
  servo2.write(POS_A);
  delay(PAUSA_2);
}

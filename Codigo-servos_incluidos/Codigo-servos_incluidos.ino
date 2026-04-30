#include <Servo.h>

// --- Parámetros configurables ---
const int PIN_EMG   = A0;
const int PIN_S1    = 10;
const int PIN_S2    = 11;

const float N         = 10.0;   // Fuerza del filtro (más alto = más suave)
const int   UMBRAL    = 50;    // Umbral de activación (0–1023). Ajusta según tu señal EMG
const int   POS_CIERRE1  = 120;      // Posición servo1 al activarse
const int   POS_CIERRE2  = 120;    // Posición servo2 al activarse
const int   POS_SUELTA1  = 0;     // Posición servo1 en reposo
const int   POS_SUELTA2  = 0;     // Posición servo2 en reposo

// --- Variables globales ---
float   medida       = 0.0;
bool    activado     = false;

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_EMG, INPUT);
  servo1.attach(PIN_S1);
  servo2.attach(PIN_S2);

  // Posición inicial de reposo
  servo1.write(POS_SUELTA1);
  servo2.write(POS_SUELTA2);
}

void loop() {
  // Filtro de media móvil exponencial
  medida = medida * (N - 1.0) / N + (float)analogRead(PIN_EMG) / N;

  Serial.print("EMG: ");
  Serial.println(medida);   // Útil para calibrar el umbral

  if (medida >= UMBRAL && !activado) {
    // --- Flanco de subida: señal supera el umbral ---
    activado = true;
    servo1.write(POS_CIERRE1);
    servo2.write(POS_CIERRE2);

  } else if (medida < UMBRAL && activado) {
    // --- Flanco de bajada: señal cae bajo el umbral ---
    activado = false;
    servo1.write(POS_SUELTA1);
    servo2.write(POS_SUELTA2);
  }

  // TODO (fase 2): mapear medida → ángulo proporcional
  // int angulo = map((int)medida, UMBRAL, 1023, 0, 180);
  // servo1.write(angulo);

  delay(20);   // ~50 Hz, adecuado para señal EMG de superficie
}
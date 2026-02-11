// EMG con filtros → LED trigger (preparado para servos)
#include <Servo.h>  // Para futuros servomotores

// Pines
const int EMG_PIN = A0;
const int LED_PIN = 10;    // LED integrado Arduino
// const int SERVOPULGAR_PIN = 9;  // Descomenta para dedo 1
// const int SERVOEDOS_PIN = 10; // Descomenta para dedo 2

// Filtros EMA
float alpha = 0.8;           // Suavizado (ajusta 0.6-0.9)
float ema_lp = 512;          // Inicial pasa-bajo (mitad ADC)
float rms = 0;               // Envelope muscular (fuerza)

// Umbrales (ajusta con Serial Plotter)
const float UMBRAL_CONTRACCION = 40;  // Valor RMS para encender LED (FELXIÓN FUERTE)
const float UMBRAL_REPOSO = 15;       // Para evitar rebotes (REPOSO + 2-3)

// Estado
bool contraccion_activa = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  // myservo1.attach(SERVOPULGAR_PIN);  // Descomenta para servos
  // myservo2.attach(SERVODEDOS_PIN);
  
  Serial.println("EMG → LED iniciado. Flexiona para calibrar.");
  delay(2000);
}

void loop() {
  // 1. Lectura cruda EMG
  int raw = analogRead(EMG_PIN);
  
  // 2. Filtro pasa-bajo exponencial
  ema_lp = alpha * raw + (1 - alpha) * ema_lp;
  
  // 3. Pasa-alto (elimina DC offset)
  float ema_hp = raw - ema_lp;
  
  // 4. Rectificación + RMS suave (mide fuerza muscular)
  rms = 0.95 * rms + 0.05 * abs(ema_hp);
  
  // 5. Detección contracción con histéresis (evita parpadeos)
  if (rms > UMBRAL_CONTRACCION && !contraccion_activa) {
    contraccion_activa = true;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("¡CONTRACCIÓN DETECTADA!");
  }
  else if (rms < UMBRAL_REPOSO && contraccion_activa) {
    contraccion_activa = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("Reposo");
  }
  
  // Debug en Serial Plotter
  Serial.print("RMS:"); Serial.print(rms, 1);
  Serial.print(" | Estado:"); Serial.println(contraccion_activa ? "ACTIVO" : "REPOSO");
  
  delay(5);  // ~200Hz muestreo (suficiente para EMG)
}


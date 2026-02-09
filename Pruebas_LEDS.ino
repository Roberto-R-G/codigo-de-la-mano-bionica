#define LED_PIN 10

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // FADE IN: 0 → 255 (500ms)
  for(int brillo = 0; brillo <= 255; brillo += 5) {
    analogWrite(LED_PIN, brillo);
    delay(10);  // 255/5 * 10ms = 500ms
  }
  
  // FADE OUT: 255 → 0 (500ms)  
  for(int brillo = 255; brillo >= 0; brillo -= 5) {
    analogWrite(LED_PIN, brillo);
    delay(10);  // Total: 1 segundo por ciclo
  }
}

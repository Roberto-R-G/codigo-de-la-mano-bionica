const int ledPin = 5;

int brightness = 0;
int step = 5;

void setup() {
  ledcAttach(ledPin, 5000, 8);
}

void loop() {
  ledcWrite(ledPin, brightness);

  brightness += step;

  if (brightness <= 0 || brightness >= 255) {
    step = -step;
  }

  delay(20);
}

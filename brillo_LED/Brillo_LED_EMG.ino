#define PIN_EMG A0
int medida = 0;
int brillo = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_EMG, INPUT);
  pinMode(10, OUTPUT); //PWM

}

void loop() {
medida = analogRead(PIN_EMG);
Serial.println(medida);
brillo = map(medida, 0, 1023, 0, 255);
analogWrite(10, brillo);
}

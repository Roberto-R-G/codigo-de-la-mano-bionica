int brillo = 0;
int cambio = 5;
bool subiendo = true;

void setup() {
  // put your setup code here, to run once:
pinMode (10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(10, brillo);
  
  // Cambia brillo gradualmente
  if(subiendo) {
    brillo += cambio;
    if(brillo >= 255) {
      subiendo = false;  // Cambia dirección
    }
  } else {
    brillo -= cambio;
    if(brillo <= 0) {
      subiendo = true;   // Cambia dirección
    }
  }
  
  delay(30);  // Velocidad suave
}

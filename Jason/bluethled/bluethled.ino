/**
 * Práctica 3
 */
int estado = "";
const int LED = 13;

/** Inicializa pines y puerto serial.  */
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);    // Arduino One sólo tiene un serial
}

/** Periódicamente revisa si hay instrucciones y asigna el estado del LED. */
void loop() {
  // Ejemplo: prende led
  digitalWrite(LED, HIGH);

  if(Serial.available() > 0) {
    estado = Serial.read();
    Serial.println("Estado" + estado);
    String teststr = Serial.readString();  // leer hasta que se termine el tiempo
    teststr.trim();                        // remueve cualquier blanco \r \n al final de la cadena leída
    if (teststr == "led") {
      Serial.println("Prende/apaga led");
      // TODO: prender y apagar led
    } else {
      Serial.println("Ignorar");
    }
  }
}

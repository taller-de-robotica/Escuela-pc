/**
Práctica 1
Autores:
  César Arzate
  Verónica E. Arriola
(versión: Mega 2560)
ARDUINO L293D(Puente H)
 5  10
 6  15
 9   7
10   2
5V   1, 9, 16
GND  4, 5, 12, 13
El motor 1 se conecta a los pines 3 y 6 del Puente H
El motor 2 se conecta a los pines 11 y 14 del Puente H
La fuente de alimentacion de los Motores se conecta a tierra y
el positivo al pin 8 del puennte H.
*/

// Pines
const int IZQ_A = 5;  // Pines a entradas <1:4>A
const int IZQ_B = 6;
const int DER_A = 9;
const int DER_B = 10;

// Estado
int vel = 255; // Velocidad de los motores (0-255)


/* Se ejecuta una sola vez, al inicio. */
void setup() {
  pinMode(DER_A, OUTPUT);
  pinMode(DER_B, OUTPUT);
  pinMode(IZQ_A, OUTPUT);
  pinMode(IZQ_B, OUTPUT);
}

/* Ejecución repetida */
void loop() {
  digitalWrite(DER_A, HIGH);
  digitalWrite(IZQ_A, HIGH);
  digitalWrite(DER_B, LOW);
  digitalWrite(IZQ_B, LOW);
  delay (1000);              // Esperar 1s
  digitalWrite(DER_A, LOW);
  digitalWrite(IZQ_A, LOW);
  digitalWrite(DER_B, LOW);
  digitalWrite(IZQ_B, LOW);
  delay (1000);
}

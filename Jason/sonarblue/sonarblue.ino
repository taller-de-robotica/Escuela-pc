/**
 * Práctica 3
 * Carro con Sensor de Distancia y Bluetooth
 * ARDUINO L293D(Puente H)
 * Conexiones a pines:
 * 5 10
 * 6 15
 * 9 7
 * 10 2
 * 5V 1, 9, 16
 * GND 4, 5, 12, 13
 * El motor 1 se conecta a los pines 3 y 6 del Puente H
 * El motor 2 se conecta a los pines 11 y 14 del Puente H
 * La fuente de alimentacion de los Motores se conecta a tierra y
 * el positivo al pin 8 del puennte H.
 *
 * Conexión entre el Módulo Bluetooth HC-06 y el Arduino
 * ARDUINO Bluetooth HC-06
 * 0 (RX) TX
 * 1 (TX) RX
 * 5V VCC
 * GND GND
 * !!Cuidado!! Las conexiones de TX y RX al modulo Bluetooth deben
 * estar desconectadas en el momento que se realiza la carga del
 * código (Sketch) al Arduino.
 *
 * Conexion Sensor Ultrasonido HC-SR04
 * ARDUINO Ultrasonido HC-SR04
 * 2 Echo
 * 3 Trig
 * 5V VCC
 * GND Gnd
 */

// Pines
const int IZQ_A = 5;  // Pines a entradas <1:4>A
const int IZQ_B = 6;
const int DER_A = 9;
const int DER_B = 10;

int vel = 255;        // Velocidad de los motores (0-255)
int estado = "g";     // Inicia detenido

const int P_ECHO = 2;        // define el pin 2 como (P_ECHO) para el Ultrasonido
const int P_TRIG = 3;        // define el pin 3 como (P_TRIG) para el Ultrasonido
int duracion, distancia;     // para Calcular distacia

/* Asigna el modo de funcionamiento de los pines al iniciar. */
void setup() {
    Serial.begin(9600); // inicia el puerto serial para
    comunicacion con el Bluetooth
    pinMode(DER_A, OUTPUT);
    pinMode(DER_B, OUTPUT);

    pinMode(IZQ_A, OUTPUT);
    pinMode(IZQ_B, OUTPUT);
    pinMode(P_ECHO, INPUT);  // define el pin 2 como entrada
    pinMode(P_TRIG, OUTPUT); // define el pin 3 como salida
    pinMode(13, OUTPUT);
}

/* Periódicamente revisa si ha recibido un comando
 * y actualiza el estado de movimiento del robot. */
void loop() {
    if(Serial.available() > 0){ // lee el bluetooth y almacena en estado
        estado = Serial.read();
    }
    if(estado=="a"){ // Boton desplazar al Frente
        analogWrite(DER_B, 0);
        analogWrite(IZQ_B, 0);
        analogWrite(DER_A, vel);
        analogWrite(IZQ_A, vel);
    }
    if(estado=="b"){ // Boton IZQ
        analogWrite(DER_B, 0);
        analogWrite(IZQ_B, 0);
        analogWrite(DER_A, 0);
        analogWrite(IZQ_A, vel);
    }
    if(estado=="c"){ // Boton Parar
        analogWrite(DER_B, 0);
        analogWrite(IZQ_B, 0);
        analogWrite(DER_A, 0);
        analogWrite(IZQ_A, 0);
    }
    if(estado=="d"){ // Boton DER
        analogWrite(DER_B, 0);
        analogWrite(IZQ_B, 0);
        analogWrite(IZQ_A, 0);
        analogWrite(DER_A, vel);
    }
    if(estado=="e"){ // Boton Reversa
        analogWrite(DER_A, 0);
        analogWrite(IZQ_A, 0);
        analogWrite(DER_B, vel);
        analogWrite(IZQ_B, vel);
    }
    if (estado =="f"){ // Boton ON, se mueve sensando distancia

        digitalWrite(P_TRIG, HIGH); // genera el pulso de trigger por 10us
        delay(0.01);
        digitalWrite(P_TRIG, LOW);
        duracion = pulseIn(P_ECHO, HIGH); // Lee el tiempo del Echo
        distancia = (duracion/2) / 29;   // calcula la distancia en centimetros
        delay(10);
        if (distancia <= 15 && distancia >= 2){ // si la distancia es menor de 15cm
            digitalWrite(13,HIGH);  // Enciende LED
            analogWrite(DER_B, 0);   // Parar los motores por 200 mili segundos
            analogWrite(IZQ_B, 0);
            analogWrite(DER_A, 0);
            analogWrite(IZQ_A, 0);
            delay (200);
            analogWrite(DER_B, vel); // Reversa durante 500 mili segundos
            analogWrite(IZQ_B, vel);
            delay(500);
            analogWrite(DER_B, 0);   // Girar durante 1100 milisegundos
            analogWrite(IZQ_B, 0);
            analogWrite(DER_A, 0);
            analogWrite(IZQ_A, vel);
            delay(1100);
            digitalWrite(13,LOW);
        }
        else{ // Si no hay obstaculos se desplaza
            al frente
            analogWrite(DER_B, 0);
            analogWrite(IZQ_B, 0);
            analogWrite(DER_A, vel);
            analogWrite(IZQ_A, vel);
        }
    }
    if(estado == "g"){ // Boton OFF, detiene los motores no hace nada
        analogWrite(DER_B, 0);
        analogWrite(IZQ_B, 0);
        analogWrite(DER_A, 0);
        analogWrite(IZQ_A, 0);
    }
}

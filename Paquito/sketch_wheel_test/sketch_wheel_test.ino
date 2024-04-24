/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car Lesson5 Wifi Control
 * CopyRight www.osoyoo.com
 * ___________________________________________________________________
 *
 * Prueba de las llantas.
 * Adaptación para Taller de Robótica Proyecto PAPIME PE104223
 * @author blackzafiro
 *
 */

#define speedPinR 3            // Front Wheel PWM pin connect Model-Y M_B ENA 
#define RightMotorDirPin1 48   // Front Right Motor direction pin 1 to Model-Y M_B IN1 (K1)
#define RightMotorDirPin2 49   // Front Right Motor direction pin 2 to Model-Y M_B IN2 (K1)
#define LeftMotorDirPin1  46   // Front Left Motor direction pin 1 to Model-Y M_B IN3  (K3)
#define LeftMotorDirPin2  47   // Front Left Motor direction pin 2 to Model-Y M_B IN4  (K3)
#define speedPinL 5            // Front Wheel PWM pin connect Model-Y M_B ENB

#define speedPinRB 6           // Rear Wheel PWM pin connect Left Model-Y M_A ENA 
#define RightMotorDirPin1B 52  // Rear Right Motor direction pin 1 to Model-Y M_A IN1 (K1)
#define RightMotorDirPin2B 53  // Rear Right Motor direction pin 2 to Model-Y M_A IN2 (K1) 
#define LeftMotorDirPin1B  50  // Rear Left Motor direction pin 1 to Model-Y M_A IN3  (K3)
#define LeftMotorDirPin2B  51  // Rear Left Motor direction pin 2 to Model-Y M_A IN4  (K3)
#define speedPinLB 7           // Rear Wheel PWM pin connect Model-Y M_A ENB

///
/// Control de motores
///

/*
 * Llanta delantera derecha.
 * Si la velocidad es cero frena.
 * Si la velocidad es negativa gira hacia atrás.
 */
void front_right_wheel(int speed)
{
  if (speed >= 0)  // Adelante
  {  
    digitalWrite(RightMotorDirPin1, HIGH);
    digitalWrite(RightMotorDirPin2, LOW); 
    analogWrite(speedPinR, speed);
  }
  else             // Atrás
  {       
    speed *= -1;
    digitalWrite(RightMotorDirPin1, LOW);
    digitalWrite(RightMotorDirPin2, HIGH); 
    analogWrite(speedPinR, speed);
  }
}

/*
 * Llanta delantera izquierda.
 * Si la velocidad es cero frena.
 * Si la velocidad es negativa gira hacia atrás.
 */
void front_left_wheel(int speed)
{
  if (speed >= 0)  // Adelante
  {
    digitalWrite(LeftMotorDirPin1, HIGH);
    digitalWrite(LeftMotorDirPin2, LOW);
    analogWrite(speedPinL, speed);
  }
  else             // Atrás
  {
    speed *= -1;
    digitalWrite(LeftMotorDirPin1, LOW);
    digitalWrite(LeftMotorDirPin2, HIGH);
    analogWrite(speedPinL, speed);
  }
}

/*
 * Llanta trasera derecha.
 * Si la velocidad es cero frena.
 * Si la velocidad es negativa gira hacia atrás.
 */
void rear_right_wheel(int speed)
{
  if (speed >= 0)  // Adelante
  {
    digitalWrite(RightMotorDirPin1B, HIGH);
    digitalWrite(RightMotorDirPin2B,LOW); 
    analogWrite(speedPinRB,speed);
  }
  else             // Atrás
  {
    speed *= -1;
    digitalWrite(RightMotorDirPin1B, LOW);
    digitalWrite(RightMotorDirPin2B,HIGH); 
    analogWrite(speedPinRB,speed);
  }
}

/*
 * Llanta trasera izquierda.
 * Si la velocidad es cero frena.
 * Si la velocidad es negativa gira hacia atrás.
 */
void rear_left_wheel(int speed)
{
  if (speed >= 0)  // Adelante
  {
    digitalWrite(LeftMotorDirPin1B,HIGH);
    digitalWrite(LeftMotorDirPin2B,LOW);
    analogWrite(speedPinLB,speed);
  }
  else             // Atrás
  {
    speed *= -1;
    digitalWrite(LeftMotorDirPin1B,LOW);
    digitalWrite(LeftMotorDirPin2B,HIGH);
    analogWrite(speedPinLB,speed);
  }
}

/*
 * Frena todas las llantas.
 */
void stop_car() {
  analogWrite(speedPinLB, 0);
  analogWrite(speedPinRB, 0);
  analogWrite(speedPinL, 0);
  analogWrite(speedPinR, 0);
}

/*
 * Inicialización de los pins
 */
void init_GPIO() {
  // Frente
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  
  // Tras
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);
   
  stop_car();
}

///
/// Comunicación por WiFi
///

#include "WiFiEsp.h"
#include "WiFiEspUdp.h"


#ifndef HOTSPOT
char ssid[] = "******"; // replace ****** with your network SSID (name)
char pass[] = "******"; // replace ****** with your network password
#else
/// Si el robot será el hotspot
char ssid[] = "osoyoo_robot"; 
#endif


int status = WL_IDLE_STATUS;
// use a ring buffer to increase speed and reduce memory allocation
char packetBuffer[5]; 
WiFiEspUDP Udp;
unsigned int localPort = 8888;  // local port to listen on

/*
 * Inicializa conexión WiFi
 */
void init_WiFi() {
  Serial1.begin(115200);
  Serial1.write("AT+UART_DEF=9600,8,1,0,0\r\n");
  delay(200);
  Serial1.write("AT+RST\r\n");
  delay(200);
  Serial1.begin(9600);    // initialize serial for ESP module
  WiFi.init(&Serial1);    // initialize ESP module

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
#ifndef HOTSPOT
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
#else
    //AP mode
    status = WiFi.beginAP(ssid, 10, "", 0);
#endif
  }

  Serial.println("You're connected to the network");
  printWiFiStatus();
  Udp.begin(localPort);
  
  Serial.print("Listening on port ");
  Serial.println(localPort);
}

/*
 * Imprime el estado de la conexión WiFi
 */
void printWiFiStatus() {
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to connect
  Serial.println();
  Serial.print("Send UDP message to http://");
  Serial.println(ip);
  Serial.println();
}


void setup() {
  Serial.begin(9600);    // depurado usando un puerto serial
  Serial.println(".´`. paquito init .´`.");

  init_GPIO();           // inicializa pines que conectan con los controladores
  init_WiFi();           // inicializa WiFi
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {                           // if you get a client,
    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    char c = packetBuffer[0];
    Serial.print(" char: ");
    Serial.println(c);

    int speed = 70;
    switch (c)                                // serial control instructions
    {  
      // Avanza llanta por llanta
      case '9':front_right_wheel(speed);break;
      case '7':front_left_wheel(speed);break;
      case '3':rear_right_wheel(speed);break;
      case '1':rear_left_wheel(speed);break;
      // Frena llanta por llanta
      case '4':front_right_wheel(0);break;
      case '6':front_left_wheel(0);break;
      case '0':rear_right_wheel(0);break;
      case '.':rear_left_wheel(0);break;
      case '5':stop_car();break;
      // Retrocede llanta por llanta
      case 'r':front_right_wheel(-speed);break;
      case 'e':front_left_wheel(-speed);break;
      case 'f':rear_right_wheel(-speed);break;
      case 'd':rear_left_wheel(-speed);break;
      default:break;
    }
  }
}

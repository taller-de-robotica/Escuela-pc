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

void setup() {
  // Depurado usando un puerto serial
  Serial.begin(9600);
  Serial.println(".´`. paquito init .´`.");
}

void loop() {
  // put your main code here, to run repeatedly:

}

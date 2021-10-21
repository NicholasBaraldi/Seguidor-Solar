#include <Servo.h>
#include <SoftwareSerial.h>
#define pin_servo_horizontal 5
#define pin_servo_vertical 4
#define pinSerialRX 2
#define pinSerialTX 3

Servo servo_horizontal;
Servo servo_vertical;
SoftwareSerial bluetooth(pinSerialRX, pinSerialTX);  //RX, TX

String comando;

void setup() {

   Serial.begin(9600);                           //Inicializa a comunicação serial padrão
   bluetooth.begin(9600);                     //Inicializa a comunicação com o módulo HC-05
   servo_horizontal.attach(pin_servo_horizontal);
   servo_horizontal.write(90);
   servo_vertical.attach(pin_servo_vertical);
   servo_vertical.write(90);   
}

void loop() {
 
if (bluetooth.available()) {                   // Módulo recebe dados
      char recebido = bluetooth.read();

      comando += recebido;

   if (recebido == ';') {

       if (comando == "A;") {
       servo_horizontal.write(70);
       servo_vertical.write(30);
       } 
       else if (comando == "B;") {
       servo_horizontal.write(10);
       servo_vertical.write(30);
       }
       else if (comando == "C;") {
       servo_horizontal.write(10);
       servo_vertical.write(10);
       }
  
     comando = "";
     }

  }

}

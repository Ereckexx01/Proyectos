#include <ESP32Servo.h>
#include "BluetoothSerial.h"

int trig = 13;
int echo = 12;
long duration;
int distance;

Servo servo_radar;
int pin_radar = 2; // servo-radar
double t_1 = 0.0;

Servo servo_timon;
int pin_timon = 4;
int numeros[] = {49, 50, 51, 52, 53}; //Botones Bluetooth
int direccion_grad[] = {50, 70, 90, 110, 130}; 

BluetoothSerial BT; //Objeto Bluetooth
//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);
  Serial.begin(9600);
  servo_radar.attach(pin_radar);
  servo_timon.attach(pin_timon);
  BT.begin("Lord_Comandante_S"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");

}
void loop() {
  

  for(int i=0;i<=180;i++){  
          
    servo_radar.write(i);
    //Ahora controlamos el timon con otro servo;v mediante Bluetooth
          if (BT.available()){ //Mientras haya datos por recibir
        Serial.print("Dato recibido: ");
        int val = BT.read();
        for (int j = 0; j <= 5; j++){
          if (val == numeros[j] ) {
            servo_timon.write(direccion_grad[j]);
            }
        }
      }
    delay(30);
    distance = lectura_dist();
    Serial.print(i); 
    Serial.print(","); 
    Serial.print(distance);
    Serial.print(".");
  }
   
  for(int i=180;i>0;i--){  
    servo_radar.write(i);
        //Ahora controlamos el timon con otro servo;v mediante Bluetooth
          if (BT.available()){ //Mientras haya datos por recibir
        Serial.print("Dato recibido: ");
        int val = BT.read();
        for (int j = 0; j <= 5; j++){
          if (val == numeros[j] ) {
            servo_timon.write(direccion_grad[j]);
            }
        }
      }
    delay(30);
    distance = lectura_dist();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    }
    

}
int lectura_dist(){
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  t_1 = duration/(2*1000000.0); //tiempo de ida en seg
  distance= sqrt(116964 * pow(t_1, 2) - 9 / 62500.0)*100;
  return distance;
}

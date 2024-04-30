#include "BluetoothSerial.h"

// Motor 
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

BluetoothSerial BT; //Objeto Bluetooth
//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  Serial.begin(115200);
  BT.begin("Lord_Comandante_S"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
}

void loop() {
      if (BT.available()){ //Mientras haya datos por recibir
        Serial.print("Dato recibido: ");
        int val = BT.read();
        Serial.println(val);
        if (val == 54 ) {
            // Hacia adelante
            digitalWrite(enable1Pin, HIGH);
            Serial.println("Adelante");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, HIGH);
            //delay(10000);
            } 
         else if (val == 55){
            digitalWrite(enable1Pin, LOW);
            Serial.println("Freno");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            //delay(1000);
            }
          else if (val == 56){
            digitalWrite(enable1Pin, HIGH);
            Serial.println("Reversa");
            digitalWrite(motor1Pin1, HIGH);
            digitalWrite(motor1Pin2, LOW); 
            //delay(10000);
            
            }     
        }

}

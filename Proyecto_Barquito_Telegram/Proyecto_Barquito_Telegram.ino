#include "CTBot.h"
#include <ESP32Servo.h>

//Ultrasonico
int trig = 13;
int echo = 12;
long duration;
int distance;
int i;

//Alarma de Proximidad
int umbral = 10;
int id = 0;


Servo servo_radar;
int pin_radar = 2; // servo-radar
double t_1 = 0.0;

Servo servo_timon;
int pin_timon = 4;
int numeros[] = {49, 50, 51, 52, 53}; //Botones Bluetooth
int direccion_grad[] = {50, 70, 90, 110, 130}; 

// Motor 
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

CTBot myBot; // Crea un objeto para interactuar con el bot de Telegram.

// Detalles de la red Wi-Fi y el token de autenticación del bot de Telegram.
String ssid = "Clase_IoT";  // Reemplazar con tu SSID de Wi-Fi.
String pass = "0123456789"; // Reemplazar con tu contraseña de Wi-Fi.
//String ssid = "pcpuma";  // Reemplazar con tu SSID de Wi-Fi.
//String pass = "mango2022"; // Reemplazar con tu contraseña de Wi-Fi.
//String ssid = "Lomitos_GuaGua";  // Reemplazar con tu SSID de Wi-Fi.
//String pass = "7B2E0C8E1M2AR"; // Reemplazar con tu contraseña de Wi-Fi.
String token = "6683073161:AAFSX-DrsV2l6CFWRYnNaA62Q6LF8_ZMu_A"; // Reemplazar con el token de tu bot de Telegram. 


void setup() {
  Serial.begin(9600); // Inicia la comunicación serial.
  Serial.print("Comenzando TelegramBot...  ");
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);

  servo_radar.attach(pin_radar);
  servo_timon.attach(pin_timon);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  myBot.wifiConnect(ssid, pass); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(token); // Establece el token de autenticación para el bot de Telegram.
  delay(2000); // Espera un momento para que la conexión se establezca.

  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection())
    Serial.println("Conectado con Bot");
  else
    Serial.println("Error en la conexión");
}

void loop() {
 
  
  for(int i=0;i<=180;i++){          
  servo_radar.write(i);
  delay(30);
  distance = lectura_dist();
  }
  
  for(int i=180;i>0;i--){  
  servo_radar.write(i);
  delay(30);
  distance = lectura_dist();
  }
  
  TBMessage msg; // Crea un objeto para almacenar los mensajes entrantes de Telegram.
//  int sensor = 

  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/start")) {
      Serial.print("Nueva interacción de: ");
      Serial.println(msg.sender.username);
      String Bienvenida = "Hola Usari@. En breve explicare que acciones puede realizar el Bot y con que comandos se deben ejecutar, los comandos son: ";
      myBot.sendMessage(msg.sender.id, Bienvenida);
    }
    else if (msg.text.equalsIgnoreCase("/1")){
    servo_timon.write(50); 
    String mensaje = "El timon se movio a la posicion 1";    
    myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/2")){
    servo_timon.write(70);  
    String mensaje = "El timon se movio a la posicion 2"; 
    myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/3")){
    servo_timon.write(90);  
    String mensaje = "El timon se movio a la posicion 3"; 
    myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/4")){
    servo_timon.write(110);  
    String mensaje = "El timon se movio a la posicion 4"; 
    myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/5")){
    servo_timon.write(130);
    String mensaje = "El timon se movio a la posicion 5"; 
    myBot.sendMessage(msg.sender.id, mensaje);  
    }
    else if (msg.text.equalsIgnoreCase("/Adelante")){
      Serial.print("Adelante va el barco");
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      String mensaje = "Avanza barquito"; 
      myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/Freno")){
      Serial.print("Frena el barco");
      digitalWrite(enable1Pin, LOW);
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      String mensaje = "Freno el barquito"; 
      myBot.sendMessage(msg.sender.id, mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/Reversa")){
      Serial.print("Reversa en el barco");
      digitalWrite(enable1Pin, HIGH);
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      String mensaje = "Reversa en el barquito"; 
      myBot.sendMessage(msg.sender.id, mensaje);
    }
//    else if (msg.text.equalsIgnoreCase("/Alarma_Activada")){
//    // Si el comando es "/Alarma_activa", activa la alarma y guarda el ID del chat.
//    state = true;
//    id = msg.sender.id;
//    String mensaje = "Alarma activada";
//    myBot.sendMessage(msg.sender.id, mensaje);
//    Serial.println(mensaje);
//    }
//    else if (msg.text.equalsIgnoreCase("/Alarma_Apagada")){
//    // Si el comando es "/Alarma_apagada", desactiva la alarma.
//    state = false;
//    id = msg.sender.id;
//    String mensaje = "Alarma desactivada";
//    myBot.sendMessage(msg.sender.id, mensaje);
//    Serial.println(mensaje);
//    id = 0; // Restablece el ID del chat ya que la alarma está desactivada.
//    }
    else {
      // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
      myBot.sendMessage(msg.sender.id, "Mensaje no válido, intenta de nuevo con: /start");
    }
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


//// Si la alarma está activada y el valor del sensor supera el umbral, envía una alerta al usuario.
// if ((state == true) && (sensor > umbral)){
// Serial.println(sensor);
// //Serial.println(id);
// String mensaje = "¡¡ALERTA!! Proximo choque en: "+(String)sensor;
// myBot.sendMessage(id, mensaje);
//}


  

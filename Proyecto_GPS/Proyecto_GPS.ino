#include <TinyGPSPlus.h>
// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
const int RXD2 = 16;
const int TXD2 = 17;
static const uint32_t GPSBaud = 9600;


void setup()
{
  //Inciazamos la comunicacion serial en ambos puertos, para el puerto
  //Serial" incluimos la velocidad GPSBaud y SERIAL_8N1
  Serial.begin(115200);
  Serial2.begin(GPSBaud,SERIAL_8N1,RXD2,TXD2);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // Este bucle se ejecuta mientras haya datos disponibles 
  //en el puerto Serial2
  
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();
  //Si pasan mas de 5 seg y se procesan menos de 10 caracteres GPS
  //se muestra un errory entra en un bucle infinito
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS no detectado: revisar conexion."));
    while(true);
  }
}

//Esta funcion muestra la informacion de ubicacion y fecha-hora
//en el monitor serial

void displayInfo()
{
  Serial.print(F("Ubicación: ")); 
  if (gps.location.isValid())//Imprimimos la ubicacion si es valida
  {
    Serial.print(gps.location.lat(), 6); //mostramos latitud con 6 digitos
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6); //motramos longitud
  }
  else
  {
    Serial.print(F("Invalido"));
  }

  Serial.print(F("  Fecha/Hora: "));//Mostramos la fecha si es valida
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("Invalido"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())//Mostramos la hora si es valida
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("Invalido"));
  }

  Serial.print(F("  Velocidad km/h "));
  if (gps.speed.isValid()){
    Serial.print(gps.speed.kmph(),6);
    Serial.print(" km/h");
    }
   else{
      Serial.print(F("Invalido"));
    }

  
  Serial.println();
}

#include <NewPing.h>

#define TRIGGER_PIN 9  // Pin del Arduino conectado al pin de activación (Trigger) del sensor
#define ECHO_PIN 10    // Pin del Arduino conectado al pin de recepción (Echo) del sensor
#define MAX_DISTANCE 200  // Distancia máxima de medición en centímetros

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(500);  // Espera 500 milisegundos entre mediciones

  unsigned int distancia = sonar.ping_cm();  // Obtiene la distancia en centímetros

  if (distancia == 0) {
    Serial.println("Fuera de rango");
  } else {
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
}

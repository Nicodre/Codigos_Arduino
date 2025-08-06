// === Variables globales necesarias (declaralas fuera de la función) ===
int minValor[5];  // Mínimos por sensor (blanco)
int maxValor[5];  // Máximos por sensor (negro)
const int sensores[5] = {A0, A1, A2, A3, A4};  // Pines de sensores analógicos

// === Funcion para calibrar sensores ===
void calibrarSensores() {
  Serial.begin(9600);
  Serial.println("🔧 Calibrando sensores... Mueve el robot sobre fondo blanco y la línea negra.");

  // Inicializar los valores extremos
  for (int i = 0; i < 5; i++) {
    minValor[i] = 1023;
    maxValor[i] = 0;
  }

  unsigned long tiempoInicio = millis();
  while (millis() - tiempoInicio < 5000) {  // Calibrar durante 5 segundos
    for (int i = 0; i < 5; i++) {
      int lectura = analogRead(sensores[i]);
      if (lectura < minValor[i]) minValor[i] = lectura;
      if (lectura > maxValor[i]) maxValor[i] = lectura;
    }
    delay(5);
  }

  Serial.println("Calibracion completa:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Sensor "); Serial.print(i);
    Serial.print(": min = "); Serial.print(minValor[i]);
    Serial.print(", max = "); Serial.println(maxValor[i]);
  }
}

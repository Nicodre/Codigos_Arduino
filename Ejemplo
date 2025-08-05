# Robot Seguidor de Línea con PID (2 sensores analógicos)

Los sensores devuelven valores analógicos de **0 (negro)** a **1023 (blanco)**.

El algoritmo PID ajusta el giro del robot en función del **error**, que se calcula como la diferencia entre los valores de los sensores.  
- **Proporcional (P)**: reacciona al error actual.  
- **Integral (I)**: corrige errores acumulados.  
- **Derivativo (D)**: anticipa cambios bruscos.

Supuestos:
Sensor izquierdo conectado a A0
Sensor derecho conectado a A1
Valores analógicos entre 0 (negro) y 1023 (blanco)
Motores controlados por puente H con PWM:
Motor izquierdo: ENA (pin 5), IN1 (pin 7), IN2 (pin 8)
Motor derecho: ENB (pin 6), IN3 (pin 9), IN4 (pin 10)

Ideas para un PID con sensores analógicos.

  // Pines sensores analógicos 
const int sensorIzq = A0;
const int sensorDer = A1;

//Define a qué entrada analógica están conectados los sensores. A0 es el sensor izquierdo, A1 es el derecho.

// Pines motores
const int ENA = 5;    // PWM motor izquierdo
const int IN1 = 7;
const int IN2 = 8;

const int ENB = 6;    // PWM motor derecho
const int IN3 = 9;
const int IN4 = 10;

// Definen los pines para controlar los motores con puente H.
// ENA/ENB son pines PWM para la velocidad.
// IN1–IN4 son para el sentido del giro.

// PID
float Kp = 0.5; //constantes proporcional, integral y derivativo.
float Ki = 0.0;
float Kd = 2.0;

float error = 0;       // error inicial. 
float errorAnterior = 0;
float integral = 0;

int velocidadBase = 120; // se puede ajustar

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motores hacia adelante
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void loop() {
  // Leer valores de los sensores analógicos
  int valorIzq = analogRead(sensorIzq);
  int valorDer = analogRead(sensorDer);

  // Calcular el error: diferencia entre lecturas  Define el desvío del robot con respecto a la línea.

  error = valorDer - valorIzq;
// Si el sensor derecho ve más blanco, la línea está a la izquierda, error negativo.
// Si el sensor izquierdo ve más blanco, línea a la derecha, error positivo.

  // PID
  integral += error;
  float derivada = error - errorAnterior;
  float correccion = Kp * error + Ki * integral + Kd * derivada;
  errorAnterior = error;

// Aquí se calcula la correccion de velocidad usando el PID:
// Proporcional: corrige proporcionalmente al error.
// Integral: corrige errores acumulados (por si se desvio mucho tiempo).
// Derivada: suaviza la reacción a cambios bruscos.
  
// Calcular velocidad de motores
  int velocidadIzq = velocidadBase + correccion;
  int velocidadDer = velocidadBase - correccion;

// Aplica la corrección:
// Si correccion > 0, el motor izquierdo va más rápido, gira a la derecha.
// Si correccion < 0, el motor derecho va más rápido, gira a la izquierda.
  
// Limitar velocidad entre 0 y 255
  velocidadIzq = constrain(velocidadIzq, 0, 255);
  velocidadDer = constrain(velocidadDer, 0, 255);

  // Aplicar velocidad
  analogWrite(ENA, velocidadIzq);
  analogWrite(ENB, velocidadDer);

  delay(10);
}

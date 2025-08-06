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
Servos continuos:
Izquierdo  pin 9
Derecho  pin 10

#include <Servo.h>

// === Servos ===
Servo servoIzq;
Servo servoDer;

const int pinServoIzq = 9;
const int pinServoDer = 10;

// === Sensores analógicos ===
const int sensores[5] = {A0, A1, A2, A3, A4}; // Sensor array
int valores[5];   // Almacena lecturas

// === PID ===
float Kp = 0.5;
float Ki = 0.0;
float Kd = 2.0;

float error = 0;
float errorAnterior = 0;
float integral = 0;

// === Movimiento ===
int velocidadBase = 0;   // 0 → servos parados en 90
int velocidadMax = 30;   // Corrección máxima +/-30

// === SETUP ===
void setup() {
  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);
  detener();
}

// === FUNCIONES DE MOVIMIENTO ===
void irAdelante(int velocidad) {
  servoIzq.write(90 + velocidad);
  servoDer.write(90 - velocidad);
}

void irAtras(int velocidad) {
  servoIzq.write(90 - velocidad);
  servoDer.write(90 + velocidad);
}

void detener() {
  servoIzq.write(90);
  servoDer.write(90);
}

void girarIzquierda(int velocidad) {
  servoIzq.write(90);
  servoDer.write(90 - velocidad);
}

void girarDerecha(int velocidad) {
  servoIzq.write(90 + velocidad);
  servoDer.write(90);
}

void girarEnLugarIzq(int velocidad) {
  servoIzq.write(90 - velocidad);
  servoDer.write(90 - velocidad);
}

void girarEnLugarDer(int velocidad) {
  servoIzq.write(90 + velocidad);
  servoDer.write(90 + velocidad);
}

// === LOOP PRINCIPAL ===
void loop() {
  // === Leer sensores ===
  int suma = 0;
  int pesoTotal = 0;
  for (int i = 0; i < 5; i++) {
    valores[i] = analogRead(sensores[i]);
    int peso = i * 1000;  // Posiciones: 0, 1000, 2000, 3000, 4000
    suma += valores[i] * peso;
    pesoTotal += valores[i];
  }

  // === Calcular posición promedio ===
  int posicion;
  if (pesoTotal != 0) {
    posicion = suma / pesoTotal;
  } else {
    // Línea no detectada → detener o buscar
    detener();
    return;
  }

  // === Calcular error ===
  error = posicion - 2000;  // Centro ideal = 2000

  // === PID ===
  integral += error;
  float derivada = error - errorAnterior;
  float correccion = Kp * error + Ki * integral + Kd * derivada;
  errorAnterior = error;

  // Limitar corrección
  correccion = constrain(correccion, -velocidadMax, velocidadMax);

  // === Aplicar movimiento con funciones ===
  int velocidadIzq = velocidadBase + correccion;
  int velocidadDer = velocidadBase - correccion;

  velocidadIzq = constrain(velocidadIzq, -velocidadMax, velocidadMax);
  velocidadDer = constrain(velocidadDer, -velocidadMax, velocidadMax);

  // Aplicar a servos según corrección
  servoIzq.write(90 + velocidadIzq);
  servoDer.write(90 - velocidadDer);

  delay(10);
}

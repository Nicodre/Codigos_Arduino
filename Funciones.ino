void seguirlinea(int p, int G, int Vi, int Vd) {
  if (p>30){
     Izquierdo(30, G);
     Derecho(-30, G);
     delay(100);
    }
  else if (p<-30){
     Izquierdo(-30, G);
     Derecho(30, G);
     delay(100);
    }
  else {    
  i=i+p;
  d=p-p_old;

  u=kp*p+ki*i+kd*d; //Define la corrección
  p_old=p;
  
  if ((p*i)<0) i=0;
  
  int VelI = VelBase + u;
  int VelD = VelBase - u;
  
  //Controlar los servomotores de rotación continua
  int leftSpeed = constrain(VelI,   VelMin,   VelMax); //Define la velocidad de los motores como la VelBase + la corrección (y el incremento) y las acota entre VelMin y VelMax
  int rightSpeed = constrain(VelD,   VelMin,   VelMax);

/*
  Serial.print("Izquierda: ");
  Serial.print(leftSpeed);
  Serial.print(" --- ");
  Serial.println(leftSpeed + Vi);
  Serial.print("Derecha: ");
  Serial.print(rightSpeed);
  Serial.print(" --- ");
  Serial.println(rightSpeed + Vd);
*/

  Izquierdo(leftSpeed + Vi, G);
  Derecho(rightSpeed + Vd, G);
  }
}

void Izquierdo(int V, int G) { //Funcion para mover el servo izquierdo con velocidad
  I_AD.write((90 + V));
  I_AT.write((90 + V)*G);
}

void Derecho(int V, int G) { //Funcion para mover el servo derecho con velocidad
  D_AD.write((90 - V));
  D_AT.write((90 - V)*G);
}

void Actualizar() {
  errorString.remove(0, 1); //Removemos 1 caracter. El caracter con index 0, caracter adicional sin utilidad que esta mandando Raspberry Pi
  error = errorString.toInt(); //Convertimos el string recibido a entero y lo guardamos en la variable grados
  bandera = banderaString.toInt();
  banderaString = "";
  banderaComplete = false;
  errorString = ""; //Limpiamos la cadena para poder recibir el siguiente comando
  errorComplete = false; //Bajamos la bandera para no volver a ingresar a la comparación hasta que recibamos un nuevo comando
}

void Recibir(int howMany) {
  while (Wire.available() > 0) { //Mientras tengamos caracteres en el buffer
    char inChar = (char)Wire.read();
    if (inChar == '\n') {
      banderaComplete = true;
    }
    else if (inChar == '&')
      errorComplete = true;
    else if (!(errorComplete)) {
      errorString += inChar;
    }
    else {
      banderaString += inChar;
    }
  }
}

void Enviar() {
  Wire.write(n);
}

void Cam(int k) {
  K = C.read();
  if (K <= k) {
    for (int i = K; i <= k; i++) {
      C.write(i);
      delay(20);
    }
  }
  else {
    for (int i = K; i >= k; i--) {
      C.write(i);
      delay(20);
    }
  }
}

void Brazo(int k, int t) {
  K = B.read();
  if (K <= k) {
    for (int i = K; i <= k; i++) {
      B.write(i);
      delay(t);
    }
  }
  else {
    for (int i = K; i >= k; i--) {
      B.write(i);
      delay(t);
    }
  }
}

//  en esta función solo hay que indicar dónde conectamos el ecco y el trigger

int distancia(int TriggerPin, int EchoPin) { 
  long duration, distanceCm;

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}
}

void GirarVerde(int L) {
  int band = bandera;
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(500);
  Actualizar();
  delay(300);
  if (bandera == band) {
    Izquierdo(15, 1);
    Derecho(15, 1);
    delay(1000);
    Izquierdo((-20 * L), 1);
    Derecho((20 * L), 1);
    delay(350);
    Izquierdo(0, 1);
    Derecho(0, 1);
    delay(200);
    Actualizar();
    delay(200);
    while (not (bandera == 11)) {
      Izquierdo((-20 * L), 1);
      Derecho((20 * L), 1);
      Actualizar();
    }
    Izquierdo(0, 1);
    Derecho(0, 1);
    delay(200);
    Izquierdo(-15, 1);
    Derecho(-15, 1);
    delay(400);
  }
}

void Esquivar(int L) {  
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(500);
  Izquierdo((-20 * L), 1);
  Derecho((20 * L), 1);
  delay(900);
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(300);
  Cam(0);
  delay(300);
  Izquierdo(20, 1);
  Derecho(20, 1);
  delay(800);
  Izquierdo((20 * L), 1);
  Derecho((-20 * L), 1);
  delay(900);                
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(300);
  long tiempo = millis();
  while (((millis() - tiempo) < 3000) and (not(bandera == 11))) {
    Izquierdo(15, 1);
    Derecho(15, 1);
    Actualizar();
  }
  if (not(bandera == 11)) {
    Izquierdo((20 * L), 1);
    Derecho((-20 * L), 1);
    delay(1200);
    Izquierdo(0, 1);
    Derecho(0, 1);
    delay(200);
    tiempo = millis();
    while (((millis() - tiempo) < 3000) and (not(bandera == 11))) {
      Izquierdo(15, 1);
      Derecho(15, 1);
      Actualizar();
    }
  }
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(100);
  Izquierdo((-20 * L), 1);
  Derecho((20 * L), 1);
  delay(500);
  Izquierdo(0, 1);
  Derecho(0, 1);
  delay(1000);
  n = 'r';
  Enviar();
  delay(200);
}


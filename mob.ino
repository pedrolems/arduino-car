#include <Servo.h>

const int servoPin = 9;

// Pinos dos motores
const int motorEsq1 = 5;
const int motorEsq2 = 4;
const int motorDir1 = 7;
const int motorDir2 = 6;

// Sensor ultrassônico nos pinos analógicos
const int trigPin = A0;
const int echoPin = A1;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  // Limpa o trigger
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Envia o sinal de trigger (pulsos de 10us)
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Lê o sinal de retorno
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  
  // Converte a duração para distância (em cm)
  long distance = duration * 0.0344 / 2;  // A velocidade do som é 343 m/s
  return distance;
}

// Funções para controle dos motores
void moverFrente() {
  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
}

void virarEsquerda() {
  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, HIGH);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
}

void virarDireita() {
  digitalWrite(motorEsq1, HIGH);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
}

void pararMotores() {
  digitalWrite(motorEsq1, LOW);
  digitalWrite(motorEsq2, LOW);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);
}

void setup() {
  servoPin.(9);  // Servo no pino 7
  Serial.begin(9600);

  // Inicializa pinos dos motores como saída
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);

  pararMotores();
}

void loop() {
  int distanciaFrente, distanciaEsquerda, distanciaDireita;

  // Medir frente (90°)
  servoPin.write(90);  // Servo virado para frente
  delay(400);
  distanciaFrente = readUltrasonicDistance(trigPin, echoPin);
  Serial.print("Frente: "); Serial.println(distanciaFrente);

  

  // Medir esquerda (0°)
  servoPin.write(0);  // Servo virado para esquerda
  delay(400);
  distanciaEsquerda = readUltrasonicDistance(trigPin, echoPin);
  Serial.print("Esquerda: "); Serial.println(distanciaEsquerda);

  // Medir direita (180°)
  servoPin.write(180);  // Servo virado para direita
  delay(400);
  distanciaDireita = readUltrasonicDistance(trigPin, echoPin);
  Serial.print("Direita: "); Serial.println(distanciaDireita);

  // Escolher a direção com maior distância
  if (distanciaFrente >= distanciaEsquerda && distanciaFrente >= distanciaDireita) {
    Serial.println("Movendo para frente");
    moverFrente();
  } else if (distanciaEsquerda > distanciaDireita) {
    Serial.println("Virando para esquerda");
    virarEsquerda();
  } else {
    Serial.println("Virando para direita");
    virarDireita();
  }

  delay(1000);  // Espera 1 segundo antes de nova leitura
  pararMotores();  // Parar os motores depois de mover
  delay(500);  // Pausa antes de realizar uma nova leitura
}

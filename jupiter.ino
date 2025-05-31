#include <Servo.h>

Servo servo;
const int servoPin = 9;  

const int motorEsq1 = 5;
const int motorEsq2 = 4;
const int motorDir1 = 6;
const int motorDir2 = 7;


const int trigPin = A0;
const int echoPin = A1;
const int distanciaMinima = 30; 

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  
}


void moverFrente() {
  analogWrite(motorEsq1, 230);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, 230);
  analogWrite(motorDir2, 0);
}

void parar() {
  analogWrite(motorEsq1, 0);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, 0);
  analogWrite(motorDir2, 0);
}

void virarEsquerda(int tempo = 280) {
  analogWrite(motorEsq1, 0);
  analogWrite(motorEsq2, 255);
  analogWrite(motorDir1, 255);
  analogWrite(motorDir2, 0);
  delay(tempo);
  parar();
}

void virarDireita(int tempo = 350) {
  analogWrite(motorEsq1, 255);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, 0);
  analogWrite(motorDir2, 255);
  delay(tempo);
  parar();
}

void setup() {
  Serial.begin(9600);
  
  servo.attach(servoPin);
  
  servo.write(90);  
  delay(1000);
  
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  moverFrente();
  
  servo.write(90);
  delay(200);  
  float distanciaFrente = medirDistancia();
  
  Serial.print("Distância frente: ");
  Serial.println(distanciaFrente);
  
  if (distanciaFrente <= distanciaMinima) {
    parar();
    delay(500);  
    
   
    servo.write(0);
    delay(500);
    float distanciaDireita = medirDistancia();
    Serial.print("Distância direita: ");
    Serial.println(distanciaDireita);
    
    servo.write(180);
    delay(500);
    float distanciaEsquerda = medirDistancia();
    Serial.print("Distância esquerda: ");
    Serial.println(distanciaEsquerda);
    
    servo.write(90);
    delay(200);
    
    if (distanciaEsquerda > distanciaDireita ) {
      Serial.println("Virando para esquerda");
      virarEsquerda();
    } 
    else if (distanciaDireita > distanciaEsquerda) {
      Serial.println("Virando para direita");
      virarDireita();
    } 
    else {
      
      Serial.println("Sem saída viável - dando ré e tentando novamente");
      delay(1000);
    }
  }
  
  delay(100);  
}
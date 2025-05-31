#include <SoftwareSerial.h>

// Configuração Bluetooth
SoftwareSerial bluetooth(8, 9);  // RX, TX

// Definição dos pinos dos motores
const int MOTOR1_PWM = 6;
const int MOTOR1_DIR = 7;
const int MOTOR2_PWM = 5;
const int MOTOR2_DIR = 4;

int incomingData[2];

// Tempo máximo sem comunicação (ms)
const unsigned long BLUETOOTH_TIMEOUT = 10000; 

// Variáveis de estado
unsigned long lastCommTime = 0;
bool connectionActive = false;

void setup() {
  // Configuração dos pinos
  pinMode(MOTOR1_DIR, OUTPUT);
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR2_DIR, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);
  
  // Inicializa comunicações
  Serial.begin(9600);
  initBluetooth();
  
  // Garante motores desligados
  stopAllMotors();
  
}

void initBluetooth() {
  bluetooth.begin(9600);
  bluetooth.setTimeout(250);  // Timeout de leitura reduzido
  clearBluetoothBuffer();
}

void clearBluetoothBuffer() {
  while (bluetooth.available()) {
    bluetooth.read();
  }
}

void stopAllMotors() {
  analogWrite(MOTOR1_PWM, 0);
  analogWrite(MOTOR2_PWM, 0);
}


void loop(){
   if (bluetooth.available() >= 2) { // Verifica se pelo menos dois caracteres estão disponíveis
    incomingData[0] = bluetooth.read();
    incomingData[1] = bluetooth.read();

      int motor1Speed = incomingData[0] - '0'; // Converte o caractere para inteiro
      int motor2Speed = incomingData[1] - '0'; // Converte o caractere para inteiro

      Serial.print("Velocidade Motor 1: ");
      Serial.println(motor1Speed);
      Serial.print("Velocidade Motor 2: ");
      Serial.println(motor2Speed);

       if (motor1Speed == 2) {
      analogWrite(6, 0); 
      analogWrite(7, 200);
    }
    if (motor1Speed == 3) {
      analogWrite(6, 0);
      analogWrite(7, 0);
    }
    if (motor1Speed == 4) {
      analogWrite(6, 255);
      analogWrite(7, 0);
    }
    if (motor1Speed == 1) {
      analogWrite(6, 0);
      analogWrite(7, 255);
    }
    if (motor2Speed == 6) {
      analogWrite(5, 150);  
      analogWrite(4, 0);
    }
    if (motor2Speed == 7) {
      analogWrite(5, 0);
      analogWrite(4, 0);
    }
    if (motor2Speed == 8) {
      analogWrite(5, 0);
      analogWrite(4, 255);
    } 
    if (motor2Speed == 5) {
      analogWrite(5, 255);
     analogWrite(4, 0);
    }
    delay(350);
   }
}

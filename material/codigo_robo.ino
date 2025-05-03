#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pinos do Motor A
int motorAPin1 = 27;  // IN1 
int motorAPin2 = 26;  // IN2 
int enableA = 14;     // ENA 

// Pinos do Motor B
int motorBPin1 = 25;  // IN3 
int motorBPin2 = 33;  // IN4 
int enableB = 12;     // ENB 

// Configurações PWM
int dutyCycle = 255;  

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Augostinho carrara"); 
  Serial.println("Bluetooth iniciado. Aguardando comandos...");

  // Configura os pinos como saídas
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableA, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableB, OUTPUT);

  // Define velocidade inicial dos motores
  analogWrite(enableA, dutyCycle); 
  analogWrite(enableB, dutyCycle); 
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();

    switch(cmd) {
      case 'F': // Frente
        digitalWrite(motorAPin1, LOW);
        digitalWrite(motorAPin2, HIGH); // Motor A para frente
        
        digitalWrite(motorBPin1, LOW);
        digitalWrite(motorBPin2, HIGH); // Motor B para frente
        Serial.println("Movendo para frente...");
        break;
      case 'B': // Trás
        digitalWrite(motorAPin1, HIGH);
        digitalWrite(motorAPin2, LOW); 
        
        digitalWrite(motorBPin1, HIGH);
        digitalWrite(motorBPin2, LOW); 
        Serial.println("Movendo para trás...");
        break;
      case 'R': // Direita
        digitalWrite(motorAPin1, LOW);
        digitalWrite(motorAPin2, HIGH); 
        
        digitalWrite(motorBPin1, HIGH);
        digitalWrite(motorBPin2, LOW); 
        Serial.println("Virando à direita...");
        break;
      case 'L': // Esquerda
        digitalWrite(motorAPin1, HIGH);
        digitalWrite(motorAPin2, LOW); // Motor A para trás
        
        digitalWrite(motorBPin1, LOW);
        digitalWrite(motorBPin2, HIGH); // Motor B para frente
        Serial.println("Virando à esquerda...");
        break;
      case 'S': // Parar
        digitalWrite(motorAPin1, LOW);
        digitalWrite(motorAPin2, LOW);
        digitalWrite(motorBPin1, LOW);
        digitalWrite(motorBPin2, LOW);
        Serial.println("Parando o veículo...");
        break;
      case 'Y': // Aumentar velocidade
        dutyCycle = min(dutyCycle + 10, 255); // Limite superior
        analogWrite(enableA, dutyCycle);
        analogWrite(enableB, dutyCycle);
        Serial.print("Velocidade aumentada! Duty Cycle: ");
        Serial.println(dutyCycle);
        break;

      case 'X': // Reduzir velocidade
        dutyCycle = max(dutyCycle - 10, 150); // Limite inferior
        analogWrite(enableA, dutyCycle);
        analogWrite(enableB, dutyCycle);
        Serial.print("Velocidade reduzida! Duty Cycle: ");
        Serial.println(dutyCycle);
        break;
      default:
        Serial.println("Comando desconhecido!");
        break;
    }
  }
}
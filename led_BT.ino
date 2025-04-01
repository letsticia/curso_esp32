#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int PINO_LED = 15;
void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT"); 
    Serial.println("Bluetooth pronto para pareamento!");
    pinMode(PINO_LED, OUTPUT); 
}

void loop() {
    if (SerialBT.available()) {
        char received = SerialBT.read();
        
        if (received != '\r' && received != '\n') { 
            Serial.print("Recebido: ");
            Serial.println(received);
            SerialBT.print("Echo: ");
            SerialBT.println(received);
        }

        if (received == 'd'){
          digitalWrite(PINO_LED, LOW);
        }

        if (received == 'l'){
          digitalWrite(PINO_LED, HIGH);
        }

    }
}

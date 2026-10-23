#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Pines estándar SDA=21, SCL=22
  Serial.println("\n--- Escaneando bus I2C en ESP32 ---");
}

void loop() {
  byte error, address;
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado en la direccion 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("!");
      nDevices++;
    }
  }
  if (nDevices == 0) {
    Serial.println("No se encontraron dispositivos I2C.");
  } else {
    Serial.println("Escaneo completado.");
  }
  delay(5000);
}
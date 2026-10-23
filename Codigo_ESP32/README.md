# Código para ESP32
#include <Wire.h>

const int MPU_ADDR = 0x68; // Dirección I2C del sensor MPU-9255
int16_t raw_az;
float az_raw = 0.0;
float az_filtered = 0.0;

// Factor de suavizado alpha (frecuencia de corte fc = 1.404 Hz equivalente)
float alpha = 0.15; 

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Inicializa I2C (SDA = GPIO21, SCL = GPIO22)
  
  // Despertar el MPU-9255 del modo sleep
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Registro PWR_MGMT_1
  Wire.write(0x00); // Set a 0 para encender
  Wire.endTransmission(true);
}

void loop() {
  // Solicitud de lectura del eje Z de aceleración (registros 0x3F y 0x40)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3F); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);
  
  raw_az = (Wire.read() << 8 | Wire.read());
  az_raw = raw_az / 16384.0; // Conversión a unidades de gravedad (g)
  
  // Ecuación en Diferencias del Filtro Digital IIR
  az_filtered = (alpha * az_raw) + ((1.0 - alpha) * az_filtered);
  
  // Salida formateada para el Serial Plotter / Registro de datos
  Serial.print("AZ_Crudo:"); Serial.print(az_raw); Serial.print(",");
  Serial.print("AZ_Filtrado:"); Serial.println(az_filtered);
  
  delay(20); // Período de muestreo Ts = 20 ms (50 Hz)
}

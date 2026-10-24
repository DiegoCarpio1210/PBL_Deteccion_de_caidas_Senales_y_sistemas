#include <Wire.h>

// =====================================
// FILTRO IIR - MPU-9250 Y ESP32
// Proyecto: Detector de caidas
// =====================================

// Conexion I2C
#define MPU_ADDR 0x68
#define SDA_PIN 21
#define SCL_PIN 22

// Parametros del filtro
const float alpha = 0.15f;

// Frecuencia nominal: 50 Hz
// Periodo: 20 milisegundos
const unsigned long Ts_us = 20000UL;

// Variables
float az_raw = 0.0f;
float az_filtered = 0.0f;

bool filtro_inicializado = false;

unsigned long siguiente_muestra = 0;

// =====================================
// CONFIGURAR SENSOR
// =====================================

bool escribirRegistro(uint8_t registro, uint8_t valor) {

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(registro);
  Wire.write(valor);

  return Wire.endTransmission() == 0;
}

bool configurarMPU() {

  // Despertar MPU-9250
  if (!escribirRegistro(0x6B, 0x00)) {
    return false;
  }

  delay(100);

  // Configurar acelerometro en +/-2g
  if (!escribirRegistro(0x1C, 0x00)) {
    return false;
  }

  return true;
}

// =====================================
// LEER ACELERACION EN Z
// =====================================

bool leerAZ(float &az) {

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3F);

  if (Wire.endTransmission(false) != 0) {
    return false;
  }

  if (Wire.requestFrom(
        (uint8_t)MPU_ADDR,
        (uint8_t)2,
        (uint8_t)true
      ) != 2) {
    return false;
  }

  int16_t rawZ = (int16_t)(
    (Wire.read() << 8) | Wire.read()
  );

  // Sensibilidad para +/-2g
  az = rawZ / 16384.0f;

  return true;
}

// =====================================
// INICIALIZACION
// =====================================

void setup() {

  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!configurarMPU()) {

    Serial.println("ERROR: MPU-9250 no detectado");

    while (true) {
      delay(1000);
    }
  }

  siguiente_muestra = micros();
}

// =====================================
// PROGRAMA PRINCIPAL
// =====================================

void loop() {

  unsigned long ahora = micros();

  // Mantener periodo nominal de 20 ms
  if ((int32_t)(ahora - siguiente_muestra) < 0) {
    return;
  }

  siguiente_muestra += Ts_us;

  // Leer aceleracion del sensor
  if (!leerAZ(az_raw)) {
    return;
  }

  // Filtro IIR de primer orden
  if (!filtro_inicializado) {

    az_filtered = az_raw;
    filtro_inicializado = true;

  } else {

    az_filtered =
      alpha * az_raw +
      (1.0f - alpha) * az_filtered;
  }

  // Mostrar resultados
  Serial.print("AZ_Crudo:");
  Serial.print(az_raw, 5);

  Serial.print(",AZ_Filtrado:");
  Serial.println(az_filtered, 5);
}

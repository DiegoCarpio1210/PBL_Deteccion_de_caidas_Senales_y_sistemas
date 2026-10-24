#include <Wire.h>

// PRUEBA 2: MOVIMIENTO Y ORIENTACION
// Sensor: MPU-9250
// Frecuencia: 50 Hz
// Duracion: 10 segundos
// Rango: +/-2g

#define MPU_ADDR 0x68
#define SDA_PIN 21
#define SCL_PIN 22

const float alpha = 0.15f;
const unsigned long Ts_us = 20000UL;
const int TOTAL_MUESTRAS = 500;

float az_crudo = 0.0f;
float az_filtrado = 0.0f;

unsigned long tiempo_inicio = 0;
unsigned long siguiente_muestra = 0;

int numero_muestra = 0;

bool filtro_inicializado = false;
bool prueba_terminada = false;

bool escribirRegistro(uint8_t registro, uint8_t valor) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(registro);
  Wire.write(valor);
  return Wire.endTransmission() == 0;
}

bool configurarMPU() {
  if (!escribirRegistro(0x6B, 0x00)) {
    return false;
  }

  delay(100);

  // Acelerometro en +/-2g
  if (!escribirRegistro(0x1C, 0x00)) {
    return false;
  }

  delay(100);
  return true;
}

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

  az = rawZ / 16384.0f;
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!configurarMPU()) {
    Serial.println("ERROR: MPU no detectado");

    while (true) {
      delay(1000);
    }
  }

  delay(3000);

  Serial.println(
    "Muestra,Tiempo_s,AZ_Crudo_g,AZ_Filtrado_g"
  );

  tiempo_inicio = micros();
  siguiente_muestra = tiempo_inicio;
}

void loop() {
  if (prueba_terminada) {
    return;
  }

  unsigned long ahora = micros();

  if ((int32_t)(ahora - siguiente_muestra) < 0) {
    return;
  }

  siguiente_muestra += Ts_us;

  if (!leerAZ(az_crudo)) {
    return;
  }

  if (!filtro_inicializado) {
    az_filtrado = az_crudo;
    filtro_inicializado = true;
  } else {
    az_filtrado =
      alpha * az_crudo +
      (1.0f - alpha) * az_filtrado;
  }

  float tiempo_s =
    (micros() - tiempo_inicio) / 1000000.0f;

  Serial.print(numero_muestra);
  Serial.print(",");

  Serial.print(tiempo_s, 5);
  Serial.print(",");

  Serial.print(az_crudo, 5);
  Serial.print(",");

  Serial.println(az_filtrado, 5);

  numero_muestra++;

  if (numero_muestra >= TOTAL_MUESTRAS) {
    prueba_terminada = true;
  }
}
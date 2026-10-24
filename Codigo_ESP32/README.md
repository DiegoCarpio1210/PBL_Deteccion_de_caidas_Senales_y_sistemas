# Código ESP32 — Sistema de Detección de Caídas

Esta carpeta contiene los programas desarrollados para el ESP32 y el sensor MPU-9250, utilizados en el proyecto de detección de caídas de la asignatura Señales y Sistemas.

El objetivo de estos programas es adquirir mediciones de aceleración, aplicar un filtro digital IIR de primer orden y realizar pruebas experimentales para analizar su comportamiento.

## 1. Componentes utilizados

* ESP32 Dev Module.
* Sensor MPU-9250.
* Cables de conexión.
* Computadora con Arduino IDE.

## 2. Conexiones

| MPU-9250 | ESP32   |
| -------- | ------- |
| VCC      | 3V3     |
| GND      | GND     |
| SDA      | GPIO 21 |
| SCL      | GPIO 22 |

La comunicación entre el sensor y el microcontrolador se realiza mediante el protocolo I²C, utilizando la dirección `0x68`.

## 3. Filtro digital IIR

El sistema utiliza un filtro digital IIR de primer orden para suavizar las variaciones de aceleración registradas por el sensor.

La ecuación implementada es:

**y[n] = 0.15x[n] + 0.85y[n−1]**

Donde:

* `x[n]`: aceleración medida por el sensor.
* `y[n]`: aceleración filtrada.
* `y[n−1]`: salida filtrada anterior.
* `α = 0.15`: coeficiente del filtro.

La frecuencia nominal de muestreo es de **50 Hz**, equivalente a un período de **20 ms**.

## 4. Descripción de los archivos

| Archivo                   | Descripción                                                                                                 |
| ------------------------- | ----------------------------------------------------------------------------------------------------------- |
| `Filtro_IIR_MPU9250.ino`  | Programa principal para leer la aceleración del eje Z y visualizar la señal cruda y filtrada continuamente. |
| `Scanner_I2C.ino`         | Programa para identificar la dirección I²C del sensor conectado.                                            |
| `Prueba_1_Reposo.ino`     | Registra 500 muestras con el sensor en reposo, utilizando un rango de ±2 g.                                 |
| `Prueba_2_Movimiento.ino` | Registra 500 muestras durante cambios de movimiento y orientación, utilizando un rango de ±2 g.             |
| `Prueba_3_Impacto.ino`    | Registra 500 muestras durante movimientos bruscos controlados, utilizando un rango de ±16 g.                |

## 5. Pruebas experimentales

Se realizaron tres pruebas para estudiar el comportamiento del filtro ante diferentes condiciones:

**Prueba 1 — Reposo:** permite observar las fluctuaciones de la aceleración cuando el sensor permanece inmóvil.

**Prueba 2 — Movimiento:** permite analizar la respuesta del filtro ante cambios de orientación y movimiento.

**Prueba 3 — Impacto simulado:** permite analizar la respuesta del filtro ante aceleraciones bruscas, utilizando un rango de medición mayor para reducir el riesgo de saturación.

Cada programa experimental registra **500 muestras durante aproximadamente 10 segundos** y finaliza automáticamente.

Los resultados se encuentran en la carpeta `Datos_Experimentales` del repositorio.

## 6. Ejecución

1. Conectar el MPU-9250 al ESP32.
2. Abrir el archivo `.ino` correspondiente en Arduino IDE.
3. Seleccionar la placa ESP32 Dev Module y el puerto correspondiente.
4. Cargar el programa.
5. Abrir el Monitor Serie a 115200 baudios.
6. Ejecutar la prueba y registrar las mediciones.

## 7. Alcance

Estos programas permiten verificar la adquisición de aceleración y el funcionamiento del filtro digital IIR.

Las pruebas documentadas corresponden a la etapa de adquisición y procesamiento de señales del detector de caídas. No constituyen, por sí solas, una validación completa de la detección de caídas.


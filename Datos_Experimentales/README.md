# Datos Experimentales — Sistema de Detección de Caídas

Esta carpeta contiene los datos experimentales obtenidos mediante el ESP32 y el acelerómetro MPU-9250 para el proyecto de detección de caídas de la asignatura Señales y Sistemas.

El objetivo de estas pruebas es analizar el comportamiento de un filtro digital IIR de primer orden ante diferentes condiciones de aceleración.

## 1. Parámetros experimentales

| Parámetro                      | Valor                     |
| ------------------------------ | ------------------------- |
| Sensor                         | MPU-9250                  |
| Microcontrolador               | ESP32                     |
| Frecuencia nominal de muestreo | 50 Hz                     |
| Período nominal de muestreo    | 20 ms                     |
| Coeficiente del filtro         | α = 0.15                  |
| Muestras por prueba            | 500                       |
| Duración aproximada            | 10 segundos               |
| Variable medida                | Aceleración del eje Z (g) |

La ecuación del filtro implementado es:

**y[n] = 0.15x[n] + 0.85y[n−1]**

Donde `x[n]` representa la aceleración cruda y `y[n]` representa la aceleración filtrada.

## 2. Descripción de los archivos

### Prueba 1 — Reposo

**Archivo:** `Prueba_1_Reposo.csv`

**Configuración:** acelerómetro en ±2 g.

Se registraron mediciones con el sensor en reposo para observar las pequeñas fluctuaciones de aceleración y analizar cómo el filtro IIR suaviza la señal.

### Prueba 2 — Movimiento y orientación

**Archivo:** `Prueba_2_Movimiento.csv`

**Configuración:** acelerómetro en ±2 g.

Se registraron mediciones durante movimientos y cambios de orientación del sensor.

Esta prueba permite observar cómo responde el filtro ante variaciones de aceleración positivas y negativas.

### Prueba 3 — Impacto simulado

**Archivo:** `Prueba_3_Impacto.csv`

**Configuración:** acelerómetro en ±16 g.

Se realizaron movimientos bruscos y controlados para registrar variaciones intensas de aceleración.

El rango de ±16 g se utilizó para reducir el riesgo de saturación observado durante un ensayo preliminar con un rango menor.

Esta prueba permite analizar la respuesta del filtro ante cambios rápidos de aceleración.

## 3. Estructura de los archivos CSV

Los archivos contienen cuatro columnas:

| Columna         | Descripción                                                            |
| --------------- | ---------------------------------------------------------------------- |
| `Muestra`       | Número consecutivo de la medición.                                     |
| `Tiempo_s`      | Tiempo transcurrido desde el inicio de la adquisición, en segundos.    |
| `AZ_Crudo_g`    | Aceleración medida directamente por el sensor, expresada en g.         |
| `AZ_Filtrado_g` | Aceleración obtenida después de aplicar el filtro IIR, expresada en g. |

Cada experimento fue programado para registrar 500 muestras y detener automáticamente la adquisición.

## 4. Objetivo de la validación

Los datos experimentales permiten estudiar:

* El comportamiento de la señal en reposo.
* La respuesta del filtro ante cambios de orientación.
* La atenuación de variaciones rápidas de aceleración.
* La respuesta del filtro ante movimientos bruscos.
* La correspondencia entre las mediciones y la ecuación de diferencias implementada.

Los archivos también sirven como base para comparar la respuesta experimental del filtro digital con el modelo continuo aproximado:

**H(s) = 8.8235 / (s + 8.8235)**

Esta comparación requiere realizar una simulación con las señales registradas y calcular las métricas de error correspondientes.

## 5. Limitaciones

Las mediciones corresponden únicamente al eje Z del acelerómetro.

Los movimientos se realizaron manualmente, por lo que no representan entradas ideales ni caídas humanas reales.

Además, las pruebas utilizaron diferentes rangos de aceleración: ±2 g para reposo y movimiento, y ±16 g para impacto simulado.

Los resultados permiten estudiar el procesamiento de señales, pero no demuestran por sí solos la capacidad del sistema para identificar caídas reales.


# Sistema de Detección de Caídas mediante ESP32 y MPU-9250

**Instituto Kriete de Ingeniería y Ciencias**
**Asignatura:** Señales y Sistemas
**Proyecto:** Aprendizaje Basado en Proyectos (PBL) — Fase 2
**Área:** Adquisición, procesamiento y análisis de señales

---

## 1. Descripción del proyecto

Este proyecto tiene como objetivo desarrollar un sistema de detección de caídas mediante el análisis de señales de aceleración obtenidas con un sensor MPU-9250 y procesadas utilizando un microcontrolador ESP32.

El sistema busca estudiar las variaciones de aceleración que pueden presentarse durante movimientos cotidianos y eventos bruscos, utilizando herramientas matemáticas de la asignatura Señales y Sistemas.

Durante la Fase 2 se trabaja principalmente en la adquisición de datos experimentales, la implementación de un filtro digital IIR de primer orden y el análisis de su comportamiento mediante un modelo matemático continuo aproximado.

Esta etapa permite establecer una base para el desarrollo posterior de un sistema capaz de identificar posibles caídas.

## 2. Objetivos

### Objetivo general

Analizar y procesar señales de aceleración obtenidas mediante un sensor MPU-9250 y un ESP32, utilizando un filtro digital IIR de primer orden y herramientas de modelado matemático para estudiar su comportamiento ante diferentes condiciones de movimiento.

### Objetivos específicos

1. Adquirir señales de aceleración del eje Z mediante el sensor MPU-9250 y el microcontrolador ESP32.
2. Implementar un filtro digital IIR de primer orden para suavizar las variaciones de aceleración registradas.
3. Realizar pruebas experimentales en condiciones de reposo, movimiento e impacto simulado.
4. Obtener una función de transferencia continua aproximada del filtro utilizando herramientas de Señales y Sistemas.
5. Analizar la estabilidad del modelo mediante la ubicación de sus polos y su respuesta en frecuencia.
6. Documentar los códigos, resultados experimentales y simulaciones para facilitar su revisión y reproducción.

## 3. Componentes y herramientas

| Componente o herramienta | Función                                          |
| ------------------------ | ------------------------------------------------ |
| ESP32                    | Adquisición y procesamiento de señales.          |
| MPU-9250                 | Medición de aceleración.                         |
| Arduino IDE              | Programación del ESP32.                          |
| MATLAB                   | Modelado matemático y análisis del filtro.       |
| Comunicación I²C         | Intercambio de datos entre el sensor y el ESP32. |
| GitHub                   | Organización y documentación del proyecto.       |

## 4. Funcionamiento general

El sistema utiliza el sensor MPU-9250 para medir la aceleración y transmitir las lecturas al ESP32 mediante comunicación I²C.

El microcontrolador procesa las mediciones mediante un filtro digital IIR de primer orden, permitiendo obtener una señal suavizada para su posterior análisis.

El funcionamiento general se divide en las siguientes etapas:

1. **Adquisición:** el MPU-9250 mide la aceleración del eje Z.
2. **Comunicación:** el ESP32 recibe las mediciones mediante I²C.
3. **Filtrado:** se aplica un filtro IIR de primer orden.
4. **Registro:** se almacenan las mediciones crudas y filtradas en archivos CSV.
5. **Análisis:** se estudia el comportamiento del filtro mediante MATLAB y un modelo matemático continuo aproximado.

La frecuencia nominal de muestreo utilizada es de **50 Hz**, equivalente a un período de **20 ms**.

## 5. Modelo matemático

### 5.1. Filtro digital IIR

El filtro implementado utiliza la siguiente ecuación de diferencias:

**y[n] = 0.15x[n] + 0.85y[n−1]**

Donde:

* `x[n]`: aceleración cruda medida por el sensor.
* `y[n]`: aceleración filtrada.
* `y[n−1]`: salida filtrada de la muestra anterior.
* `α = 0.15`: coeficiente del filtro.

Este filtro permite suavizar variaciones rápidas de aceleración, conservando principalmente las componentes de baja frecuencia.

### 5.2. Modelo continuo aproximado

Para realizar el análisis en el dominio de Laplace se utiliza una aproximación continua de primer orden.

La frecuencia angular característica se calcula mediante:

**ωc = α / [Ts(1 − α)]**

Con:

* `α = 0.15`
* `Ts = 0.02 s`

Se obtiene:

**ωc ≈ 8.8235 rad/s**

Por tanto, la función de transferencia continua aproximada es:

**H(s) = 8.8235 / (s + 8.8235)**

### 5.3. Análisis de estabilidad

El modelo continuo presenta un polo en:

**s = −8.8235**

Debido a que este polo se encuentra en el semiplano izquierdo del plano complejo, el modelo es estable.

La frecuencia característica correspondiente es aproximadamente:

**fc ≈ 1.404 Hz**

El comportamiento del modelo se estudia mediante un mapa de polos y ceros y diagramas de Bode de magnitud y fase.

**Nota:** la función H(s) corresponde a una aproximación continua del filtro digital, no a su representación discreta exacta.

## 6. Pruebas experimentales

Se realizaron tres pruebas experimentales utilizando el ESP32 y el MPU-9250.

Cada prueba fue programada para registrar **500 muestras durante aproximadamente 10 segundos**, utilizando una frecuencia nominal de 50 Hz.

### Prueba 1 — Reposo

**Archivo:** `Datos_Experimentales/Prueba_1_Reposo.csv`

Se registraron mediciones con el sensor en reposo para observar las pequeñas fluctuaciones de aceleración.

**Configuración:** rango de ±2 g.

**Objetivo:** analizar el comportamiento de la señal y la acción del filtro ante variaciones pequeñas.

### Prueba 2 — Movimiento y orientación

**Archivo:** `Datos_Experimentales/Prueba_2_Movimiento.csv`

Se realizaron movimientos y cambios de orientación del sensor para registrar variaciones de aceleración.

**Configuración:** rango de ±2 g.

**Objetivo:** analizar la respuesta del filtro ante cambios de movimiento.

### Prueba 3 — Impacto simulado

**Archivo:** `Datos_Experimentales/Prueba_3_Impacto.csv`

Se realizaron movimientos bruscos controlados para registrar aceleraciones de mayor magnitud.

**Configuración:** rango de ±16 g.

**Objetivo:** estudiar la respuesta del filtro ante cambios rápidos de aceleración.

Esta prueba corresponde a impactos simulados y no representa una validación de caídas humanas reales.

## 7. Estructura del repositorio

```text
PBL_Deteccion_de_caidas_Senales_y_sistemas/
│
├── Codigo_ESP32/
│   ├── Filtro_IIR_MPU9250.ino
│   ├── Prueba_1_Reposo.ino
│   ├── Prueba_2_Movimiento.ino
│   ├── Prueba_3_Impacto.ino
│   ├── Scanner_I2C.ino
│   └── README.md
│
├── Datos_Experimentales/
│   ├── Prueba_1_Reposo.csv
│   ├── Prueba_2_Movimiento.csv
│   ├── Prueba_3_Impacto.csv
│   └── README.md
│
├── Simulacion_MATLAB/
│   ├── Modelo_Laplace_H_s.m
│   └── README.md
│
└── README.md
```

### Descripción de las carpetas

**`Codigo_ESP32/`**

Contiene los programas utilizados para la comunicación con el sensor, el filtrado de señales y la adquisición de datos experimentales.

**`Datos_Experimentales/`**

Contiene los archivos CSV generados durante las tres pruebas, incluyendo las mediciones de aceleración cruda y filtrada.

**`Simulacion_MATLAB/`**

Contiene el código utilizado para analizar el modelo continuo aproximado del filtro, su estabilidad y su respuesta en frecuencia.

Cada carpeta incluye su propio archivo README con información específica sobre su contenido.

## 8. Reproducción del proyecto

### Adquisición de datos con ESP32

1. Conectar el sensor MPU-9250 al ESP32 mediante comunicación I²C.
2. Abrir Arduino IDE y seleccionar la placa ESP32.
3. Cargar el programa correspondiente.
4. Abrir el Monitor Serie a 115200 baudios.
5. Ejecutar las pruebas y registrar los datos generados.

Las conexiones utilizadas son:

| MPU-9250 | ESP32   |
| -------- | ------- |
| VCC      | 3V3     |
| GND      | GND     |
| SDA      | GPIO 21 |
| SCL      | GPIO 22 |

La dirección I²C utilizada es `0x68`.

### Simulación en MATLAB

1. Abrir MATLAB.
2. Ejecutar el archivo `Simulacion_MATLAB/Modelo_Laplace_H_s.m`.
3. Revisar los parámetros matemáticos calculados.
4. Analizar el mapa de polos y ceros.
5. Observar los diagramas de Bode de magnitud y fase.

## 9. Resultados de la Fase 2

Durante esta etapa se desarrollaron los siguientes elementos:

* Implementación del filtro digital IIR de primer orden en el ESP32.
* Adquisición de mediciones experimentales del eje Z del MPU-9250.
* Registro de tres pruebas con 500 muestras cada una.
* Organización de los resultados experimentales en archivos CSV.
* Obtención de un modelo continuo aproximado mediante la transformada de Laplace.
* Determinación del polo y análisis teórico de estabilidad.
* Implementación en MATLAB de gráficas para estudiar la respuesta en frecuencia.

Los archivos del repositorio permiten consultar el código desarrollado, las mediciones obtenidas y el procedimiento de análisis matemático.

## 10. Limitaciones y trabajo futuro

El sistema desarrollado durante esta fase se concentra en el procesamiento y análisis de señales de aceleración.

Entre sus limitaciones se encuentran:

* Las mediciones experimentales se concentran en el eje Z.
* Los impactos registrados corresponden a movimientos simulados.
* El modelo de Laplace es una aproximación del filtro digital.
* La simulación MATLAB actual no realiza una comparación automática con los archivos CSV.
* Todavía no se ha demostrado experimentalmente la detección confiable de caídas humanas.

Como trabajo futuro se plantea ampliar el análisis de las señales, incorporar criterios para identificar posibles caídas y evaluar el funcionamiento del sistema mediante pruebas adicionales.

## 11. Conclusión

La Fase 2 permitió establecer una base experimental y matemática para el desarrollo del sistema de detección de caídas.

Mediante el ESP32 y el MPU-9250 se obtuvieron señales de aceleración que fueron procesadas utilizando un filtro digital IIR de primer orden.

Asimismo, el análisis mediante MATLAB permitió estudiar un modelo continuo aproximado del filtro, determinar su estabilidad y representar su respuesta en frecuencia.

Estos resultados proporcionan una base para continuar con el desarrollo y la validación del sistema en las siguientes etapas del proyecto.

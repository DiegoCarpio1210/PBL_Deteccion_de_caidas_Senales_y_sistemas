# Simulación MATLAB — Sistema de Detección de Caídas

Esta carpeta contiene el código desarrollado en MATLAB para analizar matemáticamente el filtro IIR de primer orden utilizado en el proyecto de detección de caídas de la asignatura Señales y Sistemas.

El objetivo es obtener un modelo continuo aproximado del filtro digital implementado en el ESP32, determinar su función de transferencia y analizar su comportamiento mediante la ubicación de sus polos y su respuesta en frecuencia.

## 1. Archivo incluido

| Archivo                | Descripción                                                                                                                                              |
| ---------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Modelo_Laplace_H_s.m` | Calcula los parámetros del modelo continuo aproximado, determina la función de transferencia, representa el polo del sistema y genera diagramas de Bode. |

## 2. Parámetros del sistema

Los parámetros utilizados en el modelo son:

| Parámetro                      | Valor                 |
| ------------------------------ | --------------------- |
| Sensor utilizado               | MPU-9250              |
| Microcontrolador               | ESP32                 |
| Tipo de filtro                 | IIR de primer orden   |
| Coeficiente del filtro (α)     | 0.15                  |
| Frecuencia nominal de muestreo | 50 Hz                 |
| Período de muestreo (Ts)       | 0.02 s                |
| Variable analizada             | Aceleración del eje Z |

Estos parámetros corresponden a la configuración del filtro implementado en el ESP32.

## 3. Ecuación del filtro digital

El filtro IIR utilizado en el proyecto está definido por la siguiente ecuación de diferencias:

**y[n] = 0.15x[n] + 0.85y[n−1]**

Donde:

* `x[n]`: aceleración cruda medida por el sensor.
* `y[n]`: aceleración filtrada.
* `y[n−1]`: valor filtrado de la muestra anterior.
* `α = 0.15`: coeficiente del filtro.

El filtro permite suavizar las variaciones rápidas de aceleración registradas por el MPU-9250.

## 4. Modelo continuo aproximado

Para estudiar el comportamiento del filtro mediante la transformada de Laplace, se utiliza una aproximación continua de primer orden.

La frecuencia angular característica se calcula mediante:

**ωc = α / [Ts(1 − α)]**

Sustituyendo los valores:

**ωc = 0.15 / [0.02(0.85)]**

**ωc ≈ 8.8235 rad/s**

La función de transferencia del modelo continuo aproximado es:

**H(s) = 8.8235 / (s + 8.8235)**

Esta función relaciona la entrada y la salida del filtro en el dominio de Laplace.

## 5. Análisis de polos y ceros

A partir de la función de transferencia:

**H(s) = 8.8235 / (s + 8.8235)**

Se obtiene:

* **Polo:** s = −8.8235
* **Ceros finitos:** ninguno
* **Ubicación del polo:** semiplano izquierdo del plano complejo

Debido a que el polo se encuentra en el semiplano izquierdo, el modelo continuo es estable.

El programa MATLAB genera una representación gráfica para visualizar la ubicación del polo.

## 6. Respuesta en frecuencia

El código también permite analizar el comportamiento del filtro mediante diagramas de Bode.

Estos diagramas representan:

**Magnitud:** muestra cómo cambia la amplitud de la salida del filtro según la frecuencia de la señal de entrada.

**Fase:** muestra el desfase introducido por el filtro para diferentes frecuencias.

La frecuencia característica del modelo continuo es aproximadamente:

**fc = ωc / (2π) ≈ 1.404 Hz**

El filtro presenta un comportamiento pasa-bajas: conserva principalmente las componentes de baja frecuencia y atenúa progresivamente las componentes de mayor frecuencia.

## 7. Ejecución del programa

Para ejecutar la simulación:

1. Abrir MATLAB.
2. Descargar o abrir el archivo `Modelo_Laplace_H_s.m`.
3. Ejecutar el programa.
4. Revisar los parámetros calculados.
5. Observar la gráfica de polos y ceros.
6. Analizar los diagramas de Bode de magnitud y fase.

## 8. Relación con las pruebas experimentales

El modelo matemático permite estudiar el comportamiento esperado del filtro utilizado en el ESP32.

Las mediciones experimentales se encuentran en la carpeta `Datos_Experimentales` del repositorio:

* `Prueba_1_Reposo.csv`
* `Prueba_2_Movimiento.csv`
* `Prueba_3_Impacto.csv`

Estos archivos contienen la aceleración cruda y filtrada registrada durante las pruebas de reposo, movimiento e impacto simulado.

El modelo continuo permite realizar un análisis teórico complementario a las mediciones experimentales.

## 9. Alcance y limitaciones

La función de transferencia presentada corresponde a una aproximación continua del filtro digital implementado.

Por esta razón, el modelo de Laplace no representa exactamente todas las características del sistema discreto.

El programa permite calcular los parámetros teóricos y visualizar la respuesta del modelo continuo, pero no realiza automáticamente una comparación numérica con los archivos CSV experimentales.

La simulación constituye una etapa de análisis matemático del procesamiento de señales y no representa una validación completa de un detector de caídas.


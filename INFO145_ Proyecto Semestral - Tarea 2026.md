# **INFO145 : Diseño y Análisis de Algoritmos**

## **Proyecto Semestral: Técnicas de Representación y Compresión en Arreglos Ordenados**

**Profesor:** Héctor Ferrada Escobar  
**Auxiliares:** Carolina Obreque & Benjamín Parra  
**Semestre:** Primer semestre 2026

## **1\. Contexto y Objetivos**

El presente proyecto semestral tiene como propósito evaluar empírica y teóricamente el espacio de almacenamiento y el tiempo de ejecución en estructuras de datos. Los equipos de trabajo deberán implementar, medir y comparar diferentes estrategias para representar un arreglo ordenado de gran magnitud. El diseño empezará con una representación explícita estándar, luego una codificación llamada Gap-Coding apoyada por índices de muestreo, hasta llegar a técnicas de compresión asignadas específicamente a cada grupo.

### **Objetivos Específicos:**

* Implementar estructuras de datos que minimicen el uso de espacio.  
* Diseñar algoritmos de búsqueda adaptados a representaciones comprimidas.  
* Cuantificar teórica y empíricamente la complejidad espacial y temporal. (Se debe medir el tiempo al realizar varias búsquedas no basta con solo una)

## **2\. Especificaciones**

### **2.1. Caso 1: Representación Explícita (Línea Base)**

Consiste en dos arreglos de gran tamaño ordenados de menor a mayor, deben ser inicializados con valores aleatorios ordenados, siguiendo una distribución:

1. **Lineal:** (Puede ser definiendo $A\[0\]=rand(), A\[i\]=A\[i-1\]+rand()\\%\\epsilon$)  
2. **Normal:** (Puede utilizar librerías si así lo requiere) con distintas propuestas de desviaciones estándar.

Una vez inicializadas las estructuras, se deben realizar búsquedas binarias y medir su tiempo tanto teóricamente como experimentalmente para una gran cantidad de datos. Los arreglos servirán como base de control para comparar el tiempo de respuesta y el espacio utilizado de los Casos 2 y 3\.

### **2.2. Caso 2: Representación con Gap-Coding**

Se representan ambos arreglos con Gap-Coding, los arreglos originales se vuelven inaccesibles, en su lugar, se utilizara una estructura adicional llamada "sample" para ayudar a la búsqueda. Para representar un arreglo utilizando Gap-Coding se debe calcular la diferencia entre cada elemento consecutivo del arreglo ordenado. El primer elemento del arreglo resultante será el mismo que el primer elemento del arreglo original.  
Ejemplo, para un arreglo X \= \[2, 7, 10, 12, 12, 16\] los gaps serian $GC(X)=\[2,5,3,2,0,4\]$

* **Representación:** Para un arreglo ordenado A, se define GC, donde $GC\[0\]=A\[0\]$ y $GC\[i\]=A\[i\]-A\[i-1\]$ para $i\>0$. Esta estructura adicional se utiliza para reconstruir al arreglo original sin acceder a este.  
* **Índice de Muestreo (Sample):** Estructura auxiliar para permitir la búsqueda binaria (ya que en GC no hay acceso aleatorio en $\\mathcal{O}(1)$ a los valores originales).  
  * Defina un tamaño de muestra $m \\ll n$ y un salto b (estático o paramétrico). Puede proponer b como variable, por ejemplo, $m=log\_{3}n$ con $b=3^{j}$.  
  * Ejemplo: Si $A=\[2,7,10,12,12,16\]$ con $m=3$ y $b=2$, con $b=\\Delta i=\\frac{n}{m}$, el sample seria \[2, 10, 12\].  
  * Operación: Búsqueda binaria sobre el Sample para hallar un rango \[L, R\], seguida de una decodificación secuencial sobre GC en dicho intervalo para encontrar la posición del elemento.

### **2.3. Caso 3: Compresión de arreglo de gaps y Trade-off Espacio-Tiempo**

En esta última etapa, se deben comprimir los arreglos que ya estaban representados con Gap-Coding en el Caso 2, utilizando una técnica de compresión entregada mas adelante. El objetivo principal es utilizar una nueva estructura de arreglo para cada entrada, cuya representación en bits por elemento sea estrictamente menor que la inicial. Por ejemplo, si los elementos originales eran enteros de 32 bits, la técnica debe calcular un nuevo largo en bits (ya sea un largo máximo fijo para todos, o un largo variable) para que cada elemento del nuevo arreglo ocupe exclusivamente esa cantidad reducida de bits.  
Deberá mantener la capacidad de acotar el intervalo utilizando la estructura sample del Caso 2, pero la búsqueda del elemento final debe realizarse navegando y decodificando directamente sobre su nuevo arreglo comprimido a nivel de bits. Esto servirá para evaluar si el tiempo de búsqueda sacrificado es justificado por el espacio de memoria ahorrado.  
**Importante:** A cada grupo se le pedirá trabajar con uno de los algoritmos de la seccion 5\. Independiente del algoritmo asignado, el flujo de trabajo general es el siguiente:

1. **Investigar el Algoritmo:** Investigar sobre el algoritmo de compresión asignado y entregar una pequeña descripción del mismo.  
2. **Análisis Teórico:** Analizar matemáticamente el algoritmo asignado y formular una estimación teórica del espacio final. Para determinar esto, requiere encontrar la cantidad de bits utilizada por cada elemento considerando códigos de largo fijo (Worst Case Entropy) y variable. (ej. si requiere largos variables $||\\mu\_{i}||=log\_{2}(\\frac{1}{p(\\mu\_{i})})$ u otras aproximaciones). Detalle la deducción de estas fórmulas en su informe.  
3. **Implementación a Nivel de Bits:** Mapear los gaps utilizando el algoritmo sobre una estructura contigua subyacente (ej. un arreglo de bytes, short de 8/16 bits, o uint64\_t usado como mapa de bits continuo).  
4. **Búsqueda:** Se realiza búsqueda binaria sobre el Sample para hallar un rango \[L, R\] al igual que en el Caso 2\.  
5. **Decodificación y Medición:** Implementar la lógica para leer, extraer y decodificar los bits necesarios dentro del rango comprimido para encontrar el valor final buscado. Mida los tiempos para compararlos con los Casos 1 y 2\.

Para estimar tamaños base o diseñar empacados manuales, considere la siguiente tabla de referencia de tipos de datos en la arquitectura estándar (C/C++):

| Tipo de Dato | Tamaño (sizeof) | Observaciones / Rango Típico   |
| :---- | :---- | :---- |
| char / int8\_t | 1 byte (8 bits) | Útil para gaps muy pequeños (0 a 255). Ideal como bloque base de arreglos comprimidos. |
| short / int16\_t | 2 bytes (16 bits) | Gaps medianos (0 a 65,535). |
| int / int32\_t | 4 bytes (32 bits) | Estándar para valores originales. |
| long long int / int64\_t | 8 bytes (64 bits) | Máscaras de bits amplias. Soporta operaciones bitwise («, », &, |) eficientes. |

 

## **3\. Metodología de Experimentación**

Para validar sus estructuras, debe ejecutar varias pruebas de espacio y tiempo. Considere el uso de herramientas como Valgrind para evitar fugas de memoria, dado el tamaño de los datos.

* **Generación de Datos:** Arreglos aleatorios ascendentes con Distribución Lineal y Distribución Normal (Gaussiana) iterando sobre distintas desviaciones estándar.  
* **Escala de Pruebas:** Las pruebas deben ser en arreglos de gran tamaño, para los experimentos considere tamaños incrementales en potencias de 2 o de 10 (ej. $10^{6}$, $10^{7}$, $10^{8}$).  
* **Entorno de Medición:** Compile su código fuente utilizando banderas de optimización estándar (ej. g++ \-O3).

## **4\. Hitos de Entrega y Ponderaciones**

El proyecto se desarrollará a lo largo del semestre mediante entregas incrementales a través de la plataforma Siveduc. Los equipos serán de máximo 4 integrantes.

### **4.1. Hito 1: Implementación (35%) \- Jueves 28 de Mayo**

Entrega del repositorio en github con el código fuente funcional en lenguaje C++, o el que el grupo estime conveniente.  
**Estructura del Repositorio**

* Los lenguajes compilados deben proveer un script de compilación. En caso de usar C++ puede incluir un Makefile.  
* Debe incluir un archivo README.md con instrucciones de: cómo compilar, cómo ejecutar cada modo, qué argumentos recibe el programa, y qué archivos de salida produce.  
* El código debe estar modularizado: cada algoritmo de compresión debe implementarse en un archivo de cabecera propio (.hpp), separado del archivo principal main.cpp. En C++ basta con incluirlos mediante \#include "ruta/algoritmo.hpp", sin necesidad de agregar flags adicionales al Makefile.  
* El código debe usar nombres descriptivos, evitar lógica duplicada y aplicar buenas prácticas. Se recomienda separar el programa en pasos (construcción, búsqueda, medición), para facilitar la medición de los tiempos y espacio.

**Modos de Ejecución**

* **Modo benchmark:** Ejecuta la generación de datos, construcción de estructuras y medición de tiempos y espacio de forma automática para todos los casos.  
  *Ejemplo de uso:* ./main \--benchmark  
* **Modo archivo:** Recibe como argumento la ruta a un archivo .csv con números enteros, construye la estructura correspondiente y luego permite al usuario ingresar valores a buscar de forma interactiva y en qué estructura será buscado.  
  *Ejemplo de uso:* ./main \-i ruta/del/archivo.csv

**Salidas Esperadas**

* En modo benchmark, el programa debe generar un archivo .csv con las métricas recopiladas para cada caso y tamaño de entrada.  
* En modo archivo, el programa debe indicar si el valor buscado fue encontrado y en qué posición, junto con el tiempo de búsqueda.  
* El programa no debe presentar fugas de memoria ni comportamiento indefinido por desbordamiento (overflow). Se recomienda usar Valgrind.

### **4.2. Hito 2: Informe (30%) \- Jueves 11 de Junio**

Documento formal claro, objetivo y detallado de máximo 8 páginas (formato IEEE o similar).

* **Introducción y Contexto:** Contexto del problema y declaración de la hipótesis de rendimiento.  
* **Metodología y Diseño:** Análisis asintótico de costos de tiempo y espacio de sus soluciones. Inclusión de pseudocódigos. Deducción matemática de las fórmulas.  
* **Resultados y Experimentación:** Gráficos que muestren los resultados de tiempo vs tamaño (n) y espacio vs tamaño (n) para las distintas distribuciones.  
* **Conclusiones:** Debe responder a la hipótesis inicial y resumir los aspectos más relevantes.

### **4.3. Hito 3: Video (35%) \- Jueves 18 de Junio**

Cápsula de video de 8 minutos aprox donde participen todos los integrantes del grupo explicando el trabajo realizado.

* Minuto 1: Introducción y contexto técnico.  
* Minutos 2-4: Desarrollo de la solución y grabación de pantalla mostrando código.  
* Minutos 5-6: Explicación de la experimentación y discusión de hallazgos.  
* Minutos 7-8: Conclusiones y detalle de dificultades.

## **5\. Algoritmos de Compresión**

A cada grupo de trabajo se le asignará uno de los siguientes algoritmos para aplicar sobre los gaps. Nota de implementación: Como simplificación permitida, los grupos pueden empaquetar cada código en el tipo de dato más pequeño que lo contenga (uint8\_t, uint16\_t, etc.) en lugar de implementar un empaquetado bit a bit estricto.

### **5.1. Codificación de Huffman**

Algoritmo basado en la frecuencia de aparición de los gaps. Asigna una representación en bits más corta a las diferencias más comunes y una más larga a las más raras.

| Gap | Frecuencia | Código asignado   |
| :---- | :---- | :---- |
| 1 | 1000 | 0 |
| 2 | 500 | 10 |
| 5 | 80 | 110 |
| 7 | 5 | 11101011 |

 

### **5.2. Codificación de Shannon-Fano**

Similar a Huffman, genera representaciones de bits de largo variable según la probabilidad de los gaps, pero construyendo el árbol de forma descendente (top-down).

| Gap | Frecuencia | Código asignado   |
| :---- | :---- | :---- |
| 1 | 1000 | 00 |
| 2 | 500 | 01 |
| 5 | 250 | 10 |
| 7 | 125 | 110 |
| 9 | 125 | 111 |

 

### **5.3. Codificación Elias-Fano**

Técnica cuasi-sucinta que opera directamente sobre los valores del arreglo ordenado en lugar de sobre los gaps. Los k bits bajos se almacenan directamente y los bits altos se codifican en unario.

| Valor (Binario) | Bits altos (unario) | Bits bajos   |
| :---- | :---- | :---- |
| 3 (0011) | 00 → 10 | 11 |
| 6 (0110) | 01 → 010 | 10 |
| 9 (1001) | 10 → 0010 | 01 |
| 13 (1101) | 11 → 00010 | 01 |

 

### **5.4. Partitioned Elias-Fano (PEF)**

Extensión de Elias-Fano clásico que permite aplicar la técnica sobre arreglos de gaps dividiendo en bloques y acumulando los gaps localmente.

| Bloque | Gaps | Acumulado local | Uk | Bits bajos por elemento   |
| :---- | :---- | :---- | :---- | :---- |
| 0 | 2, 5, 3, 2, 0 | \[2, 7, 10, 12, 12\] | 12 1 | 1 bit |
| 1 | 1, 6, 2, 3, 4 | \[1, 7, 9, 12, 16\] | 16 1 | 1 bit |

 

### **5.5. PForDelta (Patched Frame of Reference Delta)**

Calcula un ancho máximo fijo en bits (b) que cubra a la gran mayoría de gaps. Los valores fuera (outliers) se manejan por separado.

| Bloque de gaps | \[3, 5, 2, 7, 4, 1, 256, 3, 6, ...\] |
| :---- | :---- |
| Ancho elegido | $b=4$ bits (cubre valores 0-15) |
| Outlier | gap \= 256 en posición 6 → requiere tratamiento especial |
| Resultado | todos los demás en 4 bits \+ manejo del outlier |

 

### **5.6. Codificación de Elias (Gamma y Delta)**

Códigos universales para enteros positivos cuya longitud depende únicamente de la magnitud del número.

| Valor | Código γ | Bits usados   |
| :---- | :---- | :---- |
| 1 | 1 | 1 |
| 2 | 010 | 3 |
| 3 | 011 | 3 |
| 4 | 00100 | 5 |
| 7 | 00111 | 5 |
| 8 | 0001000 | 7 |

 

## **6\. Resumen de Entregables e Hitos**

| Hito | Descripción Breve del Entregable | Ponderación | Fecha de Entrega   |
| :---- | :---- | :---- | :---- |
| 1 | Código Fuente: Implementación completa (Casos 1, 2 y 3). Debe incluir archivo Makefile y README.md explicativo. | 35% | Jueves 28 de Mayo |
| 2 | Informe: Documento formato IEEE (máx. 8 págs) con análisis asintótico, hipótesis, gráficos de tiempos y conclusiones. | 30% | Jueves 11 de Junio |
| 3 | Video: Cápsula de 8 minutos con participación de todo el equipo (Introducción, Screencast del código, Experimentación, Conclusión). | 35% | Jueves 18 de Junio |

   
Cualquier duda o solicitud de revisión de algoritmos de compresión asignados será atendida por los ayudantes del ramo. Se aconseja iniciar el trabajo experimental lo antes posible.
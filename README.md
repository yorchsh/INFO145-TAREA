# INFO145: Técnicas de Representación y Compresión en Arreglos Ordenados

## Integrantes

- David Minder
- Javier Ramirez
- Fabian Reyes
- Jorge Seron

## Descripción

Implementación y comparación empírica de tres representaciones de arreglos ordenados de gran magnitud:

- **Caso 1 — Línea base:** Arreglo explícito con búsqueda binaria estándar.
- **Caso 2 — Gap Coding:** Los gaps entre elementos consecutivos se empaquetan a nivel de bits usando el mínimo de bits necesario. Una estructura auxiliar de muestreo (sample) permite búsqueda binaria acotada seguida de decodificación secuencial.
- **Caso 3 — Shannon-Fano:** Los gaps del Caso 2 se comprimen con codificación Shannon-Fano (códigos de largo variable top-down). La búsqueda usa el sample del Caso 2 para acotar el rango y luego decodifica directamente sobre la estructura comprimida.

Ambas distribuciones de datos (uniforme y normal/gaussiana) son evaluadas en tamaños incrementales. Los resultados se exportan a `salida.csv`.

```
include/
  vector_generation.hpp   generación de vectores uniforme y normal
  binary_search.hpp       búsqueda binaria sobre vector explícito
  gap_coding.hpp          estructura GapArray con sample
  shannon_fano.hpp        codificación Shannon-Fano sobre gaps
main.cpp                  flujo principal, parsing de argumentos, benchmark
makefile                  script de compilación
entrada.csv               ejemplo de archivo de entrada
salida.csv                generado al ejecutar modo --benchmark
```

## Como compilar

```bash
make
```

Requiere g++ con soporte C++26 (`-std=c++26`). Compilado con `-O3`.

## Como ejecutar

### Modo benchmark

Genera datos automáticamente, construye las tres estructuras y mide tiempos y espacio para ambas distribuciones.

```bash
./main --benchmark
```

### Modo archivo

Recibe un archivo `.csv` con enteros, construye las estructuras y permite búsquedas interactivas.

```bash
./main -i <ruta/del/archivo.csv>
```

### Entradas y salida

El archivo de entrada debe tener enteros separados por comas (puede tener saltos de línea):

```
<NUMERO>,<NUMERO>,<NUMERO>,<NUMERO>
```

Ver `entrada.csv` como ejemplo.

En modo archivo, el programa solicita el valor a buscar y la estructura a usar, luego indica si fue encontrado, en qué posición y el tiempo de búsqueda.

La salida del benchmark se guarda en `salida.csv` con el formato:

```
<tamaño>,<tiempo_ms>,<espacio_bytes>,<distribución>,<caso>
```

### Ejemplo de ejecucion

```
Para 2^28 valores, promedio:
-----------------
fase creacion: 30 ms, espacio: 5mb
10000 busquedas caso 1: 30ms, espacio: 8mb
10000 busquedas caso 2: 70ms, espacio: 4mb
10000 busquedas caso 3: 200ms, espacio: 2mb

Creacion caso 2: 20ms
Creacion caso 3: 30ms

radio de mejora (espacio):
Caso 2 vs caso 1: 50%
Caso 3 vs caso 1: 75%

radio de mejora (tiempo):
Caso 2 vs caso 1: [tiempo]
Caso 3 vs caso 1: [insertar tiempo]

archivo creado en salida.csv
```

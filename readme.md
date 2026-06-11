# INFO145: Algoritmos de compresion

## Nombres
- David Minder
- Javier Ramírez
- Fabian Reyes
- Jorge Serón

## Descripción

El programa mide una cantidad absurda de datos en el modo benchmark:
- size_MiB: tamaño del vector original en Mebibytes
- standard_deviation_sigma: si es aplicable, desviación estándar del vector normal
Para el caso 1 (vector original):
- gen_time_ms: Tiempo de generación del vector en milisegundos
- sort_time_ms: Tiempo que tomo en ordernarse el vector
- true_search_time_ms: Tiempo que tomo en hacer RANDOM_BINARY_SEARCH_COUNT búsquedas binarias de elementos aleatorios
- true_search_found: Las veces que se encontro el elemento en el vector
- true_search_not_found: Las veces que no se encontro el elemento en el vector
- select_search_time_ms: Tiempo que tomo en hacer RANDOM_BINARY_SEARCH_COUNT búsquedas binarias usando elementos del mismo vector
- select_search_found: Las veces que se encontro el elemento en el vector (útil para validar funcionamiento correcto)
- select_search_not_found: Las veces que no se encontro el elemento en el vector

Para el caso 2 (gap coding):
- gc_gen_time: Tiempo (ms) que tomo generar el gap coding a partir del vector
- gc_word_size: Tamaño virtual de los gaps en bits
- gc_total_bits: cantidad de bits totales que se usa para almacenar los gaps
- gc_sample_size_bits: cantidad de bits totales que se usa para almacenar los samples
- gc_true_search_time_ms: Tiempo que tomo hacer RANDOM_BINARY_SEARCH_COUNT búsquedas hibridas (binarias y secuencial) de elementos aleatorios
- gc_true_search_found: Las veces que se encontro el elemento en el gap coding
- gc_true_search_not_found: Las veces que no se encontro el elemento en el gap coding
- gc_select_search_time_ms: Tiempo que tomo en hacer RANDOM_BINARY_SEARCH_COUNT búsquedas binarias usando elementos del mismo gap coding.
- gc_select_search_found:  Las veces que se encontro el elemento en el gap coding (útil para validar funcionamiento correcto) 
- gc_select_search_not_found: Las veces que no se encontro el elemento en el vector

 Para el caso 3 (shannon fano):
 - sf_gen_time_ms: Tiempo que tomo generar el shannon fano a partir del gap coding
 - sf_search_time_ms: Tiempo que tomo hacer RANDOM_BINARY_SEARCH_COUNT búsquedas de elementos del vector
 - space_bits_compressed: Espacio que ocupa el vector comprimido
 - space_bits_explicit: Bits que ocupaba el vector original

./include tiene los includes

main contiene el flujo de inicializacion y parsing
salida.csv se genera al ejecutar modo --benchmark y contiene los resultados

## Como compilar

Basta con ejecutar
```bash
make
```

## Rango de números aceptados

El programa trabaja con enteros de 64 bits con signo (`int64_t`), parseados con `strtoll`.  
Rango: `[-9223372036854775808, 9223372036854775807]`

## Como ejecutar

**Modo benchmark**: genera vectores, construye estructuras y mide tiempos para todos los casos:
```bash
./main --benchmark
```
El resultado se escribe en `salida.csv`. Opcionalmente se puede especificar otro archivo:
```bash
./main --benchmark -o <archivo_salida.csv>
```

**Modo archivo**: lee un CSV con números enteros, construye la estructura elegida y permite buscar interactivamente:
```bash
./main -i <archivo.csv>
```
El programa pregunta qué estructura usar (1, 2 o 3). Alternativamente se puede pasar directamente:
```bash
./main -i <archivo.csv> -c <caso>
```
- `-c 1`: búsqueda binaria explícita (Caso 1)
- `-c 2`: gap coding (Caso 2)
- `-c 3`: Shannon-Fano sobre gaps (Caso 3)

El programa ordena el archivo de entrada automáticamente.  
Ingrese valores a buscar uno por línea; escriba `q` para salir.

### Formato del archivo de entrada

```
<NUMERO>,<NUMERO>,<NUMERO>,...
```
O separados por comas y saltos de línea. Ver `entrada.csv` como ejemplo.

### Salida del modo benchmark

El archivo `.csv` de salida tiene el siguiente formato:

```
SETTINGS
RANDOM_BINARY_SEARCH_COUNT,<valor>

LINEAL_VECTOR
size_MiB,gen_time_ms,sort_time_ms,true_search_time_ms,true_search_found,true_search_not_found,select_search_time_ms,select_search_found,select_search_not_found,gc_gen_time,gc_word_size,gc_total_bits,gc_sample_size_bits,gc_true_search_time_ms,gc_true_search_found,gc_true_search_not_found,gc_select_search_time_ms,gc_select_search_found,gc_select_search_not_found,sf_gen_time_ms,sf_search_time_ms,space_bits_compressed,space_bits_explicit
<filas de datos>

NORMAL_VECTOR
size_MiB,standard_deviation_sigma,gen_time_ms,...
<filas de datos>
```

### Ejemplo de ejecución modo benchmark

```
%%%%%%%%%%%%%%%%%%%%%%%%%
%%                     %%
%%   BENCHMARK MODE    %%
%%                     %%
%%%%%%%%%%%%%%%%%%%%%%%%%
CASE 1: (1/4): generate: lineal distribution vector (8 mebibytes)... DONE.
    CASE 1: (2/4): sort: lineal distribution vector... DONE.
    CASE 1: (3/4): random binary search (262144n): lineal distribution vector... DONE.
    CASE 1: (4/4): random from vector binary search (262144n): lineal distribution vector... DONE.
    CASE 2: (1/3): generating gap_coding array from: lineal distribution vector... DONE.
    CASE 2: (2/3): random binary search: lineal gap_coding... DONE.
    CASE 2: (3/3): random from gap_coding binary search: lineal gap_coding... DONE.
    CASE 3: (1/2): build Shannon-Fano: lineal distribution vector... DONE.
    CASE 3: (2/2): search (262144n): lineal distribution vector... DONE.
```

### Ejemplo de ejecución modo archivo

```
$ ./main -i entrada.csv -c 3
%%%%%%%%%%%%%%%%%%%%%%%%%
%%                     %%
%%      FILE MODE      %%
%%                     %%
%%%%%%%%%%%%%%%%%%%%%%%%%
Construyendo Shannon-Fano... listo. 20 elementos. Ingrese valores, 'q' para salir:
5
5: encontrado en posicion 2 (1823 ns)
99
99: no encontrado (412 ns)
q
```

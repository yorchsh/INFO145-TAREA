# TODO — Hito 1 (Deadline: Jueves 28 Mayo)
**Quedan ~5 días. Prioridad: terminar Caso 2, luego Shannon-Fano (Caso 3).**

---

## URGENTE: Arreglar Caso 2 (gap_coding.hpp está roto)

- [ ] **1. Corregir errores de compilación en `gap_coding.hpp`**
  - `std::T*` → `T*` (línea 24)
  - Agregar `;` en línea 61
  - `block_size` → `gap.block_size` (línea 77)
  - Eliminar `&` suelto (línea 134)

- [ ] **2. Completar el constructor de GapArray**
  - Verificar que el primer elemento (`GC[0] = A[0]`) se almacena correctamente
  - Verificar que el bitpacking de gaps (shift_amount negativo) sea correcto cuando un gap cruza dos words de 64 bits
  - Corregir lógica del sample: guardar `v[0]`, `v[b]`, `v[2b]`, ... correctamente

- [ ] **3. Implementar `get(index)` en GapArray**
  - Encontrar el sample point más cercano por debajo: `s = sample[(index / jump_length)]`
  - Decodificar secuencialmente los gaps desde esa posición hasta `index`
  - Retornar el valor reconstruido

- [ ] **4. Implementar búsqueda en GapArray**
  - Búsqueda binaria sobre `sample[]` para hallar rango [L, R]
  - Decodificación secuencial en ese rango sobre el gap array
  - Retornar posición del elemento (o -1 si no existe)

- [ ] **5. Agregar Case 2 al benchmark en main.cpp**
  - Construir GapArray desde uniform_vector y normal_vector
  - Medir tiempo de construcción
  - Medir tiempo de búsqueda (trueRandom y selectRandom)
  - Medir espacio: `sizeof(uint64_t) * gap.physical_size + sizeof(T) * sample.size`

---

## Caso 3: Shannon-Fano

- [ ] **6. Estudiar Shannon-Fano (top-down)**
  - Contar frecuencias de cada gap en el arreglo
  - Ordenar por frecuencia descendente
  - Dividir recursivamente en dos grupos de igual probabilidad acumulada
  - Asignar 0 al grupo izquierdo, 1 al derecho

- [ ] **7. Crear `include/shannon_fano.hpp`**
  - Función `buildCodes(gaps)` → retorna `map<gap_value, bitstring>`
  - Función `encode(gaps, codes)` → empaqueta en arreglo de uint64_t o uint8_t
  - Función `decode(compressed, codebook, pos)` → decodifica desde posición bit

- [ ] **8. Estructura comprimida Shannon-Fano**
  - Empaquetar cada código en el tipo más pequeño que lo contenga (uint8_t, uint16_t, etc.)
    - El enunciado permite esta simplificación (sección 5, nota final)
  - Guardar el codebook junto a la estructura
  - Mantener el Sample del Caso 2 para acotar [L, R]

- [ ] **9. Búsqueda en estructura Shannon-Fano**
  - Binary search sobre Sample → [L, R]
  - Decodificar secuencialmente en el rango comprimido hasta llegar al elemento
  - Medir tiempo

- [ ] **10. Agregar Case 3 al benchmark en main.cpp**
  - Construir estructura Shannon-Fano desde gap arrays de Case 2
  - Medir tiempo de construcción, espacio, y tiempo de búsqueda

---

## Infraestructura

- [ ] **11. Modo archivo (`./main -i ruta/archivo.csv`)**
  - Leer CSV con enteros
  - Construir las 3 estructuras (Case 1, 2, 3)
  - Pedir al usuario un valor a buscar y en qué estructura
  - Mostrar: encontrado/no encontrado, posición, tiempo de búsqueda

- [ ] **12. Output CSV con métricas del benchmark**
  - Columnas: caso, distribución, n, tiempo_construccion_ms, espacio_bytes, tiempo_busqueda_ms
  - Guardarlo en un archivo como `resultados.csv`

- [ ] **13. Completar README.md**
  - Cómo compilar: `make`
  - Cómo ejecutar: `./main --benchmark` y `./main -i archivo.csv`
  - Qué argumentos recibe
  - Qué archivos de salida produce

- [ ] **14. Verificar sin fugas de memoria con Valgrind**
  - `valgrind --leak-check=full ./main --benchmark`
  - Especialmente los `new[]` en GapArray y Shannon-Fano

- [ ] **15. Limpiar archivos basura**
  - Eliminar `include/hola.hpp` (sin contenido útil)
  - Vaciar o eliminar `include/linea_base.hpp` y `include/settings.hpp` si no se usan

---

## Orden sugerido de trabajo

```
Día 1 (hoy 23 Mayo):  Items 1, 2, 3 → Caso 2 compilando y con get() funcional
Día 2 (24 Mayo):      Items 4, 5    → Búsqueda en Caso 2, wire en benchmark
Día 3 (25 Mayo):      Items 6, 7    → Estudiar e implementar Shannon-Fano
Día 4 (26 Mayo):      Items 8, 9, 10 → Integrar Shannon-Fano al benchmark
Día 5 (27 Mayo):      Items 11-15   → Infraestructura, README, Valgrind
Día 6 (28 Mayo):      Buffer + entrega
```

---

## Notas técnicas Shannon-Fano

```
Ejemplo del enunciado:
Gap  | Freq | Código
  1  | 1000 | 00
  2  |  500 | 01
  5  |  250 | 10
  7  |  125 | 110
  9  |  125 | 111

Algoritmo top-down:
1. Ordenar gaps por frecuencia: [1000, 500, 250, 125, 125]
2. Total = 2000. Mitad ≈ 1000.
3. Grupo A (suma ≤ 1000): [1000] → prefijo "0"
   Grupo B (resto): [500, 250, 125, 125] → prefijo "1"
4. Repetir recursivamente en cada grupo.

Fórmula teórica de bits por símbolo:
  L(gap_i) = ceil(log2(1/p(gap_i)))
  Espacio total = Σ freq_i * L(gap_i)  bits
```

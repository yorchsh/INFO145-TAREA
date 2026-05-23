# Estado del Proyecto — INFO145 Tarea 2026
**Última actualización:** 2026-05-23  
**Hito 1 deadline:** Jueves 28 de Mayo (5 días)  
**Algoritmo asignado:** Shannon-Fano (sección 5.2)

---

## Resumen de Hitos

| Hito | Descripción | % | Fecha |
|------|-------------|---|-------|
| 1 | Código fuente funcional (Casos 1, 2, 3) | 35% | 28 Mayo |
| 2 | Informe IEEE máx 8 págs | 30% | 11 Junio |
| 3 | Video ~8 minutos | 35% | 18 Junio |

---

## Estado por Caso

### Caso 1: Representación Explícita (Línea Base)
**Estado: COMPLETO ✅**

| Componente | Archivo | Estado |
|-----------|---------|--------|
| Generación vector uniforme | `include/vector_generation.hpp` | ✅ Listo |
| Generación vector normal (Gaussiana) | `include/vector_generation.hpp` | ✅ Listo |
| Búsqueda binaria aleatoria (true random) | `include/binary_search.hpp` | ✅ Listo |
| Búsqueda binaria desde el vector | `include/binary_search.hpp` | ✅ Listo |
| Benchmark wiring en main | `main.cpp` | ✅ Listo |
| Medición de tiempos | `main.cpp` | ✅ Listo |

**Nota:** El vector "uniforme" en realidad es una distribución uniforme pura (no la distribución lineal/incremental que pide el enunciado — A[i] = A[i-1] + rand()%ε). Revisar si eso importa para el informe.

---

### Caso 2: Gap Coding + Sample
**Estado: EN PROGRESO / ROTO ⚠️**

| Componente | Archivo | Estado |
|-----------|---------|--------|
| Estructura GapArray (esqueleto) | `include/gap_coding.hpp` | ⚠️ Errores de compilación |
| Constructor GapArray | `include/gap_coding.hpp` | ⚠️ Incompleto / bugs |
| Método `get(index)` | `include/gap_coding.hpp` | ❌ Incompleto (código roto) |
| Sample (índice de muestreo) | `include/gap_coding.hpp` | ⚠️ Parcialmente implementado |
| Búsqueda binaria sobre Sample | — | ❌ No implementado |
| Wire en benchmark de main | `main.cpp` | ❌ No wired (no aparece en main) |

**Bugs identificados en `gap_coding.hpp`:**
1. `std::T*` es inválido en C++ (línea 24) → debe ser `T*`
2. Falta `;` en `sample.jump_length = sample_jump_length` (línea 61)
3. `block_size` usado sin prefijo `gap.` (línea 77)
4. `get()` incompleto: `value += ;` y `&` suelto (líneas 133-134)
5. Puntero `p` avanzado antes del for loop (lógica incorrecta del sample)
6. `shift_amount` se declara como `std::int64_t` pero se inicializa con `block_size` sin prefijo

---

### Caso 3: Shannon-Fano sobre gaps
**Estado: NO INICIADO ❌**

| Componente | Archivo | Estado |
|-----------|---------|--------|
| Análisis teórico del algoritmo | — | ❌ |
| Implementación Shannon-Fano encoder | `include/shannon_fano.hpp` | ❌ No existe |
| Estructura comprimida a nivel de bits | — | ❌ |
| Búsqueda binaria sobre Sample (heredada de Caso 2) | — | ❌ |
| Decodificación y búsqueda en estructura comprimida | — | ❌ |
| Wire en benchmark de main | `main.cpp` | ❌ |

---

### Infraestructura General
**Estado: PARCIAL ⚠️**

| Componente | Archivo | Estado |
|-----------|---------|--------|
| Makefile | `makefile` | ✅ Existe (solo compila main) |
| README con instrucciones | `README.md` | ❌ Vacío (solo título) |
| Modo benchmark (`--benchmark`) | `main.cpp` | ⚠️ Solo Case 1 |
| Modo archivo (`-i file.csv`) | `main.cpp` | ❌ Solo stub vacío |
| Output CSV con métricas | — | ❌ No implementado |
| Sin fugas de memoria (Valgrind) | — | ❌ No verificado |

---

## Archivos del Repositorio

```
main.cpp                     ← punto de entrada, benchmark Case 1 funcional
makefile                     ← compila con g++ -O3 -std=c++26
include/
  vector_generation.hpp      ← generación vectores uniforme y normal ✅
  binary_search.hpp          ← búsqueda binaria trueRandom y selectRandom ✅
  gap_coding.hpp             ← GapArray con errores, sin get() funcional ⚠️
  linea_base.hpp             ← vacío
  settings.hpp               ← vacío
  csv.hpp                    ← (no revisado en detalle)
  hola.hpp                   ← (archivo basura, eliminar)
entrada.csv                  ← archivo de datos de ejemplo
progreso/                    ← esta carpeta de documentación
```

---

## Lo que queda para Hito 1 (28 Mayo)

Ver archivo `TODO_hito1.md` para la lista detallada y ordenada.

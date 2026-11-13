# Simulador Artemis - Escenario 2: Insercion y Estabilidad en Orbita Terrestre Baja (LEO)

Trabajo Practico Integrador Final - Algoritmos y Estructuras de Datos
Universidad Tecnologica Nacional - Facultad Regional Resistencia
Ingenieria en Sistemas de Informacion

Repositorio: https://github.com/crenerk/Laboratorio-de-lenguaje-C-Segovia-ignacio

## a) Integrantes y comision

| Integrante | Legajo | Comision |
|---|---|---|
| Ignacio Javier Segovia Cendra | 30458 | 1.2 |

Trabajo realizado de forma **individual**, con conocimiento y acuerdo del profesor de la catedra.

## b) Descripcion del escenario y reglas

### Escenario

Tras apagar sus motores de ascenso, la nave Orion es inyectada en una orbita
terrestre baja (LEO) y realiza un Movimiento Circular Uniforme (MCU) a altitud
constante. El programa simula esa orbita y responde las preguntas del escenario
a partir de los datos que ingresa el usuario.

### Datos fijos (constantes del programa)

| Constante | Valor |
|---|---|
| Constante de gravitacion universal G | 6,674 x 10^-11 N·m²/kg² |
| Masa de la Tierra | 5,972 x 10^24 kg |
| Radio terrestre medio | 6.371.000 m |

### Datos que ingresa el usuario (con validacion de tipo y rango)

| Dato | Rango aceptado |
|---|---|
| Altitud sobre la superficie | 100 a 2000 km |
| Masa de la nave | 1 a 1.000.000 kg |
| Aceleracion del propulsor lateral | 0 a 10 m/s² |
| Duracion del pulso | 0 a 600 s |

Valores de referencia del enunciado: altitud 192 km, masa 33.000 kg,
a = 0,50 m/s², dt = 10 s.

### Preguntas que resuelve el programa

**a) Velocidad orbital.** La fuerza gravitatoria actua como fuerza centripeta:

    G·M·m / r² = m·v² / r   ->   v = raiz(G·M / r)

donde r = R_tierra + altitud. El programa calcula `v` y la fuerza de atraccion
`F = G·M·m / r²`.

**b) Periodo orbital.** `T = 2·pi·r / v`, informado en segundos y en minutos.

**c) Aceleracion centripeta.** `a_c = v² / r`.

**d) Pulso lateral.** Un propulsor auxiliar genera una aceleracion `a`
constante y perpendicular a la velocidad orbital durante `dt` segundos:

- Cambio de velocidad lateral: `dv = a · dt`
- Desviacion lateral: `d = 1/2 · a · dt²`
- Velocidad final: `v_final = raiz(v² + dv²)` (las velocidades son
  perpendiculares, por lo que se componen con Pitagoras).

La trayectoria resultante deja de ser una circunferencia perfecta: al aumentar
la rapidez, la orbita pasa a ser ligeramente eliptica.

### Resultados de referencia (altitud 192 km, masa 33.000 kg)

| Magnitud | Resultado |
|---|---|
| Velocidad orbital | 7792,95 m/s |
| Periodo | 5291,52 s (88,19 min) |
| Aceleracion centripeta | 9,2534 m/s² |
| Fuerza gravitatoria | 305.362 N |
| Pulso lateral (0,50 m/s², 10 s) | dv = 5,00 m/s, desvio = 25,00 m |

### Reglas de uso

1. Primero se deben cargar los datos (opcion 1).
2. Luego se calculan los parametros orbitales (opcion 2).
3. Recien despues se puede simular el pulso lateral (opcion 3) y ver el
   reporte final (opcion 4).
4. Si se cargan datos nuevos, los calculos anteriores se reinician.

## c) Funcionamiento

Al ejecutar el programa se muestra un menu por consola:

    1. Ingresar datos de la mision
    2. Calcular parametros orbitales
    3. Simular pulso lateral
    4. Ver reporte final
    5. Salir

El menu se repite hasta elegir la opcion 5. Todas las entradas pasan por las
funciones de `validaciones.c`, que leen la linea completa con `fgets`, la
convierten con `strtol`/`strtod` y rechazan letras, texto mezclado con numeros,
valores fuera de rango, entradas vacias o demasiado largas. Ante un error se
muestra un mensaje y se vuelve a pedir el dato, sin cerrar el programa.

### Arquitectura de archivos

    main.c  ------>  simulador.c  ------>  simulador.h
       |
       +---------->  validaciones.c ---->  validaciones.h

| Archivo | Responsabilidad |
|---|---|
| `main.c` | Solo `main()`: menu principal y flujo general. |
| `simulador.h` | Constantes (`#define`), `struct Cuerpo` (typedef) y prototipos. |
| `simulador.c` | Calculos fisicos: velocidad, periodo, aceleracion, fuerza, pulso lateral y reporte. |
| `validaciones.h` / `validaciones.c` | Ingreso seguro de enteros y reales (`leer_entero`, `leer_real`). |
| `Makefile` | Compilacion automatica de los modulos. |

### Estructuras de datos y punteros

- `Cuerpo` (struct): agrupa altitud, masa, radio orbital, velocidad, periodo,
  aceleracion y fuerza de la nave.
- Las funciones reciben la struct **por puntero**. Las que solo leen usan
  `const Cuerpo *`; solo `inicializar_orbita` la modifica.
- `leer_entero` / `leer_real` y `calcular_pulso_lateral` usan punteros
  (`char *fin`, y parametros de salida `double *dv`, `*desvio`, `*v_final`)
  para devolver mas de un valor.

## d) Compilacion y ejecucion

Requisitos: compilador `gcc` y `make`.

**Windows (MSYS2 / MinGW-w64):**

    mingw32-make
    .\artemis.exe

**Linux / macOS:**

    make
    ./artemis

Para limpiar los archivos compilados: `mingw32-make clean` (Windows) o
`make clean` (Linux; en ese caso reemplazar `del` por `rm -f` en el Makefile).

Compilacion manual, sin Makefile:

    gcc -Wall main.c simulador.c validaciones.c -o artemis -lm

## e) Registro de uso de Inteligencia Artificial

Herramienta utilizada: **Claude (Anthropic)**.

| Tarea | Consulta realizada | Como se valido o adapto |
|---|---|---|
| Entorno | Instalacion de MSYS2/MinGW, PATH, VS Code y Git en Windows. | Se verifico con `gcc --version`, `mingw32-make --version` y `git --version`. Se resolvieron errores de tipeo (`x86_6` en vez de `x86_64`) y de PATH. |
| Git | Errores de `git push`/`pull` por historias distintas y archivos `.o` subidos por error. | Se uso `git pull --allow-unrelated-histories`, `.gitignore` y `git rm --cached`. |
| Validaciones | Explicacion de `fgets`, `strtol`, `strtod`, `*fin` y por que `scanf` puede generar bucles infinitos. El codigo base de `validaciones.c/.h` fue propuesto por el alumno. | Se compilo y se probo con letras, `12abc`, numeros enormes, fuera de rango y Enter vacio. |
| Diseno de `simulador.h` | Que va en un `.h` (constantes, struct, prototipos) y diferencia entre `Cuerpo *` y `const Cuerpo *`. | El alumno escribio el archivo y se corrigieron los prototipos. `inicializar_orbita` en `simulador.c` fue escrita por el alumno. |
| Logica fisica | Formulas del escenario 2. El codigo del resto de `simulador.c` (velocidad, periodo, aceleracion, fuerza, pulso lateral y reporte) fue propuesto por el alumno y revisado por claude. | Se comparo con calculos manuales y con los valores de referencia del enunciado (7792,95 m/s; 5291,52 s; 9,2534 m/s²; 305.362 N; dv = 5 m/s; desvio = 25 m). |
| Menu y Makefile | El `main.c` con menu y el `Makefile` fueron propuestos por el alumno y revisado con claude. | Se compilo con `mingw32-make`, se probaron todas las opciones y las entradas invalidas, y se corrigieron problemas de archivos sin guardar. |

El alumno revisa y puede explicar cada modulo del programa. Todo el codigo se
probo y se verifico antes de integrarlo al repositorio.

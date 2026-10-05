# Guia de Instalacion, Compilacion y Pruebas Locales
## Sistema de Gestion de Flota de Vehiculos Electricos

Proyecto academico para la asignatura de **Estructura de Datos** (Tipo D)  
**Universidad Continental** - Facultad de Ingenieria de Sistemas e Informatica  
**Docente:** Dr. Ing. Julio Arboleda H.  
**Autor:** Paul Lachi  

---

## Indice de Contenidos

1. [Descripcion General](#1-descripcion-general)
2. [Estructura del Proyecto](#2-estructura-del-proyecto)
3. [Requisitos del Sistema](#3-requisitos-del-sistema)
4. [Inicio Rapido (Quickstart)](#4-inicio-rapido-quickstart)
5. [Instrucciones de Compilacion por Entorno](#5-instrucciones-de-compilacion-por-entorno)
   - [Opcion A: Consola / Terminal (g++ / MinGW)](#opcion-a-consola--terminal-g--mingw)
   - [Opcion B: Dev-C++](#opcion-b-dev-c)
   - [Opcion C: Code::Blocks](#opcion-c-codeblocks)
   - [Opcion D: Visual Studio Code](#opcion-d-visual-studio-code)
   - [Opcion E: Compilador Online (OnlineGDB - Sin Instalacion)](#opcion-e-compilador-online-onlinegdb---sin-instalacion)
6. [Datos Precargados en el Sistema](#6-datos-precargados-en-el-sistema)
7. [Guia de Pruebas Paso a Paso](#7-guia-de-pruebas-paso-a-paso)
   - [Prueba 1: Registro con Validacion de Errores](#prueba-1-registro-con-validacion-de-errores)
   - [Prueba 2: Busqueda Secuencial por ID](#prueba-2-busqueda-secuencial-por-id)
   - [Prueba 3: Actualizacion de Viajes Realizados](#prueba-3-actualizacion-de-viajes-realizados)
   - [Prueba 4: Ordenamiento Descendente por Autonomia (Burbuja)](#prueba-4-ordenamiento-descendente-por-autonomia-burbuja)
   - [Prueba 5: Calculo Detallado y Promedio de la Flota](#prueba-5-calculo-detallado-y-promedio-de-la-flota)
   - [Prueba 6: Reportes Filtrados por Umbral Dinamico](#prueba-6-reportes-filtrados-por-umbral-dinamico)
   - [Prueba 7: Cambio de Estado Operativo](#prueba-7-cambio-de-estado-operativo)
8. [Formulas y Reglas de Negocio](#8-formulas-y-reglas-de-negocio)
9. [Documentacion e Informes Disponibles](#9-documentacion-e-informes-disponibles)

---

## 1. Descripcion General

Este software es un sistema de consola modular desarrollado en **C++** para administrar la flota de una empresa de alquiler de vehiculos electricos. 

Resuelve de manera practica la necesidad de controlar unidades, computar su rendimiento energetico real y generar reportes operativos aplicando estructuras de datos fundamentales:
* **Registros (`struct`):** Agrupa atributos de tipos mixtos (enteros, cadenas, flotantes) bajo la entidad `Vehiculo`.
* **Arreglos Unidimensionales Estaticos:** Almacena la coleccion de vehiculos en memoria contigua con tamano logico controlado por contador.
* **Busqueda Secuencial:** Localiza elementos por identificador unico en complejidad lineal O(n).
* **Algoritmo de la Burbuja (Bubble Sort):** Ordena la flota de mayor a menor utilizando una magnitud calculada (autonomia en km).
* **Control de Errores de Entrada:** Evita fallos y bucles infinitos en consola cuando se introducen caracteres alfabeticos en campos numericos.

---

## 2. Estructura del Proyecto

```text
flota_vehiculo/
|-- flota_vehiculos.cpp                   # Codigo fuente principal en C++
|-- README.md                             # Guia completa para ejecucion y pruebas
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf  # Informe academico formal listo para entrega (13 pags)
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.docx # Informe en formato Word editable con portada
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.md   # Version completa del informe en Markdown
|-- .gitignore                            # Exclusion de ejecutables y archivos temporales
`-- evidencias/                           # Capturas de pantalla de terminal de cada prueba
    |-- prueba1_registro_validaciones.png
    |-- prueba2_busqueda_id.png
    |-- prueba3_ordenamiento_autonomia.png
    |-- prueba4_reportes_umbral.png
    `-- prueba5_actualizacion_estado.png
```

---

## 3. Requisitos del Sistema

Para compilar y ejecutar el proyecto en tu computadora local necesitas:
* **Sistema Operativo:** Windows 10/11, Linux (Ubuntu, Debian, Fedora, etc.) o macOS.
* **Compilador C++:** Soporte para estandar C++11 o superior (GCC / MinGW 5.0+, Clang 3.5+ o MSVC 2015+).
* **Memoria y Espacio:** Menos de 50 MB de espacio en disco; consumo en memoria RAM despreciable (< 5 MB).

---

## 4. Inicio Rapido (Quickstart)

Si ya tienes un compilador `g++` instalado en tu sistema, ejecuta los siguientes comandos en tu terminal:

```bash
# 1. Clonar el repositorio
git clone https://github.com/PaulLachi12/flota_vehiculo.git

# 2. Entrar a la carpeta
cd flota_vehiculo

# 3. Compilar el programa
g++ -std=c++11 flota_vehiculos.cpp -o flota_vehiculos.exe

# 4. Ejecutar el sistema
# En Windows:
.\flota_vehiculos.exe

# En Linux / macOS:
./flota_vehiculos.exe
```

---

## 5. Instrucciones de Compilacion por Entorno

Elige el metodo que mejor se adapte a las herramientas instaladas en tu computadora:

### Opcion A: Consola / Terminal (g++ / MinGW)

1. Abre **PowerShell**, **CMD** o tu terminal de Linux.
2. Navega hasta el directorio del proyecto:
   ```bash
   cd ruta/hacia/flota_vehiculo
   ```
3. Ejecuta la orden de compilacion:
   ```bash
   g++ -O2 flota_vehiculos.cpp -o flota_vehiculos.exe
   ```
4. Lanza el ejecutable:
   ```bash
   .\flota_vehiculos.exe
   ```

### Opcion B: Dev-C++

1. Abre el programa **Dev-C++**.
2. En la barra superior, ve a `Archivo` > `Abrir` > `Proyecto o Archivo`.
3. Selecciona el archivo `flota_vehiculos.cpp`.
4. Presiona la tecla **F11** (o selecciona el menu `Ejecutar` > `Compilar y Ejecutar`).
5. La ventana de la consola aparecera en pantalla mostrando el menu interactivo.

### Opcion C: Code::Blocks

1. Inicia **Code::Blocks**.
2. Dirigete a `File` > `Open` y selecciona `flota_vehiculos.cpp`.
3. Presiona la tecla **F9** (o presiona el boton con forma de engranaje y triangulo verde `Build and Run`).
4. La consola se abrira de inmediato.

### Opcion D: Visual Studio Code

1. Abre la carpeta del proyecto en VS Code (`File` > `Open Folder`).
2. Asegurate de tener instalada la extension oficial de **C/C++** (de Microsoft).
3. Abre el archivo `flota_vehiculos.cpp`.
4. Presiona el boton superior derecho de **Play** (`Run C/C++ File`) o presiona `Ctrl + Shift + B` para compilar y luego ejecuta el binario en la terminal integrada.

### Opcion E: Compilador Online (OnlineGDB - Sin Instalacion)

Si no tienes ningun compilador instalado y quieres probarlo en 30 segundos:
1. Abre tu navegador web e ingresa a: **https://www.onlinegdb.com/online_c++_compiler**
2. Abre en tu editor el archivo `flota_vehiculos.cpp`, selecciona todo el texto (`Ctrl + A`) y copialo (`Ctrl + C`).
3. En la pagina web de OnlineGDB, borra todo el codigo que viene por defecto y pega tu codigo (`Ctrl + V`).
4. En la esquina superior derecha, asegurate de que en `Language` este seleccionado **C++**.
5. Presiona el boton verde **Run** (o la tecla `F9`).
6. Podras interactuar con el sistema escribiendo directamente en la consola web en la parte inferior.

---

## 6. Datos Precargados en el Sistema

Para que cualquier persona pueda probar todas las opciones del menu de inmediato sin tener que registrar manualmente unidades, el programa inicia con **4 vehiculos de demostracion**:

| ID | Modelo | Bateria (kWh) | Consumo (kWh/100km) | Viajes | Estado | Autonomia Estimada |
| :-: | :--- | :-: | :-: | :-: | :--- | :-: |
| **101** | Tesla Model 3 | 60.0 | 15.0 | 25 | Disponible | 400.00 km |
| **102** | Nissan Leaf | 40.0 | 16.5 | 12 | Disponible | 242.42 km |
| **103** | BYD Han EV | 85.4 | 18.2 | 40 | En mantenimiento | 469.23 km |
| **104** | Hyundai Ioniq 5 | 72.6 | 17.0 | 30 | Disponible | 427.06 km |

---

## 7. Guia de Pruebas Paso a Paso

Sigue esta secuencia para verificar cada una de las funcionalidades y comprobar la robustez del sistema frente a errores:

### Prueba 1: Registro con Validacion de Errores
* **Objetivo:** Verificar que el sistema no acepte IDs repetidos, capture nombres con espacios y rechace letras o negativos en valores numericos.
* **Pasos:**
  1. En el menu principal, digita `1` y presiona Enter.
  2. En `ID del vehiculo`, escribe `101` -> El sistema avisara: `[Error] El ID 101 ya se encuentra registrado. Ingrese otro ID.`
  3. En `ID del vehiculo`, escribe letras `xyz` -> El sistema avisara: `[Error] Entrada invalida. Debe ingresar un numero entero.` sin colgarse.
  4. En `ID del vehiculo`, escribe `105` (valido).
  5. En `Modelo del vehiculo`, escribe `Volvo EX30 Recharge`.
  6. En `Capacidad de bateria en kWh`, escribe `-20` -> El sistema avisara que debe ser mayor a cero (> 0).
  7. Escribe `69.0`.
  8. En `Consumo promedio en kWh/100km`, escribe `17.5`.
  9. En `Numero de viajes realizados`, escribe `8`.
  10. En `Estado`, escribe `1` (Disponible).
* **Resultado Esperado:** Mensaje de confirmacion con calculo inmediato de autonomia: `394.29 km`.

### Prueba 2: Busqueda Secuencial por ID
* **Objetivo:** Validar la recuperacion de fichas tecnicas y el control de unidades inexistentes.
* **Pasos:**
  1. En el menu principal, digita `2`.
  2. Ingresa `103` -> Muestra todos los datos del `BYD Han EV`, indicando su estado `En mantenimiento` y su autonomia de `469.23 km`.
  3. Digita `2` nuevamente e ingresa `999` -> El sistema informa claramente: `[!] No se encontro ningun vehiculo con el ID 999.`.

### Prueba 3: Actualizacion de Viajes Realizados
* **Objetivo:** Comprobar la modificacion persistente en memoria del contador de viajes.
* **Pasos:**
  1. Digita la opcion `3`.
  2. Ingresa el ID `102` (Nissan Leaf).
  3. El sistema muestra que tiene `12` viajes actuales.
  4. Ingresa la nueva cantidad: `18`.
* **Resultado Esperado:** Mensaje de actualizacion exitosa. Si luego vas a la opcion `5` (Mostrar todos), podras constatar que el Nissan Leaf ahora figura con 18 viajes.

### Prueba 4: Ordenamiento Descendente por Autonomia (Burbuja)
* **Objetivo:** Comprobar que el algoritmo de la burbuja ordena de mayor a menor autonomia en tiempo de ejecucion.
* **Pasos:**
  1. Digita la opcion `4`.
* **Resultado Esperado:** El sistema ordena y despliega la tabla. El orden resultante debe ser:
  1. `BYD Han EV` (469.23 km)
  2. `Hyundai Ioniq 5` (427.06 km)
  3. `Tesla Model 3` (400.00 km)
  4. `Volvo EX30` (394.29 km - si se registro en la prueba 1)
  5. `Nissan Leaf` (242.42 km)

### Prueba 5: Calculo Detallado y Promedio de la Flota
* **Objetivo:** Visualizar el desglose matematico y el promedio general de autonomia de toda la flota mediante acumuladores.
* **Pasos:**
  1. Digita la opcion `6`.
  2. Ingresa el ID `101` (Tesla Model 3).
* **Resultado Esperado:**
  * Desglose: Capacidad (60.0 kWh) / Consumo (15.0 kWh/100km) * 100 = 400.00 km.
  * Promedio de toda la flota calculado automaticamente.

### Prueba 6: Reportes Filtrados por Umbral Dinamico
* **Objetivo:** Evaluar las consultas condicionales con valores ingresados por el usuario.
* **Pasos:**
  1. Digita la opcion `7`.
  2. Selecciona la sub-opcion `1` (Autonomia baja) e introduce el umbral `350` km -> Se mostrara solo el `Nissan Leaf` (242.42 km).
  3. Vuelve a seleccionar la opcion `7`.
  4. Selecciona la sub-opcion `2` (Alta demanda) e introduce el umbral `25` viajes -> Se listaran las unidades con mas de 25 viajes (`BYD Han EV` con 40 y `Hyundai Ioniq 5` con 30).

### Prueba 7: Cambio de Estado Operativo
* **Objetivo:** Alternar entre unidades disponibles para renta y unidades en taller.
* **Pasos:**
  1. Digita la opcion `8`.
  2. Ingresa ID `103` (BYD Han EV).
  3. Se observa que su estado actual es `[2] En mantenimiento`.
  4. Ingresa `1` para habilitarlo como `Disponible`.
* **Resultado Esperado:** Mensaje de confirmacion. Al consultar la tabla general (opcion 5), el estado del vehiculo habra cambiado a `Disponible`.

---

## 8. Formulas y Reglas de Negocio

* **Calculo de Autonomia Estimada:**
  ```text
  Autonomia (km) = ( Capacidad de Batería en kWh / Consumo Promedio en kWh por cada 100 km ) * 100
  ```
* **Prevencion de Division por Cero:** Si el consumo promedio de un vehiculo fuese menor o igual a cero, la funcion retorna `0.0 km` automaticamente mediante una clausula de guarda antes de ejecutar la division.
* **Capacidad Fisica del Arreglo:** Definida por la constante `MAX_VEHICULOS = 100`. Si se intenta registrar el elemento 101, el sistema bloquea la accion protegiendo la memoria.
* **Codificacion de Estados:**
  * `1` = Unidad disponible para alquiler.
  * `2` = Unidad en taller por revision o mantenimiento preventivo.

---

## 9. Documentacion e Informes Disponibles

En la raiz de este repositorio se encuentran los documentos formales requeridos para la calificacion del examen parcial:

* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf](INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf):** Documento oficial en PDF (13 paginas) con formato academico de la Universidad Continental, justificaciones teoricas, analisis de complejidad algoritmica O(n) y capturas de pantalla de terminal de cada prueba.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.docx](INFORME_PARCIAL_ESTRUCTURA_DATOS.docx):** Archivo editable en Microsoft Word por si se requiere personalizar datos del estudiante.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.md](INFORME_PARCIAL_ESTRUCTURA_DATOS.md):** Version en texto Markdown con todas las tablas y explicaciones teoricas.

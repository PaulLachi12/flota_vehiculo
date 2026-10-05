# Guia de Instalacion, Ejecucion y Pruebas Locales
## Sistema de Gestion de Flota de Vehiculos Electricos

Proyecto academico para la asignatura de **Estructura de Datos** (Tipo D)  
**Universidad Continental** - Facultad de Ingenieria de Sistemas e Informatica  
**Docente:** Dr. Ing. Julio Arboleda H.  
**Lenguaje Principal:** Python 3 (Incluye version alternativa en C++)  
**Autor:** Paul Lachi  

---

## Indice de Contenidos

1. [Descripcion General](#1-descripcion-general)
2. [Estructura del Repositorio](#2-estructura-del-repositorio)
3. [Requisitos del Sistema](#3-requisitos-del-sistema)
4. [Inicio Rapido (Quickstart en 10 Segundos)](#4-inicio-rapido-quickstart-en-10-segundos)
5. [Instrucciones de Ejecucion en Python](#5-instrucciones-de-ejecucion-en-python)
   - [Opcion A: Ejecutar desde Terminal (PowerShell / CMD / Bash)](#opcion-a-ejecutar-desde-terminal-powershell--cmd--bash)
   - [Opcion B: Ejecutar en Visual Studio Code](#opcion-b-ejecutar-en-visual-studio-code)
   - [Opcion C: Ejecutar en PyCharm](#opcion-c-ejecutar-en-pycharm)
   - [Opcion D: Ejecutar Online sin Instalacion (Replit / Programiz)](#opcion-d-ejecutar-online-sin-instalacion-replit--programiz)
6. [Datos Precargados para Pruebas Inmediatas](#6-datos-precargados-para-pruebas-inmediatas)
7. [Guia de Pruebas Paso a Paso (Casos 1 al 7)](#7-guia-de-pruebas-paso-a-paso-casos-1-al-7)
8. [Formulas y Reglas de Negocio](#8-formulas-y-reglas-de-negocio)
9. [Documentos e Informes Academicos](#9-documentos-e-informes-academicos)

---

## 1. Descripcion General

Este software es un sistema de consola interactivo y modular desarrollado en **Python 3** para la gestion integral, control operativo y analisis de rendimiento energetico de una flota de vehiculos de alquiler 100% electricos.

El programa implementa con fidelidad los requerimientos de la asignatura:
* **Registros (`struct`):** Modelado a traves de una clase con atributos puros (`class Vehiculo`), encapsulando identificador, modelo, bateria, consumo, viajes y estado.
* **Arreglos Unidimensionales Estaticos:** Implementado como lista de tamano fijo prefijado (`flota = [None] * MAX_VEHICULOS`) gobernada por un contador de tamano logico (`total_vehiculos`).
* **Busqueda Secuencial (Lineal):** Localizacion de registros por ID unico en complejidad O(n).
* **Metodo de la Burbuja (Bubble Sort):** Algoritmo de intercambio manual de mayor a menor segun la autonomia estimada (km).
* **Manejo de Excepciones:** Bloques `try-except ValueError` que neutralizan el ingreso accidental de caracteres alfabeticos en campos numericos, impidiendo que el programa se cierre.

---

## 2. Estructura del Repositorio

```text
flota_vehiculo/
|-- flota_vehiculos.py                    # Codigo fuente principal en Python 3
|-- flota_vehiculos.cpp                   # Codigo fuente alternativo en C++
|-- README.md                             # Guia completa para ejecucion y pruebas
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf  # Informe tecnico formal en PDF (13 pags)
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.docx # Informe en formato Word editable con portada
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.md   # Version completa del informe en Markdown
|-- .gitignore                            # Exclusion de ejecutables y temporales
`-- evidencias/                           # Capturas de consola de cada prueba
    |-- prueba1_registro_validaciones.png
    |-- prueba2_busqueda_id.png
    |-- prueba3_ordenamiento_autonomia.png
    |-- prueba4_reportes_umbral.png
    `-- prueba5_actualizacion_estado.png
```

---

## 3. Requisitos del Sistema

* **Python 3.7 o superior** instalado (Python 3.8, 3.9, 3.10, 3.11, 3.12 o 3.13).
* No requiere instalar ninguna libreria externa con `pip` (utiliza exclusivamente librerias nativas de Python).
* Compatible con Windows 10/11, Linux y macOS.

---

## 4. Inicio Rapido (Quickstart en 10 Segundos)

Para ejecutar el programa inmediatamente, abre tu terminal y corre:

```bash
# 1. Clonar el repositorio
git clone https://github.com/PaulLachi12/flota_vehiculo.git

# 2. Entrar a la carpeta
cd flota_vehiculo

# 3. Ejecutar directamente con Python
python flota_vehiculos.py
```

---

## 5. Instrucciones de Ejecucion en Python

### Opcion A: Ejecutar desde Terminal (PowerShell / CMD / Bash)

1. Abre tu terminal favorita en la carpeta del proyecto:
   ```powershell
   cd c:\Users\Leo\alvado_parcial
   ```
2. Ejecuta el archivo:
   ```powershell
   python flota_vehiculos.py
   ```
   *(Si tienes Linux/Mac o varias versiones de Python, usa `python3 flota_vehiculos.py`).*

### Opcion B: Ejecutar en Visual Studio Code

1. Abre la carpeta del proyecto en VS Code.
2. Abre el archivo `flota_vehiculos.py`.
3. Haz clic en el boton superior derecho de **Play** (`Run Python File in Terminal`) o presiona `F5`.
4. El menu aparecera directamente en la terminal integrada inferior.

### Opcion C: Ejecutar en PyCharm

1. Abre la carpeta en PyCharm.
2. Haz clic derecho sobre `flota_vehiculos.py` y selecciona **Run 'flota_vehiculos'**.

### Opcion D: Ejecutar Online sin Instalacion (Replit / Programiz)

Si deseas probarlo desde un navegador web o celular:
1. Ingresa a **https://www.programiz.com/python-programming/online-compiler/**
2. Copia todo el codigo de `flota_vehiculos.py` y pegalo en el editor.
3. Presiona el boton **Run**.

---

## 6. Datos Precargados para Pruebas Inmediatas

Al iniciar, el sistema contiene **4 vehiculos de demostracion** para probar las funciones de inmediato:

| ID | Modelo | Bateria (kWh) | Consumo (kWh/100km) | Viajes | Estado | Autonomia Estimada |
| :-: | :--- | :-: | :-: | :-: | :--- | :-: |
| **101** | Tesla Model 3 | 60.0 | 15.0 | 25 | Disponible | 400.00 km |
| **102** | Nissan Leaf | 40.0 | 16.5 | 12 | Disponible | 242.42 km |
| **103** | BYD Han EV | 85.4 | 18.2 | 40 | En mantenimiento | 469.23 km |
| **104** | Hyundai Ioniq 5 | 72.6 | 17.0 | 30 | Disponible | 427.06 km |

---

## 7. Guia de Pruebas Paso a Paso (Casos 1 al 7)

### Caso 1: Registro con Validacion de Errores
* En el menu principal, selecciona la opcion `1`.
* En `ID del vehiculo`, escribe `101` -> El sistema avisara que ya esta registrado.
* En `ID del vehiculo`, escribe `abc` -> El sistema avisara que la entrada es invalida sin cerrarse.
* En `ID del vehiculo`, escribe `105`.
* En `Modelo`, escribe `Volvo EX30 Recharge`.
* En `Capacidad de bateria`, escribe `-15` -> Rechazado por ser negativo.
* Ingresa `69.0`, consumo `17.5`, viajes `8`, estado `1`.
* Resultado: Unidad registrada con autonomia de `394.29 km`.

### Caso 2: Busqueda Secuencial por ID
* Selecciona la opcion `2`.
* Ingresa `103` -> Despliega la ficha tecnica del `BYD Han EV`, estado `En mantenimiento` y autonomia de `469.23 km`.
* Ingresa `999` -> Notifica `[!] No se encontro ningun vehiculo con el ID 999.`.

### Caso 3: Actualizacion de Viajes Realizados
* Selecciona la opcion `3`.
* Ingresa el ID `102` (Nissan Leaf).
* Muestra 12 viajes actuales; ingresa `18`.
* Resultado: Viajes actualizados en memoria a 18.

### Caso 4: Ordenamiento Descendente por Autonomia (Burbuja)
* Selecciona la opcion `4`.
* La lista se ordena y despliega de mayor a menor rendimiento:
  1. `BYD Han EV` (469.23 km)
  2. `Hyundai Ioniq 5` (427.06 km)
  3. `Tesla Model 3` (400.00 km)
  4. `Volvo EX30` (394.29 km)
  5. `Nissan Leaf` (242.42 km)

### Caso 5: Calculo Detallado y Promedio General de la Flota
* Selecciona la opcion `6`.
* Ingresa ID `101` (Tesla Model 3).
* Despliega la formula con sus valores: `(60.0 / 15.0) * 100 = 400.00 km`.
* Calcula y muestra el promedio de autonomia de toda la flota mediante acumuladores.

### Caso 6: Reportes Filtrados por Umbral
* Selecciona la opcion `7`.
* Sub-opcion `1` (Autonomia baja): ingresa umbral `350` km -> Filtra el `Nissan Leaf` (242.42 km).
* Sub-opcion `2` (Alta demanda): ingresa umbral `25` viajes -> Filtra `BYD Han EV` (40 viajes) y `Hyundai Ioniq 5` (30 viajes).

### Caso 7: Cambio de Estado Operativo
* Selecciona la opcion `8`.
* Ingresa ID `103` (BYD Han EV).
* Se encuentra en `[2] En mantenimiento`; ingresa `1` para cambiarlo a `Disponible`.
* Si consultas la opcion `5`, veras que ahora figura como `Disponible`.

---

## 8. Formulas y Reglas de Negocio

* **Calculo de Autonomia Estimada:**
  ```text
  Autonomia (km) = ( Capacidad de Bateria en kWh / Consumo Promedio en kWh por cada 100 km ) * 100
  ```
* **Prevencion de Division por Cero:** Si el consumo promedio fuese menor o igual a cero, la funcion retorna `0.0` mediante una clausula de guarda antes de dividir.
* **Capacidad Estatica del Arreglo:** `MAX_VEHICULOS = 100`. Si se intenta registrar el elemento 101, el sistema bloquea la insercion.
* **Codificacion de Estado:** `1 = Disponible`, `2 = En mantenimiento`.

---

## 9. Documentos e Informes Academicos

* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf](INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf):** Documento oficial formal en PDF (13 paginas) adaptado a Python 3 con portada, justificacion teorica, analisis de complejidad O(n) y capturas graficas de terminal.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.docx](INFORME_PARCIAL_ESTRUCTURA_DATOS.docx):** Archivo editable en Microsoft Word para personalizar datos del estudiante.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.md](INFORME_PARCIAL_ESTRUCTURA_DATOS.md):** Version completa en Markdown para lectura rapida.

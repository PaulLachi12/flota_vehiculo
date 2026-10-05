# Guia de Instalacion, Ejecucion y Pruebas en Windows (Laptop HP)
## Sistema de Gestion de Flota de Vehiculos Electricos

Proyecto academico para la asignatura de **Estructura de Datos** (Tipo D)  
**Universidad Continental** - Facultad de Ingenieria de Sistemas e Informatica  
**Docente:** Dr. Ing. Julio Arboleda H.  
**Plataforma de Ejecucion:** Windows 10 / Windows 11 (Laptop HP)  
**Lenguaje Principal:** Python 3  
**Autor:** Paul Lachi  

---

## Indice de Contenidos

1. [Descripcion General](#1-descripcion-general)
2. [Estructura del Proyecto en tu Laptop HP](#2-estructura-del-proyecto-en-tu-laptop-hp)
3. [Requisitos en Windows](#3-requisitos-en-windows)
4. [Como Ejecutar el Programa en Windows (3 Formas Sencillas)](#4-como-ejecutar-el-programa-en-windows-3-formas-sencillas)
   - [Metodo 1: Ejecutar con un Doble Clic (ejecutar.bat)](#metodo-1-ejecutar-con-un-doble-clic-ejecutarbat)
   - [Metodo 2: Ejecutar desde PowerShell o CMD (Simbolo del Sistema)](#metodo-2-ejecutar-desde-powershell-o-cmd-simbolo-del-sistema)
   - [Metodo 3: Ejecutar desde Visual Studio Code](#metodo-3-ejecutar-desde-visual-studio-code)
5. [Datos Precargados para Pruebas Inmediatas](#5-datos-precargados-para-pruebas-inmediatas)
6. [Guia de Pruebas Paso a Paso (Casos 1 al 7)](#6-guia-de-pruebas-paso-a-paso-casos-1-al-7)
7. [Formulas y Reglas de Negocio](#7-formulas-y-reglas-de-negocio)
8. [Archivos e Informes Disponibles](#8-archivos-e-informes-disponibles)

---

## 1. Descripcion General

Este software es un sistema de consola interactivo y modular desarrollado en **Python 3** para la gestion integral, control operativo y analisis de rendimiento energetico de una flota de vehiculos de alquiler 100% electricos.

El programa cumple con todos los requisitos del curso de Estructura de Datos:
* **Registros (struct):** Modelado mediante la clase `Vehiculo` con atributos puros (id, modelo, bateria, consumo, viajes y estado).
* **Arreglos Unidimensionales Estaticos:** Implementado como lista de capacidad fija prefijada (`flota = [None] * MAX_VEHICULOS`) gobernada por un contador entero (`total_vehiculos`).
* **Busqueda Secuencial (Lineal):** Localizacion de registros por ID unico en complejidad O(n).
* **Metodo de la Burbuja (Bubble Sort):** Algoritmo de ordenamiento manual descendente segun la autonomia estimada en km.
* **Control de Errores con try-except:** Neutraliza el ingreso accidental de letras en campos numericos, evitando que la ventana de la consola se cierre o se cuelgue.

---

## 2. Estructura del Proyecto en tu Laptop HP

```text
C:\Users\Leo\alvado_parcial\
|-- ejecutar.bat                          # Lanzador por doble clic para Windows
|-- flota_vehiculos.py                    # Codigo fuente principal en Python 3
|-- flota_vehiculos.cpp                   # Codigo fuente alternativo en C++
|-- README.md                             # Esta guia de uso para Windows en laptop HP
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf  # Informe final en PDF (13 paginas)
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.docx # Informe en formato Word editable con portada
|-- INFORME_PARCIAL_ESTRUCTURA_DATOS.md   # Version del informe en texto Markdown
|-- .gitignore                            # Exclusion de archivos temporales
`-- evidencias/                           # Capturas de consola de cada prueba
    |-- prueba1_registro_validaciones.png
    |-- prueba2_busqueda_id.png
    |-- prueba3_ordenamiento_autonomia.png
    |-- prueba4_reportes_umbral.png
    `-- prueba5_actualizacion_estado.png
```

---

## 3. Requisitos en Windows

* **Laptop HP con Windows 10 o Windows 11.**
* **Python 3 instalado:** Puedes comprobarlo abriendo PowerShell o CMD y escribiendo `python --version`.
* No requiere instalar ninguna libreria externa con `pip` (funciona con las librerias nativas de Python).

---

## 4. Como Ejecutar el Programa en Windows (3 Formas Sencillas)

### Metodo 1: Ejecutar con un Doble Clic (ejecutar.bat)

Es la forma mas rapida y comoda en una laptop con Windows:
1. Abre el **Explorador de Archivos de Windows** y entra a la carpeta del proyecto:
   `C:\Users\Leo\alvado_parcial`
2. Haz **doble clic** sobre el archivo llamado **`ejecutar.bat`**.
3. Se abrira de inmediato una ventana negra de consola con el sistema listo para usar.
4. Cuando termines y salgas con la opcion 9, la ventana te permitira presionar cualquier tecla para cerrarse comodamente.

---

### Metodo 2: Ejecutar desde PowerShell o CMD (Simbolo del Sistema)

1. En tu teclado de la laptop HP, presiona la tecla **Windows + R**.
2. Escribe `powershell` (o `cmd`) y presiona **Enter**.
3. Navega a la carpeta del proyecto escribiendo:
   ```powershell
   cd c:\Users\Leo\alvado_parcial
   ```
4. Ejecuta el programa escribiendo:
   ```powershell
   python flota_vehiculos.py
   ```
5. El menu principal aparecera en pantalla.

---

### Metodo 3: Ejecutar desde Visual Studio Code

1. Abre Visual Studio Code en tu laptop HP.
2. Ve a `Archivo` > `Abrir carpeta...` y selecciona `C:\Users\Leo\alvado_parcial`.
3. Haz clic sobre el archivo `flota_vehiculos.py` en el panel izquierdo.
4. Presiona el boton de **Play** ubicado en la esquina superior derecha de la ventana (o presiona `F5`).
5. El programa se ejecutara en la terminal integrada en la parte inferior de VS Code.

---

## 5. Datos Precargados para Pruebas Inmediatas

Al iniciar, el sistema contiene **4 vehiculos de demostracion** para que puedas probar las opciones del menu sin tener que registrar datos a mano:

| ID | Modelo | Bateria (kWh) | Consumo (kWh/100km) | Viajes | Estado | Autonomia Estimada |
| :-: | :--- | :-: | :-: | :-: | :--- | :-: |
| **101** | Tesla Model 3 | 60.0 | 15.0 | 25 | Disponible | 400.00 km |
| **102** | Nissan Leaf | 40.0 | 16.5 | 12 | Disponible | 242.42 km |
| **103** | BYD Han EV | 85.4 | 18.2 | 40 | En mantenimiento | 469.23 km |
| **104** | Hyundai Ioniq 5 | 72.6 | 17.0 | 30 | Disponible | 427.06 km |

---

## 6. Guia de Pruebas Paso a Paso (Casos 1 al 7)

Para comprobar el funcionamiento completo del sistema, sigue estos pasos numerados:

### Caso 1: Registrar un vehiculo y probar validaciones de error
1. En el menu, escribe `1` y presiona Enter.
2. En `ID del vehiculo`, escribe `101` -> El sistema avisara que el ID ya esta registrado.
3. En `ID del vehiculo`, escribe letras como `abc` -> El sistema avisara que es una entrada invalida sin cerrarse.
4. En `ID del vehiculo`, escribe `105`.
5. En `Modelo`, escribe `Volvo EX30 Recharge`.
6. En `Capacidad de bateria`, escribe `-15` -> El sistema avisara que debe ser mayor a cero (> 0).
7. Escribe `69.0`, consumo `17.5`, viajes `8` y estado `1` (Disponible).
8. Resultado: Unidad agregada con autonomia calculada de `394.29 km`.

### Caso 2: Buscar vehiculo por ID
1. En el menu, escribe `2`.
2. Ingresa `103` -> Despliega la informacion del `BYD Han EV`, indicando que esta `En mantenimiento` y su autonomia de `469.23 km`.
3. Vuelve a seleccionar `2` e ingresa `999` -> Muestra el mensaje: `[!] No se encontro ningun vehiculo con el ID 999.`.

### Caso 3: Actualizar numero de viajes
1. En el menu, escribe `3`.
2. Ingresa ID `102` (Nissan Leaf).
3. Muestra que tiene 12 viajes actuales; escribe `18` y presiona Enter.
4. Resultado: El odometro de viajes se actualiza en memoria a 18.

### Caso 4: Ordenar vehiculos por autonomia (Metodo Burbuja)
1. En el menu, escribe `4`.
2. El sistema aplica el ordenamiento de mayor a menor y muestra la tabla en este orden:
   1. `BYD Han EV` (469.23 km)
   2. `Hyundai Ioniq 5` (427.06 km)
   3. `Tesla Model 3` (400.00 km)
   4. `Volvo EX30` (394.29 km)
   5. `Nissan Leaf` (242.42 km)

### Caso 5: Consultar formula de calculo y promedio de la flota
1. En el menu, escribe `6`.
2. Ingresa ID `101` (Tesla Model 3).
3. El sistema muestra la formula: `(60.0 / 15.0) * 100 = 400.00 km`.
4. Ademas, muestra el promedio general de autonomia de toda la flota mediante acumuladores.

### Caso 6: Generar reportes con umbral
1. En el menu, escribe `7`.
2. Selecciona la sub-opcion `1` (Autonomia baja) e introduce el umbral `350` -> Filtra solo el `Nissan Leaf` (242.42 km).
3. Vuelve a seleccionar `7`, elige la sub-opcion `2` (Alta demanda) e introduce el umbral `25` -> Filtra al `BYD Han EV` (40 viajes) y `Hyundai Ioniq 5` (30 viajes).

### Caso 7: Cambiar estado operativo
1. En el menu, escribe `8`.
2. Ingresa ID `103` (BYD Han EV).
3. Observa que su estado es `[2] En mantenimiento`; escribe `1` para cambiarlo a `Disponible`.
4. Si vas a la opcion `5` (Mostrar todos), podras verificar que el estado ha cambiado a `Disponible`.

---

## 7. Formulas y Reglas de Negocio

* **Calculo de Autonomia Estimada:**
  ```text
  Autonomia (km) = ( Capacidad de Bateria en kWh / Consumo Promedio en kWh por cada 100 km ) * 100
  ```
* **Prevencion de Division por Cero:** Si el consumo promedio de un vehiculo fuese menor o igual a cero, la funcion retorna `0.0` mediante una clausula de guarda previa a la division.
* **Limite del Arreglo Estatico:** `MAX_VEHICULOS = 100`. Si se intenta ingresar el vehiculo 101, el sistema bloquea el registro para proteger el tamano del arreglo.
* **Codigos de Estado:**
  * `1` = Disponible para alquiler.
  * `2` = En taller por mantenimiento.

---

## 8. Archivos e Informes Disponibles

* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf](INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf):** Documento formal en PDF (13 paginas) listo para entregar, con portada oficial, justificaciones teoricas de Python y capturas de consola.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.docx](INFORME_PARCIAL_ESTRUCTURA_DATOS.docx):** Archivo editable en Microsoft Word.
* **[INFORME_PARCIAL_ESTRUCTURA_DATOS.md](INFORME_PARCIAL_ESTRUCTURA_DATOS.md):** Version completa del informe en Markdown.

# Sistema de Gestion de Flota de Vehiculos Electricos

> **Evaluacion:** Examen Parcial - Estructura de Datos (Tipo D)  
> **Institucion:** Universidad Continental - Escuela de Ingenieria de Sistemas e Informatica  
> **Docente:** Dr. Ing. Julio Arboleda H.  
> **Lenguaje:** C++ (Estandar C++11 o superior)

---

## Descripcion del Proyecto

Sistema de consola desarrollado en **C++** para la administracion, control y analisis de rendimiento de una flota de vehiculos de alquiler 100% electricos. 

El programa implementa conceptos clave del curso:
* **Registros (`struct Vehiculo`):** Modelado cohesivo de entidades con atributos heterogeneos.
* **Arreglos Unidimensionales Estaticos:** Almacenamiento contiguo en memoria de acceso rapido O(1).
* **Busqueda Secuencial (Lineal):** Localizacion de registros por ID unico y validacion de duplicados.
* **Metodo de la Burbuja (Bubble Sort):** Ordenamiento descendente (mayor a menor) basado en un calculo derivado (Autonomia estimada en km).
* **Manejo Robusto de Excepciones:** Prevencion de bucles infinitos ante ingreso de letras o datos invalidos en teclado.

---

## Contenido del Repositorio

| Archivo / Carpeta | Descripcion |
| :--- | :--- |
| [`flota_vehiculos.cpp`](flota_vehiculos.cpp) | **Codigo fuente principal** con las 9 operaciones modulares y validaciones completas. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf`](INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf) | **Informe tecnico final en PDF (13 pags.)** con portada universitaria, las 11 secciones de la rubrica y capturas embebidas. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.docx`](INFORME_PARCIAL_ESTRUCTURA_DATOS.docx) | **Informe en Word editable** para modificar nombres, codigo de alumno o datos de entrega. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.md`](INFORME_PARCIAL_ESTRUCTURA_DATOS.md) | Version completa en Markdown para lectura rapida en cualquier editor de codigo. |
| [`evidencias/`](evidencias/) | Carpeta con las capturas de pantalla de terminal de cada caso de prueba. |

---

## Requisitos Previos

Para compilar y ejecutar el proyecto en tu maquina local solo necesitas un compilador de C++:
* **GCC / MinGW / Clang** (en Windows, Linux o macOS).
* O cualquier entorno de desarrollo (IDE) habitual: **Dev-C++, Code::Blocks, Visual Studio o VS Code**.
* *(Opcional)* Si no tienes ningun compilador instalado, puedes probarlo directamente en un compilador online.

---

## Instrucciones para Probar en Local

### Opcion 1: Compilar desde la Terminal (PowerShell / CMD / Bash)

1. Abre una terminal en la carpeta del proyecto:
   ```powershell
   cd c:\Users\Leo\alvado_parcial
   ```

2. Compila el archivo fuente con `g++`:
   ```bash
   g++ -std=c++11 flota_vehiculos.cpp -o flota_vehiculos.exe
   ```

3. Ejecuta el programa:
   * **En Windows:**
     ```powershell
     .\flota_vehiculos.exe
     ```
   * **En Linux / macOS:**
     ```bash
     ./flota_vehiculos.exe
     ```

---

### Opcion 2: Probar en Entornos de Desarrollo (IDEs)

* **En Dev-C++ / Code::Blocks:**
  1. Abre el programa.
  2. Ve a `File` > `Open` y selecciona [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
  3. Presiona la tecla **F11** (o `Execute` > `Compile & Run`).
  4. La consola se abrira automaticamente con el menu interactivo.

* **En Visual Studio / VS Code:**
  1. Abre la carpeta del proyecto.
  2. Abre [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
  3. Ejecuta con el boton de **Play / Run C/C++ File** (o con `Ctrl + F5`).

---

### Opcion 3: Probar Online sin Instalar Nada

1. Ingresa a **[OnlineGDB C++ Compiler](https://www.onlinegdb.com/online_c++_compiler)**.
2. Copia todo el contenido del archivo [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
3. Pegalo en el editor de OnlineGDB reemplazando el codigo por defecto.
4. Haz clic en el boton verde **Run** (o presiona `F9`).
5. Puedes interactuar directamente con la consola en la parte inferior.

---

## Guia de Operaciones del Menu

Al iniciar, el sistema cuenta con **4 vehiculos precargados** para pruebas inmediatas:

| ID | Modelo | Bateria (kWh) | Consumo (kWh/100km) | Viajes | Estado | Autonomia Estimada |
| :-: | :--- | :-: | :-: | :-: | :--- | :-: |
| **101** | Tesla Model 3 | 60.0 | 15.0 | 25 | Disponible | 400.00 km |
| **102** | Nissan Leaf | 40.0 | 16.5 | 12 | Disponible | 242.42 km |
| **103** | BYD Han EV | 85.4 | 18.2 | 40 | Mantenimiento | 469.23 km |
| **104** | Hyundai Ioniq 5 | 72.6 | 17.0 | 30 | Disponible | 427.06 km |

### Opciones Disponibles:
1. **[1] Registrar un nuevo vehiculo:**
   * Solicita ID (valida que sea unico y positivo).
   * Modelo (acepta nombres compuestos con espacios).
   * Capacidad de bateria en kWh (valida que sea > 0).
   * Consumo promedio en kWh/100km (valida que sea > 0).
   * Numero de viajes realizados (valida que sea >= 0).
   * Estado (1 = Disponible, 2 = En mantenimiento).
2. **[2] Buscar vehiculo por ID:**
   * Busqueda secuencial. Muestra la ficha tecnica completa o avisa si no existe.
3. **[3] Actualizar numero de viajes:**
   * Localiza la unidad por ID y permite actualizar su contador de viajes (>= 0).
4. **[4] Ordenar vehiculos por autonomia estimada:**
   * Aplica el **Metodo de la Burbuja** de mayor a menor y muestra la tabla ordenada.
5. **[5] Mostrar todos los vehiculos:**
   * Despliega la tabla formateada con todas las unidades registradas.
6. **[6] Calcular autonomia estimada (Detalle y Promedio):**
   * Muestra la formula paso a paso: Autonomia = (Bateria / Consumo) * 100.
   * Muestra el promedio general de autonomia de toda la flota mediante acumuladores.
7. **[7] Generar reportes de rendimiento:**
   * **Sub-opcion 1:** Vehiculos con autonomia baja (filtra unidades con autonomia < umbral ingresado).
   * **Sub-opcion 2:** Vehiculos con alta demanda (filtra unidades con viajes > umbral ingresado).
8. **[8] Cambiar estado del vehiculo:**
   * Conmuta entre `Disponible` y `En mantenimiento`.
9. **[9] Salir del sistema:**
   * Termina la ejecucion limpiamente.

---

## Pruebas Rapidas Sugeridas para Verificar el Funcionamiento

### Prueba 1: Validacion contra letras y errores
* Selecciona la opcion `1` (Registrar).
* En el ID, escribe `abc` -> El sistema mostrara `[Error] Entrada invalida` y te pedira el valor de nuevo sin cerrarse ni colgarse.
* Escribe `101` -> Te indicara que el ID `101` ya existe.
* Escribe `105`, modelo `Volvo EX30`, capacidad `69.0`, consumo `17.5`, viajes `8`, estado `1`.

### Prueba 2: Ordenamiento por Autonomia
* Selecciona la opcion `4`.
* Observa como la lista se ordena de forma descendente colocando en primer lugar al **BYD Han EV (469.23 km)** y al final al **Nissan Leaf (242.42 km)**.

### Prueba 3: Reportes con Umbral
* Selecciona la opcion `7`.
* Elige `1` (Autonomia baja) e ingresa `350` km -> Filtrara solo al Nissan Leaf (242.42 km).
* Elige `2` (Alta demanda) e ingresa `25` viajes -> Filtrara al BYD Han (40 viajes) y Hyundai Ioniq 5 (30 viajes).

---

## Autor y Datos Academicos

* **Asignatura:** Estructura de Datos
* **Docente:** Dr. Ing. Julio Arboleda H.
* **Seccion:** 24UC00428
* **Fecha:** 05/10/2026
* **Universidad Continental**

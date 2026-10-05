#  Sistema de Gestión de Flota de Vehículos Eléctricos

> **Evaluación:** Examen Parcial – Estructura de Datos (Tipo D)  
> **Institución:** Universidad Continental – Escuela de Ingeniería de Sistemas e Informática  
> **Docente:** Dr. Ing. Julio Arboleda H.  
> **Lenguaje:** C++ (Estándar C++11 o superior)

---

## 📋 Descripción del Proyecto

Sistema de consola desarrollado en **C++** para la administración, control y análisis de rendimiento de una flota de vehículos de alquiler 100% eléctricos. 

El programa implementa conceptos clave del curso:
* **Registros (`struct Vehiculo`):** Modelado cohesivo de entidades con atributos heterogéneos.
* **Arreglos Unidimensionales Estáticos:** Almacenamiento contiguo en memoria de acceso rápido $O(1)$.
* **Búsqueda Secuencial (Lineal):** Localización de registros por ID único y validación de duplicados.
* **Método de la Burbuja (Bubble Sort):** Ordenamiento descendente (mayor a menor) basado en un cálculo derivado (Autonomía estimada en km).
* **Manejo Robusto de Excepciones:** Prevención de bucles infinitos ante ingreso de letras o datos inválidos en teclado.

---

##  Contenido del Repositorio

| Archivo / Carpeta | Descripción |
| :--- | :--- |
| [`flota_vehiculos.cpp`](flota_vehiculos.cpp) | **Código fuente principal** con las 9 operaciones modulares y validaciones completas. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf`](INFORME_PARCIAL_ESTRUCTURA_DATOS.pdf) | **Informe técnico final en PDF (13 págs.)** con portada universitaria, las 11 secciones de la rúbrica y capturas embebidas. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.docx`](INFORME_PARCIAL_ESTRUCTURA_DATOS.docx) | **Informe en Word editable** para modificar nombres, código de alumno o datos de entrega. |
| [`INFORME_PARCIAL_ESTRUCTURA_DATOS.md`](INFORME_PARCIAL_ESTRUCTURA_DATOS.md) | Versión completa en Markdown para lectura rápida en cualquier editor de código. |
| [`evidencias/`](evidencias/) | Carpeta con las capturas de pantalla de terminal de cada caso de prueba. |

---

## ⚙️ Requisitos Previos

Para compilar y ejecutar el proyecto en tu máquina local solo necesitas un compilador de C++:
* **GCC / MinGW / Clang** (en Windows, Linux o macOS).
* O cualquier entorno de desarrollo (IDE) habitual: **Dev-C++, Code::Blocks, Visual Studio o VS Code**.
* *(Opcional)* Si no tienes ningún compilador instalado, puedes probarlo en 5 segundos en un compilador online (ver opción 3).

---

##  Instrucciones para Probar en Local

### Opción 1: Compilar desde la Terminal (PowerShell / CMD / Bash)

1. Abre una terminal en la carpeta donde clonaste o descargaste el proyecto:
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

### Opción 2: Probar en Entornos de Desarrollo (IDEs)

* **En Dev-C++ / Code::Blocks:**
  1. Abre el programa.
  2. Ve a `File` > `Open` y selecciona [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
  3. Presiona la tecla **F11** (o `Execute` > `Compile & Run`).
  4. La consola se abrirá automáticamente con el menú interactivo.

* **En Visual Studio / VS Code:**
  1. Abre la carpeta del proyecto.
  2. Abre [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
  3. Ejecuta con el botón de **Play / Run C/C++ File** (o con `Ctrl + F5`).

---

### Opción 3: Probar Online sin Instalar Nada (Recomendado para pruebas inmediatas)

1. Ingresa a **[OnlineGDB C++ Compiler](https://www.onlinegdb.com/online_c++_compiler)**.
2. Copia todo el contenido del archivo [`flota_vehiculos.cpp`](flota_vehiculos.cpp).
3. Pégalo en el editor de OnlineGDB reemplazando el código por defecto.
4. Haz clic en el botón verde **Run** (o presiona `F9`).
5. ¡Listo! Podrás interactuar directamente con la consola en la parte inferior.

---

##  Guía de Operaciones del Menú

Al iniciar, el sistema cuenta con **4 vehículos precargados** para que no tengas que ingresar datos desde cero si deseas probar de inmediato:

| ID | Modelo | Batería (kWh) | Consumo (kWh/100km) | Viajes | Estado | Autonomía Estimada |
| :-: | :--- | :-: | :-: | :-: | :--- | :-: |
| **101** | Tesla Model 3 | 60.0 | 15.0 | 25 | Disponible | 400.00 km |
| **102** | Nissan Leaf | 40.0 | 16.5 | 12 | Disponible | 242.42 km |
| **103** | BYD Han EV | 85.4 | 18.2 | 40 | Mantenimiento | 469.23 km |
| **104** | Hyundai Ioniq 5 | 72.6 | 17.0 | 30 | Disponible | 427.06 km |

### Opciones Disponibles:
1. **[1] Registrar un nuevo vehículo:**
   * Solicita ID (valida que sea único y positivo).
   * Modelo (acepta nombres compuestos con espacios).
   * Capacidad de batería en kWh (valida que sea $> 0$).
   * Consumo promedio en kWh/100km (valida que sea $> 0$).
   * Número de viajes realizados (valida que sea $\ge 0$).
   * Estado (1 = Disponible, 2 = En mantenimiento).
2. **[2] Buscar vehículo por ID:**
   * Búsqueda secuencial. Muestra la ficha técnica completa o avisa si no existe.
3. **[3] Actualizar número de viajes:**
   * Localiza la unidad por ID y permite actualizar su contador de viajes ($\ge 0$).
4. **[4] Ordenar vehículos por autonomía estimada:**
   * Aplica el **Método de la Burbuja** de mayor a menor y muestra la tabla ordenada.
5. **[5] Mostrar todos los vehículos:**
   * Despliega la tabla formateada con todas las unidades registradas.
6. **[6] Calcular autonomía estimada (Detalle y Promedio):**
   * Muestra la fórmula paso a paso: $\text{Autonomía} = (\text{Batería} / \text{Consumo}) \times 100$.
   * Muestra el promedio general de autonomía de toda la flota mediante acumuladores.
7. **[7] Generar reportes de rendimiento:**
   * **Sub-opción 1:** Vehículos con autonomía baja (filtra unidades con $\text{autonomía} < \text{umbral ingresado}$).
   * **Sub-opción 2:** Vehículos con alta demanda (filtra unidades con $\text{viajes} > \text{umbral ingresado}$).
8. **[8] Cambiar estado del vehículo:**
   * Conmuta entre `Disponible` y `En mantenimiento`.
9. **[9] Salir del sistema:**
   * Termina la ejecución limpiamente.

---

## 🧪 Pruebas Rápidas Sugeridas para Verificar el Funcionamiento

### Prueba 1: Validación contra letras y errores
* Selecciona la opción `1` (Registrar).
* En el ID, escribe `abc` $\rightarrow$ El sistema mostrará `[Error] Entrada invalida` y te pedirá el valor de nuevo sin cerrarse ni colgarse.
* Escribe `101` $\rightarrow$ Te indicará que el ID `101` ya existe.
* Escribe `105`, modelo `Volvo EX30`, capacidad `69.0`, consumo `17.5`, viajes `8`, estado `1`.

### Prueba 2: Ordenamiento por Autonomía
* Selecciona la opción `4`.
* Observa cómo la lista se ordena de forma descendente colocando en primer lugar al **BYD Han EV (469.23 km)** y al final al **Nissan Leaf (242.42 km)**.

### Prueba 3: Reportes con Umbral
* Selecciona la opción `7`.
* Elige `1` (Autonomía baja) e ingresa `350` km $\rightarrow$ Filtrará solo al Nissan Leaf (242.42 km).
* Elige `2` (Alta demanda) e ingresa `25` viajes $\rightarrow$ Filtrará al BYD Han (40 viajes) y Hyundai Ioniq 5 (30 viajes).

---

##  Autor y Datos Académicos

* **Asignatura:** Estructura de Datos
* **Docente:** Dr. Ing. Julio Arboleda H.
* **Sección:** 24UC00428
* **Fecha:** 05/10/2026
* **Universidad Continental**
# flota_vehiculo

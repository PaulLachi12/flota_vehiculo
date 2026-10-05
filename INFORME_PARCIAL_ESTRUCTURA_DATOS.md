# UNIVERSIDAD CONTINENTAL
## FACULTAD DE INGENIERÍA
### ESCUELA ACADÉMICO PROFESIONAL DE INGENIERÍA DE SISTEMAS E INFORMÁTICA

---

# INFORME TÉCNICO - EXAMEN PARCIAL DE ESTRUCTURA DE DATOS
**Tipo D – Evaluación Individual**  
**Docente:** Dr. Ing. Julio Arboleda H.  
**Sección:** 24UC00428  
**Fecha:** 05/10/2026  
**Caso Práctico:** Gestión de una Flota de Vehículos Eléctricos  
**Calificación:** 0 a 20 (Código 12 pts + Informe 8 pts)

---

## 1. Introducción (0.5 pt)

### 1.1. Descripción del Sistema
El presente software es un sistema de consola desarrollado bajo el estándar C++ diseñado para la gestión operativa y de rendimiento de una empresa de alquiler de vehículos eléctricos (EV). A diferencia de los vehículos tradicionales de combustión interna, los vehículos eléctricos demandan un control preciso sobre factores como la capacidad de almacenamiento de sus paquetes de baterías (kWh), la tasa de consumo promedio (kWh/100km) y su impacto directo en la autonomía real por carga. El sistema permite registrar unidades, actualizar su odómetro de viajes, controlar su estado de disponibilidad para mantenimiento y generar reportes analíticos para la toma de decisiones.

### 1.2. Objetivo del Programa
El objetivo del programa es automatizar de forma confiable las operaciones clave de la flota:
1. Almacenar y mantener el inventario de vehículos eléctricos sin colisiones de identificadores.
2. Calcular en tiempo real la autonomía estimada de cada vehículo según sus especificaciones técnicas de fábrica y consumo medido.
3. Facilitar la búsqueda y actualización inmediata de registros de uso y estado operativo.
4. Jerarquizar la flota de mayor a menor autonomía mediante algoritmos de ordenamiento.
5. Proveer reportes de alerta temprana sobre unidades de baja autonomía (para recarga preventiva) y de alta demanda (para asignación de mantenimiento).

### 1.3. Justificación del Uso de Estructuras (struct) y Arreglos Unidimensionales
* **Registros (`struct Vehiculo`):** Un vehículo eléctrico no puede representarse con un tipo de dato primitivo aislado. Reúne atributos heterogéneos: un ID numérico (`int`), un modelo (`string`), una capacidad de batería (`float`), un consumo medio (`float`), un conteo de viajes (`int`) y un estado de disponibilidad (`int`). El `struct` encapsula estas propiedades en una sola unidad lógica coherente, facilitando la modularidad, el paso de parámetros por referencia y evitando el uso de arreglos paralelos propensos a desincronización.
* **Arreglos Unidimensionales Estáticos (`Vehiculo flota[MAX_VEHICULOS]`):** Proporcionan asignación contigua en memoria y acceso aleatorio en tiempo constante $O(1)$ por índice. Esto garantiza un comportamiento determinístico y un consumo predecible de recursos en memoria de pila (stack), constituyendo la estructura ideal para el aprendizaje y aplicación de algoritmos fundamentales de búsqueda secuencial y ordenamiento por burbuja.

---

## 2. Lógica del Ingreso de Datos (1 pt)

### 2.1. Flujo de Captura de Datos
El procedimiento de registro de una unidad (`registrarVehiculo`) sigue un flujo secuencial estricto:
1. **Verificación de cupo:** Se evalúa si el arreglo ha alcanzado su capacidad máxima (`total >= MAX_VEHICULOS`). De ser así, se aborta la operación con un mensaje explicativo.
2. **Captura de ID y validación de unicidad:** Se solicita el ID numérico y se invoca la función de búsqueda para verificar que no exista previamente.
3. **Captura del Modelo:** Mediante `getline(cin, nuevo.modelo)` se captura la cadena completa, permitiendo espacios y caracteres alfanuméricos.
4. **Captura de Magnitudes Físicas:** Se leen la capacidad de batería (kWh) y el consumo promedio (kWh/100km) a través de validadores de números reales positivos.
5. **Captura de Parámetros Operativos:** Se lee el número de viajes completados ($\ge 0$) y se selecciona el estado operativo restringido al dominio $\{1, 2\}$.
6. **Inserción e incremento:** Se asigna el nuevo vehículo en la posición `flota[total]` y se incrementa el contador `total++`.

### 2.2. Validaciones Implementadas
| Atributo | Regla de Validación | Justificación Técnica |
| :--- | :--- | :--- |
| **ID del Vehículo** | Entero único, $> 0$ | Clave primaria lógica; no pueden coexistir dos vehículos con la misma matrícula o ID. |
| **Capacidad de Batería** | Real estrictamente $> 0$ | Magnitud física que representa energía acumulable. No existen baterías de 0 o negativos kWh. |
| **Consumo Promedio** | Real estrictamente $> 0$ | Tasa de consumo por cada 100 km. Evita además la indeterminación por división entre cero. |
| **Viajes Realizados** | Entero $\ge 0$ | Contador incremental de servicios; no admite valores negativos. |
| **Estado Operativo** | Entero $\in \{1, 2\}$ | $1 = \text{Disponible}$, $2 = \text{En mantenimiento}$. Restricción estricta de opciones. |

### 2.3. Uso de Estructuras de Control (IF, WHILE, FOR)
Se implementaron bucles interactivos `while(true)` combinados con `if-else` para la validación. A diferencia de un simple `if` que solo rechazaría la ejecución una vez, el bucle `while` retiene al operador en el campo erróneo solicitando el reingreso hasta que los datos cumplan las cotas válidas.

### 2.4. Manejo de Errores (Ingreso de Letras donde se Esperan Números)
Cuando un usuario ingresa caracteres de texto (letras, símbolos) en variables numéricas (`cin >> valor`), el flujo `std::cin` activa su bit de fallo (`failbit`), omitiendo lecturas posteriores y generando bucles infinitos. Para resolverlo de forma robusta, se diseñó la función `limpiarBuffer()`:
```cpp
void limpiarBuffer() {
    cin.clear();            // Limpia el estado de error (failbit)
    cin.ignore(10000, '\n'); // Descarta los caracteres restantes en el buffer hasta el salto de línea
}
```
Las funciones de lectura como `leerFloatPositivo()` y `leerEnteroMayorIgual()` comprueban el retorno booleano de `cin >> valor`. Si la conversión falla, capturan el error, limpian el buffer con `limpiarBuffer()` y despliegan una advertencia sin congelar el programa.

---

## 3. Lógica de Almacenamiento (1 pt)

### 3.1. Uso del Arreglo para Almacenar Vehículos
Se utiliza un arreglo unidimensional estático de registros:
```cpp
const int MAX_VEHICULOS = 100;
Vehiculo flota[MAX_VEHICULOS];
```
Cada casilla almacena los 6 atributos del vehículo de manera continua en memoria física.

### 3.2. Control del Número de Elementos (Variable Contador)
La variable entera `totalVehiculos` gobierna la dimensión lógica del arreglo frente a su capacidad física máxima:
- Actúa como índice de inserción: `flota[totalVehiculos] = nuevo;`.
- Define la frontera de parada de los bucles: `for(int i = 0; i < totalVehiculos; i++)`.
- Previene accesos fuera de rango (buffer overflow) mediante la verificación `totalVehiculos < MAX_VEHICULOS`.

### 3.3. Limitaciones del Enfoque Estático
1. **Límite de Capacidad Inflexible:** Si la empresa adquiere su vehículo número 101, el sistema se ve forzado a rechazar la operación a menos que se modifique la constante en el código fuente y se recompile.
2. **Subutilización de Memoria (Over-allocation):** Si solo se administran 5 unidades, el sistema mantiene reservados los 100 bloques de memoria, consumiendo memoria de forma ineficiente.
3. **Imposibilidad de Redimensión en Caliente:** La memoria estática reservada en el stack se define en tiempo de compilación y no puede crecer ni contraerse de acuerdo con las fluctuaciones de la flota.

---

## 4. Lógica de Actualización (1 pt)

### 4.1. Procedimiento para Actualizar el Número de Viajes
La función `actualizarViajes()` permite alterar el kilometraje y servicios acumulados de una unidad cuando regresa de una renta. El procedimiento opera directamente sobre el arreglo sin duplicar instancias.

### 4.2. Validaciones Previas
1. **Flota no vacía:** Valida que exista al menos un vehículo registrado (`total > 0`).
2. **Existencia del vehículo:** Solicita el ID y valida que el retorno de la búsqueda no sea `-1`. Si el vehículo no existe, emite una notificación de advertencia y cancela la operación.
3. **Consistencia numérica:** El nuevo número de viajes ingresado debe ser mayor o igual a cero ($\ge 0$).

### 4.3. Uso de Búsqueda Secuencial para Localizar el Vehículo
La búsqueda lineal localiza la posición física del vehículo en el arreglo y retorna su índice `indice`. Con este índice, la actualización se realiza en tiempo directo $O(1)$:
```cpp
flota[indice].viajesRealizados = nuevosViajes;
```

---

## 5. Lógica de Ordenación (1 pt)

### 5.1. Algoritmo Usado: Método de la Burbuja (Bubble Sort)
Se implementó el algoritmo de ordenamiento por intercambio (Burbuja) para organizar la flota de forma descendente (mayor a menor autonomía). El algoritmo efectúa pasadas consecutivas comparando pares de elementos adyacentes y trasladando los valores menores hacia el extremo final del arreglo.
- **Complejidad Temporal:** $O(n^2)$ en el peor de los casos y caso promedio.
- **Complejidad Espacial:** $O(1)$ (ordenamiento in-place sin uso de memoria auxiliar).

### 5.2. Proceso de Ordenación por Autonomía (Cálculo Derivado)
Dado que la autonomía no es un dato crudo almacenado sino una propiedad derivada, la condición de comparación invoca la función de cálculo sobre los elementos contiguos:
```cpp
for (int i = 0; i < total - 1; i++) {
    for (int j = 0; j < total - 1 - i; j++) {
        float autoActual = calcularAutonomia(flota[j]);
        float autoSiguiente = calcularAutonomia(flota[j + 1]);

        if (autoActual < autoSiguiente) {
            Vehiculo auxiliar = flota[j];
            flota[j] = flota[j + 1];
            flota[j + 1] = auxiliar;
        }
    }
}
```

### 5.3. Justificación Técnica: Ordenar sobre el Cálculo vs. Datos Crudos
1. **Principio de No Redundancia y Consistencia:** Si se guardara una variable `autonomia` dentro del struct, cualquier modificación en la batería o en el consumo obligaría a sincronizar manualmente dicha variable. Omitir esta actualización generaría inconsistencia de datos. Calcular la autonomía al momento de la comparación asegura que el ordenamiento refleje siempre el estado actual exacto.
2. **Evaluación Multivariable Real:** La capacidad de batería por sí sola no determina el alcance de un vehículo. Un vehículo con batería pequeña de 40 kWh y consumo bajo de 12 kWh/100km rinde 333.3 km, superando a un vehículo con batería de 50 kWh pero alto consumo de 20 kWh/100km (250 km). Ordenar sobre el cálculo derivado es la única vía técnicamente válida para reflejar el rendimiento real.

---

## 6. Lógica de Búsqueda (0.5 pt)

### 6.1. Búsqueda Secuencial por ID
La función `buscarVehiculoPorId()` itera mediante un bucle `for` desde el índice `0` hasta `total - 1`, comparando la clave de búsqueda con el ID de cada celda:
```cpp
int buscarVehiculoPorId(const Vehiculo flota[], int total, int idBuscado) {
    for (int i = 0; i < total; i++) {
        if (flota[i].id == idBuscado) {
            return i; // Encontrado
        }
    }
    return -1; // No encontrado
}
```

### 6.2. Casos Posibles
- **Elemento Encontrado:** Retorna el índice posicional $i \in [0, \text{total}-1]$. Permite a las operaciones de consulta, modificación de estado o actualización acceder de inmediato al registro.
- **Elemento No Encontrado:** Tras revisar los $n$ registros sin hallar coincidencia, retorna `-1`. El sistema interpreta este código especial para emitir mensajes informativos al usuario y prevenir lecturas fuera de rango.
- **ID Duplicado:** Se neutraliza durante el alta de vehículos. Si `buscarVehiculoPorId(flota, total, nuevoId) != -1`, se prohíbe la inserción hasta que el usuario digite un identificador no registrado.

### 6.3. Mejora Potencial: Búsqueda Binaria
Si los vehículos se mantuviesen ordenados por su identificador único (ID), se podría aplicar el algoritmo de **Búsqueda Binaria (Binary Search)**. Este algoritmo divide el espacio de búsqueda a la mitad en cada iteración ($O(\log_2 n)$). Para un arreglo de 100 vehículos, mientras que la búsqueda secuencial puede requerir hasta 100 comparaciones en el peor caso, la búsqueda binaria localizaría el vehículo en un máximo de $\lceil \log_2 100 \rceil = 7$ comparaciones.

---

## 7. Lógica de Cálculos (0.5 pt)

### 7.1. Cálculo de Autonomía Estimada
La autonomía expresa la distancia máxima proyectada en kilómetros bajo una carga de batería completa:
$$\text{Autonomía (km)} = \left(\frac{\text{Capacidad de batería (kWh)}}{\text{Consumo promedio (kWh/100km)}}\right) \times 100$$

### 7.2. Uso de Acumuladores (Promedio General de la Flota)
En la opción 6 (`consultarAutonomia`), el sistema no solo muestra el desglose del vehículo consultado, sino que calcula el promedio global de la flota mediante un acumulador:
```cpp
float acumuladorAutonomia = 0.0f;
for (int i = 0; i < total; i++) {
    acumuladorAutonomia += calcularAutonomia(flota[i]);
}
float promedioFlota = acumuladorAutonomia / total;
```
Este valor ofrece una métrica gerencial inmediata del rendimiento del parque automotor.

### 7.3. Validaciones (Prevención de División por Cero)
Si por error o anomalía el consumo promedio fuese $0$, la operación matemática resultaría en una división por cero (indeterminación o interrupción por excepción de punto flotante). Para evitar anomalías, la función incorpora una cláusula de guarda estricta:
```cpp
float calcularAutonomia(const Vehiculo& v) {
    if (v.consumoPromedio <= 0.0f) {
        return 0.0f;
    }
    return (v.capacidadBateria / v.consumoPromedio) * 100.0f;
}
```

---

## 8. Lógica de Reportes (0.5 pt)

### 8.1. Condiciones y Umbrales Dinámicos
Los reportes no utilizan valores fijos, sino que solicitan parámetros al operador en tiempo de ejecución:
1. **Reporte de Autonomía Baja:** Condición: $\text{Autonomía} < \text{Umbral}_\text{km}$. Identifica vehículos que requieren recarga inmediata o que no deben asignarse a rutas interurbanas largas.
2. **Reporte de Alta Demanda:** Condición: $\text{Viajes Realizados} > \text{Umbral}_\text{viajes}$. Detecta unidades con desgaste acelerado para programar mantenimiento preventivo en frenos, suspensión y neumáticos.

### 8.2. Filtrado y Presentación Tabular
Ambos reportes recorren secuencialmente la flota, filtran las unidades que cumplen la condición matemática y las imprimen en formato de tabla con cabecera y separadores. Si ninguna unidad cumple el criterio, se notifica claramente al usuario evitando tablas vacías.

---

## 9. Lógica del Menú (0.5 pt)

### 9.1. Implementación del Menú
El menú principal despliega las 9 opciones solicitadas en las especificaciones del examen. Cada opción se encuentra delegada en su función correspondiente, garantizando alta cohesión y bajo acoplamiento.

### 9.2. Uso de Bucles (`do-while`)
Se utiliza un bucle `do-while` controlado por la condición `opcion != 9`. Esta estructura post-test asegura que el menú se imprima al iniciar el programa y continúe desplegándose tras culminar cada acción hasta que el usuario decida voluntariamente seleccionar la opción 9 (Salir).

### 9.3. Manejo de Errores en el Menú
- **Protección contra caracteres alfabéticos:** La opción se captura mediante `leerEnteroMayorIgual`, impidiendo bloqueos del flujo `cin`.
- **Valores fuera de rango:** La cláusula `default` del `switch-case` advierte cuando se ingresa un número fuera del intervalo $[1, 9]$.

---

## 10. Pruebas del Sistema (0.5 pt)

### 10.1. Caso de Prueba 1: Registro con Manejo de Errores y Validaciones
* **Objetivo:** Comprobar el rechazo de IDs duplicados, control de caracteres alfabéticos y cotas numéricas.
* **Datos ingresados:**
  - ID 101 (Duplicado) $\rightarrow$ Rechazado con mensaje de error.
  - ID 'abc' (Entrada alfabética) $\rightarrow$ Rechazado sin bloqueo del programa.
  - ID 105 (Válido). Modelo: "Volvo EX30".
  - Capacidad -10 kWh $\rightarrow$ Rechazada ($> 0$).
  - Capacidad 69.0 kWh, Consumo 17.5 kWh/100km, Viajes 8, Estado 1 (Disponible).
* **Resultado:** Registro exitoso y cálculo inmediato de autonomía estimada (394.29 km).

### 10.2. Caso de Prueba 2: Búsqueda Secuencial por ID (Éxito y Fallo)
* **Objetivo:** Validar la localización exacta y la emisión de alertas ante registros inexistentes.
* **Datos probados:**
  - ID 103 (Existente - BYD Han EV): Muestra ficha técnica completa, estado "En mantenimiento" y autonomía de 469.23 km.
  - ID 999 (Inexistente): Emite la alerta `[!] No se encontro ningun vehiculo con el ID 999.`.

### 10.3. Caso de Prueba 3: Ordenación por Autonomía Estimada (Método Burbuja)
* **Objetivo:** Verificar que el algoritmo organice la flota de mayor a menor según su autonomía.
* **Resultado Obtenido:**
  1. ID 103 | BYD Han EV | 85.4 kWh | 18.2 kWh/100km | **469.23 km**
  2. ID 104 | Hyundai Ioniq 5 | 72.6 kWh | 17.0 kWh/100km | **427.06 km**
  3. ID 101 | Tesla Model 3 | 60.0 kWh | 15.0 kWh/100km | **400.00 km**
  4. ID 105 | Volvo EX30 | 69.0 kWh | 17.5 kWh/100km | **394.29 km**
  5. ID 102 | Nissan Leaf | 40.0 kWh | 16.5 kWh/100km | **242.42 km**

### 10.4. Caso de Prueba 4: Reportes Condicionales con Umbrales
* **Umbral Autonomía Baja (< 350 km):** Filtró con precisión el Nissan Leaf (242.42 km).
* **Umbral Alta Demanda (> 25 viajes):** Filtró el BYD Han EV (40 viajes) y el Hyundai Ioniq 5 (30 viajes).

### 10.5. Caso de Prueba 5: Actualización de Viajes y Cambio de Estado
* Se actualizó el odómetro del ID 102 (Nissan Leaf) de 12 a 18 viajes de forma persistente en memoria.
* Se conmutó el estado operativo del ID 103 (BYD Han EV) de `[2] En mantenimiento` a `[1] Disponible`.

*(Nota: Las capturas de pantalla de evidencia se encuentran embebidas en alta resolución directamente dentro del documento oficial Word `INFORME_PARCIAL_ESTRUCTURA_DATOS.docx`).*

---

## 11. Oportunidades de Mejora (0.5 pt)

### 11.1. Reflexión sobre las Limitaciones del Sistema Estático
El uso de estructuras estáticas y almacenamiento en memoria volátil cumple cabalmente con los propósitos pedagógicos del examen parcial. Sin embargo, en un entorno empresarial presenta limitaciones:
1. **Volatilidad:** Al cerrar la aplicación, todos los registros, actualizaciones de viajes y cambios de estado se borran de la memoria RAM.
2. **Capacidad fija:** El arreglo de tamaño 100 no puede adaptarse a variaciones imprevistas del tamaño de la flota sin modificar el código fuente.

### 11.2. Propuestas Técnicas de Evolución
1. **Estructuras Dinámicas de Datos:** Migrar el arreglo estático a una **Lista Doblemente Enlazada** o a un contenedor dinámico como `std::vector<Vehiculo>`, permitiendo que la flota crezca y decrezca elásticamente sin restricciones de tamaño fijo.
2. **Persistencia de Datos en Archivos:** Implementar lectura y escritura en archivos planos (CSV / JSON) o binarios mediante `<fstream>`, logrando que el programa recupere el estado de la flota al arrancar y guarde las modificaciones al salir.
3. **Integración con Bases de Datos Relacionales:** Incorporar SQLite o PostgreSQL para dotar al sistema de soporte multiusuario transaccional con propiedades ACID e indexación mediante árboles B+.
4. **Interfaz Gráfica de Usuario (GUI):** Desarrollar un panel de control interactivo mediante Qt o una interfaz web moderna, permitiendo a los operadores visualizar la flota en mapas y gráficos interactivos de rendimiento de batería.

---
*Fin del Informe Técnico.*

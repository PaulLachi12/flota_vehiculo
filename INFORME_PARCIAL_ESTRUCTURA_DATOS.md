# UNIVERSIDAD CONTINENTAL
## FACULTAD DE INGENIERIA
### ESCUELA ACADEMICO PROFESIONAL DE INGENIERIA DE SISTEMAS E INFORMATICA

---

# INFORME TECNICO - EXAMEN PARCIAL DE ESTRUCTURA DE DATOS
**Tipo D - Evaluacion Individual**  
**Docente:** Dr. Ing. Julio Arboleda H.  
**Seccion:** 24UC00428  
**Fecha:** 05/10/2026  
**Caso Practico:** Gestion de una Flota de Vehiculos Electricos  
**Lenguaje de Desarrollo:** Python 3  
**Calificacion:** 0 a 20 (Codigo 12 pts + Informe 8 pts)

---

## 1. Introduccion (0.5 pt)

### 1.1. Descripcion del Sistema
El presente software es un sistema de consola desarrollado bajo el estandar Python 3 disenado para la gestion operativa y de rendimiento de una empresa de alquiler de vehiculos electricos (EV). A diferencia de los vehiculos tradicionales de combustion interna, los vehiculos electricos demandan un control preciso sobre factores como la capacidad de almacenamiento de sus paquetes de baterias (kWh), la tasa de consumo promedio (kWh/100km) y su impacto directo en la autonomia real por carga. El sistema permite registrar unidades, actualizar su odometro de viajes, controlar su estado de disponibilidad para mantenimiento y generar reportes analiticos para la toma de decisiones.

### 1.2. Objetivo del Programa
El objetivo del programa es automatizar de forma confiable las operaciones clave de la flota:
1. Almacenar y mantener el inventario de vehiculos electricos sin colisiones de identificadores.
2. Calcular en tiempo real la autonomia estimada de cada vehiculo segun sus especificaciones tecnicas de fabrica y consumo medido.
3. Facilitar la busqueda y actualizacion inmediata de registros de uso y estado operativo.
4. Jerarquizar la flota de mayor a menor autonomia mediante algoritmos de ordenamiento.
5. Proveer reportes de alerta temprana sobre unidades de baja autonomia (para recarga preventiva) y de alta demanda (para asignacion de mantenimiento).

### 1.3. Justificacion del Uso de Estructuras (struct) y Arreglos Unidimensionales en Python
* **Registros (`class Vehiculo` como struct):** Un vehiculo electrico no puede representarse con un tipo de dato primitivo aislado. Reune atributos heterogeneos: un ID numerico (`int`), un modelo (`str`), una capacidad de bateria (`float`), un consumo medio (`float`), un conteo de viajes (`int`) y un estado de disponibilidad (`int`). La clase `Vehiculo` modela exclusivamente un registro estructurado sin metodos complejos, encapsulando estas propiedades en una sola unidad logica coherente, facilitando la modularidad y evitando el uso de listas paralelas propensas a desincronizacion.
* **Arreglos Unidimensionales Estaticos (`flota = [None] * MAX_VEHICULOS`):** Proporcionan asignacion contigua y acceso directo en tiempo constante O(1) por indice. La variable `total_vehiculos` gobierna la dimension logica. Esto garantiza un comportamiento deterministico con capacidad prefijada, constituyendo la estructura ideal para el aprendizaje y aplicacion de algoritmos fundamentales de busqueda secuencial y ordenamiento por burbuja.

---

## 2. Logica del Ingreso de Datos (1 pt)

### 2.1. Flujo de Captura de Datos
El procedimiento de registro de una unidad (`registrar_vehiculo`) sigue un flujo secuencial estricto:
1. **Verificacion de cupo:** Se evalua si el arreglo ha alcanzado su capacidad maxima (`total >= MAX_VEHICULOS`). De ser asi, se aborta la operacion con un mensaje explicativo.
2. **Captura de ID y validacion de unicidad:** Se solicita el ID numerico y se invoca la funcion de busqueda secuencial para verificar que no exista previamente.
3. **Captura del Modelo:** Se captura la cadena completa, permitiendo espacios y validando que no quede vacia.
4. **Captura de Magnitudes Fisicas:** Se leen la capacidad de bateria (kWh) y el consumo promedio (kWh/100km) a traves de validadores de numeros reales positivos (> 0).
5. **Captura de Parametros Operativos:** Se lee el numero de viajes completados (>= 0) y se selecciona el estado operativo restringido al dominio {1, 2}.
6. **Insercion e incremento:** Se almacena la nueva instancia en `flota[total]` y se incrementa el contador `total += 1`.

### 2.2. Validaciones Implementadas
| Atributo | Regla de Validacion | Justificacion Tecnica |
| :--- | :--- | :--- |
| **ID del Vehiculo** | Entero unico, > 0 | Clave primaria logica; no pueden coexistir dos vehiculos con el mismo ID. |
| **Capacidad de Bateria** | Real estrictamente > 0 | Magnitud fisica que representa energia acumulable en kWh. |
| **Consumo Promedio** | Real estrictamente > 0 | Tasa de consumo por cada 100 km. Evita ademas la indeterminacion por division entre cero. |
| **Viajes Realizados** | Entero >= 0 | Contador incremental de servicios; no admite valores negativos. |
| **Estado Operativo** | Entero in {1, 2} | 1 = Disponible, 2 = En mantenimiento. Restriccion estricta de opciones. |

### 2.3. Uso de Estructuras de Control (WHILE, IF, FOR)
Se implementaron bucles interactivos `while True` combinados con `if-else` para la validacion. A diferencia de un simple `if` que solo rechazaria la ejecucion una vez, el bucle `while` retiene al operador en el campo erroneo solicitando el reingreso hasta que los datos cumplan las cotas validas.

### 2.4. Manejo de Errores (Ingreso de Letras en Campos Numericos)
Cuando un usuario ingresa caracteres de texto (letras, simbolos) en campos numericos, la funcion `int()` o `float()` de Python genera una excepcion `ValueError`. Para evitar que el programa aborte o se cierre intempestivamente, se implementaron rutinas de lectura protegidas mediante bloques `try-except`:
```python
def leer_entero(mensaje: str) -> int:
    while True:
        entrada = input(mensaje).strip()
        try:
            return int(entrada)
        except ValueError:
            print("   [Error] Entrada invalida. Debe ingresar un numero entero.")

def leer_float_positivo(mensaje: str) -> float:
    while True:
        entrada = input(mensaje).strip()
        try:
            valor = float(entrada)
            if valor > 0.0:
                return valor
            print("   [Error] El valor debe ser estrictamente mayor que cero (> 0).")
        except ValueError:
            print("   [Error] Entrada invalida. Ingrese un valor numerico valido.")
```

---

## 3. Logica de Almacenamiento (1 pt)

### 3.1. Uso del Arreglo para Almacenar Vehiculos
Se utiliza un arreglo unidimensional estatico:
```python
MAX_VEHICULOS = 100
flota = [None] * MAX_VEHICULOS
```
Cada posicion almacena una referencia al registro `Vehiculo`.

### 3.2. Control del Numero de Elementos (Variable Contador)
La variable entera `total_vehiculos` gobierna la dimension logica del arreglo:
- Actua como indice de insercion: `flota[total_vehiculos] = nuevo`.
- Define la frontera de parada de los bucles: `for i in range(total_vehiculos)`.
- Previene desbordamiento mediante la verificacion `total_vehiculos < MAX_VEHICULOS`.

### 3.3. Limitaciones del Enfoque Estatico
1. **Capacidad Rigida:** Si la empresa adquiere su vehiculo numero 101, el sistema se ve forzado a rechazar la operacion.
2. **Subutilizacion de Memoria:** Si solo se administran 4 vehiculos, los 96 restantes permanecen reservados como `None`.
3. **Falta de Autoescalabilidad:** No puede crecer ni contraerse de acuerdo con las fluctuaciones de la flota sin modificar el codigo fuente.

---

## 4. Logica de Actualizacion (1 pt)

### 4.1. Procedimiento para Actualizar el Numero de Viajes
La funcion `actualizar_viajes` permite alterar el kilometraje y servicios acumulados de una unidad cuando regresa de una renta. El procedimiento opera directamente sobre el atributo `viajes_realizados` del objeto sin duplicar instancias.

### 4.2. Validaciones Previas
1. **Flota no vacia:** Valida que exista al menos un vehiculo registrado (`total > 0`).
2. **Existencia del vehiculo:** Solicita el ID y valida que el retorno de la busqueda no sea `-1`. Si el vehiculo no existe, emite una notificacion y cancela la operacion.
3. **Consistencia numerica:** El nuevo numero de viajes ingresado debe ser mayor o igual a cero (>= 0).

### 4.3. Uso de Busqueda Secuencial para Localizar el Vehiculo
La busqueda lineal localiza la posicion fisica del vehiculo en el arreglo y retorna su indice `indice`:
```python
flota[indice].viajes_realizados = nuevos_viajes
```

---

## 5. Logica de Ordenacion (1 pt)

### 5.1. Algoritmo Usado: Metodo de la Burbuja (Bubble Sort)
Se implemento el algoritmo de ordenamiento por intercambio (Burbuja) de forma manual en Python para organizar la flota de forma descendente (mayor a menor autonomia), sin recurrir a metodos opacos como `.sort()`:
- **Complejidad Temporal:** O(n^2) en el peor de los casos y caso promedio.
- **Complejidad Espacial:** O(1) (ordenamiento in-place).

### 5.2. Proceso de Ordenacion por Autonomia (Calculo Derivado)
Dado que la autonomia no es un dato crudo almacenado sino una propiedad derivada, la condicion de comparacion invoca la funcion de calculo sobre los elementos contiguos:
```python
for i in range(total - 1):
    for j in range(total - 1 - i):
        auto_actual = calcular_autonomia(flota[j])
        auto_siguiente = calcular_autonomia(flota[j + 1])

        if auto_actual < auto_siguiente:
            flota[j], flota[j + 1] = flota[j + 1], flota[j]
```

### 5.3. Justificacion Tecnica: Ordenar sobre el Calculo vs. Datos Crudos
1. **Consistencia de Datos:** Evita almacenar una variable redundante que podria quedar desactualizada ante modificaciones de bateria o consumo.
2. **Evaluacion Multivariable Coherente:** Un vehiculo con bateria de 40 kWh y consumo bajo (12 kWh/100km) alcanza 333.3 km, superando a un vehiculo con 50 kWh pero alto consumo (20 kWh/100km, 250 km). Ordenar sobre el calculo es la unica via valida para medir el rendimiento real.

---

## 6. Logica de Busqueda (0.5 pt)

### 6.1. Busqueda Secuencial por ID
La funcion `buscar_vehiculo_por_id` itera mediante un bucle `for` desde el indice `0` hasta `total - 1`, comparando la clave de busqueda con el ID de cada celda:
```python
def buscar_vehiculo_por_id(flota: list, total: int, id_buscado: int) -> int:
    for i in range(total):
        if flota[i].id == id_buscado:
            return i
    return -1
```

### 6.2. Casos Posibles
- **Elemento Encontrado:** Retorna el indice posicional i in [0, total-1].
- **Elemento No Encontrado:** Tras revisar los n registros sin hallar coincidencia, retorna `-1`.
- **ID Duplicado:** Se neutraliza durante el alta de vehiculos; si la busqueda retorna distinto de -1, se prohibe la insercion.

### 6.3. Mejora Potencial: Busqueda Binaria
Si los vehiculos se mantuviesen ordenados por su identificador unico (ID), se podria aplicar la Busqueda Binaria (O(log n)), pasando de 100 comparaciones en el peor caso a un maximo de 7.

---

## 7. Logica de Calculos (0.5 pt)

### 7.1. Calculo de Autonomia Estimada
La autonomia expresa la distancia maxima proyectada en kilometros bajo una carga de bateria completa:
```text
Autonomia (km) = ( Capacidad de Bateria (kWh) / Consumo Promedio (kWh/100km) ) * 100
```

### 7.2. Uso de Acumuladores (Promedio General de la Flota)
En la opcion 6 (`consultar_autonomia`), el sistema suma la autonomia de cada unidad y computa el promedio global de la flota mediante acumuladores.

### 7.3. Validaciones (Prevencion de Division por Cero)
```python
def calcular_autonomia(v: Vehiculo) -> float:
    if v.consumo_promedio <= 0.0:
        return 0.0
    return (v.capacidad_bateria / v.consumo_promedio) * 100.0
```

---

## 8. Logica de Reportes (0.5 pt)

### 8.1. Condiciones y Umbrales Dinamicos
1. **Reporte de Autonomia Baja:** Condicion: `calcular_autonomia(v) < umbral_km`.
2. **Reporte de Alta Demanda:** Condicion: `v.viajes_realizados > umbral_viajes`.

### 8.2. Filtrado y Presentacion Tabular
Ambos reportes recorren secuencialmente la flota, filtran las unidades que cumplen la condicion matematica y las imprimen en formato de tabla con cabecera y separadores limpios.

---

## 9. Logica del Menu (0.5 pt)

### 9.1. Implementacion del Menu
El menu principal despliega las 9 opciones solicitadas en las especificaciones del examen. Cada opcion se encuentra delegada en su funcion correspondiente.

### 9.2. Uso de Bucles (`while`)
Se utiliza un bucle `while opcion != 9`. Esta estructura asegura que el menu se imprima al iniciar el programa y continue desplegandose tras culminar cada accion hasta que el usuario decida voluntariamente seleccionar la opcion 9 (Salir).

---

## 10. Pruebas del Sistema (0.5 pt)

### 10.1. Caso de Prueba 1: Registro con Manejo de Errores y Validaciones
* ID duplicado = 101 (Rechazado); ID letra = 'abc' (Rechazado con try-except); ID valido = 105; Modelo = 'Volvo EX30'; Capacidad -10 kWh (Rechazada); Capacidad 69.0 kWh, Consumo 17.5, Viajes 8, Estado 1.
* Resultado: Registro exitoso y calculo inmediato de autonomia estimada (394.29 km).

### 10.2. Caso de Prueba 2: Busqueda Secuencial por ID
* ID 103 (BYD Han EV): Ficha tecnica completa recuperada.
* ID 999 (Inexistente): Emite alerta clara `[!] No se encontro ningun vehiculo con el ID 999.`.

### 10.3. Caso de Prueba 3: Ordenacion por Autonomia Estimada (Burbuja)
1. ID 103 | BYD Han EV | 85.4 kWh | 18.2 kWh/100km | **469.23 km**
2. ID 104 | Hyundai Ioniq 5 | 72.6 kWh | 17.0 kWh/100km | **427.06 km**
3. ID 101 | Tesla Model 3 | 60.0 kWh | 15.0 kWh/100km | **400.00 km**
4. ID 105 | Volvo EX30 | 69.0 kWh | 17.5 kWh/100km | **394.29 km**
5. ID 102 | Nissan Leaf | 40.0 kWh | 16.5 kWh/100km | **242.42 km**

### 10.4. Caso de Prueba 4: Reportes Condicionales con Umbrales
* Umbral Autonomia Baja (< 350 km): Filtra Nissan Leaf (242.42 km).
* Umbral Alta Demanda (> 25 viajes): Filtra BYD Han EV (40 viajes) y Hyundai Ioniq 5 (30 viajes).

### 10.5. Caso de Prueba 5: Actualizacion de Viajes y Cambio de Estado
* Odometro del ID 102 (Nissan Leaf) actualizado de 12 a 18 viajes.
* Estado del ID 103 (BYD Han EV) conmutado a `[1] Disponible`.

*(Las capturas graficas de terminal se encuentran embebidas en el documento oficial Word y PDF).*

---

## 11. Oportunidades de Mejora (0.5 pt)

1. **Estructuras Dinamicas:** Utilizar listas enlazadas manuales o listas nativas redimensionables sin limite prefijado.
2. **Persistencia en Disco:** Almacenar datos en archivos JSON o CSV mediante modulos estandar `json` o `csv`.
3. **Bases de Datos Relacionales:** Conectar con SQLite (`sqlite3`) para persistencia ACID y concurrencia.
4. **Interfaz Grafica o Web:** Crear interfaz visual con Tkinter o un panel web con Flask / Streamlit.

---
*Fin del Informe Tecnico.*

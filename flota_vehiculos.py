"""
=========================================================================================
UNIVERSIDAD CONTINENTAL
ESCUELA ACADEMICO PROFESIONAL DE INGENIERIA DE SISTEMAS E INFORMATICA

ASIGNATURA : ESTRUCTURA DE DATOS
EVALUACION : EXAMEN PARCIAL - TIPO D
DOCENTE    : Dr. Ing. Julio Arboleda H.
CASO       : GESTION DE UNA FLOTA DE VEHICULOS ELECTRICOS
LENGUAJE   : PYTHON 3
=========================================================================================
Descripcion:
Sistema modular desarrollado en Python para la administracion y control de una flota de
vehiculos de alquiler electricos. 
Implementa el concepto de registro (struct) mediante una clase de atributos puros y un 
arreglo unidimensional de tamano estatico controlado por contador. Incluye algoritmos 
de busqueda secuencial, ordenamiento por metodo de la burbuja y validacion de tipos con 
manejo de excepciones.
=========================================================================================
"""

# Capacidad maxima de almacenamiento de la flota (arreglo estatico)
MAX_VEHICULOS = 100

# =========================================================================================
# DEFINICION DEL REGISTRO (STRUCT)
# =========================================================================================
class Vehiculo:
    """
    Representa el registro (struct) de un vehiculo electrico en el sistema.
    Agrupa los atributos heterogeneos en una sola entidad logica.
    """
    def __init__(self, id_vehiculo: int, modelo: str, capacidad_bateria: float, 
                 consumo_promedio: float, viajes_realizados: int, estado: int):
        self.id = id_vehiculo                     # Identificador unico (entero)
        self.modelo = modelo                     # Modelo del vehiculo (cadena)
        self.capacidad_bateria = capacidad_bateria # Capacidad en kWh (real > 0)
        self.consumo_promedio = consumo_promedio   # Consumo en kWh/100km (real > 0)
        self.viajes_realizados = viajes_realizados # Total de viajes completados (entero >= 0)
        self.estado = estado                     # 1 = Disponible, 2 = En mantenimiento


# =========================================================================================
# FUNCIONES AUXILIARES DE LECTURA Y VALIDACION DE ENTRADAS
# =========================================================================================

def leer_entero(mensaje: str) -> int:
    """
    Lee un numero entero controlando que no se ingresen letras o caracteres invalidos.
    Usa manejo de excepciones (try-except ValueError) para evitar fallos.
    """
    while True:
        entrada = input(mensaje).strip()
        try:
            return int(entrada)
        except ValueError:
            print("   [Error] Entrada invalida. Debe ingresar un numero entero.")


def leer_entero_mayor_igual(mensaje: str, limite_inferior: int) -> int:
    """
    Lee un numero entero garantizando que cumpla una cota minima (>= limite_inferior).
    """
    while True:
        valor = leer_entero(mensaje)
        if valor >= limite_inferior:
            return valor
        print(f"   [Error] El valor debe ser mayor o igual a {limite_inferior}.")


def leer_float_positivo(mensaje: str) -> float:
    """
    Lee un valor decimal (float) garantizando que sea estrictamente positivo (> 0).
    """
    while True:
        entrada = input(mensaje).strip()
        try:
            valor = float(entrada)
            if valor > 0.0:
                return valor
            print("   [Error] El valor debe ser estrictamente mayor que cero (> 0).")
        except ValueError:
            print("   [Error] Entrada invalida. Ingrese un valor numerico valido.")


# =========================================================================================
# LOGICA DE CALCULO
# =========================================================================================

def calcular_autonomia(v: Vehiculo) -> float:
    """
    Calcula la autonomia estimada en kilometros a partir de la capacidad y el consumo.
    Formula: Autonomia = (Capacidad de bateria / Consumo promedio) * 100
    Incluye clausula de guarda para evitar division por cero.
    """
    if v.consumo_promedio <= 0.0:
        return 0.0
    return (v.capacidad_bateria / v.consumo_promedio) * 100.0


# =========================================================================================
# LOGICA DE BUSQUEDA
# =========================================================================================

def buscar_vehiculo_por_id(flota: list, total: int, id_buscado: int) -> int:
    """
    Realiza una busqueda secuencial (lineal) por ID en el arreglo unidimensional.
    Retorna el indice de posicion [0, total - 1] o -1 si no se encuentra.
    """
    for i in range(total):
        if flota[i].id == id_buscado:
            return i
    return -1


# =========================================================================================
# OPERACION 1: REGISTRAR UN NUEVO VEHICULO
# =========================================================================================

def registrar_vehiculo(flota: list, total: int) -> int:
    """
    Registra un nuevo vehiculo en la siguiente posicion libre del arreglo.
    Retorna el nuevo total de vehiculos.
    """
    print("--------------------------------------------------------")
    print("             REGISTRO DE NUEVO VEHICULO")
    print("--------------------------------------------------------")

    # 1. Control de limite del arreglo estatico
    if total >= MAX_VEHICULOS:
        print(f"[!] Capacidad maxima alcanzada ({MAX_VEHICULOS} vehiculos).")
        print("    No es posible registrar mas unidades en el arreglo estatico.")
        return total

    # 2. Captura y validacion de ID unico
    while True:
        id_ingresado = leer_entero(" Ingrese ID del vehiculo (entero positivo): ")
        if id_ingresado <= 0:
            print("   [Error] El ID debe ser un entero positivo mayor a cero.")
            continue
        
        pos = buscar_vehiculo_por_id(flota, total, id_ingresado)
        if pos != -1:
            print(f"   [Error] El ID {id_ingresado} ya se encuentra registrado. Ingrese otro ID.")
        else:
            break

    # 3. Captura del modelo (permite espacios)
    while True:
        modelo = input(" Ingrese Modelo del vehiculo: ").strip()
        if modelo:
            break
        print("   [Error] El modelo no puede quedar vacio. Reintente.")

    # 4. Captura de capacidad y consumo (> 0)
    capacidad = leer_float_positivo(" Ingrese Capacidad de bateria en kWh (> 0): ")
    consumo = leer_float_positivo(" Ingrese Consumo promedio en kWh/100km (> 0): ")

    # 5. Captura de viajes (>= 0)
    viajes = leer_entero_mayor_igual(" Ingrese Numero de viajes realizados (>= 0): ", 0)

    # 6. Captura de estado (1 o 2)
    while True:
        estado = leer_entero(" Ingrese Estado (1 = Disponible, 2 = En mantenimiento): ")
        if estado in (1, 2):
            break
        print("   [Error] Opcion de estado invalida. Solo se admite 1 o 2.")

    # 7. Almacenamiento en el arreglo unidimensional
    nuevo = Vehiculo(id_ingresado, modelo, capacidad, consumo, viajes, estado)
    flota[total] = nuevo
    total += 1

    print(f"\n>> [Exito] Vehiculo con ID {nuevo.id} registrado correctamente.")
    print(f"   Autonomia estimada inicial: {calcular_autonomia(nuevo):.2f} km.")
    return total


# =========================================================================================
# OPERACION 2: BUSCAR VEHICULO POR ID
# =========================================================================================

def buscar_vehiculo(flota: list, total: int):
    """
    Busca una unidad por ID y despliega su informacion completa si existe.
    """
    print("--------------------------------------------------------")
    print("               BUSQUEDA DE VEHICULO POR ID")
    print("--------------------------------------------------------")

    if total == 0:
        print("[!] No hay vehiculos registrados en la flota.")
        return

    id_buscado = leer_entero(" Ingrese el ID del vehiculo a buscar: ")
    indice = buscar_vehiculo_por_id(flota, total, id_buscado)

    if indice != -1:
        v = flota[indice]
        estado_texto = "Disponible" if v.estado == 1 else "En mantenimiento"
        print(f"\n>> Vehiculo encontrado exitosamente (Posicion en arreglo: {indice}):")
        print(f"   - ID                 : {v.id}")
        print(f"   - Modelo             : {v.modelo}")
        print(f"   - Capacidad bateria  : {v.capacidad_bateria:.2f} kWh")
        print(f"   - Consumo promedio   : {v.consumo_promedio:.2f} kWh/100km")
        print(f"   - Viajes realizados  : {v.viajes_realizados}")
        print(f"   - Estado actual      : {estado_texto}")
        print(f"   - Autonomia calculada: {calcular_autonomia(v):.2f} km")
    else:
        print(f"\n[!] No se encontro ningun vehiculo con el ID {id_buscado}.")


# =========================================================================================
# OPERACION 3: ACTUALIZAR NUMERO DE VIAJES
# =========================================================================================

def actualizar_viajes(flota: list, total: int):
    """
    Actualiza el contador de viajes completados de un vehiculo existente.
    """
    print("--------------------------------------------------------")
    print("            ACTUALIZAR NUMERO DE VIAJES")
    print("--------------------------------------------------------")

    if total == 0:
        print("[!] No hay vehiculos registrados en la flota.")
        return

    id_buscado = leer_entero(" Ingrese el ID del vehiculo a actualizar: ")
    indice = buscar_vehiculo_por_id(flota, total, id_buscado)

    if indice == -1:
        print(f"[!] Error: El vehiculo con ID {id_buscado} no existe en el sistema.")
        return

    v = flota[indice]
    print(f" Vehiculo seleccionado: {v.modelo}")
    print(f" Cantidad actual de viajes: {v.viajes_realizados}")

    nuevos_viajes = leer_entero_mayor_igual(" Ingrese la nueva cantidad total de viajes (>= 0): ", 0)
    v.viajes_realizados = nuevos_viajes

    print(f"\n>> [Exito] Numero de viajes actualizado satisfactoriamente a {nuevos_viajes}.")


# =========================================================================================
# OPERACION 4: ORDENAR VEHICULOS POR AUTONOMIA ESTIMADA (METODO DE LA BURBUJA)
# =========================================================================================

def ordenar_vehiculos_por_autonomia(flota: list, total: int):
    """
    Ordena el arreglo de vehiculos de mayor a menor autonomia estimada
    utilizando el clasico algoritmo de intercambio por Burbuja (Bubble Sort).
    """
    print("--------------------------------------------------------")
    print("   ORDENAR VEHICULOS POR AUTONOMIA (MAYOR A MENOR)")
    print("--------------------------------------------------------")

    if total <= 1:
        print("[!] Se requieren al menos 2 vehiculos para realizar un ordenamiento.")
        if total == 1:
            mostrar_todos_vehiculos(flota, total)
        return

    # Metodo de la Burbuja (Bubble Sort) descendente sobre calculo derivado
    for i in range(total - 1):
        for j in range(total - 1 - i):
            auto_actual = calcular_autonomia(flota[j])
            auto_siguiente = calcular_autonomia(flota[j + 1])

            # Criterio descendente: desplaza los valores mayores hacia el inicio
            if auto_actual < auto_siguiente:
                flota[j], flota[j + 1] = flota[j + 1], flota[j]

    print(">> [Exito] Flota ordenada exitosamente por autonomia estimada (descendente).\n")
    mostrar_todos_vehiculos(flota, total)


# =========================================================================================
# OPERACION 5: MOSTRAR TODOS LOS VEHICULOS
# =========================================================================================

def imprimir_cabecera_tabla():
    print("+-----+----------------------+------------+------------+--------+------------------+----------------+")
    print("| ID  | Modelo               | Bateria    | Consumo    | Viajes | Estado           | Autonomia Est. |")
    print("+-----+----------------------+------------+------------+--------+------------------+----------------+")


def imprimir_fila_vehiculo(v: Vehiculo):
    estado_texto = "Disponible" if v.estado == 1 else "En mantenimiento"
    autonomia = calcular_autonomia(v)
    print(f"| {v.id:>3} "
          f"| {v.modelo:<20} "
          f"| {v.capacidad_bateria:>7.1f} kWh "
          f"| {v.consumo_promedio:>7.1f} km  "
          f"| {v.viajes_realizados:>6} "
          f"| {estado_texto:<16} "
          f"| {autonomia:>11.2f} km |")


def mostrar_todos_vehiculos(flota: list, total: int):
    """
    Despliega la totalidad de unidades registradas en formato tabular alineado.
    """
    print("----------------------------------------------------------------------------------------------------")
    print("                                  LISTADO GENERAL DE LA FLOTA")
    print("----------------------------------------------------------------------------------------------------")

    if total == 0:
        print("[!] No hay vehiculos registrados en la flota actualmente.")
        return

    imprimir_cabecera_tabla()
    for i in range(total):
        imprimir_fila_vehiculo(flota[i])
    print("+-----+----------------------+------------+------------+--------+------------------+----------------+")
    print(f" Total de unidades registradas: {total} / {MAX_VEHICULOS}")


# =========================================================================================
# OPERACION 6: CALCULAR AUTONOMIA ESTIMADA (DETALLE Y PROMEDIO GENERAL)
# =========================================================================================

def consultar_autonomia(flota: list, total: int):
    """
    Muestra la formula matematica y el desglose de calculo para una unidad,
    ademas del promedio general de autonomia de toda la flota mediante acumuladores.
    """
    print("--------------------------------------------------------")
    print("         CALCULO DETALLADO DE AUTONOMIA ESTIMADA")
    print("--------------------------------------------------------")
    print(" Formula aplicada: Autonomia = (Capacidad / Consumo) * 100\n")

    if total == 0:
        print("[!] No hay vehiculos registrados para realizar calculos.")
        return

    id_buscado = leer_entero(" Ingrese ID del vehiculo para consultar desglose: ")
    indice = buscar_vehiculo_por_id(flota, total, id_buscado)

    if indice != -1:
        v = flota[indice]
        autonomia = calcular_autonomia(v)
        print("\n>> Desglose matematico de la unidad:")
        print(f"   - Unidad          : {v.modelo} (ID: {v.id})")
        print(f"   - Capacidad (C)   : {v.capacidad_bateria:.2f} kWh")
        print(f"   - Consumo (P)     : {v.consumo_promedio:.2f} kWh/100km")
        print(f"   - Operacion       : ({v.capacidad_bateria} / {v.consumo_promedio}) * 100")
        print(f"   - Autonomia real  : {autonomia:.2f} km por carga completa.")
    else:
        print(f"[!] Vehiculo con ID {id_buscado} no encontrado.")

    # Calculo con acumulador para el promedio general de la flota
    acumulador_autonomia = sum(calcular_autonomia(flota[i]) for i in range(total))
    promedio_flota = acumulador_autonomia / total
    print(f"\n>> Autonomia promedio de toda la flota ({total} unidades): {promedio_flota:.2f} km.")


# =========================================================================================
# OPERACION 7: GENERAR REPORTES
# =========================================================================================

def generar_reportes(flota: list, total: int):
    """
    Genera reportes de rendimiento filtrados por umbrales ingresados por el usuario.
    """
    print("--------------------------------------------------------")
    print("            MODULO DE REPORTES DE RENDIMIENTO")
    print("--------------------------------------------------------")

    if total == 0:
        print("[!] No hay vehiculos en el sistema para generar reportes.")
        return

    print(" [1] Reporte de vehiculos con AUTONOMIA BAJA (Autonomia < umbral)")
    print(" [2] Reporte de vehiculos con ALTA DEMANDA (Viajes > umbral)")
    subopcion = leer_entero_mayor_igual(" Seleccione tipo de reporte [1 o 2]: ", 1)

    if subopcion == 1:
        umbral_km = leer_float_positivo(" Ingrese umbral de autonomia minima en km: ")
        encontrados = 0

        print(f"\n>> VEHICULOS CON AUTONOMIA MENOR A {umbral_km:.2f} KM:")
        imprimir_cabecera_tabla()

        for i in range(total):
            if calcular_autonomia(flota[i]) < umbral_km:
                imprimir_fila_vehiculo(flota[i])
                encontrados += 1
        print("+-----+----------------------+------------+------------+--------+------------------+----------------+")

        if encontrados == 0:
            print(">> Ningun vehiculo se encuentra por debajo del umbral indicado.")
        else:
            print(f">> Total de vehiculos identificados con autonomia baja: {encontrados}")

    elif subopcion == 2:
        umbral_viajes = leer_entero_mayor_igual(" Ingrese umbral minimo de viajes completados: ", 0)
        encontrados = 0

        print(f"\n>> VEHICULOS CON ALTA DEMANDA (VIAJES MAYOR A {umbral_viajes}):")
        imprimir_cabecera_tabla()

        for i in range(total):
            if flota[i].viajes_realizados > umbral_viajes:
                imprimir_fila_vehiculo(flota[i])
                encontrados += 1
        print("+-----+----------------------+------------+------------+--------+------------------+----------------+")

        if encontrados == 0:
            print(">> No existen vehiculos que superen el umbral de viajes especificado.")
        else:
            print(f">> Total de vehiculos con alta demanda: {encontrados}")
    else:
        print("[!] Opcion de reporte invalida.")


# =========================================================================================
# OPERACION 8: CAMBIAR ESTADO DEL VEHICULO
# =========================================================================================

def cambiar_estado_vehiculo(flota: list, total: int):
    """
    Modifica el estado operativo de una unidad (1 = Disponible, 2 = En mantenimiento).
    """
    print("--------------------------------------------------------")
    print("           CAMBIAR ESTADO DE OPERACION")
    print("--------------------------------------------------------")

    if total == 0:
        print("[!] No hay vehiculos registrados en la flota.")
        return

    id_buscado = leer_entero(" Ingrese ID del vehiculo a modificar: ")
    indice = buscar_vehiculo_por_id(flota, total, id_buscado)

    if indice == -1:
        print(f"[!] Vehiculo con ID {id_buscado} no encontrado en el sistema.")
        return

    v = flota[indice]
    estado_texto = "[1] Disponible" if v.estado == 1 else "[2] En mantenimiento"
    print(f" Unidad seleccionada: {v.modelo} (ID: {v.id})")
    print(f" Estado actual: {estado_texto}")

    while True:
        nuevo_estado = leer_entero(" Ingrese nuevo estado (1 = Disponible, 2 = En mantenimiento): ")
        if nuevo_estado in (1, 2):
            break
        print("   [Error] Valor invalido. Debe seleccionar 1 o 2.")

    v.estado = nuevo_estado
    resultado_texto = "Disponible" if nuevo_estado == 1 else "En mantenimiento"
    print(f"\n>> [Exito] Estado actualizado a: {resultado_texto}.")


# =========================================================================================
# FUNCION PRINCIPAL (MAIN)
# =========================================================================================

def main():
    # Inicializacion del arreglo estatico unidimensional con tamano maximo
    flota = [None] * MAX_VEHICULOS
    total_vehiculos = 0

    # Precarga de datos iniciales para pruebas inmediatas
    flota[0] = Vehiculo(101, "Tesla Model 3", 60.0, 15.0, 25, 1)
    flota[1] = Vehiculo(102, "Nissan Leaf", 40.0, 16.5, 12, 1)
    flota[2] = Vehiculo(103, "BYD Han EV", 85.4, 18.2, 40, 2)
    flota[3] = Vehiculo(104, "Hyundai Ioniq 5", 72.6, 17.0, 30, 1)
    total_vehiculos = 4

    opcion = 0
    while opcion != 9:
        print("\n========================================================")
        print("    SISTEMA DE GESTION DE FLOTA DE VEHICULOS ELECTRICOS")
        print("========================================================")
        print(" [1] Registrar un nuevo vehiculo")
        print(" [2] Buscar vehiculo por ID")
        print(" [3] Actualizar numero de viajes")
        print(" [4] Ordenar vehiculos por autonomia estimada (mayor a menor)")
        print(" [5] Mostrar todos los vehiculos")
        print(" [6] Calcular autonomia estimada (Detalle y Promedio)")
        print(" [7] Generar reportes de rendimiento")
        print(" [8] Cambiar estado del vehiculo (Disponible / Mantenimiento)")
        print(" [9] Salir del sistema")
        print("========================================================")

        opcion = leer_entero_mayor_igual("Seleccione una opcion [1-9]: ", 1)
        print()

        if opcion == 1:
            total_vehiculos = registrar_vehiculo(flota, total_vehiculos)
        elif opcion == 2:
            buscar_vehiculo(flota, total_vehiculos)
        elif opcion == 3:
            actualizar_viajes(flota, total_vehiculos)
        elif opcion == 4:
            ordenar_vehiculos_por_autonomia(flota, total_vehiculos)
        elif opcion == 5:
            mostrar_todos_vehiculos(flota, total_vehiculos)
        elif opcion == 6:
            consultar_autonomia(flota, total_vehiculos)
        elif opcion == 7:
            generar_reportes(flota, total_vehiculos)
        elif opcion == 8:
            cambiar_estado_vehiculo(flota, total_vehiculos)
        elif opcion == 9:
            print(">> Finalizando el sistema de gestion de flota. Hasta pronto.")
        else:
            print("[!] Opcion invalida. Por favor seleccione una opcion entre 1 y 9.")


if __name__ == "__main__":
    main()

/*
 * =========================================================================================
 * UNIVERSIDAD CONTINENTAL
 * ESCUELA ACADÉMICO PROFESIONAL DE INGENIERÍA DE SISTEMAS E INFORMÁTICA
 * 
 * ASIGNATURA : ESTRUCTURA DE DATOS
 * EVALUACIÓN : EXAMEN PARCIAL - TIPO D
 * DOCENTE    : Dr. Ing. Julio Arboleda H.
 * CASO       : GESTIÓN DE UNA FLOTA DE VEHÍCULOS ELÉCTRICOS
 * =========================================================================================
 * Descripción:
 * Sistema modular desarrollado en C++ para la administración y control de una flota de
 * vehículos de alquiler eléctricos. Implementa estructuras de datos estáticas (struct y
 * arreglos unidimensionales), algoritmos de búsqueda secuencial y ordenamiento por método
 * de la burbuja, además de validación exhaustiva de entradas y prevención de errores de tipo.
 * =========================================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Capacidad máxima de la flota (arreglo estático)
const int MAX_VEHICULOS = 100;

// Definición de la estructura para representar un Vehículo Eléctrico
struct Vehiculo {
    int id;                   // Identificador único (entero)
    string modelo;            // Modelo de la unidad (cadena)
    float capacidadBateria;   // Capacidad en kWh (real > 0)
    float consumoPromedio;    // Consumo promedio en kWh/100km (real > 0)
    int viajesRealizados;     // Total de viajes completados (entero >= 0)
    int estado;               // 1 = Disponible, 2 = En mantenimiento
};

// =========================================================================================
// PROTOTIPOS DE FUNCIONES
// =========================================================================================

// Funciones auxiliares de lectura y validación de tipos
void limpiarBuffer();
int leerEntero(const string& mensaje);
int leerEnteroMayorIgual(const string& mensaje, int limiteInferior);
float leerFloatPositivo(const string& mensaje);

// Funciones de lógica de negocio y cálculos
float calcularAutonomia(const Vehiculo& v);
int buscarVehiculoPorId(const Vehiculo flota[], int total, int idBuscado);

// Funciones de las operaciones del menú
void registrarVehiculo(Vehiculo flota[], int &total);
void buscarVehiculo(const Vehiculo flota[], int total);
void actualizarViajes(Vehiculo flota[], int total);
void ordenarVehiculosPorAutonomia(Vehiculo flota[], int total);
void mostrarTodosVehiculos(const Vehiculo flota[], int total);
void consultarAutonomia(const Vehiculo flota[], int total);
void generarReportes(const Vehiculo flota[], int total);
void cambiarEstadoVehiculo(Vehiculo flota[], int total);

// Funciones auxiliares de presentación
void imprimirFilaVehiculo(const Vehiculo& v);
void imprimirCabeceraTabla();

// =========================================================================================
// FUNCIÓN PRINCIPAL (MAIN)
// =========================================================================================
int main() {
    Vehiculo flota[MAX_VEHICULOS];
    int totalVehiculos = 0;
    int opcion = 0;

    // Precarga opcional de datos iniciales para demostración y pruebas inmediatas
    flota[0] = {101, "Tesla Model 3", 60.0f, 15.0f, 25, 1};
    flota[1] = {102, "Nissan Leaf", 40.0f, 16.5f, 12, 1};
    flota[2] = {103, "BYD Han EV", 85.4f, 18.2f, 40, 2};
    flota[3] = {104, "Hyundai Ioniq 5", 72.6f, 17.0f, 30, 1};
    totalVehiculos = 4;

    do {
        cout << "\n";
        cout << "========================================================\n";
        cout << "    SISTEMA DE GESTION DE FLOTA DE VEHICULOS ELECTRICOS\n";
        cout << "========================================================\n";
        cout << " [1] Registrar un nuevo vehiculo\n";
        cout << " [2] Buscar vehiculo por ID\n";
        cout << " [3] Actualizar numero de viajes\n";
        cout << " [4] Ordenar vehiculos por autonomia estimada (mayor a menor)\n";
        cout << " [5] Mostrar todos los vehiculos\n";
        cout << " [6] Calcular autonomia estimada (Detalle y Promedio)\n";
        cout << " [7] Generar reportes de rendimiento\n";
        cout << " [8] Cambiar estado del vehiculo (Disponible / Mantenimiento)\n";
        cout << " [9] Salir del sistema\n";
        cout << "========================================================\n";

        opcion = leerEnteroMayorIgual("Seleccione una opcion [1-9]: ", 1);

        cout << "\n";
        switch (opcion) {
            case 1:
                registrarVehiculo(flota, totalVehiculos);
                break;
            case 2:
                buscarVehiculo(flota, totalVehiculos);
                break;
            case 3:
                actualizarViajes(flota, totalVehiculos);
                break;
            case 4:
                ordenarVehiculosPorAutonomia(flota, totalVehiculos);
                break;
            case 5:
                mostrarTodosVehiculos(flota, totalVehiculos);
                break;
            case 6:
                consultarAutonomia(flota, totalVehiculos);
                break;
            case 7:
                generarReportes(flota, totalVehiculos);
                break;
            case 8:
                cambiarEstadoVehiculo(flota, totalVehiculos);
                break;
            case 9:
                cout << ">> Finalizando el sistema de gestion de flota. Hasta pronto.\n";
                break;
            default:
                cout << "[!] Opcion invalida. Por favor seleccione una opcion entre 1 y 9.\n";
                break;
        }

    } while (opcion != 9);

    return 0;
}

// =========================================================================================
// IMPLEMENTACIÓN DE FUNCIONES DE VALIDACIÓN Y CONTROL DE ENTRADA
// =========================================================================================

// Limpia el estado de error de cin y descarta caracteres restantes en el buffer
void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Lee un entero controlando que no se ingresen letras o simbolos
int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            limpiarBuffer();
            return valor;
        }
        cout << "   [Error] Entrada invalida. Debe ingresar un numero entero.\n";
        limpiarBuffer();
    }
}

// Lee un entero validando que cumpla una cota minima (ej. >= 0 o rango)
int leerEnteroMayorIgual(const string& mensaje, int limiteInferior) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            limpiarBuffer();
            if (valor >= limiteInferior) {
                return valor;
            }
            cout << "   [Error] El valor debe ser mayor o igual a " << limiteInferior << ".\n";
        } else {
            cout << "   [Error] Entrada invalida. Ingrese unicamente numeros enteros.\n";
            limpiarBuffer();
        }
    }
}

// Lee un valor decimal (float) garantizando que sea estrictamente positivo (> 0)
float leerFloatPositivo(const string& mensaje) {
    float valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            limpiarBuffer();
            if (valor > 0.0f) {
                return valor;
            }
            cout << "   [Error] El valor debe ser estrictamente mayor que cero (> 0).\n";
        } else {
            cout << "   [Error] Entrada invalida. Ingrese un valor numerico valido.\n";
            limpiarBuffer();
        }
    }
}

// =========================================================================================
// LÓGICA DE CÁLCULO
// =========================================================================================

// Calcula la autonomía estimada en kilómetros
// Fórmula: Autonomía = (Capacidad de batería / Consumo promedio) * 100
float calcularAutonomia(const Vehiculo& v) {
    if (v.consumoPromedio <= 0.0f) {
        return 0.0f; // Previene divisiones por cero o valores indeterminados
    }
    return (v.capacidadBateria / v.consumoPromedio) * 100.0f;
}

// =========================================================================================
// LÓGICA DE BÚSQUEDA
// =========================================================================================

// Realiza una búsqueda secuencial por ID. Retorna el índice del elemento o -1 si no existe.
int buscarVehiculoPorId(const Vehiculo flota[], int total, int idBuscado) {
    for (int i = 0; i < total; i++) {
        if (flota[i].id == idBuscado) {
            return i; // Encontrado en la posición i
        }
    }
    return -1; // No existe en el arreglo
}

// =========================================================================================
// OPERACIÓN 1: REGISTRAR UN NUEVO VEHÍCULO
// =========================================================================================
void registrarVehiculo(Vehiculo flota[], int &total) {
    cout << "--------------------------------------------------------\n";
    cout << "             REGISTRO DE NUEVO VEHICULO\n";
    cout << "--------------------------------------------------------\n";

    // 1. Control de límite del arreglo estático
    if (total >= MAX_VEHICULOS) {
        cout << "[!] Capacidad maxima alcanzada (" << MAX_VEHICULOS << " vehiculos).\n";
        cout << "    No es posible registrar mas unidades en el arreglo estatico.\n";
        return;
    }

    Vehiculo nuevo;

    // 2. Validación de ID único
    while (true) {
        nuevo.id = leerEntero(" Ingrese ID del vehiculo (entero positivo): ");
        if (nuevo.id <= 0) {
            cout << "   [Error] El ID debe ser un entero positivo mayor a cero.\n";
            continue;
        }
        int pos = buscarVehiculoPorId(flota, total, nuevo.id);
        if (pos != -1) {
            cout << "   [Error] El ID " << nuevo.id << " ya se encuentra registrado. Ingrese otro ID.\n";
        } else {
            break;
        }
    }

    // 3. Captura del modelo (permite espacios)
    cout << " Ingrese Modelo del vehiculo: ";
    getline(cin, nuevo.modelo);
    while (nuevo.modelo.empty()) {
        cout << "   [Error] El modelo no puede quedar vacio. Reintente: ";
        getline(cin, nuevo.modelo);
    }

    // 4. Captura y validación de capacidad de batería (> 0)
    nuevo.capacidadBateria = leerFloatPositivo(" Ingrese Capacidad de bateria en kWh (> 0): ");

    // 5. Captura y validación de consumo promedio (> 0)
    nuevo.consumoPromedio = leerFloatPositivo(" Ingrese Consumo promedio en kWh/100km (> 0): ");

    // 6. Captura y validación de número de viajes (>= 0)
    nuevo.viajesRealizados = leerEnteroMayorIgual(" Ingrese Numero de viajes realizados (>= 0): ", 0);

    // 7. Captura y validación de estado (1 o 2)
    while (true) {
        nuevo.estado = leerEntero(" Ingrese Estado (1 = Disponible, 2 = En mantenimiento): ");
        if (nuevo.estado == 1 || nuevo.estado == 2) {
            break;
        }
        cout << "   [Error] Opcion de estado invalida. Solo se admite 1 o 2.\n";
    }

    // Almacenamiento en el arreglo e incremento del contador
    flota[total] = nuevo;
    total++;

    cout << "\n>> [Exito] Vehiculo con ID " << nuevo.id << " registrado correctamente.\n";
    cout << "   Autonomia estimada inicial: " << fixed << setprecision(2) 
         << calcularAutonomia(nuevo) << " km.\n";
}

// =========================================================================================
// OPERACIÓN 2: BUSCAR VEHÍCULO POR ID
// =========================================================================================
void buscarVehiculo(const Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "               BUSQUEDA DE VEHICULO POR ID\n";
    cout << "--------------------------------------------------------\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos registrados en la flota.\n";
        return;
    }

    int idBuscado = leerEntero(" Ingrese el ID del vehiculo a buscar: ");
    int indice = buscarVehiculoPorId(flota, total, idBuscado);

    if (indice != -1) {
        const Vehiculo& v = flota[indice];
        cout << "\n>> Vehiculo encontrado exitosamente (Posicion en arreglo: " << indice << "):\n";
        cout << "   - ID                : " << v.id << "\n";
        cout << "   - Modelo            : " << v.modelo << "\n";
        cout << "   - Capacidad bateria : " << fixed << setprecision(2) << v.capacidadBateria << " kWh\n";
        cout << "   - Consumo promedio  : " << fixed << setprecision(2) << v.consumoPromedio << " kWh/100km\n";
        cout << "   - Viajes realizados : " << v.viajesRealizados << "\n";
        cout << "   - Estado actual     : " << (v.estado == 1 ? "Disponible" : "En mantenimiento") << "\n";
        cout << "   - Autonomia calculada: " << fixed << setprecision(2) << calcularAutonomia(v) << " km\n";
    } else {
        cout << "\n[!] No se encontro ningun vehiculo con el ID " << idBuscado << ".\n";
    }
}

// =========================================================================================
// OPERACIÓN 3: ACTUALIZAR NÚMERO DE VIAJES
// =========================================================================================
void actualizarViajes(Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "            ACTUALIZAR NUMERO DE VIAJES\n";
    cout << "--------------------------------------------------------\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos registrados en la flota.\n";
        return;
    }

    int idBuscado = leerEntero(" Ingrese el ID del vehiculo a actualizar: ");
    int indice = buscarVehiculoPorId(flota, total, idBuscado);

    if (indice == -1) {
        cout << "[!] Error: El vehiculo con ID " << idBuscado << " no existe en el sistema.\n";
        return;
    }

    cout << " Vehiculo seleccionado: " << flota[indice].modelo << "\n";
    cout << " Cantidad actual de viajes: " << flota[indice].viajesRealizados << "\n";

    int nuevosViajes = leerEnteroMayorIgual(" Ingrese la nueva cantidad total de viajes (>= 0): ", 0);
    flota[indice].viajesRealizados = nuevosViajes;

    cout << "\n>> [Exito] Numero de viajes actualizado satisfactoriamente a " 
         << nuevosViajes << ".\n";
}

// =========================================================================================
// OPERACIÓN 4: ORDENAR VEHÍCULOS POR AUTONOMÍA ESTIMADA (MÉTODO BURBUJA)
// =========================================================================================
void ordenarVehiculosPorAutonomia(Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "   ORDENAR VEHICULOS POR AUTONOMIA (MAYOR A MENOR)\n";
    cout << "--------------------------------------------------------\n";

    if (total <= 1) {
        cout << "[!] Se requieren al menos 2 vehiculos para realizar un ordenamiento.\n";
        if (total == 1) {
            mostrarTodosVehiculos(flota, total);
        }
        return;
    }

    // Algoritmo de Burbuja (Bubble Sort) descendente
    // Se compara la autonomía estimada calculada dinámicamente mediante la función
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            float autoActual = calcularAutonomia(flota[j]);
            float autoSiguiente = calcularAutonomia(flota[j + 1]);

            // Criterio de orden descendente: si el actual tiene menor autonomia que el siguiente, se intercambian
            if (autoActual < autoSiguiente) {
                Vehiculo auxiliar = flota[j];
                flota[j] = flota[j + 1];
                flota[j + 1] = auxiliar;
            }
        }
    }

    cout << ">> [Exito] Flota ordenada exitosamente por autonomia estimada (descendente).\n\n";
    mostrarTodosVehiculos(flota, total);
}

// =========================================================================================
// OPERACIÓN 5: MOSTRAR TODOS LOS VEHÍCULOS
// =========================================================================================
void imprimirCabeceraTabla() {
    cout << "+-----+----------------------+------------+------------+--------+------------------+----------------+\n";
    cout << "| ID  | Modelo               | Bateria    | Consumo    | Viajes | Estado           | Autonomia Est. |\n";
    cout << "+-----+----------------------+------------+------------+--------+------------------+----------------+\n";
}

void imprimirFilaVehiculo(const Vehiculo& v) {
    string estadoTexto = (v.estado == 1) ? "Disponible" : "Mantenimiento";
    cout << "| " << setw(3) << v.id << " "
         << "| " << setw(20) << left << v.modelo << right << " "
         << "| " << setw(7) << fixed << setprecision(1) << v.capacidadBateria << " kWh "
         << "| " << setw(7) << fixed << setprecision(1) << v.consumoPromedio << " km "
         << "| " << setw(6) << v.viajesRealizados << " "
         << "| " << setw(16) << left << estadoTexto << right << " "
         << "| " << setw(11) << fixed << setprecision(2) << calcularAutonomia(v) << " km |\n";
}

void mostrarTodosVehiculos(const Vehiculo flota[], int total) {
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "                                  LISTADO GENERAL DE LA FLOTA\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos registrados en la flota actualmente.\n";
        return;
    }

    imprimirCabeceraTabla();
    for (int i = 0; i < total; i++) {
        imprimirFilaVehiculo(flota[i]);
    }
    cout << "+-----+----------------------+------------+------------+--------+------------------+----------------+\n";
    cout << " Total de unidades registradas: " << total << " / " << MAX_VEHICULOS << "\n";
}

// =========================================================================================
// OPERACIÓN 6: CALCULAR AUTONOMÍA ESTIMADA (DETALLE Y PROMEDIO GENERAL)
// =========================================================================================
void consultarAutonomia(const Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "         CALCULO DETALLADO DE AUTONOMIA ESTIMADA\n";
    cout << "--------------------------------------------------------\n";
    cout << " Formula aplicada: Autonomia = (Capacidad / Consumo) * 100\n\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos registrados para realizar calculos.\n";
        return;
    }

    int idBuscado = leerEntero(" Ingrese ID del vehiculo para consultar desglose: ");
    int indice = buscarVehiculoPorId(flota, total, idBuscado);

    if (indice != -1) {
        const Vehiculo& v = flota[indice];
        float autonomia = calcularAutonomia(v);

        cout << "\n>> Desglose matematico de la unidad:\n";
        cout << "   - Unidad          : " << v.modelo << " (ID: " << v.id << ")\n";
        cout << "   - Capacidad (C)   : " << fixed << setprecision(2) << v.capacidadBateria << " kWh\n";
        cout << "   - Consumo (P)     : " << fixed << setprecision(2) << v.consumoPromedio << " kWh/100km\n";
        cout << "   - Operacion       : (" << v.capacidadBateria << " / " << v.consumoPromedio << ") * 100\n";
        cout << "   - Autonomia real  : " << fixed << setprecision(2) << autonomia << " km por carga completa.\n";
    } else {
        cout << "[!] Vehiculo con ID " << idBuscado << " no encontrado.\n";
    }

    // Cálculo adicional con acumulador para estadísticas generales de la flota
    float acumuladorAutonomia = 0.0f;
    for (int i = 0; i < total; i++) {
        acumuladorAutonomia += calcularAutonomia(flota[i]);
    }
    float promedioFlota = acumuladorAutonomia / total;
    cout << "\n>> Autonomia promedio de toda la flota (" << total << " unidades): " 
         << fixed << setprecision(2) << promedioFlota << " km.\n";
}

// =========================================================================================
// OPERACIÓN 7: GENERAR REPORTES
// =========================================================================================
void generarReportes(const Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "            MODULO DE REPORTES DE RENDIMIENTO\n";
    cout << "--------------------------------------------------------\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos en el sistema para generar reportes.\n";
        return;
    }

    cout << " [1] Reporte de vehiculos con AUTONOMIA BAJA (Autonomia < umbral)\n";
    cout << " [2] Reporte de vehiculos con ALTA DEMANDA (Viajes > umbral)\n";
    int subopcion = leerEnteroMayorIgual(" Seleccione tipo de reporte [1 o 2]: ", 1);

    if (subopcion == 1) {
        float umbralKm = leerFloatPositivo(" Ingrese umbral de autonomia minima en km: ");
        int encontrados = 0;

        cout << "\n>> VEHICULOS CON AUTONOMIA MENOR A " << fixed << setprecision(2) << umbralKm << " KM:\n";
        imprimirCabeceraTabla();

        for (int i = 0; i < total; i++) {
            if (calcularAutonomia(flota[i]) < umbralKm) {
                imprimirFilaVehiculo(flota[i]);
                encontrados++;
            }
        }
        cout << "+-----+----------------------+------------+------------+--------+------------------+----------------+\n";

        if (encontrados == 0) {
            cout << ">> Ningun vehiculo se encuentra por debajo del umbral indicado.\n";
        } else {
            cout << ">> Total de vehiculos identificados con autonomia baja: " << encontrados << "\n";
        }

    } else if (subopcion == 2) {
        int umbralViajes = leerEnteroMayorIgual(" Ingrese umbral minimo de viajes completados: ", 0);
        int encontrados = 0;

        cout << "\n>> VEHICULOS CON ALTA DEMANDA (VIAJES MAYOR A " << umbralViajes << "):\n";
        imprimirCabeceraTabla();

        for (int i = 0; i < total; i++) {
            if (flota[i].viajesRealizados > umbralViajes) {
                imprimirFilaVehiculo(flota[i]);
                encontrados++;
            }
        }
        cout << "+-----+----------------------+------------+------------+--------+------------------+----------------+\n";

        if (encontrados == 0) {
            cout << ">> No existen vehiculos que superen el umbral de viajes especificado.\n";
        } else {
            cout << ">> Total de vehiculos con alta demanda: " << encontrados << "\n";
        }
    } else {
        cout << "[!] Opcion de reporte invalida.\n";
    }
}

// =========================================================================================
// OPERACIÓN 8: CAMBIAR ESTADO DEL VEHÍCULO
// =========================================================================================
void cambiarEstadoVehiculo(Vehiculo flota[], int total) {
    cout << "--------------------------------------------------------\n";
    cout << "           CAMBIAR ESTADO DE OPERACION\n";
    cout << "--------------------------------------------------------\n";

    if (total == 0) {
        cout << "[!] No hay vehiculos registrados en la flota.\n";
        return;
    }

    int idBuscado = leerEntero(" Ingrese ID del vehiculo a modificar: ");
    int indice = buscarVehiculoPorId(flota, total, idBuscado);

    if (indice == -1) {
        cout << "[!] Vehiculo con ID " << idBuscado << " no encontrado en el sistema.\n";
        return;
    }

    cout << " Unidad seleccionada: " << flota[indice].modelo << " (ID: " << flota[indice].id << ")\n";
    cout << " Estado actual: " << (flota[indice].estado == 1 ? "[1] Disponible" : "[2] En mantenimiento") << "\n";

    int nuevoEstado = 0;
    while (true) {
        nuevoEstado = leerEntero(" Ingrese nuevo estado (1 = Disponible, 2 = En mantenimiento): ");
        if (nuevoEstado == 1 || nuevoEstado == 2) {
            break;
        }
        cout << "   [Error] Valor invalido. Debe seleccionar 1 o 2.\n";
    }

    flota[indice].estado = nuevoEstado;
    cout << "\n>> [Exito] Estado actualizado a: " 
         << (nuevoEstado == 1 ? "Disponible" : "En mantenimiento") << ".\n";
}

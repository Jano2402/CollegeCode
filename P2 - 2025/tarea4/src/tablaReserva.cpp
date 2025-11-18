#include "../include/tablaReserva.h"

// Estructura para los nodos de la lista enlazada en cada bucket
struct NodoTabla {
    int isbn;
    TColaDePrioridadReservas colaReservas;
    NodoTabla* siguiente;
};

// Estructura principal de la tabla
struct rep_tablaTablaReserva {
    NodoTabla** buckets;  // Array de listas enlazadas
    int tamaño;           // Tamaño de la tabla (max)
    int cantidad;         // Cantidad total de reservas
    int N;                // Parámetro N
};

// Función hash
static int calcularHash(int isbn, int tamaño) {
    return isbn % tamaño;
}

TTablaReserva crearTTablaReserva(int max, int N) {
    TTablaReserva nuevaTabla = new rep_tablaTablaReserva;
    nuevaTabla->tamaño = max;
    nuevaTabla->cantidad = 0;
    nuevaTabla->N = N;
    
    // Crear array de buckets
    nuevaTabla->buckets = new NodoTabla*[max];
    for (int i = 0; i < max; i++) {
        nuevaTabla->buckets[i] = NULL;
    }
    
    return nuevaTabla;
}

void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva) {
    int pos = calcularHash(isbn, tabla->tamaño);
    
    // Buscar si ya existe un nodo para este ISBN
    NodoTabla* actual = tabla->buckets[pos];
    NodoTabla* anterior = NULL;
    
    while (actual != NULL && actual->isbn != isbn) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual != NULL) {
        // El ISBN ya existe, insertar en su cola de prioridad
        insertarTColaDePrioridadReservas(actual->colaReservas, reserva);
    } else {
        // Crear nuevo nodo para el ISBN
        NodoTabla* nuevoNodo = new NodoTabla;
        nuevoNodo->isbn = isbn;
        nuevoNodo->colaReservas = crearTColaDePrioridadReservas(tabla->N);
        insertarTColaDePrioridadReservas(nuevoNodo->colaReservas, reserva);
        nuevoNodo->siguiente = NULL;
        
        // Insertar en la lista
        if (anterior == NULL) {
            tabla->buckets[pos] = nuevoNodo;
        } else {
            anterior->siguiente = nuevoNodo;
        }
    }
    
    tabla->cantidad++;
}

bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro) {
    int pos = calcularHash(isbnLibro, tabla->tamaño);
    NodoTabla* actual = tabla->buckets[pos];
    
    // Buscar el nodo con el ISBN
    while (actual != NULL && actual->isbn != isbnLibro) {
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        return false; // No existe el ISBN
    }
    
    // Verificar si existe una reserva con ese CI socio en la cola
    return estaTColaDePrioridadReservas(actual->colaReservas, ciSocio, isbnLibro);
}

TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn) {
    int pos = calcularHash(isbn, tabla->tamaño);
    NodoTabla* actual = tabla->buckets[pos];
    
    while (actual != NULL && actual->isbn != isbn) {
        actual = actual->siguiente;
    }
    
    // PRE: perteneceTTablaReserva(tabla, isbn) garantiza que actual != NULL
    return actual->colaReservas;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn) {
    int pos = calcularHash(isbn, tabla->tamaño);
    NodoTabla* actual = tabla->buckets[pos];
    
    while (actual != NULL && actual->isbn != isbn) {
        actual = actual->siguiente;
    }
    
    // PRE: perteneceTTablaReserva(tabla, isbn) garantiza que actual != NULL
    return prioritarioTColaDePrioridadReservas(actual->colaReservas);
}

void liberarTTablaReserva(TTablaReserva &tabla) {
    if (tabla == NULL) return;
    
    // Liberar todos los buckets y sus nodos
    for (int i = 0; i < tabla->tamaño; i++) {
        NodoTabla* actual = tabla->buckets[i];
        while (actual != NULL) {
            NodoTabla* siguiente = actual->siguiente;
            liberarTColaDePrioridadReservas(actual->colaReservas);
            delete actual;
            actual = siguiente;
        }
    }
    
    delete[] tabla->buckets;
    delete tabla;
    tabla = NULL;
}
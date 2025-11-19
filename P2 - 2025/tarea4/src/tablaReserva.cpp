#include "../include/tablaReserva.h"

struct NodoTabla {
    int isbn;
    TColaDePrioridadReservas colaReservas;
    NodoTabla* siguiente;
};

struct rep_tablaTablaReserva {
    NodoTabla** array;
    int tamaño;
    int cantidad;
    int N;
};

static int calcularHash(int isbn, int tamaño) {
    return isbn % tamaño;
}

TTablaReserva crearTTablaReserva(int max, int N) {
    TTablaReserva nuevaTabla = new rep_tablaTablaReserva;
    nuevaTabla->tamaño = max;
    nuevaTabla->cantidad = 0;
    nuevaTabla->N = N;
    nuevaTabla->array = new NodoTabla*[max];
    for (int i = 0; i < max; i++) {
        nuevaTabla->array[i] = NULL;
    }
    return nuevaTabla;
}

void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva) {
    int pos = calcularHash(isbn, tabla->tamaño);
    NodoTabla* actual = tabla->array[pos];
    NodoTabla* anterior = NULL;
    
    while (actual != NULL && actual->isbn != isbn) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != NULL) {
        insertarTColaDePrioridadReservas(actual->colaReservas, reserva);
    } else {
        NodoTabla* nuevoNodo = new NodoTabla;
        nuevoNodo->isbn = isbn;
        nuevoNodo->colaReservas = crearTColaDePrioridadReservas(tabla->N);
        insertarTColaDePrioridadReservas(nuevoNodo->colaReservas, reserva);
        nuevoNodo->siguiente = NULL;
        if (anterior == NULL) {
            tabla->array[pos] = nuevoNodo;
        } else {
            anterior->siguiente = nuevoNodo;
        }
    }
    tabla->cantidad++;
}

bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro) {
    int pos = calcularHash(isbnLibro, tabla->tamaño);
    NodoTabla* actual = tabla->array[pos];
    while (actual != NULL && actual->isbn != isbnLibro) {
        actual = actual->siguiente;
    }
    if (actual == NULL) {
        return false;
    }
    return estaTColaDePrioridadReservas(actual->colaReservas, ciSocio, isbnLibro);
}

TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn) {
    int pos = calcularHash(isbn, tabla->tamaño);
    NodoTabla* actual = tabla->array[pos];
    
    while (actual != NULL && actual->isbn != isbn) {
        actual = actual->siguiente;
    }
    return actual->colaReservas;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn) {
    int pos = calcularHash(isbn, tabla->tamaño);
    NodoTabla* actual = tabla->array[pos];
    
    while (actual != NULL && actual->isbn != isbn) {
        actual = actual->siguiente;
    }
    return prioritarioTColaDePrioridadReservas(actual->colaReservas);
}

void liberarTTablaReserva(TTablaReserva &tabla) {
    if (tabla == NULL) return;
    for (int i = 0; i < tabla->tamaño; i++) {
        NodoTabla* actual = tabla->array[i];
        while (actual != NULL) {
            NodoTabla* siguiente = actual->siguiente;
            liberarTColaDePrioridadReservas(actual->colaReservas);
            delete actual;
            actual = siguiente;
        }
    }
    
    delete[] tabla->array;
    delete tabla;
    tabla = NULL;
}
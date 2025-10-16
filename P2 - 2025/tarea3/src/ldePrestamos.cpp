#include "../include/ldePrestamos.h"

struct nodoDoble{
    TPrestamo prestamo;
    nodoDoble* next;
    nodoDoble* prev;
};

typedef struct nodoDoble *TNodoDoble;

struct rep_ldePrestamos {
    nodoDoble* inicio;
    nodoDoble* final;
    nat elementos;
};

TLDEPrestamos crearTLDEPrestamosVacia(){
    TLDEPrestamos prestamos = new rep_ldePrestamos;
    prestamos->inicio = NULL;
    prestamos->final = NULL;
    //
    prestamos->elementos = 0;
    return prestamos;
}

void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo){
    TNodoDoble nodo = new nodoDoble;
    nodo->prestamo = prestamo;
    nodo->next = NULL;
    nodo->prev = NULL;
    
    // si la lista está vacía conectamos el inicio y el final al nodo
    if (ldePrestamos->inicio == NULL) {
        ldePrestamos->inicio = nodo;
        ldePrestamos->final = nodo;
        //
        ldePrestamos->elementos++;
        return;
    }
    // si insertas al inicio
    if (compararTFechas(fechaRetiroTPrestamo(ldePrestamos->inicio->prestamo),fechaRetiroTPrestamo(prestamo)) == 1) {
        ldePrestamos->inicio->prev = nodo;
        nodo->next = ldePrestamos->inicio;
        ldePrestamos->inicio = nodo;
        //
        ldePrestamos->elementos++;
        return;
    }
    // recorrer la lista hasta encontrar un mayor
    TNodoDoble actual = ldePrestamos->inicio;
    while (actual->next != NULL && compararTFechas(fechaRetiroTPrestamo(actual->prestamo), fechaRetiroTPrestamo(prestamo)) != 1) {
        actual = actual->next;
    }
    // insertar luego del actual
    nodo->next = actual->next;
    nodo->prev = actual;
    actual->next = nodo;
    //
    ldePrestamos->elementos++;
    // si insertas al final
    if (nodo->next == NULL) {
        ldePrestamos->final = nodo;
    } else {
        nodo->next->prev = nodo;
    }
}

void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos){
    if (ldePrestamos == NULL) return;

    TNodoDoble actual = ldePrestamos->inicio;
    while (actual != NULL) {
        TNodoDoble aux = actual;
        actual = actual->next;
        liberarTPrestamo(aux->prestamo);
        delete aux;
    }
    delete ldePrestamos; 
    ldePrestamos = NULL;
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf("%s\n", "LDE Préstamos:");
    TNodoDoble actual = ldePrestamos->inicio;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->next;
    }
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf("%s\n", "LDE Préstamos:");
    TNodoDoble actual = ldePrestamos->final;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->prev;
    }
}

nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos){
    /*int count = 0;
    TNodoDoble actual = ldePrestamos->inicio;
    while (actual != NULL) {
        count++;
        actual = actual->next;
    }*/
    return ldePrestamos->elementos;
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->inicio->prestamo;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->final->prestamo;
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n){
    int count = 1;
    TNodoDoble actual = ldePrestamos->inicio;
    while (count < n && actual != NULL) {
        actual = actual->next;
        count++;
    }
    if (actual != NULL) {
        return actual->prestamo;
    }
    return NULL;
}

// criterio = 0 -> prestamos retornados
// criterio = 1 -> prestamos no retornados
TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio){
    TLDEPrestamos prestamosFiltrados = crearTLDEPrestamosVacia(); 
    TNodoDoble actual = ldePrestamos->inicio;
    
    if (criterio == 0) {
        while (actual != NULL) {
            if (fechaDevolucionTPrestamo(actual->prestamo) != NULL) {
                insertarTLDEPrestamos(prestamosFiltrados, copiarTPrestamo(actual->prestamo));
                prestamosFiltrados->elementos++;
            }
            actual = actual->next;
        }
    } else {
        while (actual != NULL) {
            if (fechaDevolucionTPrestamo(actual->prestamo) == NULL) {
                insertarTLDEPrestamos(prestamosFiltrados, copiarTPrestamo(actual->prestamo));
                prestamosFiltrados->elementos++;
            }
            actual = actual->next;
        }
    }
    return prestamosFiltrados;
}

// Funciones tarea 3

void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos) {
    if (ldePrestamos == NULL) return;

    TNodoDoble actual = ldePrestamos->inicio;
    while (actual != NULL) {
        TNodoDoble aux = actual;
        actual = actual->next;

        liberarTPrestamoSoloEstructura(aux->prestamo);

        delete aux;
    }

    delete ldePrestamos;
    ldePrestamos = NULL;
}

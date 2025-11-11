#include "../include/colaDePrioridadReservas.h"

struct rep_colaDePrioridadReservas {
    TReserva* reservas;
    int cantidad;
    int capacidad;
    bool esMinHeap;
};

TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    TColaDePrioridadReservas cola = new rep_colaDePrioridadReservas;
    cola->reservas = new TReserva[N];
    cola->cantidad = 0;
    cola->capacidad = N;
    cola->esMinHeap = true;
    return cola;
}

void flotarMinHeap(TColaDePrioridadReservas &cp, int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (rangoTSocio(socioTReserva(cp->reservas[indice])) < rangoTSocio(socioTReserva(cp->reservas[padre]))) {
            TReserva temp = cp->reservas[indice];
            cp->reservas[indice] = cp->reservas[padre];
            cp->reservas[padre] = temp;
            indice = padre;
        } else {
            break;
        }
    }
}

void flotarMaxHeap(TColaDePrioridadReservas &cp, int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (rangoTSocio(socioTReserva(cp->reservas[indice])) > rangoTSocio(socioTReserva(cp->reservas[padre]))) {
            TReserva temp = cp->reservas[indice];
            cp->reservas[indice] = cp->reservas[padre];
            cp->reservas[padre] = temp;
            indice = padre;
        } else {
            break;
        }
    }
}

void hundirMinHeap(TColaDePrioridadReservas &cp, int indice) {
    int n = cp->cantidad;
    while (2 * indice + 1 < n) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int menor = indice;

        if (hijoIzq < n && rangoTSocio(socioTReserva(cp->reservas[hijoIzq])) < rangoTSocio(socioTReserva(cp->reservas[menor]))) {
            menor = hijoIzq;
        }
        
        if (hijoDer < n && rangoTSocio(socioTReserva(cp->reservas[hijoDer])) < rangoTSocio(socioTReserva(cp->reservas[menor]))) {
            menor = hijoDer;
        }
        
        // Manejo de empates: seguir por izquierda
        if (menor == indice && hijoIzq < n && 
            rangoTSocio(socioTReserva(cp->reservas[hijoIzq])) == rangoTSocio(socioTReserva(cp->reservas[indice]))) {
            menor = hijoIzq;
        }

        if (menor != indice) {
            TReserva temp = cp->reservas[indice];
            cp->reservas[indice] = cp->reservas[menor];
            cp->reservas[menor] = temp;
            indice = menor;
        } else {
            break;
        }
    }
}

void hundirMaxHeap(TColaDePrioridadReservas &cp, int indice) {
    int n = cp->cantidad;
    while (2 * indice + 1 < n) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int mayor = indice;

        if (hijoIzq < n && rangoTSocio(socioTReserva(cp->reservas[hijoIzq])) > rangoTSocio(socioTReserva(cp->reservas[mayor]))) {
            mayor = hijoIzq;
        }
        
        if (hijoDer < n && rangoTSocio(socioTReserva(cp->reservas[hijoDer])) > rangoTSocio(socioTReserva(cp->reservas[mayor]))) {
            mayor = hijoDer;
        }
        
        // Manejo de empates: seguir por izquierda
        if (mayor == indice && hijoIzq < n && 
            rangoTSocio(socioTReserva(cp->reservas[hijoIzq])) == rangoTSocio(socioTReserva(cp->reservas[indice]))) {
            mayor = hijoIzq;
        }

        if (mayor != indice) {
            TReserva temp = cp->reservas[indice];
            cp->reservas[indice] = cp->reservas[mayor];
            cp->reservas[mayor] = temp;
            indice = mayor;
        } else {
            break;
        }
    }
}

// FUNCIÓN CRÍTICA CORREGIDA - INVERTIR EL ARRAY
void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp == NULL || cp->cantidad <= 1) return;

    // Cambiar el tipo de heap
    cp->esMinHeap = !cp->esMinHeap;

    // INVERTIR EL ARRAY literalmente
    for (int i = 0; i < cp->cantidad / 2; i++) {
        TReserva temp = cp->reservas[i];
        cp->reservas[i] = cp->reservas[cp->cantidad - 1 - i];
        cp->reservas[cp->cantidad - 1 - i] = temp;
    }

    // Reconstruir el heap después de invertir
    for (int i = cp->cantidad / 2 - 1; i >= 0; i--) {
        if (cp->esMinHeap) {
            hundirMinHeap(cp, i);
        } else {
            hundirMaxHeap(cp, i);
        }
    }
}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp != NULL) {
        for (int i = 0; i < cp->cantidad; i++) {
            liberarTReserva(cp->reservas[i]);
        }
        delete[] cp->reservas;
        delete cp;
        cp = NULL;
    }
}

void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {
    if (cp->cantidad < cp->capacidad) {
        cp->reservas[cp->cantidad] = reserva;
        cp->cantidad++;
        
        if (cp->esMinHeap) {
            flotarMinHeap(cp, cp->cantidad - 1);
        } else {
            flotarMaxHeap(cp, cp->cantidad - 1);
        }
    }
}

bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp == NULL || cp->cantidad == 0;
}

TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp->reservas[0];
}

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp == NULL || cp->cantidad == 0) return;

    liberarTReserva(cp->reservas[0]);
    
    if (cp->cantidad == 1) {
        cp->cantidad--;
        return;
    }
    
    cp->reservas[0] = cp->reservas[cp->cantidad - 1];
    cp->cantidad--;
    
    if (cp->esMinHeap) {
        hundirMinHeap(cp, 0);
    } else {
        hundirMaxHeap(cp, 0);
    }
}

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    for (int i = 0; i < cp->cantidad; i++) {
        if (ciTSocio(socioTReserva(cp->reservas[i])) == ciSocio && 
            isbnTLibro(libroTReserva(cp->reservas[i])) == isbnLibro) {
            return true;
        }
    }
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    for (int i = 0; i < cp->cantidad; i++) {
        if (ciTSocio(socioTReserva(cp->reservas[i])) == ciSocio && 
            isbnTLibro(libroTReserva(cp->reservas[i])) == isbnLibro) {
            return rangoTSocio(socioTReserva(cp->reservas[i]));
        }
    }
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    TColaDePrioridadReservas copia = crearTColaDePrioridadReservas(cp->capacidad);
    copia->cantidad = cp->cantidad;
    copia->esMinHeap = cp->esMinHeap;
    
    for (int i = 0; i < cp->cantidad; i++) {
        copia->reservas[i] = copiarTReserva(cp->reservas[i]);
    }
    
    return copia;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {
    if (cp == NULL || cp->cantidad == 0) return;
    for (int i = 0; i < cp->cantidad; i++) {
        imprimirTReserva(cp->reservas[i]);
    }
}
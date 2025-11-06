#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.

struct rep_colaDePrioridadReservas {
    TReserva* reservas;
    int cantidad;
};

TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    TColaDePrioridadReservas cola = new rep_colaDePrioridadReservas;
    cola->reservas = new TReserva[N];
    cola->cantidad = 0;
    return cola;
}

void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    
}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
  for (int i = 0; i < cp->cantidad; i++) {
    liberarTReserva(cp->reservas[i]);
  }
  delete[] cp->reservas;
  delete cp;
  cp = NULL;
}

void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {
    int i = cp->cantidad;
    cp->reservas[i] = reserva;
    cp->cantidad;

    while (i > 0) {
      int padre = (i - 1) / 2;
      if (rangoTSocio(socioTReserva(cp->reservas[i])) < rangoTSocio(socioTReserva(cp->reservas[padre]))){
        TReserva tmp = cp->reservas[i];
        cp->reservas[i] = cp->reservas[padre];
        cp->reservas[padre] = tmp;
        i = padre;
      } else {
        break;
      }
    }
}

bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    if (cp->cantidad == 0) return true;
    return false;
}

TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp == NULL || cp->cantidad == 0) return;

    int hijoIzq, hijoDer, menor;
    int n = cp->cantidad;

    liberarTReserva(cp-reservas[0]);
    cp->reservas[0] = cp->reservas[cp->cantidad - 1];
    cp->cantidad--;

    if (cp->cantidad > 0) {
        while (2 * 0 /*indice*/ + 1 < n) {
            hijoIzq = 2 * 0 + 1;
            hijoDer = 2 * 0 + 2;
            menor = 0;

            if (hijoIzq < n && socioTReserva(rangoTSocio(cp->reservas[hijoIzq])) < socioTReserva(rangoTSocio(cp->reservas[menor]))) {
                menor = hijoIzq;
            }
            if (hijoDer < n && socioTReserva(rangoTSocio(cp->reservas[hijoDer])) < socioTReserva(rangoTSocio(cp->reservas[menor]))) {
                menor = hijoDer;
            }

            if (menor != 0) {
              TReserva tmp = cp->reservas[0];
              cp->reservas[0] = cp->reservas[menor];
              cp->reservas[menor] = tmp;
              indice = menor;
            } else {
              break;
            }
        }
    }
}

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {

}



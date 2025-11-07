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
    cp->cantidad++;

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
    return cp->reservas[0];
}

// función auxiliar
void hundirTColaDePrioridadReservasMinHeap(TColaDePrioridadReservas &cp, int indice) {
    int hijoIzq, hijoDer, menor;
    int n = cp->cantidad;

    if (cp->cantidad > 0) {
      while (2 * indice + 1 < n) {
        hijoIzq = 2 * indice + 1;
        hijoDer = 2 * indice + 2;
        menor = indice;

        if (hijoIzq < n && rangoTSocio(socioTReserva(cp->reservas[hijoIzq])) < rangoTSocio(socioTReserva(cp->reservas[menor]))) {
          menor = hijoIzq;
        }
        if (hijoDer < n && rangoTSocio(socioTReserva(cp->reservas[hijoDer])) < rangoTSocio(socioTReserva(cp->reservas[menor]))) {
          menor = hijoDer;
        }

        if (menor != indice) {
          TReserva tmp = cp->reservas[indice];
          cp->reservas[indice] = cp->reservas[menor];
          cp->reservas[menor] = tmp;
          indice = menor;
        } else {
          break;
        }
      }
    }
}
// termina función auxiliar

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp == NULL || cp->cantidad == 0) return;

    liberarTReserva(cp->reservas[0]);
    cp->reservas[0] = cp->reservas[cp->cantidad - 1];
    cp->cantidad--;

    hundirTColaDePrioridadReservasMinHeap(cp, 0);
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



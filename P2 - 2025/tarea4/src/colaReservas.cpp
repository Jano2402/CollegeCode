#include "../include/colaReservas.h"

typedef struct Nodo {
  TReserva reserva;
  struct Nodo *siguiente;
} Nodo;

struct rep_colaReservas {
  Nodo *frente;
  Nodo *final;
  nat cantidad;
};

TColaReservas crearTColaReservas(){
  TColaReservas cola = new rep_colaReservas;
  cola->frente = NULL;
  cola->final = NULL;
  cola->cantidad = 0;
  return cola;
}

void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva) {
  if (colaReservas == NULL) {
    colaReservas = new rep_colaReservas;
    colaReservas->frente = colaReservas->final = NULL;
  }

  Nodo *nuevo = new Nodo;
  nuevo->reserva = reserva;
  nuevo->siguiente = NULL;

  if (colaReservas->frente == NULL) {
    colaReservas->frente = colaReservas->final = nuevo;
    colaReservas->cantidad++;
  } else {
    colaReservas->final->siguiente = nuevo;
    colaReservas->final = nuevo;
    colaReservas->cantidad++;
  }
}

void desencolarTColaReservas(TColaReservas &colaReservas) {
  // Precondición: cantidadTColaReservas(colaReservas) > 0
  // Pero igual validamos por seguridad
  if (colaReservas == NULL || colaReservas->frente == NULL) return;

  Nodo *aBorrar = colaReservas->frente;
  colaReservas->frente = aBorrar->siguiente;

  // liberar la reserva contenida
  liberarTReserva(aBorrar->reserva);
  delete aBorrar;
  colaReservas->cantidad--;

  // Si la cola quedó vacía, final debe quedar en NULL
  if (colaReservas->frente == NULL)
    colaReservas->final = NULL;
}

TReserva frenteTColaReservas(TColaReservas colaReservas) {
    return colaReservas->frente->reserva;
}

nat cantidadTColaReservas(TColaReservas colaReservas){
    return colaReservas->cantidad;
}

void imprimirTColaReservas(TColaReservas colaReservas) {
  printf("Cola de Reservas:\n");
  if (colaReservas == NULL || colaReservas->frente == NULL) {
    return;
  }

  Nodo *actual = colaReservas->frente;
  while (actual != NULL) {
    imprimirTReserva(actual->reserva);
    actual = actual->siguiente; // avanzar al siguiente nodo
  }
}

void liberarTColaReservas(TColaReservas &colaReservas) {
  if (colaReservas == NULL) return;

  Nodo *actual = colaReservas->frente;
  while (actual != NULL) {
    Nodo *aBorrar = actual;
    actual = actual->siguiente;

    liberarTReserva(aBorrar->reserva);
    delete aBorrar;
  }

  delete colaReservas;
  colaReservas = NULL;
}

TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas) {
  TReserva reserva = colaReservas->frente->reserva;
  Nodo *aBorrar = colaReservas->frente;
  colaReservas->frente = colaReservas->frente->siguiente;
  delete aBorrar;
  aBorrar = NULL;
  return reserva;
}

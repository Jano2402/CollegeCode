#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros{
  int *conjuntoGeneros;
  int tope;
  int cantMax;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  TConjuntoGeneros conjuntoGeneros = new rep_conjuntogeneros;
  conjuntoGeneros->conjuntoGeneros = new int[cantMax];
  for (int i = 0; i < cantMax; i++) {
    conjuntoGeneros->conjuntoGeneros[i] = -1;
  }
  conjuntoGeneros->tope = 0;
  conjuntoGeneros->cantMax = cantMax;
  return conjuntoGeneros;
}

bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  return (c->tope == 0);
}

void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (id >= 0 && id < c->cantMax && c->conjuntoGeneros[id] == -1) {
    c->conjuntoGeneros[id] = id;
    c->tope++;
  }
}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (c->conjuntoGeneros[id] != -1) {
    c->conjuntoGeneros[id] = -1;
    c->tope--;
  }
}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  if (id < 0 || id >= c->cantMax) return false;
  return (c->conjuntoGeneros[id] != -1);
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  return c->tope;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantMax;
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c){
  bool primero = true;
  for (int i = 0; i < c->cantMax; i++) {
    if (c->conjuntoGeneros[i] != -1) {
      if (!primero) printf(" ");
      printf("%i", c->conjuntoGeneros[i]);
      primero = false;
    }
  }
  printf("\n");
}

void liberarTConjuntoGeneros(TConjuntoGeneros &c){
  delete[] c->conjuntoGeneros;
  delete c;
  c = NULL;
}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros unionConjuntos = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->conjuntoGeneros[i] == -1 && c2->conjuntoGeneros[i] == -1) {
      unionConjuntos->conjuntoGeneros[i] = -1;
    } else if (c1->conjuntoGeneros[i] == c2->conjuntoGeneros[i]) {
      unionConjuntos->conjuntoGeneros[i] = c1->conjuntoGeneros[i];
    } else if (c1->conjuntoGeneros[i] == -1 && c2->conjuntoGeneros[i] != -1) {
      unionConjuntos->conjuntoGeneros[i] = c2->conjuntoGeneros[i];
    } else {
      unionConjuntos->conjuntoGeneros[i] = c1->conjuntoGeneros[i];
    }
  };
  return unionConjuntos;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros interseccion = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->conjuntoGeneros[i] == c2->conjuntoGeneros[i]) {
      interseccion->conjuntoGeneros[i] = c1->conjuntoGeneros[i];
    }
  }
  return interseccion;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros diferencia = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->conjuntoGeneros[i] == c2->conjuntoGeneros[i]) {
      diferencia->conjuntoGeneros[i] = -1;
    } else {
      diferencia->conjuntoGeneros[i] = c1->conjuntoGeneros[i];
    }
  }
  return diferencia;
}

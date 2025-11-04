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
    // Use the larger cantMax to avoid out-of-bounds access
    int maxCant = (c1->cantMax > c2->cantMax) ? c1->cantMax : c2->cantMax;
    TConjuntoGeneros unionConjuntos = crearTConjuntoGeneros(maxCant);
    
    // Copy all elements from c1
    for (int i = 0; i < c1->cantMax; i++) {
        if (c1->conjuntoGeneros[i] != -1) {
            insertarTConjuntoGeneros(unionConjuntos, i);
        }
    }
    
    // Copy all elements from c2
    for (int i = 0; i < c2->cantMax; i++) {
        if (c2->conjuntoGeneros[i] != -1) {
            insertarTConjuntoGeneros(unionConjuntos, i);
        }
    }
    
    return unionConjuntos;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
    int maxCant = (c1->cantMax > c2->cantMax) ? c1->cantMax : c2->cantMax;
    TConjuntoGeneros interseccion = crearTConjuntoGeneros(maxCant);
    
    for (int i = 0; i < maxCant; i++) {
        if (i < c1->cantMax && i < c2->cantMax && 
            c1->conjuntoGeneros[i] != -1 && c2->conjuntoGeneros[i] != -1) {
            insertarTConjuntoGeneros(interseccion, i);
        }
    }
    
    return interseccion;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
    TConjuntoGeneros diferencia = crearTConjuntoGeneros(c1->cantMax);
    
    for (int i = 0; i < c1->cantMax; i++) {
        if (c1->conjuntoGeneros[i] != -1 && 
            (i >= c2->cantMax || c2->conjuntoGeneros[i] == -1)) {
            insertarTConjuntoGeneros(diferencia, i);
        }
    }
    
    return diferencia;
}
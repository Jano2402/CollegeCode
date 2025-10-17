
#include "../include/agGeneros.h"
#include <assert.h>


struct rep_agGeneros {
  int identificador;
  char nombre[MAX_NOMBRE];
  TAGGeneros hijo;
  TAGGeneros hermano;
};

TAGGeneros crearTAGGeneros(){
  return NULL;
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
  if (idGeneroPadre == -1 && arbolGeneros == NULL) {
    arbolGeneros = new rep_agGeneros;
    arbolGeneros->identificador = idGenero;
    strcpy(arbolGeneros->nombre, nombreGenero);
    arbolGeneros->hijo = NULL;
    arbolGeneros->hermano = NULL;
    return;
  } 
  if (arbolGeneros == NULL) return;
  if (arbolGeneros->identificador == idGeneroPadre) {
    TAGGeneros hijo = new rep_agGeneros;
    hijo->hermano = NULL;
    hijo->hijo = NULL;
    hijo->identificador = idGenero;
    strcpy(hijo->nombre, nombreGenero);
    hijo->hermano = arbolGeneros->hijo;
    arbolGeneros->hijo = hijo;
    return;
  }
  insertarGeneroTAGGeneros(arbolGeneros->hijo, idGeneroPadre, idGenero, nombreGenero);
  insertarGeneroTAGGeneros(arbolGeneros->hermano, idGeneroPadre, idGenero, nombreGenero);
}

// Usando recursión ( No se si se permite )
void imprimirRecursivo(TAGGeneros nodo, int nivel);

void imprimirRecursivo(TAGGeneros nodo, int nivel) {
    if (nodo == NULL) return;

    // Imprimir indentación
    for (int i = 0; i < nivel; i++) printf("    ");

    // Imprimir nodo actual
    printf("%d - %s\n", nodo->identificador, nodo->nombre);

    // Imprimir hijos con nivel aumentado
    imprimirRecursivo(nodo->hijo, nivel + 1);

    // Imprimir hermanos al mismo nivel
    imprimirRecursivo(nodo->hermano, nivel);
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
    printf("Árbol de géneros:\n");
    imprimirRecursivo(arbolGeneros, 0);
}
//

void liberarTAGGeneros(TAGGeneros &arbolGeneros) {
  if (arbolGeneros == NULL) return;

  // Guardar punteros antes de borrar
  TAGGeneros hijo = arbolGeneros->hijo;
  TAGGeneros hermano = arbolGeneros->hermano;

  liberarTAGGeneros(hijo);     // liberar hijos
  liberarTAGGeneros(hermano);  // liberar hermanos

  delete arbolGeneros;
  arbolGeneros = NULL;
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  if (arbolGeneros == NULL) return false;  // caso base

  if (arbolGeneros->identificador == idGenero)
    return true;

  // Buscar en los hijos o hermanos
  return existeGeneroTAGGeneros(arbolGeneros->hijo, idGenero) ||
         existeGeneroTAGGeneros(arbolGeneros->hermano, idGenero);
}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  if (arbolGeneros == NULL) return NULL;
  if (arbolGeneros->identificador == idGenero) {
    return arbolGeneros->nombre;
  }
  char* resultadoHijo = nombreGeneroTAGGeneros(arbolGeneros->hijo, idGenero);
  if (resultadoHijo != NULL) {
    return resultadoHijo;
  }
  char* resultadoHer = nombreGeneroTAGGeneros(arbolGeneros->hermano, idGenero);
  if (resultadoHer != NULL) {
    return resultadoHer;
  }
  return NULL;
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
  int hijos = alturaTAGGeneros(arbolGeneros->hijo);
  int hermanos = alturaTAGGeneros(arbolGeneros->hermano);
  return 1 + (hijos > hermanos ? hijos : hermanos);
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
  return 1 + cantidadTAGGeneros(arbolGeneros->hijo) + cantidadTAGGeneros(arbolGeneros->hermano);
}

TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
  return NULL;
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
  return NULL;
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
  return 0;
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero){
}

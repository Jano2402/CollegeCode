
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

void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
  static int nivel = -1; // -1 para que el primer nodo (raíz) empiece en 0

  if (arbolGeneros == NULL) return;

  // Si es la primera llamada, imprimimos el título
  if (nivel == -1) {
    printf("Árbol de géneros:\n");
    nivel = 0;
  }

  // Imprimir indentación
  for (int i = 0; i < nivel; i++) printf("    ");

  // Imprimir el nodo actual
  printf("%d - %s\n", arbolGeneros->identificador, arbolGeneros->nombre);

  // Imprimir hijos (aumentando nivel)
  nivel++;
  imprimirTAGGeneros(arbolGeneros->hijo);
  nivel--;

  // Imprimir hermanos (mismo nivel)
  imprimirTAGGeneros(arbolGeneros->hermano);

  // Si volvimos al nivel raíz, reiniciar para futuras llamadas
  if (nivel == 0) nivel = -1;
}

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
  
}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  return NULL;
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros){
  return 0;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  return 0;
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

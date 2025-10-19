
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

nat alturaTAGGeneros(TAGGeneros arbolGeneros) {
  if (arbolGeneros == NULL) return 0;
  int alturaHijo = 1 + alturaTAGGeneros(arbolGeneros->hijo);
  int alturaHermano = alturaTAGGeneros(arbolGeneros->hermano);
  return (alturaHijo > alturaHermano) ? alturaHijo : alturaHermano;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
  return 1 + cantidadTAGGeneros(arbolGeneros->hijo) + cantidadTAGGeneros(arbolGeneros->hermano);
}

TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
  if (arbolGeneros == NULL) return NULL;
  if (arbolGeneros->identificador == idGenero) return arbolGeneros;

  TAGGeneros encontrado = obtenerSubarbolTAGGeneros(arbolGeneros->hijo, idGenero);
  if (encontrado) return encontrado;

  return obtenerSubarbolTAGGeneros(arbolGeneros->hermano, idGenero);
}

// auxiliar para obtenerConjuntoGeneros
void agregarDescendientes(TAGGeneros nodo, TConjuntoGeneros &conjunto) {
    if (nodo == NULL) return;
    
    insertarTConjuntoGeneros(conjunto, nodo->identificador);
    
    // Agregar todos los hijos recursivamente
    agregarDescendientes(nodo->hijo, conjunto);
    agregarDescendientes(nodo->hermano, conjunto);
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
    // Encontrar el nodo que contiene el género buscado
    TAGGeneros nodoBuscado = obtenerSubarbolTAGGeneros(arbolGeneros, idGenero);
    
    if (nodoBuscado == NULL) {
        return crearTConjuntoGeneros(0); // Género no encontrado
    }
    
    // Calcular tamaño necesario para el conjunto
    int maxId = obtenerMaxTAGGeneros(nodoBuscado);
    TConjuntoGeneros resultado = crearTConjuntoGeneros(maxId + 1);
    
    // Agregar todos los descendientes al conjunto
    agregarDescendientes(nodoBuscado, resultado);
    
    return resultado;
}

// auxiliar para ObtenerMaxTAGGeneros
int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c; // si no fueron mayores los anteriores, este es el mayor
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
  if (arbolGeneros == NULL) return -1;
  int maxHijo = obtenerMaxTAGGeneros(arbolGeneros->hijo);
  int maxHer = obtenerMaxTAGGeneros(arbolGeneros->hermano);
  return max(arbolGeneros->identificador, maxHijo, maxHer);
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero){
  if (arbolGeneros == NULL) return;
  if (arbolGeneros->identificador == idGenero) {
    TAGGeneros temp = arbolGeneros->hermano;
    liberarTAGGeneros(arbolGeneros->hijo);
    delete arbolGeneros;
    arbolGeneros = temp;
    return;
  }
  removerGeneroTAGGeneros(arbolGeneros->hijo, idGenero);
  removerGeneroTAGGeneros(arbolGeneros->hermano, idGenero);
}

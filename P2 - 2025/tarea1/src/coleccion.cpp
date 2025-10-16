#include "../include/coleccion.h"

struct rep_coleccion {
    TLibro coleccion[MAX_LIBROS];
    int tope;
};


// Función para crear una TColeccion vacía que puede almacenar hasta MAX_LIBROS libros. 
TColeccion crearTColeccion(){
    TColeccion coleccion = new rep_coleccion;
    coleccion->tope = 0;
    return coleccion;
}

// Función para liberar la memoria asociada a una colección de libros. 
// Recibe una referencia a un elemento de tipo TColeccion y libera su memoria
// Debe liberar además la memoria de cada uno de los libros de la colección. 
void liberarTColeccion(TColeccion& c){
    for (int i = 0; i < c->tope; i++) {
        liberarTLibro(c->coleccion[i]);
    }
    delete c;
    c = NULL;
}

// Función para agregar un nuevo libro 'l' a la colección 'l'
// Recibe un elemento de tipo TColeccion y un elemento de tipo TLibro y lo agrega a la colección en orden por fecha de edición (de menor a mayor)
// Si dos libros tienen la misma fecha de edición, deben ordenarse por orden de ingreso a la colección, 
// quedando antes el último de ellos en ser ingresado (de más reciente a más antiguo). 
// Si la cantidad de libros en la colección es igual a MAX_LIBROS, la función no tiene efecto
void agregarEnTColeccion(TColeccion& c, TLibro l){
    if (c->tope < MAX_LIBROS) {
        int i = c->tope;
        while (i > 0 && compararTFechas(fechaEdicionTLibro(c->coleccion[i - 1]), fechaEdicionTLibro(l)) > 0) {
            c->coleccion[i] = c->coleccion[i - 1];
            i--;
        }
        c->coleccion[i] = l;
        c->tope = c->tope + 1;
    } 
}

// Función para imprimir la información de todos los libros en la colección
// Recibe un elemento de tipo TColeccion e imprime la información de sus libros
// en orden cronológico por fecha de edición (el orden en el que aparecen en la colección). 
// El formato en el que se debe imprimir la información de la colección es utilizando de 
// forma secuencial la función imprimirTLibro
// 
// Colección de libros:
// Libro <isbn 1> 
// Título: <título 1>
// Autor: <nombre autor 1> <apellido autor 1>
// Descripción: <descripcion 1>
// Género: <id género 1>
// Fecha de edición: <fecha de edición 1>
// Libro <isbn 2> 
// Título: <título 2>
// Autor: <nombre autor 2> <apellido autor 2>
// Descripción: <descripcion 2>
// Género: <id género 2>
// Fecha de edición: <fecha de edición 2>
// .... 
// Si la colección está vacía solo imprime el cabezal.
void imprimirTColeccion(TColeccion c){
    for (int i = 0; i < c->tope; i++) {
        imprimirTLibro(c->coleccion[i]);
    }
}

// Función para verificar si un libro con isbn 'isbn' existe en la colección 'c' 
// Recibe una colección c y un isbn y retorna true si y solo si la colección c contiene
// un libro con isbn 'isbn'
bool estaEnTColeccion(TColeccion c, int isbn){
    int i = 0;
    while (i < c->tope && isbnTLibro(c->coleccion[i]) != isbn) {
        i++;
    }
    if ( i < c->tope ) return true; 
    else return false;
}

// Función para obtener un libro de una colección
// Recibe una colección y un isbn y regresa el libro con ese isbn
// El libro retornado comparte memoria con el parámetro. 
// PRE: El libro debe estar en la colección
TLibro obtenerDeTColeccion(TColeccion c, int isbn){
    if(estaEnTColeccion(c, isbn)) {
        int i = 0;
        while (i < c->tope && isbnTLibro(c->coleccion[i]) != isbn) {
            i++;
        }
        return c->coleccion[i];
    } else {
        return NULL;
    }
}

// Función que retorna true si y solo si existe algún libro en la colección editado 
// el día de la fecha pasada por parámetro.
// La función debe ejecutar un algoritmo de búsqueda binaria.
bool existenLibrosFechaTColeccion(TColeccion c, TFecha f){
    int inicio = 0;
    int mitad = 0;
    int final = c->tope - 1;
    while (inicio <= final) {
        mitad = (int)((inicio + final) / 2);

        if (compararTFechas(f, fechaEdicionTLibro(c->coleccion[mitad])) == 0) {
            return true;
        } else if (compararTFechas(f, fechaEdicionTLibro(c->coleccion[mitad])) > 0) {
            inicio = mitad + 1;
        } else {
            final = mitad - 1;
        }
    }
    return false;
}

// Función para imprimir todos los libros de una colección con el género pasado por parámetro.
// Recibe una colección y un género e imprime la información de los libros con dicho género,
// ordenados por orden de inserción en la colección (en el orden en que aparecen en la colección)
// Si no hay libros con dicho género, no imprime nada.
void imprimirLibrosGeneroTColeccion(TColeccion c, int idGenero){
    for (int i = 0; i < c->tope; i++) {
        if (idGeneroTLibro(c->coleccion[i]) == idGenero) {
            imprimirTLibro(c->coleccion[i]);
        }
    }
}

// Función para remover un libro de una colección
// Recibe una coleccón y el isbn del libro y remueve el libro con ese isbn de la colección.
// PRE: El libro debe pertenecer a la colección
void removerDeTColeccion(TColeccion& c, int isbn){
    int i = 0;
    while (i < c->tope && isbnTLibro(c->coleccion[i]) != isbn) i++;
    liberarTLibro(c->coleccion[i]);
    c->coleccion[i] = NULL;
    while(i < c->tope - 1) {
        c->coleccion[i] = c->coleccion[i + 1];
        i++;
    }
    
    c->tope--;
}
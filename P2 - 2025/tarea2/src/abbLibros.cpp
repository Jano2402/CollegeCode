#include "../include/abbLibros.h"

struct rep_abbLibros {
    TLibro libro;
    TABBLibros izq;
    TABBLibros der;
};

TABBLibros crearTABBLibrosVacio(){
    return NULL;
}

void insertarLibroTABBLibros(TABBLibros &abbLibros, TLibro libro){
    if (abbLibros == NULL) {
        abbLibros = new rep_abbLibros;
        abbLibros->libro = libro;
        abbLibros->der = NULL;
        abbLibros->izq = NULL;
        return;
    }
    if (isbnTLibro(libro) < isbnTLibro(abbLibros->libro)) {
        insertarLibroTABBLibros(abbLibros->izq, libro);
    } else {
        insertarLibroTABBLibros(abbLibros->der, libro);
    }
}

void imprimirTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) {
        return;
    }
    imprimirTABBLibros(abbLibros->izq);
    imprimirTLibro(abbLibros->libro);
    imprimirTABBLibros(abbLibros->der);
}

void liberarTABBLibros(TABBLibros &abbLibros){
    if (abbLibros == NULL) {
        return;
    }
    liberarTABBLibros(abbLibros->izq);
    liberarTABBLibros(abbLibros->der);
    liberarTLibro(abbLibros->libro);
    delete abbLibros;
    abbLibros = NULL;
}

bool existeLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (abbLibros == NULL) return false;

    if (isbnTLibro(abbLibros->libro) == isbn) return true;
    
    if (isbn < isbnTLibro(abbLibros->libro))
        return existeLibroTABBLibros(abbLibros->izq, isbn);
    else
        return existeLibroTABBLibros(abbLibros->der, isbn);
}

TLibro obtenerLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (isbnTLibro(abbLibros->libro) == isbn) {
        return abbLibros->libro;
    }
    if (isbn < isbnTLibro(abbLibros->libro)) {
        return obtenerLibroTABBLibros(abbLibros->izq, isbn);
    } else {
        return obtenerLibroTABBLibros(abbLibros->der, isbn);
    }
}

nat alturaTABBLibros(TABBLibros abbLibros) {
    if (abbLibros == NULL) {
        return 0;
    }
    int izq = alturaTABBLibros(abbLibros->izq);
    int der = alturaTABBLibros(abbLibros->der);
    return 1 + (izq > der ? izq : der);
}

TLibro maxISBNLibroTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) {
        return NULL;
    }
    if (abbLibros->der == NULL) {
        return abbLibros->libro; 
    }
    return (maxISBNLibroTABBLibros(abbLibros->der));
}

void removerLibroTABBLibros(TABBLibros &abbLibros, int isbn){
    if (abbLibros == NULL) {
        return;
    }
    if (isbn < isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->izq, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->der, isbn);
    } else {
        if (abbLibros->izq == NULL && abbLibros->der == NULL) {
            liberarTABBLibros(abbLibros);
        } else if (abbLibros->izq == NULL) {
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->der;
            liberarTLibro(temp->libro);
            delete temp;
            temp = NULL;
        } else if (abbLibros->der == NULL) {
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->izq;
            liberarTLibro(temp->libro);
            delete temp;
            temp = NULL;
        } else {
            TABBLibros predecesor = abbLibros->izq; 
            while (predecesor->der != NULL) {
                predecesor = predecesor->der;
            }
            liberarTLibro(abbLibros->libro);
            abbLibros->libro = copiarTLibro(predecesor->libro);
            removerLibroTABBLibros(abbLibros->izq, isbnTLibro(predecesor->libro));
        } 
    }
}

int cantidadTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) {
        return 0;
    }

    return 1 + cantidadTABBLibros(abbLibros->izq) + cantidadTABBLibros(abbLibros->der);
}

void obtenerNesimoLibroTABBLibrosAux(TABBLibros abbLibros, int n, int &k, TLibro &res){
}

TLibro obtenerNesimoLibroTABBLibros(TABBLibros abbLibros, int n) {
    if (abbLibros == NULL) {
        return NULL;
    }

    int k = cantidadTABBLibros(abbLibros->izq);

    if (n == k + 1) {
        return abbLibros->libro;
    } else if (n <= k) {
        return obtenerNesimoLibroTABBLibros(abbLibros->izq, n);
    } else {
        return obtenerNesimoLibroTABBLibros(abbLibros->der, n - k - 1);
    }
}

void insertarTodos(TABBLibros &destino, TABBLibros origen) {
    if (origen == NULL) return;
    insertarLibroTABBLibros(destino, copiarTLibro(origen->libro));
    insertarTodos(destino, origen->izq);
    insertarTodos(destino, origen->der);
}

TABBLibros filtradoPorGeneroTABBLibros(TABBLibros abbLibros, int genero) {
    if (abbLibros == NULL) {
        return NULL;
    }

    TABBLibros nuevo = NULL;

    if (idGeneroTLibro(abbLibros->libro) == genero) {
        insertarLibroTABBLibros(nuevo, copiarTLibro(abbLibros->libro));
    }

    TABBLibros izqFilter = filtradoPorGeneroTABBLibros(abbLibros->izq, genero);
    TABBLibros derFilter = filtradoPorGeneroTABBLibros(abbLibros->der, genero);

    insertarTodos(nuevo, izqFilter);
    liberarTABBLibros(izqFilter);
    insertarTodos(nuevo, derFilter);
    liberarTABBLibros(derFilter);

    return nuevo;
}
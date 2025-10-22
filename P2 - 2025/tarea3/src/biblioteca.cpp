#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
  TABBLibros libros;
  TLSESocios socios;
  TLDEPrestamos prestamos;
  TAGGeneros generos;
  TColaReservas reservas;
};

TBiblioteca crearTBiblioteca(){
  TBiblioteca b = new rep_biblioteca;
  b->libros = crearTABBLibrosVacio();
  b->socios = crearTLSESociosVacia();
  b->prestamos = crearTLDEPrestamosVacia();
  b->generos = crearTAGGeneros();
  b->reservas = crearTColaReservas();
  return b;
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
  assert(biblioteca != NULL);
  insertarGeneroTAGGeneros(biblioteca->generos, idGeneroPadre, idGenero, nombreGenero);
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){
  assert(biblioteca != NULL);
  insertarLibroTABBLibros(biblioteca->libros, libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){
  assert(biblioteca != NULL);
  insertarTLSESocios(biblioteca->socios, socio);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
  assert(biblioteca != NULL);
  TSocio socio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);
  TSocio sCop = copiarTSocio(socio);
  TLibro lCop = copiarTLibro(libro);
  TPrestamo prestamo = crearTPrestamo(sCop, lCop, fechaPrestamo);
  insertarTLDEPrestamos(biblioteca->prestamos, prestamo);
}

bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
  if (!biblioteca) return false;
  if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro)) return false;
  nat p = cantidadTLDEPrestamos(biblioteca->prestamos);
  for (nat i = 1; i <= p; ++i) {
      TPrestamo pr = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);
      if (isbnTLibro(libroTPrestamo(pr)) == isbnLibro && !fueRetornadoTPrestamo(pr)) {
          return false;
      }
  }
  return true;
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){
  assert(biblioteca != NULL);
  TSocio socio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);
  TReserva r = crearTReserva(copiarTSocio(socio), copiarTLibro(libro));
  encolarTColaReservas(biblioteca->reservas, r);
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
  assert(biblioteca != NULL);
  nat p = cantidadTLDEPrestamos(biblioteca->prestamos);
  for (nat i = 1; i <= p; ++i) {
      TPrestamo pr = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);
      if (ciTSocio(socioTPrestamo(pr)) == ciSocio &&
          isbnTLibro(libroTPrestamo(pr)) == isbnLibro &&
          compararTFechas(fechaRetiroTPrestamo(pr), fechaPrestamo) == 0) {
          actualizarFechaDevolucionTPrestamo(pr, fechaDevolucion);
          return;
      }
  }
}

void imprimirSociosTBiblioteca(TBiblioteca biblioteca){
  if (!biblioteca) return;
  imprimirTLSESocios(biblioteca->socios);
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){
  if (!biblioteca) return;
  imprimirTABBLibros(biblioteca->libros);
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
  if (!biblioteca) return;
  imprimirTColaReservas(biblioteca->reservas);
}

void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
  if (!biblioteca) return;
  imprimirTLDEPrestamos(biblioteca->prestamos);
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
  if (!biblioteca) return crearTABBLibrosVacio();
  TConjuntoGeneros conj = obtenerConjuntoGeneros(biblioteca->generos, idGenero);
  TABBLibros res = crearTABBLibrosVacio();
  int n = cantidadTABBLibros(biblioteca->libros);
  for (int i = 1; i <= n; ++i) {
      TLibro lb = obtenerNesimoLibroTABBLibros(biblioteca->libros, i);
      if (perteneceTConjuntoGeneros(conj, idGeneroTLibro(lb))) {
          insertarLibroTABBLibros(res, copiarTLibro(lb));
      }
  }
  liberarTConjuntoGeneros(conj);
  return res;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
  if (!biblioteca) return;
  liberarTABBLibros(biblioteca->libros);
  liberarTLSESocios(biblioteca->socios);
  liberarTLDEPrestamos(biblioteca->prestamos);
  liberarTAGGeneros(biblioteca->generos);
  liberarTColaReservas(biblioteca->reservas);
  delete biblioteca;
  biblioteca = NULL;
}
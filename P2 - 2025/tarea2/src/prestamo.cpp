
#include "../include/prestamo.h"

struct rep_prestamo {
  TSocio socio;
  TLibro libro;
  TFecha fechaRetiro;
  TFecha fechaDevo;
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro){
  TPrestamo prestamo = new rep_prestamo;
  prestamo->socio = socio;
  prestamo->libro = libro;
  prestamo->fechaRetiro = fechaRetiro;
  prestamo->fechaDevo = NULL;
  return prestamo;
}
 
void imprimirTPrestamo(TPrestamo prestamo){
  printf("%s %s a %s %s.\n", "Préstamo de libro", tituloTLibro(prestamo->libro), nombreTSocio(prestamo->socio), apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevo != NULL) {
    imprimirTFecha(prestamo->fechaDevo);
  } else {
    printf("%s\n", "No retornado");
  }
}

void liberarTPrestamo(TPrestamo &prestamo){
  liberarTSocio(prestamo->socio);
  liberarTLibro(prestamo->libro);
  liberarTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevo != NULL) {
    liberarTFecha(prestamo->fechaDevo);
  }
  delete prestamo;
  prestamo = NULL;
}

TSocio socioTPrestamo(TPrestamo prestamo){
  return prestamo->socio;
}
 
TFecha fechaRetiroTPrestamo(TPrestamo prestamo){
  return prestamo->fechaRetiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo){
  return prestamo->fechaDevo;
}

TLibro libroTPrestamo(TPrestamo prestamo){
  return prestamo->libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo){
  return (prestamo->fechaDevo != NULL);
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion){
  if (prestamo->fechaDevo == NULL) {
    prestamo->fechaDevo = fechaDevolucion;
  } else {
    liberarTFecha(prestamo->fechaDevo);
    prestamo->fechaDevo = fechaDevolucion;
  }
}

TPrestamo copiarTPrestamo(TPrestamo prestamo){
  TPrestamo copiaPrestamo = new rep_prestamo;
  copiaPrestamo->socio = copiarTSocio(prestamo->socio);
  copiaPrestamo->libro = copiarTLibro(prestamo->libro);
  copiaPrestamo->fechaRetiro = copiarTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevo != NULL) { copiaPrestamo->fechaDevo = copiarTFecha(prestamo->fechaDevo); } else { copiaPrestamo->fechaDevo = NULL; }
  return copiaPrestamo;
}
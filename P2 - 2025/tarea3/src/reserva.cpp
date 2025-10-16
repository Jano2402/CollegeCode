
#include "../include/reserva.h"

struct rep_reserva {
  TSocio socio;
  TLibro libro;
};

TReserva crearTReserva(TSocio socio, TLibro libro){
  TReserva reserva = new rep_reserva;
  reserva->socio = socio;
  reserva->libro = libro;
  return reserva;
}

void imprimirTReserva(TReserva reserva){
  printf("%s %s %s %s %s.\n","Reserva de libro", tituloTLibro(reserva->libro), "por", nombreTSocio(reserva->socio), apellidoTSocio(reserva->socio));
}

void liberarTReserva(TReserva &reserva){
  liberarTSocio(reserva->socio);
  liberarTLibro(reserva->libro);
  delete reserva;
  reserva = NULL;
}

TSocio socioTReserva(TReserva reserva){
  return reserva->socio;
}

TLibro libroTReserva(TReserva reserva){
  return reserva->libro;
}

TReserva copiarTReserva(TReserva reserva){
  TReserva copia = new rep_reserva;
  copia->socio = copiarTSocio(reserva->socio);
  copia->libro = copiarTLibro(reserva->libro);
  return copia;
}

void liberarTReservaSoloEstructura(TReserva &reserva) {
  if (reserva == NULL) return; 
  delete reserva;
  reserva = NULL;
}


#include "../include/lseSocios.h"

struct rep_lseSocios {
	TSocio socio;
	TLSESocios next;
};

TLSESocios crearTLSESociosVacia(){
    return NULL;
}

bool esVaciaTLSESocios(TLSESocios lseSocios){
	return (lseSocios == NULL);
}

void imprimirTLSESocios(TLSESocios lseSocios){
	printf("%s\n", "Lista de Socios:");
	while (lseSocios != NULL) {
		imprimirTSocio(lseSocios->socio);
		lseSocios = lseSocios->next;
	};
}

void liberarTLSESocios(TLSESocios &lseSocios){
	TLSESocios actual = lseSocios;
    while (actual != NULL) {
        TLSESocios siguiente = actual->next;
        liberarTSocio(actual->socio);
        delete actual;
        actual = siguiente;
    }
    lseSocios = NULL;
}

void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio){
	TLSESocios nuevo = new rep_lseSocios;
	nuevo->socio = socio;
	nuevo->next = NULL;

	if (lseSocios == NULL || compararTFechas(fechaAltaTSocio(lseSocios->socio), fechaAltaTSocio(socio)) == 1) {
		nuevo->next = lseSocios;
		lseSocios = nuevo;
		return;
	}

	TLSESocios actual = lseSocios;
	while (actual->next != NULL && compararTFechas(fechaAltaTSocio(actual->next->socio), fechaAltaTSocio(socio)) != 1) {
		actual = actual->next;
	}

	nuevo->next = actual->next;
	actual->next = nuevo;
}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci){
	while (lseSocios != NULL && (ciTSocio(lseSocios->socio) != ci)) {
		lseSocios = lseSocios->next;
	}
	return (lseSocios != NULL);
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci){
    while (lseSocios != NULL) {
        if (ciTSocio(lseSocios->socio) == ci) {
            return lseSocios->socio;
        }
        lseSocios = lseSocios->next;
    }
    return NULL;
}

TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n){
	int actual = 1;
	while (lseSocios != NULL && actual != n) {
		lseSocios = lseSocios->next;
		actual++;
	}
	return lseSocios->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios){
	nat cant = 0;
	while (lseSocios != NULL) {
		lseSocios = lseSocios->next;
		cant++;
	}
	return cant;
}

void removerSocioTLSESocios(TLSESocios &lseSocios, int ci){
	TLSESocios actual = lseSocios;
    TLSESocios anterior = NULL;

	while (actual != NULL && ciTSocio(actual->socio) != ci) {
		anterior = actual;
		actual = actual->next;
	}

	if (actual == NULL) return;

	if (anterior == NULL) {
		lseSocios = actual->next;
	} else {
		anterior->next = actual->next;
	}

	liberarTSocio(actual->socio);
	delete actual;
}
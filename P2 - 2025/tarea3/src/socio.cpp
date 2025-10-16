#include "../include/socio.h"

struct rep_socio {
    int ci;
    char nombre[MAX_NOMBRE_SOCIO];
    char apellido[MAX_APELLIDO_SOCIO];
    TFecha fechaAlta;
    int genFavs[MAX_GENEROS_FAVORITOS];
    int topeGenFavs;
};
 
TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta){
    TSocio socio = new rep_socio;
    socio->ci = ci;
    strcpy(socio->nombre, nombre);
    strcpy(socio->apellido, apellido);
    socio->fechaAlta = crearTFecha(diaAlta, mesAlta, anioAlta);
    socio->topeGenFavs = 0;
    return socio;
}

void imprimirTSocio(TSocio socio){
    printf("Socio %d: %s %s\n", socio->ci, socio->nombre, socio->apellido);
    printf("Fecha de alta: ");
    imprimirTFecha(socio->fechaAlta);
    printf("Géneros favoritos: ");
    for (int i = 0; i < socio->topeGenFavs; i++) {
        printf("%d ", socio->genFavs[i]);
    }
    printf("\n");
}

void liberarTSocio(TSocio &socio){
    liberarTFecha(socio->fechaAlta);
    delete socio;
    socio = NULL;
}

int ciTSocio(TSocio socio){
    return socio->ci;
}

char* nombreTSocio(TSocio socio){
    return socio->nombre;
}

char* apellidoTSocio(TSocio socio){
    return socio->apellido;
}

TFecha fechaAltaTSocio(TSocio socio){
    return socio->fechaAlta;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
    if (socio->topeGenFavs < MAX_GENEROS_FAVORITOS - 1 && socio->topeGenFavs != MAX_GENEROS_FAVORITOS - 1) {
        socio->genFavs[socio->topeGenFavs] = idGenero;
        socio->topeGenFavs++;
    }
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    for (int i = 0; i < socio->topeGenFavs; i++) {
        if (socio->genFavs[i] == idGenero)
            return true;
    }
    return false;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){
    return socio->topeGenFavs;
}

TSocio copiarTSocio(TSocio socio){
    TSocio copiaSocio = new rep_socio;
    copiaSocio->ci = socio->ci;
    strcpy(copiaSocio->nombre, socio->nombre);
    strcpy(copiaSocio->apellido, socio->apellido);
    copiaSocio->fechaAlta = copiarTFecha(socio->fechaAlta);
    for (int i = 0; i < socio->topeGenFavs; i++) {
        copiaSocio->genFavs[i] = socio->genFavs[i];
    }
    copiaSocio->topeGenFavs = socio->topeGenFavs;
    return copiaSocio;
}

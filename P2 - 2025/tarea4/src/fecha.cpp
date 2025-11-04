#include "../include/fecha.h"


struct rep_fecha {
	nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}
void imprimirTFecha(TFecha fecha) {
    printf("%u/%u/%u\n", fecha->dia, fecha->mes, fecha->anio);
}

TFecha copiarTFecha(TFecha fecha) {
    TFecha copia = new rep_fecha;
    copia->dia = fecha->dia;
    copia->mes = fecha->mes;
    copia->anio = fecha->anio;
    return copia;
}

/************ Parte 3.9 ************/
/*Escriba el código a continuación */
/*Recuerde que las funciones auxiliares
  deben declararse antes de ser utilizadas*/

nat diasMes(nat mes, nat anio) {
    switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        if (anio % 400 == 0 || (anio % 4 == 0 && anio % 100 != 0)) {
            return 29;
        }
        return 28;
    
    default:
        return 0;
    }
};

void aumentarTFecha(TFecha &fecha, nat dias) {
    // Función para aumentar una fecha en una cantidad dada de días
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

/****** Fin de parte Parte 3.9 *****/

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    if (fecha1->anio != fecha2->anio)
        return (fecha1->anio > fecha2->anio) ? 1 : -1;

    if (fecha1->mes != fecha2->mes)
        return (fecha1->mes > fecha2->mes) ? 1 : -1;

    if (fecha1->dia != fecha2->dia)
        return (fecha1->dia > fecha2->dia) ? 1 : -1;

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fecha.h"

void conseguirFechaActual(int *dia, int *mes, int *anio)
{
    //La funci�n time() obtiene el tiempo actual en segundos desde el Epoch (1 de enero de 1970)
    time_t current_time = time(NULL);

    // Convertir el tiempo actual a la estructura tm
    //La funci�n localtime() convierte el tiempo en segundos a una estructura tm que contiene la fecha y la hora desglosadas en componentes (a�o, mes, d�a, etc.).
    struct tm *local_time = localtime(&current_time);

    // Almacenar el d�a, mes y a�o en variables enteras
    *dia = local_time->tm_mday;
    *mes = local_time->tm_mon + 1; // Los meses van de 0 a 11, se suma 1 para obtener de 1 a 12
    *anio = local_time->tm_year + 1900; // Los a�os desde 1900
}

void obtenerHoraActual(int *hora, int *minuto) {

    time_t tiempoActual;
    struct tm *tiempoDesglosado;

    // Obtener el tiempo actual
    tiempoActual = time(NULL);  // Usar time() para obtener el tiempo actual
    // Desglosar el tiempo en componentes (hora, minuto, segundo, etc.)
    tiempoDesglosado = localtime(&tiempoActual);

    // Asignar la hora y los minutos a los punteros proporcionados
    *hora = tiempoDesglosado->tm_hour;
    *minuto = tiempoDesglosado->tm_min;
}

#ifndef LOGS_H_INCLUDED
#define LOGS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Empleado.h"
#include "fecha.h"
#include "pila.h"

typedef struct{

    Fecha fecha;
    char id[9];

}Logs;

///Guardado de logs
void guardarLog(char archivo[],char inicioID[]);
void guardarLogEnArchivo(char archivo[],Logs l);

///Muestra de logs
void mostrarLogDeAuno(Logs l);
void mostrarLogsDelDia(char archivo[]);
void mostrarID(Pila pila, Pila hora, Pila minutos, int i);
void mostrarLogsPorFecha(char archivo[],Fecha f);
void mostrarArregloLogs(Logs arregloLogs[], int validos);

#endif // LOGS_H_INCLUDED

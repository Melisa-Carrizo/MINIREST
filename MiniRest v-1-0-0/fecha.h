#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef struct
{

    int dia;
    int mes;
    int anio;
    int hora;
    int minutos;

} Fecha;

void obtenerHoraActual(int *hora, int *minuto);
void conseguirFechaActual(int *dia, int *mes, int *anio);

#endif // FECHA_H_INCLUDED

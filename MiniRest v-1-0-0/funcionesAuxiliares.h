#ifndef FUNCIONESAUXILIARES_H_INCLUDED
#define FUNCIONESAUXILIARES_H_INCLUDED
#include "fecha.h"

///GOTOXY
void goTo(int x,int y); //GoTo acomoda los textos en la pantalla

///ESTETICA
void dejarEspacios(int espacio, int largo);
void limpiarYContinuar();//Espera a que el usuario quiera continuar y

///FUNCIONES DE OPCION
char guardarCambios(int x, int y);
char cargarOtro(char tipoStruct[]);
char opcionOrdenado();
char opcionActividad();
char opcionOcupacion();
char ordenFilradoProductosPrecio();
char opcionRolEmpleado();
char confirmacionProductos();
char opcionFiltrarProductos();
int editarEstadoActividad(int actividadVieja);

///Fecha
Fecha ingresoFecha();

///LOGS
char opcionLogs();

///FUNCIONES PARA ARCHIVOS
int calcularTamanioArchivo(char archivo[]);
int calcularValidosArchivos(char archivo[],int tipoDato);
int crearArchivo (char archivo[]);


#endif // FUNCIONESAUXILIARES_H_INCLUDED

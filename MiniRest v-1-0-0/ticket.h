#ifndef TICKET_H_INCLUDED
#define TICKET_H_INCLUDED
#include "mesas.h"
#include "Productos.h"
#include "fecha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IVA 21


typedef struct
{
    char id[6];
    char mesaUsada[5];
    char idProductos[30][30];
    float precioProducto[30];
    int validosProducto;
    Fecha fechaTicket;
    float descuento;
    float total;
    int estado;///1.activo 2.cobrado 3.cancelado

} Ticket;


///ALTA
Ticket cargarTicket(char archivoT[], char archivoP[], char archivoM[]);
void cargarTicketEnArchivo(char archivoT[], char archivoP[], char archivoM[]);
void productoAcargar(char respuesta[]);
void aniadirProductosTicket(char archivoP[], Ticket *t);
void buscarUltimoTicket(char archivo[], char id[]);
void generarIdTicket(char idUltTicket[], char idTicket[]);

///BAJA
void cancelarTicket(Ticket *t, char archivoM[]);

///MODIFICACION
void editarTicket(char archivoT[], char archivoP[], char archivoM[]);
char menuEdicionTicket();
void sobreescribirTicket(char archivoT[], int pos, Ticket t);
void sobreescribirProductoEnTicket(Ticket *t, char nombreProducto[], int *verificar);
void eliminarProducto(Ticket *t, char archivoT[], char archivoP[]);
float sumarProductos(float arr[], int validos, int i, float suma);
float calcularTotalTicket(float arr[], int validos, float desc);
void cobrarTicket(char archivoT[], char archivoM[]);

///CONSULTA
int contarEnteros(float numero);
void imprimirEspacios(int espacios);
void mostrarTicket(Ticket t);
int compararFecha(Fecha fecha1, Fecha fecha2);
void filtrarTicketFecha(char archivo[]);
int mostrarTicketPorFecha(char archivo[], Fecha f);
void filtrarTicketPorID(char archivo[], int x, int y);
void buscarTicketPorID(char archivo[],char id[]);
int buscarTicketPorMesa(char archivoT[], char idMesa[]);
Mesa ingresarIdMesaParaTicket(char archivoM[], char idMesa[], int *flag);
Ticket buscarYretornarTicketPorPosicionDesdeFinal(char archivoT[], int pos);

#endif // TICKET_H_INCLUDED

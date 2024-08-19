#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "mensajesAviso.h"
#include "menu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_SOFT_ORANGE "\x1b[38;2;204;111;18m"

///MENSAJES SIMULACION
void cargandoPrograma75()
{
    system("cls");
    printf("\n\n\n      ");
    printf("\n                       CARGANDO 0%%...\n         ");
    for(int i = 0; i<40; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(32,5);
    printf(ANSI_COLOR_RESET" 10%%...");
    goTo(10,6);
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }

    for(int i = 0; i<30; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(32,5);
    printf(ANSI_COLOR_RESET" 27%%...");
    goTo(10,6);
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }
    for(int i = 0; i<20; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(32,5);
    printf(ANSI_COLOR_RESET" 51%%...");
    goTo(10,6);
    for(int i = 0; i<20; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(32,5);
    printf(ANSI_COLOR_RESET" 75%%...");
    goTo(10,6);
    for(int i = 0; i<30; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c"ANSI_COLOR_RESET,177);
    }
}

void cargaProgramaAl00()
{
    Sleep(800);
    goTo(32,5);
    printf(ANSI_COLOR_RESET" 100%%...");
    goTo(10,6);
    for(int i = 0; i<40; i++)
    {
        printf(ANSI_COLOR_GREEN"%c"ANSI_COLOR_RESET,178);
    }
    Sleep(800);
}

void cerrandoPrograma()
{
    system("cls");
    printf("\n\n\n      ");
    printf("\n                  CERRANDO ARCHIVOS 0%%...     \n         ");
    for(int i = 0; i<40; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(0,4);
    printf(ANSI_COLOR_RESET"\n                  GUARDANDO CAMBIOS 10%%...     \n         ");
    goTo(10,6);
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }

    for(int i = 0; i<30; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(0,4);
    printf(ANSI_COLOR_RESET"\n                  LIMPIANDO MESAS 27%%...       \n         ");
    goTo(10,6);
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }
    for(int i = 0; i<20; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(0,4);
    printf(ANSI_COLOR_RESET"\n                   CONTANDO TICKETS 51%%...             \n         ");
    goTo(10,6);
    for(int i = 0; i<20; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",177);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",176);
    }
    Sleep(800);
    goTo(0,4);
    printf(ANSI_COLOR_RESET"\n                  CERRANDO CAJA 75%%...                 \n         ");
    goTo(10,6);
    for(int i = 0; i<30; i++)
    {
        printf(ANSI_COLOR_GREEN"%c",178);
    }
    for(int i = 0; i<10; i++)
    {
        printf(ANSI_COLOR_GREEN"%c"ANSI_COLOR_RESET,177);
    }
    Sleep(800);
    goTo(0,4);
    printf(ANSI_COLOR_RESET"\n                  NOS VEMOS MA%cANA 100%%...         \n         ",165);
    goTo(10,6);
    for(int i = 0; i<40; i++)
    {
        printf(ANSI_COLOR_GREEN"%c"ANSI_COLOR_RESET,178);
    }
    Sleep(800);

    printf("\n\n");
}

void adios(char nombreEmpleado[])
{
    system("cls");
    printf("\n\n\n\n");
    printf("                ===========================================\n");
    printf("                |                ADIOS :(                 |\n");
    printf("                |            "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET, nombreEmpleado);
    dejarEspacios(29,strlen(nombreEmpleado));
    printf("|\n");
    printf("                ===========================================\n");
    Sleep(1000);
}

///CAMBIOS
void cambiosGuardados()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|     "ANSI_COLOR_GREEN"CAMBIOS APLICADOS"ANSI_COLOR_RESET"    |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

///MESA
void mesaGuardada()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|       "ANSI_COLOR_GREEN"MESA GUARDADA"ANSI_COLOR_RESET"      |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}
///EMPLEADOS

void empleadoGuardado()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|     "ANSI_COLOR_GREEN"EMPLEADO GUARDADO"ANSI_COLOR_RESET"    |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

///PRODUCTO

void productoGuardado()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|     "ANSI_COLOR_GREEN"PRODUCTO GUARDADO"ANSI_COLOR_RESET"    |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

///TICKET
void ticketCobrado()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|      "ANSI_COLOR_GREEN"TICKET COBRADO"ANSI_COLOR_RESET"      |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

void ticketCancelado()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|     "ANSI_COLOR_RED"TICKET CANCELADO"ANSI_COLOR_RESET"     |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

void ticketCargado()
{
    system("cls");
    printf("\n");
    printf("============================\n");
    printf("|                          |\n");
    printf("|      "ANSI_COLOR_GREEN"TICKET CARGADO"ANSI_COLOR_RESET"      |\n");
    printf("|                          |\n");
    printf("============================\n");
    Sleep(1100);
}

void productoEliminadoDelTicket()
{
    system("cls");
    printf("\n");
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|     "ANSI_COLOR_GREEN"PRODUCTO ELIMINADO DEL TICKET"ANSI_COLOR_RESET"      |\n");
    printf("|                                        |\n");
    printf("==========================================\n");
    Sleep(1100);
}

void stockReincorporado()
{
    system("cls");
    printf("\n");
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|    "ANSI_COLOR_GREEN"PRODUCTO REINCORPORADO AL STOCK"ANSI_COLOR_RESET"     |\n");
    printf("|                                        |\n");
    printf("==========================================\n");
    Sleep(1100);
}

void productoNoEncontradoEnTicket()
{
    system("cls");
    printf("\n");
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|    "ANSI_COLOR_RED"PRODUCTO NO ENCONTRADO EN TICKET"ANSI_COLOR_RESET"    |\n");
    printf("|                                        |\n");
    printf("==========================================\n");
    Sleep(1100);
}

void productoCargadoAlTicket()
{
    printf("\n");
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|       "ANSI_COLOR_GREEN"PRODUCTO CARGADO AL TICKET"ANSI_COLOR_RESET"       |\n");
    printf("|                                        |\n");
    printf("==========================================\n");
    Sleep(1100);
}

void ticketAlcanzoTope() {
    system("cls");
    printf("\n");
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("| "ANSI_COLOR_RED"EL TICKET ALCANZO SU TOPE DE PRODUCTOS"ANSI_COLOR_RESET" |\n");
    printf("|                                        |\n");
    printf("==========================================\n");
    Sleep(1100);
}

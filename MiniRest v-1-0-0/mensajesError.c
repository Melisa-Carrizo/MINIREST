#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "mensajesError.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

///ERRORES GENERALES
void mensajeErrorOpcionInvalida()
{
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|        "ANSI_COLOR_RED"OPCION INGRESADA NO VALIDA"ANSI_COLOR_RESET"       |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
}

void mensajeErrorDePrograma()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|             "ANSI_COLOR_RED"ERROR DE PROGRAMA"ANSI_COLOR_RESET"           |\n");
    printf("|          Si el problema persiste        |\n");
    printf("|         comuniquese con el soporte      |\n");
    printf("|                                         |\n");
    printf("|                  555-5555               |\n");
    printf("===========================================\n\n");
    limpiarYContinuar();

}

void datosIngresadosIncorrectos()
{
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|       "ANSI_COLOR_RED"DATOS INGRESADOS NO VALIDOS"ANSI_COLOR_RESET"       |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
}

void errorLargoId()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|           "ANSI_COLOR_RED"LARGO DE ID INVALIDO"ANSI_COLOR_RESET"          |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

void nombreInexistente()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|             "ANSI_COLOR_RED"NOMBRE INEXISTENTE"ANSI_COLOR_RESET"          |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

void idInexistente()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|             "ANSI_COLOR_RED"EL ID NO EXISTE"ANSI_COLOR_RESET"             |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

///ERRORES DE MESA
void errorMesaInexiste()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|             "ANSI_COLOR_RED"LA MESA NO EXISTE"ANSI_COLOR_RESET"           |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");

}

void errorMesaExistente()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|             "ANSI_COLOR_RED"LA MESA YA EXISTE"ANSI_COLOR_RESET"           |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

///EMPLEADOS

void dniExistente()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|            "ANSI_COLOR_RED"EL DNI YA EXISTE"ANSI_COLOR_RESET"             |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

void dniInexistente()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|            "ANSI_COLOR_RED"EL DNI NO EXISTE"ANSI_COLOR_RESET"             |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

///TICKET
void ticketYaCobrado()
{
    system("cls");
    printf("\n");
    printf(" ============================\n");
    printf(" |                          |\n");
    printf(" |    "ANSI_COLOR_RED"TICKET YA COBRADO"ANSI_COLOR_RESET"     |\n");
    printf(" |                          |\n");
    printf(" ============================\n");
    Sleep(1100);
}

void faltaStock()
{
    system("cls");
    printf("\n");
    printf(" ============================\n");
    printf(" |                          |\n");
    printf(" |       "ANSI_COLOR_RED"NO HAY STOCK"ANSI_COLOR_RESET"       |\n");
    printf(" |                          |\n");
    printf(" ============================\n");
    Sleep(1100);
}

void noSeEncontroTicket()
{
    system("cls");
    printf("\n");
    printf(" =======================================\n");
    printf(" |                                     |\n");
    printf(" |    "ANSI_COLOR_RED"NO SE ENCONTRO NINGUN TICKET"ANSI_COLOR_RESET"     |\n");
    printf(" |                                     |\n");
    printf(" =======================================\n");
    Sleep(1100);
}

///LOGS
void noRegistro()
{
    system("cls");
    printf("\n\n===========================================\n");
    printf("|                                         |\n");
    printf("|     "ANSI_COLOR_RED"NO SE REGISTRO IDS EN ESA FECHA"ANSI_COLOR_RESET"     |\n");
    printf("|                                         |\n");
    printf("===========================================\n\n");
    Sleep(1100);
    system("cls");
}

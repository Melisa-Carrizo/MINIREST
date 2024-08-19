#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionesAuxiliares.h"
#include "fecha.h"
#include "mensajesError.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_SOFT_ORANGE "\x1b[38;2;204;111;18m"
#define ANSI_COLOR_RESET   "\x1b[0m"

///GOTOXY
void goTo(int x,int y)  //GoTo acomoda los textos en la pantalla
{
    printf("%c[%d;%df",0x1B,y,x);
}

///ESTETICA
void limpiarYContinuar()//Espera a que el usuario quiera continuar y
{
    printf("\n\n");
    system("pause");
    system("cls");
}

void dejarEspacios(int espacio, int largo)//Printea espacios en la pantalla
{
    int cantEspacios;

    cantEspacios = espacio-largo;
        for(int i = 0; i<cantEspacios; i++)
        {
            printf(" ");
        }


}

///FUNCIONES DE OPCION

char guardarCambios(int x, int y)//Pide que ingrese si quiere guardar los cambios y la retorna, pide x e y para posicionar el cursor del scanf
{
    char confirmar;

    printf("\n");
    printf(" ===================================\n");
    printf(" |                                 |\n");
    printf(" |         GUARDAR CAMBIOS         |\n");
    printf(" |                                 |\n");
    printf(" | 1.Si                            |\n");
    printf(" |                                 |\n");
    printf(" | 2.No                            |\n");
    printf(" |                                 |\n");
    printf(" | ->                              |\n");
    printf(" |                                 |\n");
    printf(" ===================================\n");

    do
    {
        goTo(x,y);
        fflush(stdin);
        scanf("%c",&confirmar);

        if(confirmar != '1' && confirmar != '2')
        {
            goTo(0,y-1);
            printf(" |     "ANSI_COLOR_RED"INGRESE UNA OPCION VALIDA"ANSI_COLOR_RESET"   |\n");
            printf(" | ->                              |\n");

        }

    }while(confirmar != '1' && confirmar != '2');

    return confirmar;
}

char cargarOtro(char tipoStruct[])//Ingresa la opcion de cargar otro y lo retorna, pide pasar el tipo de struct o un string para completar. Ejemplo tipostruct[] = "EMPLEADO" CARGAR OTRO EMPLEADO?
{
    char confirmar;
    system("cls");
    printf("\n");
    printf(" ===================================\n");
    printf(" |                                 |\n");
    printf(" |      CARGAR OTRO %s       |\n",tipoStruct);
    printf(" |                                 |\n");
    printf(" | 1.Si                            |\n");
    printf(" |                                 |\n");
    printf(" | 2.No                            |\n");
    printf(" |                                 |\n");
    printf(" | ->                              |\n");
    printf(" |                                 |\n");
    printf(" ===================================\n");

    do
    {

        goTo(7,10);
        fflush(stdin);
        scanf("%c",&confirmar);

        if(confirmar != '1' && confirmar != '2')
        {
            goTo(0,9);
            printf(" |    "ANSI_COLOR_RED"INGRESE UNA OPCION VALIDA"ANSI_COLOR_RESET"    |\n");
            printf(" | ->                              |\n");

        }

    }while(confirmar != '1' && confirmar != '2');

    system("cls");

    return confirmar;
}

char opcionOrdenado()//Ingresa la opcion de ordenado y lo retorna
{
    char opcion;
    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|        ELIJA UNA OPCION         |\n");
        printf("|                                 |\n");
        printf("|  1. Menor a mayor               |\n");
        printf("|                                 |\n");
        printf("|  2. Mayor a menor               |\n");
        printf("|                                 |\n");
        printf("|  0. Volver                      |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&opcion);
        system("cls");

        if(opcion != '1' && opcion != '0' && opcion !='2')
        {
            mensajeErrorOpcionInvalida();
        }

    }while(opcion != '1' && opcion != '0' && opcion !='2');

    return opcion;
}

char opcionActividad()//Ingresa la opcion de actividad y la retorna
{
    char opcion;
    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|        ELIJA UNA OPCION         |\n");
        printf("|                                 |\n");
        printf("|  1. Activo                      |\n");
        printf("|                                 |\n");
        printf("|  2. Inactivo                    |\n");
        printf("|                                 |\n");
        printf("|  0. Volver                      |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&opcion);
        system("cls");

        if(opcion != '1' && opcion != '0' && opcion !='2')
        {
            mensajeErrorOpcionInvalida();
        }

    }while(opcion != '1' && opcion != '0' && opcion !='2');

    return opcion;
}

char opcionOcupacion()//Ingresa la opcion de ocupacion de mesa y la retorna
{
    char opcion;
    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|        ELIJA UNA OPCION         |\n");
        printf("|                                 |\n");
        printf("|  1. Ocupada                     |\n");
        printf("|                                 |\n");
        printf("|  2. Desocupada                  |\n");
        printf("|                                 |\n");
        printf("|  0. Volver                      |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&opcion);
        system("cls");

        if(opcion != '1' && opcion != '0' && opcion !='2')
        {
            mensajeErrorOpcionInvalida();
        }

    }while(opcion != '1' && opcion != '0' && opcion !='2');

    return opcion;
}

char opcionRolEmpleado()//Ingresa una opcion de empleado y la retorna
{
    char dato;
    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|        ELIJA UNA OPCION         |\n");
        printf("|                                 |\n");
        printf("|  1. Empleado                    |\n");
        printf("|                                 |\n");
        printf("|  2. Administrador               |\n");
        printf("|                                 |\n");
        printf("|  0. Volver                      |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&dato);
        system("cls");

        if(dato != '1' && dato != '2' && dato != '0')
        {
            mensajeErrorOpcionInvalida();
        }

    }while(dato != '1' && dato != '2' && dato != '0');

    return dato;

}

char opcionFiltrarProductos() //Opcion para filtrar productos y la retorna
{

    char opcionFiltro;

    do{

    system("cls");
    printf("===================================\n");
    printf("|                                 |\n");
    printf("|            VER PRODUCTOS        |\n");
    printf("|                                 |\n");
    printf("| 1.Ver todo                      |\n");
    printf("|                                 |\n");
    printf("| 2.Filtrar                       |\n");
    printf("|                                 |\n");
    printf("| 0.Volver                        |\n");
    printf("|                                 |\n");
    printf("| ->                              |\n");
    printf("|                                 |\n");
    printf("===================================\n");
    goTo(6,11);
    fflush(stdin);
    scanf("%c",&opcionFiltro);

    if(opcionFiltro != '0' && opcionFiltro != '1' && opcionFiltro != '2'){

        mensajeErrorOpcionInvalida();
    }

    }while(opcionFiltro != '0' && opcionFiltro != '1' && opcionFiltro != '2');

    return opcionFiltro;

}

int editarEstadoActividad(int actividadVieja)//Edita el estado de actividad automaticamente
{
    if(actividadVieja == 0)//Si la estructura estaba desactivada la activa
    {
        actividadVieja = 1;
    }
    else//Si la estructura estaba activada la desactiva
    {
        actividadVieja = 0;
    }

    return actividadVieja;//Retorna la actividad cambiada
}

///Fecha
Fecha ingresoFecha()//Pide el ingreso de una fecha y lo devuelve
{

    Fecha f;
    system("cls");
    printf(" =====================================================\n");
    printf(" |                                                   |\n");
    printf(" |  INGRESE EL DIA  ->                               |\n");
    printf(" |  "ANSI_COLOR_SOFT_ORANGE"SI EL DIA ES MENOR A 10 INGRESE UN SOLO NRO"ANSI_COLOR_RESET"      |\n");
    printf(" |                                                   |\n");
    printf(" |  INGRESE EL NUMERO DEL MES ->                     |\n");
    printf(" |  "ANSI_COLOR_SOFT_ORANGE"SI EL DIA ES MENOR A 10 INGRESE UN SOLO NRO"ANSI_COLOR_RESET"      |\n");
    printf(" |                                                   |\n");
    printf(" |  INGRESE EL A%cO  ->                               |\n",165);
    printf(" |  "ANSI_COLOR_SOFT_ORANGE"INGRESE EL A%cO COMPLETO. EJEMPLO: 2024"ANSI_COLOR_RESET"           |\n",165);
    printf(" |                                                   |\n");
    printf(" =====================================================\n");

    do{

        goTo(24,3);
        scanf("%d",&f.dia);

        if(f.dia > 31 && f.dia < 1){
            goTo(0,2);
            printf(" |  "ANSI_COLOR_RED"INGRESE UN DIA VALIDO(ENTRE 1-31)"ANSI_COLOR_RESET"                |\n");
            printf(" |  INGRESE EL DIA  ->                               |\n");

        }

    }while(f.dia > 31 && f.dia < 1);

    do
    {
        goTo(34,6);
        scanf("%d",&f.mes);

        if(f.mes<1 && f.mes >12)
        {
            goTo(0,5);
            printf(" |  "ANSI_COLOR_RED"INGRESE UN MES VALIDO(ENTRE 1-12)"ANSI_COLOR_RESET"                |\n");
            printf(" |  INGRESE EL NUMERO DEL MES ->                     |\n");
        }

    }while(f.mes<1 && f.mes >12);

    goTo(24,9);
    scanf("%d",&f.anio);

    return f;
}

///LOGS
char opcionLogs()// Menu de ver logs, retorna la opcion elegida
{

    char opcion;
    do
    {

        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|            VER LOGS             |\n");
        printf("|                                 |\n");
        printf("| 1.Ver logs de hoy               |\n");
        printf("|                                 |\n");
        printf("| 2.Mostrar por fecha             |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&opcion);

        if(opcion !='1' && opcion !='2' && opcion !='0')
        {
            mensajeErrorOpcionInvalida();
        }

    }
    while(opcion !='1' && opcion !='2' && opcion !='0');

    return opcion;

}

///FUNCIONES PARA ARCHIVOS

int calcularTamanioArchivo(char archivo[])//Calcula el tamaño entero de un archivo
{
    FILE* buff;

    buff = fopen(archivo,"rb");

    int tamanioArchivo = 0;

    if(buff)
    {
        fseek(buff,0,2);
        tamanioArchivo = ftell(buff);

        fclose(buff);
    }
    else
    {
        printf("No se pudo abrir el archivo o no existe :(");
    }

    return tamanioArchivo;
}

int calcularValidosArchivos(char archivo[],int tipoDato)//Calcula los validos de un archivo y los devuelve
{
    int tamanio = calcularTamanioArchivo(archivo);

    int validos = tamanio/tipoDato;

    return validos;
}

int crearArchivo (char archivo[]) //Crea un archivo devuelve 1 si lo abrió o 0 si no abrió.
{
    int flag = 0;

    FILE *buff = fopen(archivo,"ab");

    if(buff)
    {
        flag = 1;
        fclose(buff);
    }

    return flag;
}

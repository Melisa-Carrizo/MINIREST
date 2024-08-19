#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inicioSesion.h"
#include "Empleado.h"
#include "menu.h"
#include "logs.h"
#include "funcionesAuxiliares.h"
#include "mensajesError.h"
#include "mensajesAviso.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_SOFT_ORANGE "\x1b[38;2;204;111;18m"

///--------Inicio de programa y sesion--------///

void cargaDelPrograma() ///Barra de carga y creacion de los archivos al iniciar el programa
{

    char archivoEmpleados[] = "Empleados.bin";
    char archivoMesas[] = "Mesas.bin";
    char archivoProductos[] = "Productos.bin";
    char archivoTicket[] = "Ticket.bin";
    char archivoLogs[] = "Logs.bin";

    int flag = crearArchivo(archivoEmpleados);

    cargandoPrograma75();
    if(flag)
    {
        flag = crearArchivo(archivoLogs);

        if (flag)
        {
            flag = crearArchivo(archivoMesas);

            if(flag)
            {
                flag = crearArchivo(archivoTicket);

                if(flag)
                {
                    flag = crearArchivo(archivoProductos);

                    cargaProgramaAl00();

                    inicioSesionPrograma(archivoMesas,archivoProductos,archivoEmpleados,archivoTicket,archivoLogs);

                }
                else
                {
                    mensajeErrorDePrograma();
                }
            }
            else
            {
                mensajeErrorDePrograma();
            }
        }
        else
        {
            mensajeErrorDePrograma();
        }
    }
    else
    {
        mensajeErrorDePrograma();
    }

}

void inicioSesionPrograma(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[])///Funcion principal donde envia al usuario
{                                                                                                                                    ///a su menu correspondiente segun su inicio de sesion

    char inicioID[9];
    char nombreInicioActual[30];
    char inicioContra[10];
    int inicioValido;
    char entradaSalida;

    do
    {

       entradaSalida=inicioPrograma(entradaSalida);

        if(entradaSalida == '1')    ///si el usuario desea iniciar sesion entra al programa, sino, sale
        {

            inicioLogIn(inicioID,inicioContra); ///lo envia al login

            inicioValido=inicioSesion(archivoEmpleados,inicioID,inicioContra);  ///verifica los datos ingresados

            system("cls");

            switch(inicioValido)
            {

            case -1:///Datos no validos

                datosIngresadosIncorrectos();

                break;

            case 1:///Administrador

                guardarLog(archivoLogs,inicioID);///guarda el logeo

                menuGeneralAdmin(archivoMesas,archivoProductos,archivoEmpleados,archivoTicket,archivoLogs,inicioID,nombreInicioActual); ///redireccion al menu administrador

                break;

            case 2:///Empleado

                guardarLog(archivoLogs,inicioID);///guarda el logeo

                menuGeneralEmpleado(archivoMesas,archivoProductos,archivoEmpleados,archivoTicket,inicioID,nombreInicioActual);  ///redireccion al menu empleado

                break;

            }

        }

        if(entradaSalida != '0')    ///si la opcion elegida por el usuario es 0 sale del programa
        {

            system("cls");

        }

    }
    while(entradaSalida!='0');  ///corta el bucle cuando el usuario desea salir

    cerrandoPrograma();
}

char inicioPrograma(char entradaSalida)/// inicio del programa
{

        system("cls");//ES PQ EL GOTOXY SINO TIRA CUALQUIERA.
        imprimirMiniRest();

        printf("==============================\n");
        printf("|                            |\n");
        printf("| 1. Iniciar sesion          |\n");
        printf("|                            |\n");
        printf("| 0. Salir                   |\n");
        printf("|                            |\n");
        printf("| ->                         |\n");
        printf("==============================\n");
        goTo(6,15);
        fflush(stdin);
        scanf("%c",&entradaSalida);

        if(entradaSalida!= '1' && entradaSalida!= '0'){

            mensajeErrorOpcionInvalida();

        }

        return entradaSalida; ///retorna la opcion elegida por el usuario
}

void inicioLogIn(char inicioID[],char inicioContra[])///Inicio de sesion
{

            system("cls");
            printf("========================================\n");
            printf("|                                      |\n");
            printf("|  Ingresar ID/DNI ->                  |\n");
            printf("|                                      |\n");
            printf("|  Ingresar contrase%ca ->              |\n",164);
            printf("|                                      |\n");
            printf("========================================\n");

            fflush(stdin);
            goTo(23,3);
            gets(inicioID);

            fflush(stdin);
            goTo(27,5);
            gets(inicioContra);

}

int inicioSesion(char archivo[],char inicioID[],char inicioContra[])///Funcion principal de inicio sesion. Devuelve -1 si el usuario está inactivo o el id y/o contraseña no coinciden
{                                                                   ///, o devuelve el rol administrativo si el usuario ingresado es valido


    int aux1=verificacionIDempleado(archivo,inicioID);
    int i = -1;

    if(aux1==0)
    {
        int aux2=verificacionEstadoActividad(archivo,inicioID);

        if(aux2==1)
        {

            int aux3=verificacionContraEmpleado(archivo,inicioContra,inicioID);

            if(aux3==0)
            {

                i=verificacionRolAdministrativo(archivo,inicioID);

            }

        }

    }

    return i;

}

///--------Verificacion de los datos del empleado--------///
int verificacionIDempleado(char archivo[], char id[])///Verificacion de id del empleado existente en el archivo ///MODIFICADO
{
    FILE* buff = fopen(archivo,"rb");

    Empleado aux;
    int i=-1;

    if(buff)
    {
        while( (fread(&aux,sizeof(Empleado),1,buff)) > 0 && i!=0)
        {
            i=strcmp(aux.id,id);
        }

        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

    return i;

}

int verificacionContraEmpleado(char archivo[],char contra[],char id[])///Verifica si la contraseña corresponde al id ingresado
{                                        ///Devuelve 0 si la ingresada es igual a la existente en el archivo o un num distinto de 0 si no es.


    FILE* buff = fopen(archivo,"rb");

    Empleado aux;
    int i=-1;

    if(buff)
    {

        while( (fread(&aux,sizeof(Empleado),1,buff)) > 0 && i!=0)
        {

            if( (strcmp(aux.id,id))==0 )
            {

                i=strcmp(aux.clave,contra);

            }

        }

        fclose(buff);

    }
    else
    {

        printf("Ha ocurrido un error. Autodestruccion");

    }

    return i;
}

int verificacionRolAdministrativo(char archivo[], char id[])///Devuelve el rol administrativo del usuario correspondiente.
{

    FILE* buff = fopen(archivo,"rb");

    Empleado e;
    int i = -1;
    int rol;

    if(buff)
    {

        while( (fread(&e,sizeof(Empleado),1,buff)) > 0 && i != 0)
        {

            i=strcmp(e.id,id);  //compara el id ingresado con el del empleado leido en el archivo

            if( i == 0)
            {

                rol=e.rolAdministrativo;    //guarda el rol del empleado en la variable

            }

        }

        fclose(buff);
    }
    else
    {

        printf("Ha ocurrido un error. Autodestruccion");

    }

    return rol; //retorna el rol del empleado
}

int verificacionEstadoActividad(char archivo[], char id[])///Devuelve el estado de actividad del usuario.
{

    FILE* buff = fopen(archivo,"rb");

    Empleado e;
    int i = -1;
    int estado;

    if(buff)
    {

        while( (fread(&e,sizeof(Empleado),1,buff)) > 0 && i != 0)
        {

            i=strcmp(e.id,id);

            if( i == 0)
            {

                estado=e.estadoActividad;

            }

        }

        fclose(buff);
    }
    else
    {

        printf("Ha ocurrido un error. Autodestruccion");

    }

    return estado;


}

void identificarNombre(char archivo[],char inicioID[],char nombre[])///Identifica el nombre del empleado que inicio sesion
{
    FILE* buff = fopen(archivo,"rb");

    Empleado e;

    if(buff)
    {
        while( (fread(&e,sizeof(Empleado),1,buff)) > 0 )
        {
            if((strcmp(e.id,inicioID)) == 0)    //verifica el nombre del empleado y si lo encuentra lo copia en nombre
            {
                strcpy(nombre,e.nombreApellido);
            }
        }
        fclose(buff);
    }
}


#include <stdio.h>
#include <stdlib.h>
#include "Empleado.h"
#include "fecha.h"
#include "funcionesAuxiliares.h"
#include "inicioSesion.h"
#include "logs.h"
#include "menu.h"
#include "mesas.h"
#include "mensajesAviso.h"
#include "mensajesError.h"
#include "Productos.h"
#include "ticket.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_SOFT_ORANGE "\x1b[38;2;204;111;18m"

///--------Menus generales--------///

///Menu General Admin

void menuGeneralAdmin(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[],char inicioID[],char nombreInicioActual[])
{

    char control;

    identificarNombre(archivoEmpleados,inicioID,nombreInicioActual);

    do{

            system("cls");

                    printf("=======================================\n");
                    printf("|                                     |\n");
                    printf("|     Bienvenido,                     |\n");
                    goTo(19,3);
                    printf(ANSI_COLOR_CYAN "%s\n"ANSI_COLOR_RESET,nombreInicioActual);
                    printf("|                                     |\n");
                    printf("| Usted inicio en modo: " ANSI_COLOR_GREEN "Administrador " ANSI_COLOR_RESET "|\n" );
                    printf("|                                     |\n");
                    printf("=======================================\n");

                    printf("\n");

                    printf("===============================\n");
                    printf("|                             |\n");
                    printf("| 1. Mesas                    |\n");
                    printf("|                             |\n");
                    printf("| 2. Productos                |\n");
                    printf("|                             |\n");
                    printf("| 3. Empleados                |\n");
                    printf("|                             |\n");
                    printf("| 4. Tickets                  |\n");
                    printf("|                             |\n");
                    printf("| 5. Ver Logs                 |\n");
                    printf("|                             |\n");
                    printf("| 0. Cerrar sesion            |\n");
                    printf("|                             |\n");
                    printf("| ->                          |\n");
                    printf("===============================\n");
                    goTo(6,23);
                    fflush(stdin);
                    scanf("%c",&control);

            caseMenuAdmin(archivoMesas,archivoProductos,archivoEmpleados,archivoTicket,archivoLogs,control);

        }while(control!='0');

        adios(nombreInicioActual);
}

void caseMenuAdmin(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[],char control)
{
    switch(control){

        case '1':///CASE MESA

            switchMesa(archivoMesas);

            break;

        case '2': ///PRODUCTOS

            menuProductos(archivoProductos);

            break;

        case '3':///Empleados

            menuEmpleadoAdmin(archivoEmpleados);

            break;

        case '4':///Ticket

            menuTicket(archivoTicket,archivoMesas,archivoProductos);

            break;

        case '5':///Logs

            menuLogs(archivoLogs);

            break;

        case '0':
            break;

        default:
            mensajeErrorOpcionInvalida();
            break;

        break;

        }

}

///Menu general Empleado

void menuGeneralEmpleado(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char inicioID[],char nombreInicioActual[])
{

    char control;

    identificarNombre(archivoEmpleados,inicioID,nombreInicioActual);

    do
    {
        system("cls");

                    printf("=======================================\n");
                    printf("|                                     |\n");
                    printf("|          Bienvenido,                |\n");
                    goTo(24,3);
                    printf(ANSI_COLOR_CYAN "%s\n"ANSI_COLOR_RESET,nombreInicioActual);
                    printf("|                                     |\n");
                    printf("|   Usted inicio en modo: " ANSI_COLOR_GREEN "Empleado " ANSI_COLOR_RESET "   |\n" );
                    printf("|                                     |\n");
                    printf("=======================================\n");

                    printf("\n");

                    printf("===============================\n");
                    printf("|                             |\n");
                    printf("| 1. Mesas                    |\n");
                    printf("|                             |\n");
                    printf("| 2. Productos                |\n");
                    printf("|                             |\n");
                    printf("| 3. Tickets                  |\n");
                    printf("|                             |\n");
                    printf("| 0. Cerrar sesion            |\n");
                    printf("|                             |\n");
                    printf("| ->                          |\n");
                    printf("===============================\n");
                    goTo(6,19);
                    fflush(stdin);
                    scanf("%c",&control);

        caseMenuEmpleado(archivoMesas,archivoProductos,archivoEmpleados,archivoTicket,control);

    }
    while(control!='0');

    adios(nombreInicioActual);
}

void caseMenuEmpleado(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char control)
{

    switch(control)
        {

        case '1':

            switchMesaEmpleado(archivoMesas);

            break;

        case '2':

            menuProductosEmpleado(archivoProductos);

            break;

        case '3':

            menuTicket(archivoTicket,archivoMesas,archivoProductos);

            break;

        case '0':

            break;

        default:

            mensajeErrorOpcionInvalida();

            break;

        }

}

///--------Menu Parte Empleado Admin--------///
void menuEmpleadoAdmin(char archivoEmpleados[])
{

    char control;

    do{

        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|            EMPLEADOS            |\n");
        printf("|                                 |\n");
        printf("| 1.Agregar empleado              |\n");
        printf("|                                 |\n");
        printf("| 2.Modificar empleado            |\n");
        printf("|                                 |\n");
        printf("| 3.Ver empleados                 |\n");
        printf("|                                 |\n");
        printf("| 4.Buscar empleado               |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,15);
        fflush(stdin);
        scanf("%c",&control);

        if(control=='1' || control=='2' || control=='3' || control=='4'){

            switchEmpleado(archivoEmpleados,control);

        }else if(control!='1' && control!='2' && control!='3' && control!='4' && control!='0'){

            mensajeErrorOpcionInvalida();

        }


    }while(control!='0');

}

void switchEmpleado(char archivo[], char control)
{

    system("cls");
    switch(control)
    {

    case '1':

        cargarEmpleados(archivo);

        break;

    case '2':

        editarEmpleados(archivo);

        break;

    case '3':

        menuMostrarEmpleadosAdmin(archivo);

        break;

    case '4':

        menuBusquedaEmpleados(archivo);

        break;

    case '0':
        break;

    }

}

void menuMostrarEmpleadosAdmin(char archivoEmpleados[])
{

    char opcion;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|          VER EMPLEADOS          |\n");
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
        scanf("%c",&opcion);

        if (opcion != '0' && opcion != '1' && opcion != '2')
        {
            mensajeErrorOpcionInvalida();

        }else if(opcion == '1' || opcion == '2')
        {
            menuElegirFiltroEmpleados(archivoEmpleados,opcion);
        }

    }while(opcion!='0' && opcion != '1' && opcion != '2' );

}

void menuElegirFiltroEmpleados(char archivoEmpleados[],char opcion)
{

    char filtro;

    if(opcion == '2')
    {

        do{

        system("cls");
        printf(" ===================================\n");
        printf(" |                                 |\n");
        printf(" |        ELIJA UNA OPCION         |\n");
        printf(" |                                 |\n");
        printf(" | 1.Nombre                        |\n");
        printf(" |                                 |\n");
        printf(" | 2.ID/DNI                        |\n");
        printf(" |                                 |\n");
        printf(" | 3.Rol administrativo            |\n");
        printf(" |                                 |\n");
        printf(" | 4.Estado de actividad           |\n");
        printf(" |                                 |\n");
        printf(" | 0.Volver                        |\n");
        printf(" |                                 |\n");
        printf(" | ->                              |\n");
        printf(" |                                 |\n");
        printf(" ===================================\n");
        goTo(7,15);
        fflush(stdin);
        scanf("%c",&filtro);

        switchFiltroEmpleados(archivoEmpleados,filtro);

        }while(filtro != '0');

    }
    else if(opcion == '1')
    {

        verTodoEmpleados(archivoEmpleados);

        limpiarYContinuar();

    }

}

void switchFiltroEmpleados(char archivo[], char filtro)
{

    system("cls");
    switch(filtro)
    {

    case '0':
        break;
    case '1':

        filtrarEmpleadosNombres(archivo);

        break;

    case '2':

        filtrarEmpleadosID(archivo);

        break;

    case '3':

        filtrarEmpleadosPorRol(archivo);

        break;

    case '4':

        filtrarEmpleadosActividad(archivo);

        break;

    default:

        mensajeErrorOpcionInvalida();

        break;
    }

}

void menuBusquedaEmpleados(char archivoEmpleados[])
{

    char nombre[30];

    printf(" ===================================\n");
    printf(" |                                 |\n");
    printf(" |         BUSCAR EMPLEADO         |\n");
    printf(" |                                 |\n");
    printf(" | INGRESE EL NOMBRE DEL EMPLEADO  |\n");
    printf(" | QUE DESEA BUSCAR O 0 PARA SALIR |\n");
    printf(" |                                 |\n");
    printf(" | ->                              |\n");
    printf(" |                                 |\n");
    printf(" ===================================\n");
    goTo(7,8);
    fflush(stdin);
    gets(nombre);

    if( strcmp(nombre,"0")!=0 ){

    system("cls");
    buscarEmpleadoPorNombre(archivoEmpleados,nombre);

    }

}

///Menu Mesas

void switchVerMesas(char archivo[])
{

    char operador;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|            VER MESAS            |\n");
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
        scanf("%c",&operador);

        switch(operador)
        {
        case '0':
            break;
        case '1':
            verTodoMesas(archivo);
            break;
        case '2':
            switchFiltrarMesas(archivo);
            break;
        default:
            mensajeErrorOpcionInvalida();
            break;
        }

    }while(operador != '0');
}

void switchFiltrarMesas(char archivo[])
{

    char operador;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|        ELIJA UNA OPCION         |\n");
        printf("|                                 |\n");
        printf("| 1.ID/Numero                     |\n");
        printf("|                                 |\n");
        printf("| 2.Estado de ocupacion           |\n");
        printf("|                                 |\n");
        printf("| 3.Estado de actividad           |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,13);
        fflush(stdin);
        scanf("%c",&operador);

        switch(operador)
        {
        case '0':
            break;
        case '1':
            filtrarMesasMayorAmenor(archivo);
            break;
        case '2':
            filtrarMesasOcupacion(archivo);
            break;
        case '3':
            filtrarMesasActividad(archivo);
            break;
        default:
            mensajeErrorOpcionInvalida();
            break;
        }

    }while(operador != '0');
}

void switchMesa(char archivoMesas[])
{
    char control;

    do
    {
        system("cls");
        printf("============================\n");
        printf("|          MESAS           |\n");
        printf("|                          |\n");
        printf("| 1. Crear mesa            |\n");
        printf("|                          |\n");
        printf("| 2. Ver mesa              |\n");
        printf("|                          |\n");
        printf("| 3. Modificar mesa        |\n");
        printf("|                          |\n");
        printf("| 4. Buscar mesa           |\n");
        printf("|                          |\n");
        printf("| 0. Volver                |\n");
        printf("|                          |\n");
        printf("| ->                       |\n");
        printf("============================\n");
        goTo(6,14);
        fflush(stdin);
        scanf("%c",&control);

        switch(control)
        {
        case '0':
            break;

        case '1':
            system("cls");

            printf("============================\n");
            printf("|                          |\n");
            printf("|        CREAR MESA        |\n");
            printf("|                          |\n");
            printf("============================\n");
            agregarMesaEnArchivo(archivoMesas);

            break;

        case '2':
            system("cls");
            switchVerMesas(archivoMesas);

            break;

        case '3':
            system("cls");

            printf("============================\n");
            printf("|                          |\n");
            printf("|       MODIFICAR MESA     |\n");
            printf("|                          |\n");
            printf("============================\n");

            editarMesa(archivoMesas);

            break;

        case '4':
            system("cls");

            printf("============================\n");
            printf("|                          |\n");
            printf("|        BUSCAR MESA       |\n");
            printf("|                          |\n");
            printf("============================\n");

            buscarYmostrarMesaPorID(archivoMesas);

            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }

    }
    while(control!='0');
}

///Menu Productos

void menuProductos(char archivo[])
{

    char opcion;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|            PRODUCTOS            |\n");
        printf("|                                 |\n");
        printf("| 1.Agregar producto              |\n");
        printf("|                                 |\n");
        printf("| 2.Modificar producto            |\n");
        printf("|                                 |\n");
        printf("| 3.Ver producto                  |\n");
        printf("|                                 |\n");
        printf("| 4.Dar de baja/reactivar         |\n");
        printf("|                                 |\n");
        printf("| 5.Buscar producto               |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,17);
        fflush(stdin);
        scanf("%c",&opcion);

        if( opcion=='1' || opcion=='2' || opcion=='3' || opcion=='4' || opcion=='5' ){

            switchMenu2(archivo, opcion);

        }else if( opcion!='1' && opcion!='2' && opcion!='3' && opcion!='4' && opcion!='5' && opcion!='0' ){

            mensajeErrorOpcionInvalida();

        }

    }
    while (opcion != '0');

}

void switchMenu2(char archivo[], char opcion)
{

    system("cls");

    switch (opcion) {

    case '1':

    crearProductos(archivo);

        break;

    case '2':

    modificarProducto(archivo);

        break;

    case '3':

    menuVerProductos(archivo);

        break;

    case '4':

    darDeBaja(archivo);

        break;

    case '5':

    switchBusqueda(archivo);

        break;

    }

}

void menuVerProductos(char archivo[])
{

    char opcionFiltrar;

    opcionFiltrar = opcionFiltrarProductos();

    system("cls");

    switch (opcionFiltrar) {
    case '1':

        verTodoProductos(archivo);

        system("pause");

        break;

    case '2':

        switchFiltradoGeneral(archivo);

        break;
    }

    system("cls");

}

void switchFiltradoGeneral(char archivo[])
{

    char filtro;

    do {

        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|         FILTRAR PRODUCTOS       |\n");
        printf("|                                 |\n");
        printf("| 1.Nombre                        |\n");
        printf("|                                 |\n");
        printf("| 2.ID                            |\n");
        printf("|                                 |\n");
        printf("| 3.Precio                        |\n");
        printf("|                                 |\n");
        printf("| 4.Stock                         |\n");
        printf("|                                 |\n");
        printf("| 5.Estado de actividad           |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,17);
        fflush(stdin);
        scanf("%c",&filtro);

        if( filtro == '1' || filtro == '2' || filtro == '3' || filtro == '4' || filtro == '5' ){

            switchFiltradoProductos(archivo,filtro);

        }else if( filtro!= '0' ){

            mensajeErrorOpcionInvalida();

        }

    } while (filtro != '0');

    if( filtro != '0' ){

        limpiarYContinuar();
    }

}

void switchFiltradoProductos(char archivo[], char filtro1)
{
    char filtro;

    system("cls");
    switch (filtro1)
        {
        case '0':
            break;
        case '1':

            filtrarProductosNombre(archivo);

            break;

        case '2':

            filtro = opcionOrdenado();
            filtrarProductosID(archivo,filtro);

            break;

        case '3':

            filtrarProductosPrecio(archivo);

            break;

        case '4':

            filtrarProductosStock(archivo);

            break;

        case '5':

            filtro = opcionActividad();
            filtrarProductosActividad(archivo,filtro);

            if(filtro != '0'){

                limpiarYContinuar();
            }

            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }
}

void switchBusqueda(char archivo[])
{

    char filtro;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|  INGRESE EL METODO DE BUSQUEDA  |\n");
        printf("|                                 |\n");
        printf("| 1.Nombre de producto            |\n");
        printf("|                                 |\n");
        printf("| 2.ID de producto                |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("===================================\n");
        fflush(stdin);
        goTo(6,11);
        scanf("%c",&filtro);

        switchBusquedaDeProductos(archivo,filtro);

    }
    while (filtro != '0');

}

void switchBusquedaDeProductos(char archivo[],char filtro)
{

    switch (filtro)
        {

        case '0':
            break;

        case '1':
            buscarYmostrarProductoNombre(archivo);
            break;

        case '2':
            buscarYmostrarProductoID(archivo);
            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }

}

///Menu Ticket

void menuTicket(char archivoTicket[], char archivoMesas[], char archivoProductos[])
{

    char control2;

    do{

        system("cls");
        printf("============================\n");
        printf("|          TICKET          |\n");
        printf("|                          |\n");
        printf("| 1. Crear ticket          |\n");
        printf("|                          |\n");
        printf("| 2. Ver ticket            |\n");
        printf("|                          |\n");
        printf("| 3. Buscar ticket         |\n");
        printf("|                          |\n");
        printf("| 4. Editar ticket         |\n");
        printf("|                          |\n");
        printf("| 5. Cobrar ticket         |\n");
        printf("|                          |\n");
        printf("| 0. Volver                |\n");
        printf("|                          |\n");
        printf("| ->                       |\n");
        printf("============================\n");
        goTo(6,16);
        fflush(stdin);
        scanf("%c",&control2);

        if(control2=='1' || control2=='2' || control2=='3' ||control2=='4' ||control2=='5' || control2=='5'){

            switchTicketsAdmin(archivoTicket, archivoMesas,archivoProductos,control2);

        }else if(control2!='0'){

            mensajeErrorOpcionInvalida();

        }


    }while(control2 != '0');

}

void switchVerTIcket(char archivoTicket[])
{

    char operador;

    do
    {
        system("cls");
        printf(" ===================================\n");
        printf(" |                                 |\n");
        printf(" |            VER TICKET           |\n");
        printf(" |                                 |\n");
        printf(" | 1.Ver por fecha                 |\n");
        printf(" |                                 |\n");
        printf(" | 0.Volver                        |\n");
        printf(" |                                 |\n");
        printf(" | ->                              |\n");
        printf(" |                                 |\n");
        printf(" ===================================\n");
        goTo(8,9);
        fflush(stdin);
        scanf("%c",&operador);

        switch(operador)
        {
        case '0':
            break;
        case '1':
            filtrarTicketFecha(archivoTicket);
            break;
        default:
            mensajeErrorOpcionInvalida();
            break;
        }

    }while(operador != '0');
}

void switchTicketsAdmin(char archivoTicket[], char archivoMesas[], char archivoProductos[], char control2)
{

        system("cls");

        switch(control2){

            case '0':
                break;

            case '1':

                printf("============================\n");
                printf("|                          |\n");
                printf("|       CREAR TICKET       |\n");
                printf("|                          |\n");
                printf("============================\n");
                cargarTicketEnArchivo(archivoTicket,archivoProductos,archivoMesas);
                break;

            case '2':

                switchVerTIcket(archivoTicket);
                break;

            case '3':
                filtrarTicketPorID(archivoTicket,8,6);
                break;

            case '4':

                printf("============================\n");
                printf("|                          |\n");
                printf("|     MODIFICAR TICKET     |\n");
                printf("|                          |\n");
                printf("============================\n");
                editarTicket(archivoTicket,archivoProductos, archivoMesas);
                break;

            case '5':


                printf("============================\n");
                printf("|                          |\n");
                printf("|       COBRAR TICKET      |\n");
                printf("|                          |\n");
                printf("============================\n");
                cobrarTicket(archivoTicket,archivoMesas);
                break;


            default:
                mensajeErrorOpcionInvalida();
                break;
            }
}

///Logs

void menuLogs(char archivo[])
{

    system("cls");
    char opcion;

    do{

    opcion=opcionLogs();

    system("cls");
    switch(opcion){

case '1':

    printf("--Logs del dia--\n\n");
    mostrarLogsDelDia(archivo);

    break;
case '2':

    menuLogsPorFecha(archivo);

    break;

    }

    }while(opcion!='0');

}

void menuLogsPorFecha(char archivo[])
{

    Fecha f=ingresoFecha();

    mostrarLogsPorFecha(archivo,f);

}

///--------Menu Parte Empleado--------///

///Menu mesas
void switchMesaEmpleado(char archivoMesas[])
{
    char control;

    do
    {
        system("cls");
        printf("============================\n");
        printf("|          MESAS           |\n");
        printf("|                          |\n");
        printf("| 1. Ver mesa              |\n");
        printf("|                          |\n");
        printf("| 2. Buscar mesa           |\n");
        printf("|                          |\n");
        printf("| 0. Volver                |\n");
        printf("|                          |\n");
        printf("| ->                       |\n");
        printf("============================\n");
        goTo(6,10);
        fflush(stdin);
        scanf("%c",&control);

        switch(control)
        {
        case '0':
            break;

        case '1':

            system("cls");
            switchVerMesas(archivoMesas);

            break;

        case '2':
            system("cls");

            printf("============================\n");
            printf("|                          |\n");
            printf("|       BUSCAR MESAS       |\n");
            printf("|                          |\n");
            printf("============================\n");

            buscarYmostrarMesaPorID(archivoMesas);

            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }

    }
    while(control!='0');
}

///Menu Productos
void menuProductosEmpleado(char archivoProductos[])
{

    char opcion;

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|            PRODUCTOS            |\n");
        printf("|                                 |\n");
        printf("| 1.Ver producto                  |\n");
        printf("|                                 |\n");
        printf("| 2.Buscar producto               |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        goTo(6,11);
        fflush(stdin);
        scanf("%c",&opcion);

        if(opcion=='1' || opcion=='2'){

            switchMenuProductosEmpleado(archivoProductos, opcion);

        }else if(opcion!='1' && opcion!='2' && opcion!='0'){

            mensajeErrorOpcionInvalida();

        }

    }
    while (opcion != '0');

}

void switchMenuProductosEmpleado(char archivoProductos[], char opcion)
{

    switch (opcion) {

    case '1':

    menuVerProductos(archivoProductos);

        break;

    case '2':

    switchBusqueda(archivoProductos);

        break;

    }

}

///Cartel MiniRest
void imprimirMiniRest()
{
    system("cls");
    printf(ANSI_COLOR_SOFT_ORANGE" |_____||_____| |_____| |_____|\\____| |_____| |____| |___| |________|  \\______.'   |_____|   \n");
    Sleep(300);

    system("cls");
    printf("  _| |_\\/_| |_   _| |_   _| |_\\   |_   _| |_   _| |  \\ \\_   _| |__/ | | \\____) |    _| |_    \n");
    printf(" |_____||_____| |_____| |_____|\\____| |_____| |____| |___| |________|  \\______.'   |_____|   \n");

    Sleep(300);
    system("cls");
    printf("   | |\\  /| |     | |     | |\\ \\| |     | |     |  __ /      |  _| _   _.____`.      | |     \n");
    printf("  _| |_\\/_| |_   _| |_   _| |_\\   |_   _| |_   _| |  \\ \\_   _| |__/ | | \\____) |    _| |_    \n");
    printf(" |_____||_____| |_____| |_____|\\____| |_____| |____| |___| |________|  \\______.'   |_____|   \n");

    Sleep(300);
    system("cls");
    printf("   |   \\/   |     | |     |   \\ | |     | |     | |__) |     | |_ \\_| | (___ \\_| |_/ | | \\_| \n");
    printf("   | |\\  /| |     | |     | |\\ \\| |     | |     |  __ /      |  _| _   _.____`.      | |     \n");
    printf("  _| |_\\/_| |_   _| |_   _| |_\\   |_   _| |_   _| |  \\ \\_   _| |__/ | | \\____) |    _| |_    \n");
    printf(" |_____||_____| |_____| |_____|\\____| |_____| |____| |___| |________|  \\______.'   |_____|   \n");

    Sleep(300);
    system("cls");
    printf("  ____    ____   _____   ____  _____   _____   _______      ________    ______    _________  \n");
    printf(" |_   \\  /   _| |_   _| |_   \\|_   _| |_   _| |_   __ \\    |_   __  | .' ____ \\  |  _   _  | \n");
    printf("   |   \\/   |     | |     |   \\ | |     | |     | |__) |     | |_ \\_| | (___ \\_| |_/ | | \\_| \n");
    printf("   | |\\  /| |     | |     | |\\ \\| |     | |     |  __ /      |  _| _   _.____`.      | |     \n");
    printf("  _| |_\\/_| |_   _| |_   _| |_\\   |_   _| |_   _| |  \\ \\_   _| |__/ | | \\____) |    _| |_    \n");
    printf(" |_____||_____| |_____| |_____|\\____| |_____| |____| |___| |________|  \\______.'   |_____|   \n\n\n"ANSI_COLOR_RESET);
    Sleep(300);
}

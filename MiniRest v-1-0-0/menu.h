#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

///--------Menus generales--------///

///Menu general admin
void menuGeneralAdmin(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[],char inicioID[],char nombreInicioActual[]);
void caseMenuAdmin(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[],char control);

///Menu general empleado
void menuGeneralEmpleado(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char inicioID[],char nombreInicioActual[]);
void caseMenuEmpleado(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char control);

///Menu empleados admin
void menuEmpleadoAdmin(char archivoEmpleado[]);
void switchEmpleado(char archivo[], char control);
void menuMostrarEmpleadosAdmin(char archivoEmpleados[]);
void menuElegirFiltroEmpleados(char archivoEmpleados[],char opcion);
void switchFiltroEmpleados(char archivo[], char filtro);
void menuBusquedaEmpleados(char archivoEmpleados[]);

///Menu mesas admin
void switchVerMesas(char archivo[]);
void switchFiltrarMesas(char archivo[]);
void switchMesa(char archivoMesas[]);
void switchMesaEmpleado(char archivoMesas[]);

///Menu Ticket
void menuTicket(char archivoTicket[], char archivoMesas[], char archivoProductos[]);
void switchVerTIcket(char archivoTicket[]);
void switchTicketsAdmin(char archivoTicket[], char archivoMesas[], char archivoProductos[], char control2);

///Logs
void menuLogs(char archivo[]);
void menuLogsPorFecha(char archivo[]);

///Menu productos admin
void menuProductos(char archivo[]);
void switchMenu2(char archivo[], char opcion);
void menuVerProductos(char archivo[]);
void switchFiltradoGeneral(char archivo[]);
void switchFiltradoProductos(char archivo[], char filtro1);
void switchBusqueda(char archivo[]);
void switchBusquedaDeProductos(char archivo[],char filtro);

///--------Menu productos empleado--------///
void menuProductosEmpleado(char archivoProductos[]);
void switchMenuProductosEmpleado(char archivoProductos[], char opcion);


///Cartel MiniRest
void imprimirMiniRest();

#endif // MENU_H_INCLUDED

#ifndef MENSAJESERROR_H_INCLUDED
#define MENSAJESERROR_H_INCLUDED

///ERRORES GENERALES
void mensajeErrorOpcionInvalida();
void mensajeErrorDePrograma();
void datosIngresadosIncorrectos();
void errorLargoId();
void nombreInexistente();
void idInexistente();

///ERRORES DE MESA
void errorMesaInexiste();
void errorMesaExistente();

///EMPLEADOS
void dniExistente();
void dniInexistente();


///TICKET
void ticketYaCobrado();
void faltaStock();
void noSeEncontroTicket();

///LOGS
void noRegistro();

#endif // MENSAJESERROR_H_INCLUDED

#ifndef INICIOSESION_H_INCLUDED
#define INICIOSESION_H_INCLUDED

///Inicio sesion
void cargaDelPrograma();
void inicioSesionPrograma(char archivoMesas[],char archivoProductos[],char archivoEmpleados[],char archivoTicket[],char archivoLogs[]);
char inicioPrograma(char entradaSalida);
void inicioLogIn(char inicioID[],char inicioContra[]);
int inicioSesion(char archivo[],char inicioID[],char inicioContra[]);

///Verificacion de datos
int verificacionIDempleado(char archivo[], char id[]);
int verificacionContraEmpleado(char archivo[],char contra[],char id[]);
int verificacionRolAdministrativo(char archivo[], char id[]);
int verificacionEstadoActividad(char archivo[], char id[]);

///Identificador de nombre
void identificarNombre(char archivo[],char inicioID[],char nombre[]);
#endif // INICIOSESION_H_INCLUDED

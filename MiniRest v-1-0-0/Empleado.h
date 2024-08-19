#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#define CLAVE_ADMIN "1234"
#define CLAVE_EMPLEADO "1111"

///STRUCT
typedef struct
{

    char id[9]; //NRO DE DNI
    char nombreApellido[30];
    char clave[5]; //CONTRASEÑA
    int rolAdministrativo; //1-Admin, 2-Empleado
    int estadoActividad; //1-Activo, 0-Inactivo

} Empleado;

///MUESTRA DE EMPLEADOS
void mostrarEmpleado (Empleado e);
void verTodoEmpleados(char archivo[]);

///CARGA DE EMPLEADOS
void cargarEmpleados(char archivo[]);
Empleado cargarEmpleadoDeAUno(char archivo[]);

///FILTRADO DE EMPLEADOS
int pasajeEmpleadosArreglo(char archivo[],Empleado arrEmpleados[], int validos, int dim);
void filtrarEmpleadosActividad(char archivo[]);
void filtrarEmpleadosID(char archivo[]);
void filtrarEmpleadosNombres(char archivo[]);
void filtrarEmpleadosPorRol(char archivo[]);

///ORDENAMIENTO DEL ARREGLO
int buscarPosMenor(int validos, int i, Empleado e[]);
void ordenarPorSeleccion(int validos, Empleado e[]);
void insertarEmpleadoNombre(Empleado arrEmpleados[], Empleado insertada, int validos);
void ordenarEmpleadosMenorAmayorNombre(Empleado arrEmpleados[], int validos);

///BUSQUEDA DE EMPLEADOS
Empleado buscarYRetornarEmpleado(char archivo[],int pos);
int buscarEmpleadoPorID(char archivo[], char idBuscado[]);
void buscarEmpleadoPorNombre(char archivo[],char nombre[]);

///EDICION DE EMPLEADOS
void editarEmpleados(char archivo[]);
void switchEditarEmpleado(char archivo[], Empleado e, int pos);
void editarNombreEmpleado(char archivo[],Empleado e,int pos);
void editarIdEmpleado(char archivo[],Empleado e,int pos);
void editarIdEmpleado(char archivo[],Empleado e,int pos);
void editarActivacionEmpleados(char archivo[],Empleado e,int pos);
void sobreescribirEmpleado(char archivo[],Empleado e, int pos);

#endif // EMPLEADO_H_INCLUDED

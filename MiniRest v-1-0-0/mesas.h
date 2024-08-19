#ifndef MESAS_H_INCLUDED
#define MESAS_H_INCLUDED

typedef struct
{

    char id[5];
    int estadoOcupacion; //1-Ocupada, 0-Desocupada
    int estadoActividad; //1-Activo, 0-Inactiva

} Mesa;

///ALTA
Mesa agregarMesaDeAuno(char archivo[]);
void agregarMesaEnArchivo(char archivo[]);

///BAJA

//Tambien se usa sobreescribir mesa para la baja

///CONSULTA
void ingresarIDMesaBuscado(char id[], char archivo[]);
int buscarMesaPorID(char archivo[], char idBuscado[]);
Mesa buscarYRetornarMesa(char archivo[],int pos);
void buscarYmostrarMesaPorID(char archivo[]);

///LISTADO
void mostrarMesa(Mesa m);
void insertarMesa(Mesa arrMesa[], Mesa insertada, int validos);
void ordenarMesasMenorAmayor(Mesa arrMesa[], int validos);
int pasarMesaAarreglo(char archivo[], Mesa arrMesa[], int validos, int dim);
void mostrarArregloMesas(Mesa arrMesa[], int validos);
void mostrarArregloMesasDesdeFinal(Mesa arrMesa[], int validos);
void filtrarMesasActividad(char archivo[]);
void filtrarMesasMayorAmenor(char archivo[]);
void filtrarMesasOcupacion(char archivo[]);
void verTodoMesas(char archivo[]);

///MODIFICACION
void sobreescribirMesa(char archivo[],Mesa m, int pos);
void editarIdMesa(char id[], char archivo[]);
int editarEstadoOcupacion(int estadoViejo);
void editarMesa(char archivo[]);
Mesa switchEditarMesa(Mesa m, char *flag, char archivo[]);

#endif // MESAS_H_INCLUDED

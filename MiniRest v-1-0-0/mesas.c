#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesAuxiliares.h"
#include "mensajesAviso.h"
#include "mensajesError.h"
#include "mesas.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

///ALTA

Mesa agregarMesaDeAuno(char archivo[]) //Carga una mesa y la retorna
{

    Mesa m;
    int flag;

    m.estadoActividad = 1;//Inicializa el estado de actividad de la mesa como ACTIVA
    m.estadoOcupacion = 0;//Inicializa el estado de ocupacion de la mesa como INACTIVO
    printf("============================\n");
    printf("|                          |\n");
    printf("|       INGRESE EL ID      |\n");
    printf("|        DE LA MESA        |\n");
    printf("|                          |\n");
    printf("| ->                       |\n");
    printf("|                          |\n");
    printf("|  INGRESE 0 PARA SALIR    |\n");
    printf("============================\n");
    printf("======================================\n");
    printf("|            "ANSI_COLOR_RED"ADVERTENCIA"ANSI_COLOR_RESET"             |\n");
    printf("|                                    |\n");
    printf("|  El id ingresado debe ser mayor    |\n");
    printf("|  a 4 caracteres.                   |\n");
    printf("|  EJEMPLO. ID : 0001                |\n");
    printf("|                                    |\n");
    printf("======================================\n");

    do
    {
        fflush(stdin);
        goTo(6,11);
        gets(m.id);//Pide el ingreso de el id de mesa

        if(strcmp(m.id,"0")!=0) //Si el usuario no ingreso 0 significa que intentó ingresar un id valido y no quiere salir de la pantalla.
        {
            if(strlen(m.id) != 4)//Si el largo del id no es de 4, no es un id valido
            {
                goTo(0,10);
                printf("|    "ANSI_COLOR_RED"INGRESE UN ID VALIDO"ANSI_COLOR_RESET"  |\n");//Imprime el error y limpia la pantalla para que vuelva a ingresar un id
                printf("| ->                       |\n");

            }else if (strlen(m.id) == 4)
            {
                flag = buscarMesaPorID(archivo,m.id);

                if(flag >= 0)//Si flag es mayor a -1 significa que la mesa ya existe
                {
                    goTo(0,10);
                    printf("|      "ANSI_COLOR_RED"LA MESA YA EXISTE"ANSI_COLOR_RESET"   |\n");//Imprime el error y limpia la pantalla para que vuelva a ingresar un id
                    printf("| ->                       |\n");
                }
            }
        }

    }while( (strlen(m.id) != 4 && strcmp(m.id,"0")!=0) || (flag >= 0 && strcmp(m.id,"0")!=0));//Mientras el id no sea valido, y el usuario no quiera salir, repite el proceso

    return m;
}

void agregarMesaEnArchivo(char archivo[]) //Carga una mesa en un archivo
{
    FILE *buff;

    Mesa m;

    char control;

    m = agregarMesaDeAuno(archivo);//Carga una mesa en "m"

    if ( strcmp(m.id,"0") != 0 )//Si el usuario no ingreso 0 significa que ingresó un id valido
    {
        buff = fopen(archivo,"ab");

        if(buff)
        {
            do{

                system("cls");
                mostrarMesa(m);//Le muestra la mesa que cargó al usuario
                control = guardarCambios(6,19);//Pregunta si quiere guardar los cambios

                if(control == '1')//Guarda los cambios si es que el usuario asi lo desea.
                {
                    fwrite(&m,sizeof(Mesa),1,buff);
                    mesaGuardada();
                }
            }while(control != '1' && control != '2');
            fclose(buff);
        }
        else// Si el buffer no abrio imprime un msj de error
        {
            mensajeErrorDePrograma();
        }
    }
}

///BAJA
//USA SOBREEESCRIBIR MESA Y DE funcionesAuxiliares.h usa editarEstadoActividad

///CONSULTA

void ingresarIDMesaBuscado(char id[], char archivo[]) //Muestra un mensaje y pide que se ingrese un id de mesa
{
    int flag;

    printf("============================\n");
    printf("|                          |\n");
    printf("|       INGRESE EL ID      |\n");
    printf("|        DE LA MESA        |\n");
    printf("|       0 PARA SALIR       |\n");
    printf("| ->                       |\n");
    printf("|                          |\n");
    printf("============================\n");

    do
    {
        fflush(stdin);
        goTo(6,11);
        gets(id);//Pide el ingreso de el id de mesa

        if(strcmp(id,"0")!=0) //Si el usuario no ingreso 0 significa que intentó ingresar un id valido y no quiere salir de la pantalla.
        {
            if(strlen(id) != 4)//Si el largo del id no es de 4, no es un id valido
            {
                goTo(0,10);
                printf("|    "ANSI_COLOR_RED"INGRESE UN ID VALIDO"ANSI_COLOR_RESET"  |\n");//Imprime el error y limpia la pantalla para que vuelva a ingresar un id
                printf("| ->                       |\n");

            }else if (strlen(id) == 4)
            {
                flag = buscarMesaPorID(archivo,id);

                if(flag < 0)//Si flag es menor a -1 significa que la mesa no existe
                {
                    goTo(0,10);
                    printf("|      "ANSI_COLOR_RED"LA MESA NO EXISTE"ANSI_COLOR_RESET"   |\n");//Imprime el error y limpia la pantalla para que vuelva a ingresar un id
                    printf("| ->                       |\n");
                }
            }
        }

    }while( (strlen(id) != 4 && strcmp(id,"0")!=0) || (flag < 0 && strcmp(id,"0")!=0));//Mientras el id no sea valido, y el usuario no quiera salir, repite el proceso
}

int buscarMesaPorID(char archivo[], char idBuscado[]) //Busca una mesa en el archivo, si la encuentra devuelve su posicion, sino devuelve -1
{
    FILE *buff = fopen(archivo,"rb");

    Mesa m;

    int i = 0;
    int flag = 0;

    if(buff)
    {
        while( (fread(&m,sizeof(Mesa),1,buff))>0 && flag == 0)
        {

            if(strcmp(m.id,idBuscado)==0) //Si encuentra la mesa declara flag como 1 para cortar la busqueda
            {
                flag = 1;
            }

            i++;
        }
        fclose(buff);

    }
    else
    {
        mensajeErrorDePrograma();
    }

    if(flag != 1)// si no encontro la mesa, cambia lo que guarda i a 1 asi devuelve -1
    {
        i = 0;
    }

    return i-1;

}

Mesa buscarYRetornarMesa(char archivo[],int pos) //Busca y retorna una mesa por posicion
{
    FILE *buff = fopen(archivo,"rb");

    Mesa m;

    if(buff)
    {
        fseek(buff,sizeof(Mesa)*pos,0); //Posiciona el cursor en la posicion pasada por parametro
        fread(&m,sizeof(Mesa),1,buff);// Lee la mesa para retornarla
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

    return m;
}

void buscarYmostrarMesaPorID(char archivo[]) //Busca y muestra una mesa por su id
{
    char idBuscado[5];

    Mesa m;

    int pos;

    ingresarIDMesaBuscado(idBuscado, archivo); //Ingresa un id de mesa

    system("cls");

    if(strcmp(idBuscado,"0")!=0)
    {
        pos = buscarMesaPorID(archivo,idBuscado);// Busca la mesa ingresada

        if( pos >= 0)
        {
            m = buscarYRetornarMesa(archivo,pos);// Retorna la mesa
            mostrarMesa(m);//Muestra la mesa
            limpiarYContinuar();
        }
        else
        {
           errorMesaInexiste();
        }
    }
}

///LISTADO

void mostrarMesa (Mesa m) //Muestra la mesa pasada por parametro
{

    printf("===================================\n");
    printf("|                                 |\n");
    printf("| ID/Numero de mesa: %s         |\n", m.id);
    printf("|                                 |\n");

    if (m.estadoOcupacion == 1)
    {
        printf("| Estado de Ocupacion: Ocupada    |\n");
    }
    else
    {
        printf("| Estado de Ocupacion: Desocupada |\n");
    }

    printf("|                                 |\n");

    if (m.estadoActividad == 1)
    {

        printf("| Estado de Actividad: Activo     |\n");

    }
    else
    {

        printf("| Estado de Actividad: Inactivo   |\n");

    }
    printf("|                                 |\n");
    printf("===================================\n");
}

void insertarMesa(Mesa arrMesa[], Mesa insertada, int validos) //Inserta una mesa
{

    while(validos>=0 && strcmp(arrMesa[validos].id,insertada.id)>0)
    {
        arrMesa[validos+1] = arrMesa[validos];
        validos--;
    }

    arrMesa[validos+1] = insertada;
}

void ordenarMesasMenorAmayor(Mesa arrMesa[], int validos) //Ordena las mesas por su id de mayor a menor por metodo de insercion
{
    for(int i = 0; i<validos-1; i++)
    {
        insertarMesa(arrMesa,arrMesa[i+1],i);
    }
}

int pasarMesaAarreglo(char archivo[], Mesa arrMesa[], int validos, int dim) //Pasa un archivo de mesas a un arreglo
{
    FILE *buff = fopen(archivo,"rb");

    Mesa m;

    if(buff)
    {
        while( (fread(&m,sizeof(Mesa),1,buff)) > 0 && validos<dim)//Mientras que lea una mesa y validos sea menor a la dimension pasada agrega la mesa leida al arreglo pasado por parametro
        {
            arrMesa[validos] = m;
            validos++;
        }

        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

    return validos; //Retorna los validos
}

void mostrarArregloMesas(Mesa arrMesa[], int validos) //Muestra un arreglo de mesas de la posicion 0 al final
{
    for(int i = 0; i<validos; i++)
    {
        mostrarMesa(arrMesa[i]);
    }
}

void mostrarArregloMesasDesdeFinal(Mesa arrMesa[], int validos) //Muestra un arreglo de mesas desde la posicion final a la 0
{
    validos--;

    for(validos; validos >= 0 ; validos--)
    {
        mostrarMesa(arrMesa[validos]);
    }
}

void filtrarMesasActividad(char archivo[]) //Filtra y muestra las mesas por actividad
{
    char opcion;

    opcion = opcionActividad(); //Pide que ingrese si desea ver las mesas activas o inactivas

    Mesa m;

    if(opcion == '1' || opcion == '2') //Si la opcion es valida y no quiere salir muestra las mesas
    {
        FILE *buff = fopen(archivo,"rb");

        if(buff)
        {
            if(opcion == '1')
            {
                printf("===================================\n");
                printf("|                                 |\n");
                printf("|          MESAS ACTIVAS          |\n");
                printf("|                                 |\n");
                printf("===================================\n");
                while( (fread(&m,sizeof(Mesa),1,buff)) > 0)//Lee la mesa
                {
                    if(m.estadoActividad == 1) //Si el estado coincide con lo que el usuario quiere ver la muestra
                    {
                        mostrarMesa(m);
                    }
                }
                limpiarYContinuar();
            }
            else
            {
                printf("===================================\n");
                printf("|                                 |\n");
                printf("|         MESAS INACTIVAS         |\n");
                printf("|                                 |\n");
                printf("===================================\n");

                while( (fread(&m,sizeof(Mesa),1,buff)) > 0)//Lee la mesa
                {
                    if(m.estadoActividad == 0)//Si el estado coincide con lo que el usuario quiere ver la muestra
                    {
                        mostrarMesa(m);
                    }
                }
                limpiarYContinuar();
            }

            fclose(buff);
        }
        else
        {
            mensajeErrorDePrograma();
        }
    }
}

void filtrarMesasMayorAmenor(char archivo[]) //Filtra las mesas de mayor a menor o al reves segun asi lo desee el usuario
{
    char opcion;

    int validos = calcularValidosArchivos(archivo,sizeof(Mesa));//Calcula los validos del archivo

    Mesa arrMesa[validos];

    pasarMesaAarreglo(archivo,arrMesa,0,validos);//Pasa las mesas del archivo al arreglo

    ordenarMesasMenorAmayor(arrMesa,validos); //Ordena las mesas por metodo de insercion

    opcion = opcionOrdenado(); //Le pregunta al usuario si en el orden que las quiere ver

    if(opcion == '1')//Si la opcion es 1 la muestra desde la posicion 0 a la final
    {
        mostrarArregloMesas(arrMesa,validos);
        limpiarYContinuar();
    }
    else if (opcion == '2')//Si la opcion es 2 la muestra desde la posicion final a la 0
    {
        mostrarArregloMesasDesdeFinal(arrMesa,validos);
        limpiarYContinuar();
    }
}

void filtrarMesasOcupacion(char archivo[]) //Filtra y muestra las mesas por ocupacion
{
    char opcion;

    opcion = opcionOcupacion();//Le pregunta al usuario si quiere ver las mesas ocupadas o desocupadas

    Mesa m;

    if(opcion == '1' || opcion == '2')//Si el usuario ingreso una opcion valida y no quiso salir abre el archivo para mostrar las mesas
    {
        FILE *buff = fopen(archivo,"rb");

        if(buff)
        {
            if(opcion == '1')//Si la opcion es 1 muestra las mesas ocupadas
            {
                printf("===================================\n");
                printf("|                                 |\n");
                printf("|         MESAS OCUPADAS          |\n");
                printf("|                                 |\n");
                printf("===================================\n");
                while( (fread(&m,sizeof(Mesa),1,buff)) > 0)
                {
                    if(m.estadoOcupacion == 1)//Si el estado de la mesa coincide con el que el usuario quiere ver, muestra la mesa
                    {
                        mostrarMesa(m);
                    }
                }
                limpiarYContinuar();
            }
            else//Si el usuario ingresó 2 muestra las mesas desocupadas
            {   printf("===================================\n");
                printf("|                                 |\n");
                printf("|        MESAS DESOCUPADAS        |\n");
                printf("|                                 |\n");
                printf("===================================\n");
                while( (fread(&m,sizeof(Mesa),1,buff)) > 0)
                {
                    if(m.estadoOcupacion == 0)//Si el estado de la mesa coincide con el que el usuario quiere ver, muestra la mesa
                    {
                        mostrarMesa(m);
                    }
                }
                limpiarYContinuar();
            }
            fclose(buff);
        }
        else
        {
            mensajeErrorDePrograma();
        }
    }

}

void verTodoMesas(char archivo[]) //Muestra todas las mesas
{
    system("cls");

    FILE *buff = fopen(archivo,"rb");

    Mesa m;

    if(buff)//Abre el archivo y muestra todas las mesas existentes hasta que deje de leer mesas
    {
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|             MESAS               |\n");
        printf("|                                 |\n");
        printf("===================================\n");
        while( (fread(&m,sizeof(Mesa),1,buff)) > 0)
        {
            mostrarMesa(m);
        }
        limpiarYContinuar();

        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

}

///MODIFICACION
void sobreescribirMesa(char archivo[],Mesa m, int pos) //Sobreescribe una mesa en el archivo en la posicion pasada por parametro
{
    FILE *buff;

    if (pos >= 0) //Si la posicion es mayor o igual a 0 significa que la encontró entonces abre el archivo para modificarla
    {
        buff = fopen(archivo,"r+b");

        if(buff){

            fseek(buff,sizeof(Mesa)*pos,0);
            fwrite(&m,sizeof(Mesa),1,buff);

            fclose(buff);

        }else{

        mensajeErrorDePrograma();

        }
    } else
    {
        errorMesaExistente();
    }
}

void editarIdMesa(char id[], char archivo[]) //Pide el ingreso de un nuevo id de mesa
{
    int flag;

    printf("===================================\n");
    printf("|                                 |\n");
    printf("|       INGRESE EL NUEVO ID       |\n");
    printf("|          EJEMPLO: 0001          |\n");
    printf("|      O PRESIONE 0 PARA SALIR    |\n");
    printf("|                                 |\n");
    printf("| ->                              |\n");
    printf("|                                 |\n");
    printf("===================================\n");

    do
    {
        fflush(stdin);
        goTo(6,7);
        gets(id);

        if(strcmp(id,"0")!=0)
        {
            if(strlen(id) != 4)
            {
                goTo(0,6);
                printf("|    "ANSI_COLOR_RED"INGRESE UN ID VALIDO"ANSI_COLOR_RESET"         |\n");
                printf("| ->                              |\n");

            }else if (strlen(id) == 4)
            {
                flag = buscarMesaPorID(archivo,id);

                if(flag >= 0)
                {
                    goTo(0,6);
                    printf("|      "ANSI_COLOR_RED"LA MESA YA EXISTE"ANSI_COLOR_RESET"          |\n");
                    printf("| ->                              |\n");
                }
            }
        }
    }while( (strlen(id) != 4 && strcmp(id,"0")!=0) || (flag >= 0 && strcmp(id,"0")!=0));
}

int editarEstadoOcupacion(int estadoViejo) //Edita el estado de ocupacion automaticamente
{

    if(estadoViejo == 0)
    {
        estadoViejo = 1;
    }
    else
    {
        estadoViejo = 0;
    }

    return estadoViejo;

}

void editarMesa(char archivo[]) //Edita una mesa ,elegida por el usuario, en el archivo
{
    char idBuscado[5];
    char control;
    int pos;
    Mesa m;

    ingresarIDMesaBuscado(idBuscado, archivo);

    pos = buscarMesaPorID(archivo,idBuscado); //Busca la mesa ingresada

    if( pos >= 0 && strcmp(idBuscado,"0")!= 0)//Si la mesa existe y el usuario no quiso salir pasa a buscar la mesa y retornarla para editarla
    {
        m = buscarYRetornarMesa(archivo,pos);
        system("cls");
        m = switchEditarMesa(m, &control, archivo);
        system("cls");

        if(control != '0' && strcmp(m.id,"0")!=0) //Si la mesa fue editada y el usuario no quiso salir en ningun momento del programa pasa a editar la nueva mesa
        {
            printf("===================================\n");
            printf("|                                 |\n");
            printf("|           NUEVA MESA            |\n");
            printf("|                                 |\n");
            printf("===================================\n");
            printf("\n");

            do{

                system("cls");
                mostrarMesa(m);//Muestra la mesa editada
                control = guardarCambios(6,19); //Pregunta si quiere guardar los cambios

                if(control == '1')//Si el usuario quiso guardar los cambios, sobreeescribe la mesa en el archivo en la posicion que estaba
                {
                    sobreescribirMesa(archivo,m,pos);
                    mesaGuardada();
                }

            }while(control != '1' && control != '2');

        }
    }
}

Mesa switchEditarMesa(Mesa m, char *flag, char archivo[]) //Switch para editar mesa
{
    char operador;
    do
    {
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|    ELIJA UNA OPCION A EDITAR    |\n");
        printf("|                                 |\n");
        printf("| 1.ID/Numero                     |\n");
        printf("|                                 |\n");
        printf("| 2.Estado de ocupacion           |\n");
        printf("|                                 |\n");
        printf("| 3.Dar de baja/reactivar         |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("===================================\n");
        fflush(stdin);
        goTo(6,13);
        scanf("%c",&operador);

        system("cls");

        switch(operador)
        {
        case '0':
            break;

        case '1':
            editarIdMesa(m.id, archivo);

            if( strcmp(m.id,"0")!=0 ){
                *flag = 1;//Cambia flag a 1 para indicar que se realizo un cambio en la mesa
            }

            break;

        case '2':
            m.estadoOcupacion = editarEstadoOcupacion(m.estadoOcupacion);
            *flag = 1;//Cambia flag a 1 para indicar que se realizo un cambio en la mesa
            break;

        case '3':
            m.estadoActividad = editarEstadoActividad(m.estadoActividad);
            *flag = 1;//Cambia flag a 1 para indicar que se realizo un cambio en la mesa
            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }

        if(*flag == 1 && (operador=='1' || operador=='2' || operador=='3') ){

            cambiosGuardados();

        }

        system("cls");

    }while(operador != '0'); //Mientras el usuario quiera cambiar campos de la mesa se repite el menu, y mientras el usuario ingrese una opcion invalida

    return m;
}


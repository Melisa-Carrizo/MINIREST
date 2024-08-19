#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Empleado.h"
#include "funcionesAuxiliares.h"
#include "inicioSesion.h"
#include "mensajesAviso.h"
#include "mensajesError.h"
#include "menu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

///--------MUESTRA DE EMPLEADOS--------///
void mostrarEmpleado (Empleado e)///Muestra una planilla con los datos de un empleado
{
    int cantEspacios;
    printf(" =================================================\n");
    printf(" |                                               |\n");
    printf(" |  Nombre: %s",e.nombreApellido);                      //Printf al nombre del empleado

    cantEspacios = 37-strlen(e.nombreApellido);
    for(int i = 0; i<cantEspacios; i++)
    {
        printf(" ");
    }
    printf("|\n");

    printf(" |                                               |\n");
    printf(" |  ID: %s                                 |\n",e.id); //Printf al ID/DNI del empleado
    printf(" |                                               |\n");

    if(e.rolAdministrativo==1)                                     //Printf al rol del empleado el cual es determinado por su atributo
    {                                                              //y lo muestra segun indique el condicional
        printf(" |  Rol Administrativo: Administrador            |\n");

    }
    else if(e.rolAdministrativo == 2)
    {
        printf(" |  Rol Administrativo: Empleado                 |\n");

    }
    printf(" |                                               |\n");
    if(e.estadoActividad==1)                                       //Printf al estado de actividad del empleado el cual es determinado por su atributo
    {                                                              //y lo muestra segun indique el condicional
        printf(" |  Estado de actividad: Activo                  |\n");


    }
    else
    {
        printf(" |  Estado de actividad: Inactivo                |\n");

    }

    printf(" |                                               |\n");
    printf(" =================================================\n");

}

void verTodoEmpleados(char archivo[])//Muestra todos los empleados del archivo recibido por parametros
{
    system("cls");

    FILE* buff = fopen(archivo,"rb"); //Abre el archivo en lectura e inicializa el buff

    Empleado aux;

    if(buff)
    {
        while( (fread(&aux,sizeof(Empleado),1,buff)) > 0)   //Si el buff se abre correctamente entra en bucle mientras hay empleados para leer
        {
            mostrarEmpleado(aux);   //Cada vez que lee un empleado los envia a mostrarEmpleados como parametro para mostrarlo
        }

        fclose(buff);  //Cierra el buffer

    }
    else
    {
        mensajeErrorDePrograma(); //Mensaje de error si no se puede abrir el archivo
    }

}


///--------CARGA DE EMPLEADOS--------///
void cargarEmpleados(char archivo[])///Guarda empleado en el archivo recibido
{

    FILE* buff = fopen(archivo,"ab"); //Crea e inicializa el buff y abre el archivo para escribir a continuacion de lo ultimo cargado

    char confirmar;
    Empleado aux;

    int verificacion;

    aux=cargarEmpleadoDeAUno(archivo);  //Se llama a la funcion para cargar un empleado donde se rellena una plantilla con su informacion y se guarda en el empleado aux

    if(buff)
    {
        system("cls");
        if(strcmp(aux.nombreApellido,"0")!= 0 && strcmp(aux.id,"0")!= 0 && aux.rolAdministrativo != 0)//Compara si que la info ingresada sea distinta de 0, si es 0
        {
            //directamente sale de la funcionalidad, sino, entra
            mostrarEmpleado(aux);

            confirmar = guardarCambios(7,21);   //Confirmacion antes de guardar los datos del empleado

            if(confirmar == '1')    //Si ingreso para guardar el empleado entra a la verificacion
            {
                verificacion=verificacionIDempleado(archivo,aux.id);    //Verifica el id del empleado si ya esta cargado en el archivo
                //si esta cargado tirara un mensaje de error de dni existente,sino,lo guardara
                if(verificacion == -1 || verificacion == 1)
                {

                    fwrite(&aux,sizeof(Empleado),1,buff);
                    empleadoGuardado();

                }
                else
                {
                    dniExistente(); //Mensaje de error dni existente
                }
            }

        }

        fclose(buff);   //Cierra el buff
    }
    else
    {
        mensajeErrorDePrograma();   //Mensaje de error de programa si no se abre bien el archivo
    }

}

Empleado cargarEmpleadoDeAUno(char archivo[])///Pide los datos del empleado y lo retona para que la otra funcion lo guarde
{

    Empleado e;
    int flag;
    //planilla de informacion la cual vera el usuario y donde ingresara la informacion del empelado que quiera cargar
    printf(" =============================================\n");
    printf(" |                                           |\n");
    printf(" |       INGRESE EL NOMBRE Y APELLIDO        |\n");
    printf(" |                DEL EMPLEADO               |\n");
    printf(" |           (hasta 29 caracteres)           |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |       INGRESE EL DNI DEL EMPLEADO         |\n");
    printf(" |                                           |\n");
    printf(" |               "ANSI_COLOR_RED"ADVERTENCIA"ANSI_COLOR_RESET"                 |\n");
    printf(" |     Si el dni es menor a 8 caracteres     |\n");
    printf(" |              complete con 0.              |\n");
    printf(" |             EJEMPLO: 01234567             |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |       INGRESE EL ROL DEL EMPLEADO         |\n");
    printf(" |                                           |\n");
    printf(" |  1. Administrativo                        |\n");
    printf(" |                                           |\n");
    printf(" |  2. Empleado                              |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |          PARA SALIR PRESIONE 0 EN         |\n");
    printf(" |          CUALQUIERA DE LOS CAMPOS         |\n");
    printf(" =============================================\n");

    goTo(8,7);  //acomoda el texto en la pantalla
    fflush(stdin);
    gets(e.nombreApellido); //lee el nombre ingresado por el usuario
    if( strcmp(e.nombreApellido,"0") != 0 ) //verifica que el nombre sea distinto de 0, si es 0, sale de la funcion
    {                                       //sino, ingresa al condicional

        do
        {

            goTo(8,16);
            fflush(stdin);
            gets(e.id); //lee el id ingresado por el usuario

            if(strcmp(e.id,"0")!=0){

                if(strlen(e.id)!= 8 && strcmpi(e.id,"0")!= 0)//Si el id ingresado el distinto a 8 de largo y es 0, tira un mensaje de id no valido
                {
                    goTo(0,15);
                    printf(" |          "ANSI_COLOR_RED"INGRESE UN DNI/ID VALIDO"ANSI_COLOR_RESET"         |\n");
                    printf(" |  ->                                       |\n");
                }
                else    //Si el id es valido verificara que el id ingresado no exista, si existe, tira un mensaje de error
                {
                    flag = buscarEmpleadoPorID(archivo,e.id); //si la funcion encuentra al empleado con el id ingresado ya cargado retorna 1
                    if(flag >= 0)
                    {
                        goTo(0,15);
                        printf(" |            "ANSI_COLOR_RED"EL DNI YA EXISTE"ANSI_COLOR_RESET"               |\n");
                        printf(" |  ->                                       |\n");
                    }
                }

            }

        }
        while( (strlen(e.id) != 8 && strcmp(e.id,"0")!=0) || (flag >= 0 && strcmp(e.id,"0")!=0));//Repetira esto hata que el id sea de largo distinto a 8 y que el id no sea 0

    if(strcmp(e.id,"0")!=0 && strcmp(e.nombreApellido,"0")!=0){

            do
            {
                goTo(8,24);
                scanf("%d",&e.rolAdministrativo);   //Lee el numero ingresado por el usuario
                if(e.rolAdministrativo != 1 && e.rolAdministrativo != 2 && e.rolAdministrativo != 0)    //si el rol ingresado es distinto de 1, 2 o 0 muestra un mensaje de error
                {
                    goTo(0,23);
                    printf(" |     "ANSI_COLOR_RED"INGRESE UNA OPCION DE ROL VALIDO"ANSI_COLOR_RESET"      |\n");
                    printf(" |  ->                                       |\n");
                }

            }
            while(e.rolAdministrativo != 1 && e.rolAdministrativo != 2 && e.rolAdministrativo != 0);///repetira esto hasta que la opcion ingresada sea 1, 2 o 0


            e.estadoActividad = 1;  //Pone el estado de actividad como activo por default

            if(e.rolAdministrativo == 1)    //Setea la contraseña del usuario dependiendo del su rol administrativo
            {
                strcpy(e.clave,CLAVE_ADMIN);    //le asigna 1234 si es admin

            }
            else if (e.rolAdministrativo == 2)
            {
                strcpy(e.clave,CLAVE_EMPLEADO); //le asigna 1111 si es empleado
            }
        }

    }

    return e;   //retorna el empleado cargado
}


///--------FILTRADO DE EMPLEADOS--------///
int pasajeEmpleadosArreglo(char archivo[],Empleado arrEmpleados[], int validos, int dim)//Pasa los empleados a un arreglo para operar comodamente a la hora de filtrar y mostrar
{

    FILE *buff = fopen(archivo,"rb");   //abre el archivo en lectura

    Empleado e;

    if(buff)    //si se abre correctamente el archivo entra al condicional
    {
        while( (fread(&e,sizeof(Empleado),1,buff)) > 0 && validos<dim) //mientras lea un empleado y los validos sean menpres que la dimension, guarda el empleado ledigo en e
        {
            arrEmpleados[validos] = e;  //guarda en el arreglo de empleados en la posicion de validos el empleado leido e incrementa validos
            validos++;
        }

        fclose(buff);   //cierra el buff
    }
    else    //sino se abre correctamente, muestra un mensaje de error del programa
    {
        mensajeErrorDePrograma();
    }

    return validos; //retorna los validos del arreglo
}

void filtrarEmpleadosActividad(char archivo[]) ///filtrara y muestra los empleados segun su estado de actividad
{

    FILE* buff = fopen(archivo,"rb");   //Abre el archivo en modo lectura

    Empleado e;

    char dato;  //la variable dato es donde se guardara la desicion del empleado si mostrar activos o inactivos

    do
    {
        dato=opcionActividad(); //Le pregunta al usuario como quiere filtrar, lo retorna y se guarda en dato

        if(dato != '0' && (dato == '1' || dato == '2'))///Si dato es distinto de cero y si es 1 o 2 entra al conidiconal
        {
            if(buff)    //Si el archivo se abre correctamente entra y muestra los datos segun la desicion del usuario
            {
                if(dato == '2'){

                    printf("===================================\n");
                    printf("|                                 |\n");
                    printf("|       EMPLEADOS INACTIVOS       |\n");
                    printf("|                                 |\n");
                    printf("===================================\n");

                }else if(dato == '1'){

                    printf("===================================\n");
                    printf("|                                 |\n");
                    printf("|        EMPLEADOS ACTIVOS        |\n");
                    printf("|                                 |\n");
                    printf("===================================\n");

                }

                while( (fread(&e,sizeof(Empleado),1,buff)) > 0) //mientras lea un empleado, lo almacena en el Empleado e
                {
                    if(dato == '2') //si la opcion del usuario es 2 mostrara los empleados inactivos
                    {
                        if(e.estadoActividad == 0)
                        {
                            mostrarEmpleado(e);
                        }
                    }
                    else if(dato == '1') //si la opcion del usuario es 1 mostrara los empleados activos
                    {
                        if(e.estadoActividad == 1)
                        {
                            mostrarEmpleado(e);
                        }
                    }
                }
                fclose(buff);   //cierra el archivo

                limpiarYContinuar();    //limpia la pantalla y pone un system pause
            }
            else    //mensaje de error si el archivo no se abre correctamente
            {
                mensajeErrorDePrograma();
            }
        }

    }
    while(dato!= '0' && dato != '1' &&  dato != '2');///se repetira esto mientras el dato ingresado por el usuario sea distinto de 1, 2 o 0
}

void filtrarEmpleadosID(char archivo[])///Filtra los empleados por su DNI usa ordenamiento seleccion
{
    int i = 0;
    int validos=calcularValidosArchivos(archivo,sizeof(Empleado));  //calcula la cantidad de empleados cargados en el archivo
    char orden; //variable donde guardara el como mostrar los empeleados ordenados por id

    orden=opcionOrdenado(); //le pregunta al usuario en que orden quiere filtrar los id

    if(orden != '0' && (orden == '1' || orden == '2')) //si el orden es distinto a 0 y es 1 o 2 entra al condicional
    {
        Empleado arrEmpleados[validos]; //crea un arreglo de empleados para guardarlos


        pasajeEmpleadosArreglo(archivo,arrEmpleados,0,validos); //pasa todos los empleados del archivo al arreglo

        ordenarPorSeleccion(validos,arrEmpleados);  //ordena los empleados del arreglo por seleccion de menor a mayor

        if(orden == '1')    //si la opcion del empleado es 1 mostrara los empleados del menor id al mayor
        {
            while(i<validos)
            {
                mostrarEmpleado(arrEmpleados[i]);   //muestra los empleados en la posicion de i
                i++;
            }
        }
        else if (orden == '2')//si la opcion del empleado es 2 mostrara los empleados del mayor id al menor
        {
            i=validos-1;

            while(i>=0)
            {
                mostrarEmpleado(arrEmpleados[i]);   //muestra los empleados en la posicion de i
                i--;
            }
        }

        limpiarYContinuar();    //limpia la consola y la pausa

    }
    else if(orden != '0' && orden != '1' && orden != '2')//si no entra al condicional y no ingresa una respuesta que no sea 0, 1 o 2 muestra un mensaje de error
    {
        mensajeErrorOpcionInvalida();
    }
}

void filtrarEmpleadosNombres(char archivo[])///Filtra los empleados por su nombre usa ordenamiento por insercion
{
    int i=0;
    int validos=calcularValidosArchivos(archivo,sizeof(Empleado));  //calcula la cantidad de empleados cargados en el archivo
    char orden; //variable donde guardara el como mostrar los empeleados ordenados por nombre

    orden=opcionOrdenado(); //le pregunta al usuario en que orden quiere filtrar los id

    if(orden != '0' && (orden == '1' || orden == '2'))
    {

        Empleado arrEmpleados[validos];//crea un arreglo de empleados para guardarlos

        pasajeEmpleadosArreglo(archivo,arrEmpleados,0,validos); //pasa todos los empleados del archivo al arreglo

        ordenarEmpleadosMenorAmayorNombre(arrEmpleados,validos);

        if(orden == '1')    //si la opcion es 1 mostrara de menor a mayor los empleados por nombre
        {
            while(i<validos)
            {
                mostrarEmpleado(arrEmpleados[i]);   //manda el empleado en la posicion de i a la funcion de mostrarEmpleado
                i++;
            }
        }
        else if(orden == '2')   //si la opcion es 2 mostrara de mayor a menor los empleados por nombre
        {
            i=validos-1;

            while(i>=0)
            {
                mostrarEmpleado(arrEmpleados[i]);   //manda el empleado en la posicion de i a la funcion de mostrarEmpleado
                i--;
            }
        }
        limpiarYContinuar();
    }
    else if(orden != '0' && orden != '1' && orden != '2')   //Esto se repetira mientras la opcion ingresada por el usuario sea distinta de 1, 2 o 0
    {
        mensajeErrorOpcionInvalida();   //mensaje de error si el usuario no ingresa
    }
}

void filtrarEmpleadosPorRol(char archivo[])///Filtra el empleado dependiendo de la opcion elegida por el usuario
{                                         ///muestra si es empleado o admin
    char dato;

    dato=opcionRolEmpleado();//le pregunta al usuario si quiere mostrar empleados o administradores

    FILE* buff = fopen(archivo,"rb");

    Empleado e;
    if(dato != '0' && (dato == '1' || dato == '2')) //entrara al condicional si la opcion ingresada por el usuario
    {                                              //es distinto a 0 y si es 1 o 2
        if(buff)    //si logra abrir bien el archivo entra al conidicional
        {
            while( (fread(&e,sizeof(Empleado),1,buff)) > 0 )    //leera el archivo y el empleado que lea lo guarda en e hasta que ya haya leido todo el archivo
            {
                if(dato == '1') //si la opcion ingresada por el usuario es 1 muestra los empleados
                {
                    if(e.rolAdministrativo != 1)
                    {
                        mostrarEmpleado(e); //muestra de empleados
                    }
                }
                else if(dato == '2')    //si la opcion ingresada por el usuario es 2 muestra los administradores
                {
                    if(e.rolAdministrativo == 1)
                    {
                        mostrarEmpleado(e); //muestra de empleados con rol administrador

                    }
                }
            }
            fclose(buff);
            limpiarYContinuar();    //limpia y pausa la consola
        }
        else    //si no se abre correctamente el archivo muestra un mensaje de error
        {
            mensajeErrorDePrograma();
        }
    }
    else if(dato != '0' && dato != '1' && dato != '2')  //si usuario ingrese una opcion distinta de 1,2 o 3 tira un mensaje de opcion invalida
    {
        mensajeErrorOpcionInvalida();
    }
}

///--------ORDENAMIENTO DEL ARREGLO--------///
int buscarPosMenor(int validos, int i, Empleado e[])///Busca el empleado con el menor id
{//ordenamiento por seleccion
    Empleado menor = e[i];
    int pos = i;

    while(i<validos)
    {
        if((strcmpi(menor.id, e[i].id))> 0)
        {
            menor=e[i];
            pos = i;
        }

        i++;
    }

    return pos;
}

void ordenarPorSeleccion(int validos, Empleado e[])///Ordenamiento por seleccion del id
{//ordenamiento por seleccion
    Empleado aux;

    int posMenor = 0;

    for(int i = 0; i<validos-1; i++)
    {
        posMenor = buscarPosMenor(validos,i,e);

        aux = e[i];
        e[i] = e[posMenor];
        e[posMenor] = aux;
    }
}

void insertarEmpleadoNombre(Empleado arrEmpleados[], Empleado insertada, int validos)///Compara los nombres y los va ordenando
{//ordenamiento por insercion
    while(validos>=0 && strcmpi(arrEmpleados[validos].nombreApellido, insertada.nombreApellido) > 0)
    {
        arrEmpleados[validos+1] = arrEmpleados[validos];
        validos--;
    }

    arrEmpleados[validos+1] = insertada;
}

void ordenarEmpleadosMenorAmayorNombre(Empleado arrEmpleados[], int validos)///Ordenamiento por insercion del nombre
{//ordenamiento por insercion
    for(int i = 0; i<validos-1; i++)
    {
        insertarEmpleadoNombre(arrEmpleados,arrEmpleados[i+1],i);
    }
}


///--------BUSQUEDA DE EMPLEADOS--------///
Empleado buscarYRetornarEmpleado(char archivo[],int pos)///Busca un empleado y si lo encuentra lo retona
{                                       ///Sirve para identificar la posicion del empleado para la edicion
    FILE *buff = fopen(archivo,"rb");   //abre el archivo en lectura

    Empleado e;

    if(buff)
    {
        fseek(buff,sizeof(Empleado)*pos,0); //posiciona el cursor en la posicion que recibe por parametros
        fread(&e,sizeof(Empleado),1,buff);  //lee el empleado
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();   //mensaje de error si no se abre correctamente el archivo
    }

    return e;
}

int buscarEmpleadoPorID(char archivo[], char idBuscado[])///Busca un empleado por su ID y retorna su posicion en el archivo
{                                           ///Se usa para verificar si ya hay un empleado con la id ingresada en la carga

    FILE *buff = fopen(archivo,"rb");   //abre el archivo en lectura

    Empleado e;

    int i = 0;  //variable que nos ayudara a encontrar la posicion del empleado
    int flag = 0;

    if(buff)
    {
        while( (fread(&e,sizeof(Empleado),1,buff))>0 && flag == 0)  //lee el archivo y lo que lee lo va guarndando en e mientras
        {                                                           //que no haya leido todo el archivo y mientras que flagg sea 0

            if(  (strcmpi(e.id, idBuscado)) == 0  )  //compara el id del empleado leido en el archivo con el id buscado
            {                                       //si lo encuentra le asigna a flag 1 para cortar el bucle
                flag = 1;
            }

            i++;
        }
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();   //mensaje de error si no se abre correctamente el archivo
    }

    if(flag != 1)   //si flag no es 1 setea a i en -1 para indicar que no se encontro en el archivo
    {
        i = -1;
    }

    return i-1; //retorna la posicion del empleado

}

void buscarEmpleadoPorNombre(char archivo[],char nombre[])///Busca un empleado por su nombre y si lo encuentra lo muestra
{
    FILE* buff = fopen(archivo,"rb");   //abre el archivo en lectura

    Empleado e;

    int i = 0;  //variable que verifica si existe el nombre, si lo encuentra incrementa
    int flag = 0;
    if(buff)
    {
        while( (fread(&e,sizeof(Empleado),1,buff)) > 0 )    //lee el archivo hasta que se termine y lo va almacenando en e
        {
            if((strcmpi(e.nombreApellido, nombre)) == 0 )    //compara el nombre del empleado que lee con el nombre que se esta buscando y si son iguales entra al condicional
            {
                mostrarEmpleado(e); //muestra el empleado
                i++;

                flag = 1;

            }
        }
        if(flag)
        {
            limpiarYContinuar();
        }
        fclose(buff);
    }
    else    //si no se abre correctamente el archivo tira un mensaje de error
    {
        mensajeErrorDePrograma();
    }

    if(i == 0)  //si no encontro ningun empleado con ese nombre muestra un mensaje de nombre insexistente
    {
        nombreInexistente();
    }
}


///--------EDICION DE EMPLEADOS--------///
void editarEmpleados(char archivo[])///Busca por el id al empleado, si lo encuentra lo envia al switch de edicion, sino, reinicia hasta ingresar 0
{
    char idBusqueda[9];
    Empleado e;
    int pos;

    do
    {

        printf(" ============================\n");
        printf(" |                          |\n");
        printf(" |     INGRESE EL ID DEL    |\n");
        printf(" |    EMPLEADO A MODIFICAR  |\n");
        printf(" |     O 0 PARA SALIR       |\n");
        printf(" |                          |\n");
        printf(" | ->                       |\n");
        printf(" |                          |\n");
        printf(" ============================\n");
        goTo(8,7);
        fflush(stdin);
        gets(idBusqueda);   //lee el id ingresado por el usuario
        system("cls");

        if(strlen(idBusqueda)==8 && strcmp(idBusqueda,"0") != 0)    //verifica que el largo del id sea 8 y distinto de 0
        {
            pos = buscarEmpleadoPorID(archivo,idBusqueda);  //busca la posicion del empleado por el id y la guarda en pos, retorna la posicion o -1 si no lo encuentra

            if(pos > -1)    //si encontro el empleado entra al condicional
            {
                e=buscarYRetornarEmpleado(archivo,pos); //busca al empleado por la posicion
                mostrarEmpleado(e); //muestra el empleado
                switchEditarEmpleado(archivo,e,pos);    //da las opciones de edicion sobre el empleado
            }
            else//si no encuentra el empleado muestra un mensaje de error
            {
                dniInexistente();
            }
        }
        else if(strcmp(idBusqueda,"0") != 0 && strlen(idBusqueda)!= 8) //si el id ingresado es distinto de 8 de largo muestra un mensaje de error
        {
            errorLargoId();
        }
    system("cls");
    }
    while(strcmp(idBusqueda,"0") != 0);

}

void switchEditarEmpleado(char archivo[], Empleado e, int pos)///Da las opciones de edicion de los campos y redirige a su respectiva funcion
{
    char control;

    limpiarYContinuar();

    do
    {
        system("cls");
        printf(" ============================\n");
        printf(" |                          |\n");
        printf(" |     INGRESE EL CAMPO     |\n");
        printf(" |       A MODIFICAR        |\n");
        printf(" |                          |\n");
        printf(" | 1.Nombre                 |\n");
        printf(" |                          |\n");
        printf(" | 2.Id                     |\n");
        printf(" |                          |\n");
        printf(" | 3.Dar de baja/ reactivar |\n");
        printf(" |                          |\n");
        printf(" | 0.Volver                 |\n");
        printf(" |                          |\n");
        printf(" | ->                       |\n");
        printf(" |                          |\n");
        printf(" ============================\n");

        fflush(stdin);
        goTo(7,14); //acomoda el scanf en la pantalla
        scanf("%c",&control);

        switch(control)//opciones de editar campos de un empleado
        {
        case '0':
            break;

        case '1':   //edicion de nombre

            system("cls");
            editarNombreEmpleado(archivo,e,pos);
            break;

        case '2':   //edicion del id

            system("cls");
            editarIdEmpleado(archivo,e,pos);
            break;

        case '3':   //edicion dar de alta

            system("cls");
            editarActivacionEmpleados(archivo,e,pos);
            break;

        default:
            system("cls");
            mensajeErrorOpcionInvalida();   //mensaje de error si no ingreso ninguna opcion valida
            break;
        }
    }while(control != '0');

}

void editarNombreEmpleado(char archivo[],Empleado e,int pos)///Edicion del nombre del empleado
{

    char control;

    printf(" ============================\n");
    printf(" |                          |\n");
    printf(" |     INGRESE EL NOMBRE    |\n");
    printf(" |     NUEVO DEL EMPLEADO   |\n");
    printf(" |                          |\n");
    printf(" | ->                       |\n");
    printf(" |                          |\n");
    printf(" ============================\n");
    fflush(stdin);
    goTo(7,6);
    gets(e.nombreApellido); //lee el nombre nuevo ingresado por el usuario
    system("cls");
    mostrarEmpleado(e);

    control = guardarCambios(7,21); //le pregunta al usuario si quiere guardar los cambios y lo guarda en opcion

    if(control == '1')  //si el usuario ingreso 1 sobreescribe el empleado
    {

        sobreescribirEmpleado(archivo,e,pos);
        empleadoGuardado(); //mensaje de empleado guardado
    }

}

void editarIdEmpleado(char archivo[],Empleado e,int pos)///Editar del ID del empleado
{

    char control;
    int flag;

    printf(" ============================\n");
    printf(" |                          |\n");
    printf(" |       INGRESE EL ID      |\n");
    printf(" |     NUEVO DEL EMPLEADO   |\n");
    printf(" |                          |\n");
    printf(" | ->                       |\n");
    printf(" |                          |\n");
    printf(" ============================\n");
    do
    {
        goTo(7,6);
        fflush(stdin);
        gets(e.id); //lee el nuevo id ingresado por el usuario

        if(strlen(e.id)!= 8 && strcmp(e.id,"0")!= 0)    //si el latgo del id es distinto a 8 y distinto a 0 muestra un mensaje de error
        {
            goTo(0,5);
            printf(" | "ANSI_COLOR_RED"INGRESE UN DNI/ID VALIDO"ANSI_COLOR_RESET" |\n");
            printf(" | ->                       |\n");
        }
        else    //si el largo es distinto de 8 y 0 ingresa
        {
            flag = buscarEmpleadoPorID(archivo,e.id);   //busca el empleado por el id, si ya hay un empleado cargado con ese id retorna su posicion
            if(flag >= 0)   //si flag guarda una posicion, muestra un mensaje de error
            {
                goTo(0,5);
                printf(" |      "ANSI_COLOR_RED"EL DNI YA EXISTE"ANSI_COLOR_RESET"    |\n");
                printf(" | ->                       |\n");
            }
        }

    }
    while( (strlen(e.id) != 8 && strcmp(e.id,"0")!=0) || (flag >= 0 && strcmp(e.id,"0")!=0));   //esto se repetira mientras que el largo del id sea distinto de 8 y distinto de 0 o mientras
    system("cls");                                                                            //que flag sea una posicion y sea distinto a cero

    if(flag<0 && strcmp(e.id,"0")!=0)
    {
        mostrarEmpleado(e); //muestra al empleado

        control = guardarCambios(7,21); //pregunta al usuario se guardar los cambios

        if(control == '1')  //si el usuario ingreso 1 sobreescribe a los empleados con los nuevos datos
        {

            sobreescribirEmpleado(archivo,e,pos);
            empleadoGuardado();     //mensaje de empleado guardado
        }
    }
}

void editarActivacionEmpleados(char archivo[],Empleado e,int pos)///Editar estado de actividad del empleado
{

    char control;

    if(e.estadoActividad==1)   //si el estado de actividad es activo lo cambia a inactivo
    {

        e.estadoActividad=0;

    }
    else if (e.estadoActividad==0)  //si el estado de actividad es inactivo lo cambia a activo
    {

        e.estadoActividad=1;
    }

    system("cls");

    mostrarEmpleado(e);     //muestra el empleado con el nuevo estado de actividad

    control = guardarCambios(7,21);     //le pregunta al usuario se guardar el cambio

    if(control == '1')     //si ingresa 1 sobreescribe el empleado viejo con los nuevos datos
    {
        sobreescribirEmpleado(archivo,e,pos);
        empleadoGuardado(); //mensaje de empleado guardado
    }

}

void sobreescribirEmpleado(char archivo[],Empleado e, int pos)///Sobreescribe el empleado con los datos editados
{
    FILE *buff;

    if ( pos >= 0 )    //si la posicion que recibe por parametros es valida entra
    {
        buff = fopen(archivo,"r+b");    //abre el archivo en r+b para poder leerlo y editarlo

        if(buff)
        {

            fseek(buff,sizeof(Empleado)*pos,0);     //mueve el cursor a la posicion del empleado
            fwrite(&e,sizeof(Empleado),1,buff);     //sobreescribe el empleado viejo por el que recibe por parametros

            fclose(buff);

        }
        else
        {

            mensajeErrorDePrograma();   //mensaje de error

        }
    }
    else
    {
        dniExistente();   //si la posicion recibida no es valida muestra mensaje de error
    }


}




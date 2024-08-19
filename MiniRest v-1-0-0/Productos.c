#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Productos.h"
#include "funcionesAuxiliares.h"
#include "mensajesAviso.h"
#include "mensajesError.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

///ALTA
Producto agregarProductoDeAuno(char archivo[]) //Carga un producto y lo retorna
{

    Producto p;
    int flag;

    p.estadoActividad = 1;

    printf(" =============================================\n");
    printf(" |                                           |\n");
    printf(" |              INGRESE EL NOMBRE            |\n");
    printf(" |                DEL PRODUCTO               |\n");
    printf(" |            (hasta 29 caracteres)          |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |          INGRESE EL ID DEL PRODUCTO       |\n");
    printf(" |            (hasta 29 caracteres)          |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |        INGRESE EL PRECIO DEL PRODUCTO     |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" |        INGRESE EL STOCK DEL PRODUCTO      |\n");
    printf(" |                                           |\n");
    printf(" |  ->                                       |\n");
    printf(" |                                           |\n");
    printf(" | PRESIONE 0 EN CUALQUIER CAMPO PARA SALIR  |\n");
    printf(" =============================================\n");

    do{

        goTo(8,7);
        fflush(stdin);
        gets(p.nombre);

        flag=buscarProductoPorNombre(archivo,p.nombre);

        if( strcmp(p.nombre,"0")!= 0 && flag>=0 )//Evalua que el usuario ingrese un nombre valido
            {
                    goTo(0,6);
                    printf(" |            "ANSI_COLOR_RED"EL NOMBRE YA EXISTE"ANSI_COLOR_RESET"            |\n");
                    printf(" |  ->                                       |\n");
            }

    }while((flag >= 0 && strcmp(p.nombre,"0")!=0));

    if(strcmp(p.nombre,"0")!=0 && flag <0 )//Evalua que el usuario no quiera salir
    {
        do{

        goTo(8,11);
        fflush(stdin);
        gets(p.id);

        flag=buscarProductoPorID(archivo,p.id);

        if( strcmp(p.id,"0")!= 0 && flag>=0 )//Evalua que el usuario ingrese un id valido
        {
                goTo(0,10);
                printf(" |              "ANSI_COLOR_RED"EL ID YA EXISTE"ANSI_COLOR_RESET"              |\n");
                printf(" |  ->                                       |\n");
        }

        }while( strcmp(p.id,"0")!=0 && flag >= 0 );


        if(strcmp(p.id,"0")!=0 && flag < 0 )//Evalua que el usuario no quiera salir
        {
            do
            {
                goTo(8,15);
                scanf("%f", &p.precio);

                if(p.precio != 0 && p.precio <0)//Evalua que el usuario ingrese un precio valido
                {
                    goTo(0,14);
                    printf(" |          "ANSI_COLOR_RED"EL PRECIO ES MENOR A $1"ANSI_COLOR_RESET"          |\n");
                    printf(" |  ->                                       |\n");
                }

            }
            while(p.precio != 0 && p.precio <0);

            if(p.precio != 0)//Evalua que el usuario no quiera salir
            {
                do
                {
                    goTo(8,19);
                    scanf("%d", &p.stock);

                    if(p.stock != 0 && p.stock <0)//Evalua que el usuario ingrese un stock valido
                    {
                        goTo(0,18);
                        printf(" |           "ANSI_COLOR_RED"EL STOCK ES MENOR A 0"ANSI_COLOR_RESET"           |\n");
                        printf(" |  ->                                       |\n");
                    }

                }
                while(p.stock != 0 && p.stock <0);
            }
        }
    }

    return p;
}

void crearProductos(char archivo[])
{
    FILE* buff;

    char confirmar;

    Producto p;

    p = agregarProductoDeAuno(archivo);

    buff = fopen(archivo,"ab");

    if(buff)
    {
        system("cls");

        if(strcmp(p.nombre,"0")!= 0 && strcmp(p.id,"0") && p.stock != 0 && p.precio !=0) //Evalua que el usuario no haya salido en ningun momento de la carga de producto
        {
            mostrarProducto(p);//Muestra el producto final
            confirmar = guardarCambios(7,23);

            if (confirmar == '1') //Lo guarda si el usuario lo desea
            {
                fwrite(&p,sizeof(Producto),1,buff);
                productoGuardado();
            }

        }

        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }
}

///BAJA
void darDeBaja(char archivo[])//Da de baja un producto
{
    Producto p;

    char idBuscado[30];

    int pos;

    char control;

    do{

        ingresarIDProducto(idBuscado);//Ingresa un id de producto

        if( strcmp(idBuscado,"0")!=0 ){

            system("cls");

            pos = buscarProductoPorID(archivo,idBuscado);

            FILE *buffer;

            if(pos >-1)//Si encuentra el producto
            {
                buffer= fopen(archivo, "r+b");

                if (buffer)
                {

                    fseek(buffer, pos*sizeof(Producto), 0);
                    fread(&p,sizeof(Producto),1,buffer);

                    p.estadoActividad = editarEstadoActividad(p.estadoActividad); //Cambia su estado de actividad
                    system("cls");
                    cambiosGuardados();
                    system("cls");

                    mostrarProducto(p);//Muestra el resultado final

                    control = guardarCambios(7,23);

                    if (control == '1')//Lo guarda si el usuario lo desea
                    {

                        fseek(buffer, pos*sizeof(Producto), 0);
                        fwrite(&p, sizeof(Producto), 1, buffer);
                    }
                    fclose(buffer);

                }
                else
                {
                    mensajeErrorDePrograma();
                }

            }
            else
            {
                idInexistente();
            }

        }

    }while( strcmp(idBuscado,"0")!=0 );


}

///MODIFICACION
Producto modificarProducto2(char archivo[],Producto p, char *flag)//Modifica un producto, devuelve 1 con *flag si cambio algo del producto
{

    char opcion;
    char temporal[30];
    mostrarProducto(p);

    limpiarYContinuar();

    do
    {
        system("cls");
        printf("===================================\n");
        printf("|                                 |\n");
        printf("|    ELIJA UNA OPCION A EDITAR    |\n");
        printf("|                                 |\n");
        printf("| 1.Nombre                        |\n");
        printf("|                                 |\n");
        printf("| 2.ID                            |\n");
        printf("|                                 |\n");
        printf("| 3.Precio                        |\n");
        printf("|                                 |\n");
        printf("| 4.Stock                         |\n");
        printf("|                                 |\n");
        printf("| 0.Volver                        |\n");
        printf("|                                 |\n");
        printf("| ->                              |\n");
        printf("===================================\n");
        goTo(6,15);
        fflush(stdin);
        scanf("%c", &opcion);

        switch(opcion)
        {
        case '0':
            break;
        case '1':


            ingresarNuevoNombreProducto(archivo,temporal);

            if( strcmp(temporal,"0")!=0 ){

                strcpy(p.nombre,temporal);
                *flag = '1';

            }
            break;

        case '2':
            ingresarNuevoIDProducto(archivo,temporal);

            if( strcmp(temporal,"0")!=0 ){

                strcpy(p.nombre,temporal);
                *flag = '1';

            }

            break;

        case '3':
            ingresarPrecioNuevoProducto(&p.precio);

            if( p.precio!=0 ){

                *flag = '1';

            }

            break;

        case '4':
            ingresarNuevoStockProducto(&p.stock);

            if( p.stock!=0 ){

                *flag = '1';

            }

            break;

        default:
            mensajeErrorOpcionInvalida();
            break;
        }

        if(*flag == 1 && (opcion=='1' || opcion=='2' || opcion=='3') ){

            cambiosGuardados();

        }

    }
    while(opcion != '0');

    return p;
}

void modificarProducto(char archivo[])//Modifica al producto en el archivo
{
    Producto p;

    FILE *buffer;

    char idBuscado[30];

    int pos;

    char control, flag;

    do{

    ingresarIDProducto(idBuscado);//Pide que ingrese un id de producto al cual desea modificar

    if( strcmp(idBuscado,"0")!=0 ){


            system("cls");

            pos = buscarProductoPorID(archivo,idBuscado);//Busca el producto en el archivo

            if(pos >-1)
            {
                buffer= fopen(archivo, "r+b");

                if (buffer)
                {

                    fseek(buffer, pos*sizeof(Producto), 0);//Posiciona el cursor atras del que quiere leer
                    fread(&p,sizeof(Producto),1,buffer);//Lee el producto

                    p = modificarProducto2(archivo,p, &flag);//Llama a modificar el producto

                        if(flag)//Si modificó algo del producto lo muestra
                        {
                            do{

                            system("cls");
                            mostrarProducto(p);
                            control = guardarCambios(7,23);

                            if (control == '1')//Guarda el producto si el usuario asi lo desea
                            {
                                fseek(buffer, pos*sizeof(Producto), 0);//Vuelve a posicionar el cursor
                                fwrite(&p, sizeof(Producto), 1, buffer);//Escribe el producto
                            }

                            }while(control != '1' && control != '2');
                        }

                    fclose(buffer);

                }
                else
                {
                    mensajeErrorDePrograma();
                }

            }
            else
            {
                idInexistente();
            }


    }
        }while( strcmp(idBuscado,"0")!=0 );

}

void ingresarNuevoNombreProducto(char archivo[],char nombreProducto[])//Pide que se ingrese el nuevo nombre del producto
{
    int flagValido;

    system("cls");
    printf("\n ==================================\n");
    printf(" |                                |\n");
    printf(" |    INGRESE EL NOMBRE NUEVO     |\n");
    printf(" |          0 PARA SALIR          |\n");
    printf(" | ->                             |\n");
    printf(" |                                |\n");
    printf(" ==================================\n");

    do{
        goTo(7,6);
        fflush(stdin);
        gets(nombreProducto);

        if(strcmp(nombreProducto,"0")!=0){

            flagValido=buscarProductoPorNombre(archivo,nombreProducto);

            if(flagValido>=0){//Evalua que el usuario ingrese un nombre valido

                goTo(0,6);

                printf(" | ->                             |\n");
                printf(" |       "ANSI_COLOR_RED"EL NOMBRE YA EXISTE"ANSI_COLOR_RESET"      |\n");

            }
        }

    }while(strcmp(nombreProducto,"0")!=0 && flagValido>=0);

}

void ingresarNuevoIDProducto(char archivo[],char idProducto[])//Pide que se ingrese el nuevo id del producto
{
    int flagValido;

    system("cls");
    printf("\n ==================================\n");
    printf(" |                                |\n");
    printf(" |       INGRESE EL ID NUEVO      |\n");
    printf(" |          0 PARA SALIR          |\n");
    printf(" | ->                             |\n");
    printf(" |                                |\n");
    printf(" ==================================\n");

    do{
        goTo(7,6);
        fflush(stdin);
        gets(idProducto);

        if(strcmp(idProducto,"0")!=0){

            flagValido=buscarProductoPorID(archivo,idProducto);

            if(flagValido>=0){//Evalua que el usuario ingrese un nombre valido

                goTo(0,6);

                printf(" | ->                             |\n");
                printf(" |         "ANSI_COLOR_RED"EL ID YA EXISTE"ANSI_COLOR_RESET"        |\n");

            }
        }

    }while(strcmp(idProducto,"0")!=0 && flagValido>=0);

}

void ingresarPrecioNuevoProducto(float *precio)//Pide que se ingrese el nuevo precio del producto
{
    system("cls");
    printf("\n ==================================\n");
    printf(" |                                |\n");
    printf(" |     INGRESE EL PRECIO NUEVO    |\n");
    printf(" |          0 PARA SALIR          |\n");
    printf(" | ->                             |\n");
    printf(" |                                |\n");
    printf(" ==================================\n");
    do
    {
        goTo(7,6);
        fflush(stdin);
        scanf("%f",precio);

        if(*precio < 0)//Evalua que el precio ingresado sea valido
        {
            goTo(0,5);
            printf(" |   "ANSI_COLOR_RED"INGRESE UN PRECIO MAYOR A 0"ANSI_COLOR_RESET"  |\n");
            printf(" | ->                             |\n");
        }

    }
    while(*precio < 0);

}

void ingresarNuevoStockProducto(int *stock)//Pide que se ingrese el nuevo stock del producto
{
    system("cls");
    printf("\n ==================================\n");
    printf(" |                                |\n");
    printf(" |      INGRESE EL STOCK NUEVO    |\n");
    printf(" |          0 PARA SALIR          |\n");
    printf(" | ->                             |\n");
    printf(" |                                |\n");
    printf(" ==================================\n");
    do
    {
        goTo(7,6);
        scanf("%d",stock);

        if(*stock<0)//Evalua que el stock ingresado sea valido
        {
            goTo(0,5);
            printf(" |   "ANSI_COLOR_RED"INGRESE UN STOCK MAYOR A 0"ANSI_COLOR_RESET"   |\n");
            printf(" | ->                             |\n");
        }

    }
    while(*stock<0);
}

void modificarStockAutomatico(char archivo[], int pos, int valor)//Modifica automaticamente el stock segun el valor indicado(decrementa o aumenta)
{
    Producto p;

    FILE *buff = fopen(archivo, "r+b");

    if (buff)
    {
        fseek(buff, sizeof(Producto) * pos, 0);
        fread(&p, sizeof(Producto), 1, buff);
        fseek(buff, sizeof(Producto) * (-1), 1);
        p.stock = p.stock + valor;
        fwrite(&p, sizeof(Producto), 1, buff);
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }
}

///CONSULTA Y LISTADO

void verTodoProductos(char archivo[])//Muestra todos los productos del archivo
{
    FILE *buff = fopen(archivo, "rb");

    Producto p;

    if (buff)
    {

        while (fread(&p, sizeof(Producto), 1, buff) > 0)
        {

            mostrarProducto(p);
        }

        fclose(buff);

    }
    else
    {

        mensajeErrorDePrograma();
    }
}

void mostrarProducto (Producto p)//Muestra un producto
{
    char precioString[10];
    char stockString[10];

    itoa(p.precio,precioString,10);
    itoa(p.stock,stockString,10);

    printf(" =================================================\n");
    printf(" |                                               |\n");
    printf(" |  NOMBRE: %s",p.nombre);

    dejarEspacios(37,strlen(p.nombre));
    printf("|\n");
    printf(" |                                               |\n");
    printf(" |  ID: %s",p.id);

    dejarEspacios(41,strlen(p.id));
    printf("|\n");
    printf(" |                                               |\n");
    printf(" |  PRECIO: %s",precioString);

    dejarEspacios(37,strlen(precioString));
    printf("|\n");

    printf(" |                                               |\n");
    if(p.stock == 0)
    {
        printf(" |  STOCK: "ANSI_COLOR_RED"%s"ANSI_COLOR_RESET,stockString);
    }
    else if(p.stock < 6)
    {
        printf(" |  STOCK: "ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET,stockString);
    }
    else
    {
        printf(" |  STOCK: "ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET,stockString);
    }

    dejarEspacios(38,strlen(stockString));
    printf("|\n");
    printf(" |                                               |\n");
    if(p.estadoActividad==1)
    {
        printf(" |  ESTADO DE ACTIVIDAD: "ANSI_COLOR_GREEN"ACTIVO"ANSI_COLOR_RESET"                  |\n");


    }
    else
    {
        printf(" |  ESTADO DE ACTIVIDAD: "ANSI_COLOR_RED"INACTIVO"ANSI_COLOR_RESET"                |\n");

    }

    printf(" |                                               |\n");
    printf(" =================================================\n");

}

void mostrarProductoReducido(Producto p)//Muestra un producto pero solo su nombre y su precio
{
    int cantEspacios;
    printf("\n\n\n");
    printf(" =================================================\n");
    printf(" |                                               |\n");
    printf(" |             PRODUCTO ENCONTRADO               |\n");
    printf(" |                                               |\n");
    printf(" |  NOMBRE: %s",p.nombre);

    cantEspacios = 37-strlen(p.nombre);
    for(int i = 0; i<cantEspacios; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf(" |                                               |\n");
    printf(" |  PRECIO:                                      |\n");
    printf(" |                                               |\n");
    printf(" =================================================\n");
    goTo(14,21);
    printf("%.2f",p.precio);
}

void ingresarIDProducto(char id[])//Pide el ingreso de un id de producto
{
            system("cls");
            printf("======================================\n");
            printf("|                                    |\n");
            printf("|            INGRESE EL ID           |\n");
            printf("|            DEL PRODUCTO            |\n");
            printf("|            0 PARA SALIR            |\n");
            printf("| ->                                 |\n");
            printf("|                                    |\n");
            printf("======================================\n");

            fflush(stdin);
            goTo(6,6);
            gets(id);

}

void pasajeProductosArreglo(char archivo[], Producto arregloProductos[], int validos, int dim)//Pasa los productos a un arreglo
{
    FILE *buff = fopen(archivo,"rb");

    Producto p;

    if(buff)
    {

        while( (fread(&p,sizeof(Producto),1,buff)) > 0 && validos<dim)
        {

            arregloProductos[validos] = p;
            validos++;
        }

        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }
}

void filtrarProductosActividad(char archivo[], char dato)//Filtra los productos por actividad
{
    FILE *buff = fopen(archivo,"rb");

    Producto p;

    if(buff)
    {
        while((fread(&p,sizeof(Producto),1,buff)) > 0)
        {

            if(dato == '2' && p.estadoActividad == 0)//Si la actividad coincide con el dato lo muestra
            {
                mostrarProducto(p);
            }
            else if (dato == '1' && p.estadoActividad == 1)//Si la actividad coincide con el dato lo muestra
            {
                mostrarProducto(p);
            }

        }
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

}

void ordenarProductosID(Producto arregloProductos[], int validos)//Ordena los productos por ID por metodo de insercion
{
    for(int i = 0; i<validos-1; i++)
    {
        insertarProductoID(arregloProductos, arregloProductos[i+1],i);
    }
}

void insertarProductoID(Producto arregloProducto[], Producto insertada, int validos)//Inserta los productos en un arreglo por su id
{

    while(validos>=0 && strcmpi(arregloProducto[validos].id,insertada.id) > 0)
    {
        arregloProducto[validos+1] = arregloProducto[validos];
        validos--;
    }

    arregloProducto[validos+1] = insertada;
}

void filtrarProductosID(char archivo[], char orden)//Filtra los productos por id segun el orden (mayor a menor, menor a mayor ) que quiera el usuario(pasado por parametro)
{
    int i = 0;

    int validos = calcularValidosArchivos(archivo,sizeof(Producto));//Calcula el tamaño del arreglo

    Producto arregloProductos[validos];

    pasajeProductosArreglo(archivo,arregloProductos,0,validos);//Pasa los productos al arreglo justo creado

    ordenarProductosID(arregloProductos, validos);//Ordena los productos por id

    if(orden == '2')//Muestra de menor a mayor
    {
        while(i<validos)
        {
            mostrarProducto(arregloProductos[i]);
            i++;
        }
        limpiarYContinuar();

    }
    else if(orden == '1')//Muestra de mayor a menor
    {
        i = validos-1;

        while(i>-1)
        {
            mostrarProducto(arregloProductos[i]);
            i--;
        }

        limpiarYContinuar();
    }
}

void ordenarProductosNombre (Producto arreglo[], int ultimaPosicion, Producto dato)//Ordena los productos por nombre por metodo de insercion
{

    while (ultimaPosicion >= 0 && strcmpi(dato.nombre, arreglo[ultimaPosicion].nombre) == -1)
    {

        arreglo[ultimaPosicion+1] = arreglo[ultimaPosicion];
        ultimaPosicion--;

    }

    arreglo[ultimaPosicion+1] = dato;

}

void insertarProductoNombre(Producto arreglo[], Producto insertada, int validos)//Inserta los productos en un arreglo por su nombre
{
    while(validos>=0 && strcmpi(arreglo[validos].nombre, insertada.nombre) > 0)
    {
        arreglo[validos+1] = arreglo[validos];
        validos--;
    }

    arreglo[validos+1] = insertada;
}

void ordenarProductosMenorAmayorNombre(Producto arreglo[], int validos)//Ordena los productos por nombre por metodo de insercion
{
    for(int i = 0; i<validos-1; i++)
    {
        insertarProductoNombre(arreglo,arreglo[i+1],i);
    }
}

void filtrarProductosNombre(char archivo[])//Filtra los productos por nombre segun el orden (mayor a menor, menor a mayor ) que quiera el usuario
{
    int validos = 0;

    validos = calcularValidosArchivos(archivo, sizeof(Producto));//Calcula el tamaño del arreglo

    Producto arreglo[validos];

    pasajeProductosArreglo(archivo, arreglo, 0, validos); //Pasa los productos al arreglo justo creado

    ordenarProductosMenorAmayorNombre(arreglo, validos);//Ordena los productos por nombre

    char opcion;

    opcion = opcionOrdenado();

    system("cls");

    if (opcion == '1')//Muestra de menor a mayor
    {

        int i = 0;

        while (i < validos)
        {

            mostrarProducto(arreglo[i]);
            i++;

        }
        limpiarYContinuar();

    }
    else if (opcion == '2')  //Muestra de mayor a menor
    {

        int i = validos - 1;

        while (i > -1)
        {

            mostrarProducto(arreglo[i]);
            i--;

        }
        limpiarYContinuar();

    }

}

void filtrarProductosPrecio(char archivo[])//Filtra los productos por precio
{
    int i = 0;

    char opcion;

    int validos = calcularValidosArchivos(archivo,sizeof(Producto));

    Producto arregloProductos[validos];

    pasajeProductosArreglo(archivo,arregloProductos,0,validos);

    ordenarProductosPrecio(arregloProductos, validos);

    opcion = opcionOrdenado();

    system("cls");

    if(opcion == '1')
    {
        while(i<validos)
        {
            mostrarProducto(arregloProductos[i]);
            i++;
        }
        limpiarYContinuar();
    }
    else if (opcion == '2')
    {
        i = validos-1;
        while(i>-1)
        {
            mostrarProducto(arregloProductos[i]);
            i--;
        }
        limpiarYContinuar();
    }
}

void ordenarProductosPrecio(Producto arregloProductos[], int validos)//Ordena por metodo de insercion los productos por precio
{

    for(int i = 0; i<validos-1; i++)
    {

        insertarProductoPrecio(arregloProductos, arregloProductos[i+1],i);

    }
}

void insertarProductoPrecio(Producto arregloProducto[], Producto insertada, int validos) //Inserta un producto en un arreglo por su precio
{

    while(validos>=0 && arregloProducto[validos].precio > insertada.precio)
    {
        arregloProducto[validos+1] = arregloProducto[validos];
        validos--;
    }

    arregloProducto[validos+1] = insertada;
}

void insertarProductoStock(Producto arregloProducto[], Producto insertada, int validos)//Inserta un producto en un arreglo por su stock
{

    while(validos>=0 && arregloProducto[validos].stock > insertada.stock)
    {
        arregloProducto[validos+1] = arregloProducto[validos];
        validos--;
    }

    arregloProducto[validos+1] = insertada;
}

void ordenarProductosStock(Producto arregloProductos[], int validos)//Ordena por metodo de insercion los productos por stock
{

    for(int i = 0; i<validos-1; i++)
    {

        insertarProductoStock(arregloProductos, arregloProductos[i+1],i);
    }
}

void filtrarProductosStock(char archivo[])//Filtra los productos por su precio
{
    int i = 0;

    char opcion ;

    opcion = opcionOrdenado();

    int validos = calcularValidosArchivos(archivo,sizeof(Producto));

    Producto arregloProductos[validos];

    pasajeProductosArreglo(archivo,arregloProductos,0,validos);

    ordenarProductosStock(arregloProductos, validos);

    system("cls");

    if(opcion == '1')
    {
        while(i<validos)
        {
            mostrarProducto(arregloProductos[i]);
            i++;
        }
        limpiarYContinuar();

    }
    else if (opcion == '2')
    {
        i = validos-1;

        while(i>-1)
        {
            mostrarProducto(arregloProductos[i]);
            i--;
        }
        limpiarYContinuar();
    }
}

void IDingresadoAbuscar(char id[]) //Pide el ingreso del id que quiere buscar
{

    system("cls");
    printf("======================================\n");
    printf("|                                    |\n");
    printf("|          INGRESE EL ID DEL         |\n");
    printf("|          PRODUCTO A BUSCAR         |\n");
    printf("|            0 PARA SALIR            |\n");
    printf("| ->                                 |\n");
    printf("|                                    |\n");
    printf("======================================\n");
    fflush(stdin);
    goTo(6,6);
    gets(id);

}

int buscarProductoPorID(char archivo[], char id[])//Busca la posicion del producto guiado por su id
{
    FILE* buff = fopen(archivo,"rb");

    Producto p;

    int flag = 0;

    int i = 0;

    if(buff)
    {

        while( (fread(&p,sizeof(Producto),1,buff)) > 0 && flag != 1)
        {
            i++;

            if(strcmpi(p.id, id) == 0)
            {

                flag = 1;

            }
        }
        fclose(buff);

    }
    else
    {

        mensajeErrorDePrograma();
    }

    if (flag != 1)
    {

        i = 0;
    }

    return i-1;
}

void buscarYmostrarProductoID(char archivo[])//Busca y muestra la posicion del producto por el id ingresado en la funcion
{
    Producto p;

    FILE *buff;

    int flag;

    char id[30];

    do{

        IDingresadoAbuscar(id);

        if( strcmp(id,"0")!=0 ){

            flag = buscarProductoPorID(archivo, id);

            if (flag > -1)
            {

                buff = fopen(archivo, "rb");

                if (buff)
                {

                    fseek(buff, sizeof(Producto)*flag, 0);

                    fread(&p, sizeof(Producto), 1, buff);

                    printf("\n\n\n");
                    mostrarProducto(p);
                    limpiarYContinuar();

                    fclose(buff);

                }
                else
                {
                    mensajeErrorDePrograma();
                }

            }
            else
            {
                idInexistente();
            }

        }

    }while( strcmp(id,"0")!=0 );

}

void nombreIngresadoAbuscar(char nombre[])//Pide el ingreso del nombre que quiere buscar
{

    system("cls");
    printf("======================================\n");
    printf("|                                    |\n");
    printf("|        INGRESE EL NOMBRE DEL       |\n");
    printf("|          PRODUCTO A BUSCAR         |\n");
    printf("|            0 PARA SALIR            |\n");
    printf("| ->                                 |\n");
    printf("|                                    |\n");
    printf("======================================\n");
    fflush(stdin);
    goTo(6,6);
    gets(nombre);
}

int buscarProductoPorNombre(char archivo[], char nombre[])//Busca la posicion del producto guiado por su nombre
{

    FILE* buff = fopen(archivo,"rb");

    Producto p;

    int flag = 0;

    int i = 0;

    if(buff)
    {

        while( (fread(&p,sizeof(Producto),1,buff)) > 0 && flag != 1)
        {

            i++;

            if(strcmpi(p.nombre, nombre) == 0)
            {

                flag = 1;

            }
        }
        fclose(buff);

    }
    else
    {

        mensajeErrorDePrograma();

    }

    if (flag != 1)
    {

        i = 0;

    }

    return i-1;

}

void buscarYmostrarProductoNombre(char archivo[])//Busca y muestra la posicion del producto por el nombre ingresado en la funcion
{

    Producto p;

    FILE *buff;

    int flag;

    char nombre[30];

    do{

        nombreIngresadoAbuscar(nombre);

        if( strcmp(nombre,"0")!=0 ){

            flag = buscarProductoPorNombre(archivo, nombre);


            if (flag > -1)
            {

                buff = fopen(archivo, "rb");

                if (buff)
                {

                    fseek(buff, sizeof(Producto)*flag, 0);

                    fread(&p, sizeof(Producto), 1, buff);

                    printf("\n\n\n");
                    mostrarProducto(p);
                    limpiarYContinuar();

                    fclose(buff);

                }
                else
                {

                    mensajeErrorDePrograma();

                }

            }
            else
            {

                nombreInexistente();
            }

        }

    }while( strcmp(nombre,"0")!=0 );
}

Producto buscarYretornarProductoPorPosicion(char archivo[], int pos) //Busca y retorna un producto segun la posicion pasada
{
    Producto p;

    FILE *buff = fopen(archivo, "r+b");

    if (buff)
    {
        fseek(buff, sizeof(Producto) * pos, 0);
        fread(&p, sizeof(Producto), 1, buff);
        fclose(buff);
    }
    else
    {
        mensajeErrorDePrograma();
    }

    return p;
}

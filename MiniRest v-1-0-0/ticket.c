#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ticket.h"
#include "funcionesAuxiliares.h"
#include "mensajesError.h"
#include "fecha.h"
#include "mesas.h"
#include "mensajesAviso.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_SOFT_ORANGE "\x1b[38;2;204;111;18m"

///--------ALTA--------///

Ticket cargarTicket(char archivoT[], char archivoP[], char archivoM[])//Carga un ticket y lo retorna
{
    Ticket t;
    Mesa m;
    char ultId[6];

    int flag;

    buscarUltimoTicket(archivoT,ultId);//Busca el ultimo id de ticket cargado

    generarIdTicket(ultId,t.id);//Genera el id del ticket nuevo

    conseguirFechaActual(&t.fechaTicket.dia,&t.fechaTicket.mes,&t.fechaTicket.anio);//Consigue la fecha actual del ticket

    m = ingresarIdMesaParaTicket(archivoM,t.mesaUsada,&flag);//Pide que ingrese la mesa a la cual se relaciona el ticket, y devuelve la estructura de la mesa y la posicion

    if(strcmpi(t.mesaUsada,"0")!=0)//Si el usuario no quiso salir sigue a la parte donde el usuario carga productos y se cambian los archivos
    {
        t.validosProducto = 0;//Inicializa los validos del ticket en 0

        aniadirProductosTicket(archivoP, &t);//Añade productos al ticket
        t.descuento = 0;//Inicializa el descuento en 0
        t.estado = 1;//Inicializa el estado del ticket para cobrar
        t.total = 0;//Inicializa el total de la mesa en 0
        m.estadoOcupacion = editarEstadoOcupacion(m.estadoOcupacion);//Cambia el estado de ocupacion de la mesa
        sobreescribirMesa(archivoM,m,flag);//Cambia el estado de la mesa en el archivo
    }

    return t;
}

void cargarTicketEnArchivo(char archivoT[], char archivoP[], char archivoM[])//Carga un ticket en el archivo de tickets
{
    Ticket t;

    FILE* buff;

    t = cargarTicket(archivoT,archivoP,archivoM);//Carga el ticket

    if(strcmpi(t.mesaUsada,"0")!=0)//Si el usuario no quiso salir guarda el ticket
    {
        buff = fopen(archivoT,"ab");

        if(buff){

            fwrite(&t,sizeof(Ticket),1,buff);
            ticketCargado();
            fclose(buff);
        }else{

            mensajeErrorDePrograma();

        }
    }
}

void aniadirProductosTicket(char archivoP[], Ticket *t)//Añade productos a un ticket mientras el usuario asi lo desee
{

    char confir = '1';
    char respuesta[30];
    int pos;
    Producto p;
    if(t->validosProducto < 30)
    {

        do {
            system("cls");
            printf(" =============================================\n");
            printf(" |                                           |\n");
            printf(" |        CARGAR PRODUCTOS AL TICKET         |\n");
            printf(" |                                           |\n");
            printf(" =============================================\n");

            productoAcargar(respuesta);//El usuario ingresa el nombre del producto que quiere cargar

            pos = buscarProductoPorNombre(archivoP, respuesta);//Busca el producto por nombre en el archivo de productos

            if (pos > -1) //Si el producto existe lo retorna
            {
                p = buscarYretornarProductoPorPosicion(archivoP, pos);
                if(p.estadoActividad == 1)
                {
                    if (p.stock > 0) //Si hay stock del producto lo carga
                    {
                        modificarStockAutomatico(archivoP, pos, -1);//Modifica el stock del producto (le resta 1)

                        strcpy(t->idProductos[t->validosProducto], p.nombre);//Copia el id de producto en el arreglo del ticket
                        t->precioProducto[t->validosProducto] = p.precio;//Copia el precio de producto en el arreglo del ticket
                        t->validosProducto++;//Aumenta los validos del ticket
                        mostrarProductoReducido(p);//Muestra el producto que se agregó
                        printf("\n\n");
                        productoCargadoAlTicket();

                    } else
                    {
                        printf("\n\n\n");
                        faltaStock();
                    }
                }else
                {
                    printf("\n\n\n====================\n");
                    printf("| "ANSI_COLOR_RED"Producto inactivo"ANSI_COLOR_RESET"|\n");
                    printf("====================\n");
                    sleep(1);
                }
            } else {
                nombreInexistente();
            }

            confir = cargarOtro("PRODUCTO");

        } while (confir != '2');
    }else
    {
        ticketAlcanzoTope();
    }
}

void productoAcargar(char respuesta[])//Pide el ingreso del nombre de un producto
{

    printf("\n");
    printf(" ===============================================\n");
    printf(" |                                             |\n");
    printf(" |        INGRESE EL NOMBRE DEL PRODUCTO       |\n");
    printf(" |                                             |\n");
    printf(" |  ->                                         |\n");
    printf(" |                                             |\n");
    printf(" ===============================================\n");
    goTo(8,11);
    fflush(stdin);
    gets(respuesta);

}

void buscarUltimoTicket(char archivo[], char id[])//Busca el ultimo id de ticket cargado
{
    FILE* buff=fopen(archivo,"rb");

    Ticket u;

    int flag;

    if(buff){

        fseek(buff,sizeof(Ticket)*(-1),2);//Posiciona el cursor para leer el ultimo
        flag = fread(&u,sizeof(Ticket),1,buff);//Lee el ultimo ticket

        if(flag > 0 )
        {
            strcpy(id,u.id);//Copia el ultimo id cargado en id

        }else if (flag == 0) //Si no encontró nada significa que no hay tickets cargados, devuelve un ticket inicial
        {
            strcpy(id,"00000");
        }

        fclose(buff);
    }else{

        mensajeErrorDePrograma();

    }
}

void generarIdTicket(char idUltTicket[], char idTicket[])//Genera un id de ticket
{
    int cantCeros;

    char cero[] = "0";
    char idAux[6]= "";
    char idAux2[6]= "";

    int i = atoi(idUltTicket);//Convierte el ultimo id de ticket en un int

    i++;//Lo incrementa

    itoa(i,idAux,10);//pasa la id

    cantCeros = 5 - (strlen(idAux));//Calcula la cantidad de ceros a agregar al id

    for(int j = 0; j<cantCeros; j++)//Concatena los 0 al string auxiliar
    {
        strcat(idAux2, cero);
    }

    strcat(idAux2,idAux);//Concatena los 0 con i

    strcpy(idTicket,idAux2);//Copia el id limpio al id de ticket
}

///--------BAJA--------///
void cancelarTicket(Ticket *t, char archivoM[])//Cancela un ticket
{
    Mesa m;
    char opcion;

    cambiosGuardados();
    system("cls");
    opcion = guardarCambios(6,10);
    if (opcion == '1')
    {
        int posMesa = buscarMesaPorID(archivoM,t->mesaUsada);//Busca la posicion de la mesa asociada al ticket

        t->estado = 3;//Cambia el estado del ticket

        m = buscarYRetornarMesa(archivoM,posMesa);//Busca y retorna la mesa

        m.estadoOcupacion = editarEstadoOcupacion(m.estadoOcupacion);//Cambia el estado de ocupacion de la mesa

        sobreescribirMesa(archivoM,m,posMesa);//Sobreescribe la mesa

        ticketCancelado();
    }else
    {
        system("cls");
    }
}

///--------MODIFICACION--------///

void editarTicket(char archivoT[], char archivoP[], char archivoM[])//Edita un ticket
{
    Ticket t;

    char id[5];
    char opcion;
    int pos;

    ingresarIDMesaBuscado(id, archivoM);//Pide que se ingrese un id

    if(strcmp(id,"0")!= 0)
    {
        pos = buscarTicketPorMesa(archivoT,id);//Busca el ticket

        system("cls");

        if(pos > -1)//Si encuentra el ticket sigue a editarlo
        {
            t = buscarYretornarTicketPorPosicionDesdeFinal(archivoT,pos);//Busca el ticket

            if(t.estado==1)//Si el ticket no se cobró o canceló lo retorna
            {
                do
                {
                    opcion= menuEdicionTicket();
                    system("cls");
                    switch(opcion){
                    case '0':
                        break;
                    case '1':
                        aniadirProductosTicket(archivoP,&t);//Añade productos al ticket
                        break;

                    case '2':
                        eliminarProducto(&t,archivoT,archivoP);//Elimina un producto del ticket
                        break;

                    case '3':
                        cancelarTicket(&t,archivoM);//Cancela un ticket
                        break;
                        }

                    if (opcion == '1' || opcion == '2'  || (t.estado == 3 && opcion !='0'))//Si la opcion es valida y el usuario no quiso salir
                    {
                        system("cls");
                        mostrarTicket(t);//Muestra el ticket modificado
                        limpiarYContinuar();
                        sobreescribirTicket(archivoT,pos,t);//Sobreescribe el ticket
                    }

                }while(opcion != '0');

            }else if (t.estado == 2)
            {

                ticketYaCobrado();

            }else
            {
                ticketCancelado();
            }

        }else
        {
            noSeEncontroTicket();
        }
    }
}

char menuEdicionTicket()//Menu para ingresar la opcion de edicion del ticket
{

    char opcion;

    printf("===================================\n");
    printf("|                                 |\n");
    printf("|    ELIJA UNA OPCION A EDITAR    |\n");
    printf("|                                 |\n");
    printf("| 1.Agregar productos al ticket   |\n");
    printf("|                                 |\n");
    printf("| 2.Eliminar producto del ticket  |\n");
    printf("|                                 |\n");
    printf("| 3.Cancelar ticket               |\n");
    printf("|                                 |\n");
    printf("| 0.Volver                        |\n");
    printf("|                                 |\n");
    printf("| ->                              |\n");
    printf("|                                 |\n");
    printf("===================================\n");
    fflush(stdin);
    goTo(6,13);
    scanf("%c",&opcion);

    if(opcion !='1' && opcion!='2' && opcion!='3' && opcion!='0')
    {
        mensajeErrorOpcionInvalida();
        system("cls");
    }

    return opcion;
}

void sobreescribirTicket(char archivoT[], int pos, Ticket t)//Sobreescribe un ticket por su posicion
{
    FILE *buff;

    buff = fopen(archivoT,"r+b");

    if(buff)
    {
        fseek(buff,sizeof(Ticket)*(pos*-1),2);//Posiciona el cursor

        fwrite(&t,sizeof(Ticket),sizeof(Ticket),buff);//Escribe el ticket

        fclose(buff);
    }else
    {
        mensajeErrorDePrograma();
    }
}

void sobreescribirProductoEnTicket(Ticket *t, char nombreProducto[], int *verificar)//Sobreescribe productos en el arreglo de id de productos del ticket
{
    int flag = 0;
    int i = 0;

    // Buscar el producto por su nombre usando while y flag
    while (i < t->validosProducto && !flag)
    {
        if (strcmpi(t->idProductos[i], nombreProducto) == 0)
        {
            flag = 1;
        }
        else
        {
            i++;
        }
    }

    if (flag)// Desplazar los elementos restantes para sobrescribir el producto eliminado
    {
        while (i < t->validosProducto - 1)
        {
            strcpy(t->idProductos[i], t->idProductos[i + 1]);
            t->precioProducto[i] = t->precioProducto[i + 1];
            i++;
        }
        t->validosProducto--; //Reduce productos válidos
    }

    *verificar = flag;//Devuelve si elimino el producto del ticket
}

void eliminarProducto(Ticket *t, char archivoT[], char archivoP[])//"Elimina" un producto del ticket
{
    char productoEliminado[30];
    char opcion;
    int pos, flag;
    printf(" =============================================\n");
    printf(" |                                           |\n");
    printf(" |       ELIMINAR PRODUCTO DEL TICKET        |\n");
    printf(" |                                           |\n");
    printf(" =============================================\n");
    productoAcargar(productoEliminado);//Ingresa el nombre del ticket que quiere eliminar

    sobreescribirProductoEnTicket(t,productoEliminado,&flag); //Llama a la funcion de sobreescribir

    if(flag)//Si sobreescribe aumenta el stock del producto
    {
        productoEliminadoDelTicket();

        system("cls");
        printf(" ==================================\n");
        printf(" |                                |\n");
        printf(" | INGRESE SI QUIERE REINCORPORAR |\n");
        printf(" |      AL STOCK EL PRODUCTO      |\n");
        printf(" |          ELIMINADO             |\n");
        printf(" | 1.Si                           |\n");
        printf(" |                                |\n");
        printf(" | 2.No                           |\n");
        printf(" |                                |\n");
        printf(" | ->                             |\n");
        printf(" |                                |\n");
        printf(" ==================================\n");
        do
        {
            goTo(7,10);
            fflush(stdin);
            scanf("%c",&opcion);

            if(opcion != '1' && opcion !='2')
            {
                goTo(0,9);
                printf(" |    "ANSI_COLOR_RED"INGRESE UNA OPCION VALIDA"ANSI_COLOR_RESET"   |\n");
                printf(" | ->                             |\n");
            }

        }while(opcion != '1' && opcion !='2');

        if(opcion == '1')//Si el usuario desea, aumenta el stock del producto
        {
            pos = buscarProductoPorNombre(archivoP, productoEliminado);//Busca la posicion del producto

            modificarStockAutomatico(archivoP,pos,1);//Lo incrementa

            stockReincorporado();
        }

    }else
    {
        productoNoEncontradoEnTicket();
    }
}

float sumarProductos(float arr[], int validos, int i, float suma)//Suma los productos del arreglo de precios de producto de forma recursiva
{
    if (i == validos) {
        return suma;
    } else {
        return sumarProductos(arr, validos, i + 1, suma + arr[i]);
    }
}

float calcularTotalTicket(float arr[], int validos, float desc)// Calcula el total del ticket
{
    float suma = sumarProductos(arr, validos, 0, 0);//Retorna la suma
    suma = suma - (suma * (desc / 100));//Aplica el descuento
    suma = suma + (suma * ((float)IVA/100)); // Aplica el iva
    return suma;
}

void cobrarTicket(char archivoT[], char archivoM[])//Realiza cobra un ticket
{
    Ticket t;

    Mesa m;

    char id[5];

    char opcion;

    int pos;

    ingresarIDMesaBuscado(id, archivoM);//Ingresa el id de mesa

    if(strcmp(id,"0")!=0){

        pos = buscarTicketPorMesa(archivoT,id);//Busca la posicion del ticket

        system("cls");

        if(pos > -1)//Si encuentra el ticket
        {
            t = buscarYretornarTicketPorPosicionDesdeFinal(archivoT,pos);//Busca el ticket por posicion

            if(t.estado==1)//Si el ticket no fue cobrado o cancelado ingresa el descuento y lo cobra
            {
                printf(" ==========================================\n");
                printf(" |                                        |\n");
                printf(" |     INGRESE EL DESCUENTO DEL TICKET    |\n");
                printf(" |                                        |\n");
                printf(" | -> %%                                   |\n");
                printf(" |                                        |\n");
                printf(" ==========================================\n");
                goTo(9,5);
                fflush(stdin);
                scanf("%f",&t.descuento);
                printf("\n\n\n");
                t.total = calcularTotalTicket(t.precioProducto, t.validosProducto, t.descuento);//calcula el total
                mostrarTicket(t);//Muestra el ticket final
                limpiarYContinuar();
                opcion = guardarCambios(7,10);//Pregunta al usuario si desea guardar el ticket

                if(opcion == '1')//Si desea guardarlo lo guarda
                {
                    t.estado = 2;//Cambia el estado de ticket a cobrado

                    sobreescribirTicket(archivoT,pos,t);//Sobreescribe el ticket

                    pos = buscarMesaPorID(archivoM,id);//Busca la posicion de la mesa

                    m = buscarYRetornarMesa(archivoM,pos);//Retorna la mesa

                    m.estadoOcupacion = editarEstadoOcupacion(m.estadoOcupacion);//La desocupa

                    sobreescribirMesa(archivoM,m,pos);//Sobreescribe la mesa

                    ticketCobrado();//Imprime mensaje de ticket cobrado
                }


            }else if (t.estado == 2){

                ticketYaCobrado();

            }else
            {
                ticketCancelado();
            }

        } else
        {
            noSeEncontroTicket();
        }
    }

}

///--------CONSULTA--------///

int contarEnteros(float numero) //Cuenta los enteros de un float
{
    // Buffer para almacenar la representación del número como cadena
    char buffer[50];

    // Convertir el float a cadena con una precisión suficiente
    snprintf(buffer, sizeof(buffer), "%.1f", numero);

    // Buscar el punto decimal en la cadena
    char* punto = strchr(buffer, '.');

    // Si no se encuentra un punto decimal, contar toda la longitud de la cadena
    if (punto == NULL) {
        return strlen(buffer);
    }

    // La cantidad de dígitos antes del punto decimal es la distancia desde el inicio hasta el punto
    return punto - buffer;
}

void imprimirEspacios(int espacios)//Imprime una cierta cantidad de espacios dada por parametro
{
    for(int i = 0; i<espacios; i++)
    {
        printf(" ");
    }
}

void mostrarTicket(Ticket t)//Imprime un ticket
{
    int cantEnteros;

     t.total = calcularTotalTicket(t.precioProducto, t.validosProducto, t.descuento);

    printf(" |===============================================================|\n");
    printf(" |                         Ticket %s                          |\n", t.id);
    printf(" |===============================================================|\n");

    printf(" | Fecha: ");
    if(t.fechaTicket.dia<10)
    {
        printf("0");
    }
    printf("%d", t.fechaTicket.dia);
    printf("/");
    if(t.fechaTicket.mes<10)
    {
        printf("0");
    }
    printf("%d", t.fechaTicket.mes);
    printf("/%d                                             |\n", t.fechaTicket.anio);

    printf(" | Mesa: %s                                                    |\n", t.mesaUsada);
    printf(" | Cant  Descripcion                                 P.Unit      |\n");
    printf(" |---------------------------------------------------------------|\n");

    for (int i = 0; i < t.validosProducto; i++)
    {
        printf(" |  1     %s",t.idProductos[i]);
        dejarEspacios(43,strlen(t.idProductos[i]));

        printf("%.2f", t.precioProducto[i]);

        cantEnteros = contarEnteros(t.precioProducto[i]);

        imprimirEspacios(12-cantEnteros-3);

    printf("|\n");
    }


    printf(" |===============================================================|\n");

    printf(" | Descuento:                                        %.2f", t.descuento);

    cantEnteros = contarEnteros(t.descuento);

    imprimirEspacios(12-cantEnteros-3);

    printf("|\n");

    printf(" | IVA :                                             %.2d%%         |\n",IVA);

    printf(" | Total:                                            %.2f", t.total);
    cantEnteros = contarEnteros(t.total);

    imprimirEspacios(12-cantEnteros-3);

    printf("|\n");
    printf(" |===============================================================|\n");
    if(t.estado == 1)
    {
        printf(" |                       TICKET A COBRAR                         |\n");

    }else if(t.estado == 2)
    {
        printf(" |                       TICKET COBRADO                          |\n");

    }else
    {
        printf(" |                      TICKET CANCELADO                         |\n");

    }
    printf(" |===============================================================|\n");
    printf(" |                   Gracias por su compra!                      |\n");
    printf(" |===============================================================|\n\n");

}

int compararFecha(Fecha fecha1, Fecha fecha2)//Compara dos fechas, devuelve 1 si son iguales, 0 si no lo son
{
    int flag=0;

    if(fecha1.dia == fecha2.dia && fecha1.mes == fecha2.mes && fecha1.anio == fecha2.anio){

        flag++;

    }

    return flag;
}

void filtrarTicketFecha(char archivo[])//Pide el ingreso de una fecha y llama a filtrar los tickets que coincidan con esa fecha
{

    int verificacion=0;

    Fecha f=ingresoFecha();

    verificacion=mostrarTicketPorFecha(archivo,f);

    if(verificacion == 1)///Si encuentra fechas que coincidan, permite el ingreso de un id de esos tickets para mostrarlo detalladamente
    {
        goTo(0,1);
        filtrarTicketPorID(archivo,8,6);

    }else
    {
        noSeEncontroTicket();
    }
}

int mostrarTicketPorFecha(char archivo[], Fecha f)//Busca y muestra los tickes que coincidan con la fecha pasada por parametro
{
    FILE* buff = fopen(archivo,"rb");

    Ticket t;

    int i=0;
    int comp=0;

    if(buff){

        system("cls");
        printf(" ==============================\n");
        printf(" |                            |\n");
        printf(" |     TICKETS ENCONTRADOS    |\n");
        printf(" |                            |\n");
        while( fread(&t,sizeof(Ticket),1,buff) > 0 ){

            i=compararFecha(t.fechaTicket,f);

            if(i == 1){
                printf(" |  TICKET NRO: %s         |\n",t.id);
                comp=1;
            }

        }
        printf(" |                            |\n");
        printf(" ==============================\n");

        limpiarYContinuar();

        fclose(buff);

    }else{

        mensajeErrorDePrograma();

    }

    return comp;
}

void filtrarTicketPorID(char archivo[], int x, int y)//Pide que se ingrese un id de ticket para buscarlo
{
    char id[6];


    do
    {
        system("cls");
        printf(" ===============================================\n");
        printf(" |                                             |\n");
        printf(" |           INGRESE EL ID DEL TICKET          |\n");
        printf(" |        QUE QUIERE BUSCAR O 0 PARA SALIR     |\n");
        printf(" |                                             |\n");
        printf(" |  ->                                         |\n");
        printf(" |                                             |\n");
        printf(" ===============================================\n");

        goTo(x,y);
        fflush(stdin);
        gets(id);

        if(strlen(id)!= 5 && strcmp(id,"0")!=0)//Si el id no es valido vuelve a pedirle que ingrese e imprime el mensaje de id invalido
        {
            goTo(0,y-1);
            printf(" |             "ANSI_COLOR_RED"INGRESE UN ID VALIDO"ANSI_COLOR_RESET"            |\n");
            printf(" |  ->                                         |\n");
            Sleep(1100);
        }

        if(strlen(id) == 5)
        {
            buscarTicketPorID(archivo,id);//Si el id es valido busca el ticket
        }

    }while( strlen(id) != 5 && strcmp(id,"0")!=0);//Si el id es invalido o el usuario quiere salir sale del bucle


}

void buscarTicketPorID(char archivo[],char id[])//Busca un ticket por id
{

    FILE* buff = fopen(archivo,"rb");

    Ticket aux;

    int flag = 0;

    if(buff){

        while( fread(&aux,sizeof(Ticket),1,buff) > 0 && flag == 0){

            if(strcmp(id,aux.id) == 0 ){
                flag = 1;
                system("cls");
                mostrarTicket(aux);
                limpiarYContinuar();
            }

        }

        if(flag==0){

            noSeEncontroTicket();

        }

        fclose(buff);
    }else
    {

        mensajeErrorDePrograma();

    }

}

int buscarTicketPorMesa(char archivoT[], char idMesa[])//Busca un ticket por id de mesa
{
    FILE *buff;

    Ticket t;
    int desplazamiento = -1;
    int i = 0;
    int flag = 0;
    buff = fopen(archivoT,"rb");

    if(buff)
    {
        fseek(buff,sizeof(Ticket)*desplazamiento,2);//Posiciona el cursor atras del ticket a leer
        while(fread(&t,sizeof(Ticket),1,buff) && flag == 0)//Lee el ticket
        {
            if(strcmpi(t.mesaUsada,idMesa)==0)//Compara la mesa usada con el id
            {
                flag = 1;//Corta el while
            }
            desplazamiento--;//Decrementa el desplazamiento
            i++;//Aumenta la posicion del ticket
            fseek(buff,sizeof(Ticket)*desplazamiento,2);
        }

        fclose(buff);
    }else
    {
        mensajeErrorDePrograma();
    }

    if(flag == 0)
    {
        i = -1;
    }

    return i;//Devuelve su posicion
}

Mesa ingresarIdMesaParaTicket(char archivoM[], char idMesa[], int *flag)//Ingresa un id de mesa para inicializar un ticket y evalua que sea valido
{
    Mesa m;

    printf(" ===================================\n");
    printf(" |                                 |\n");
    printf(" |     INGRESE EL ID DE LA MESA    |\n");
    printf(" |      O PRESIONE 0 PARA SALIR    |\n");
    printf(" |                                 |\n");
    printf(" |                                 |\n");
    printf(" | ->                              |\n");
    printf(" |                                 |\n");
    printf(" ===================================\n");

    do
    {
        fflush(stdin);
        goTo(7,12);
        gets(idMesa);

        if(strcmp(idMesa,"0")!=0)//Evalua que el usuario no haya querido salir
        {
            if(strlen(idMesa) != 4)//Evalua si el largo de id es valido para ser de una mesa
            {
                goTo(0,11);
                printf(" |    "ANSI_COLOR_RED"INGRESE UN ID VALIDO"ANSI_COLOR_RESET"         |\n");
                printf(" | ->                              |\n");

            }else if (strlen(idMesa) == 4)//Evalua si el id es valido
            {

                *flag = buscarMesaPorID(archivoM,idMesa);//Busca la mesa

                if (*flag > -1)//Si encuentra la mesa la retorna
                {
                    m = buscarYRetornarMesa(archivoM,*flag);//Busca y retorna la mesa

                    if(m.estadoOcupacion == 1   || m.estadoActividad == 0)//Evalua el estado de actividad de la mesa
                    {
                        goTo(0,11);
                        printf(" |    "ANSI_COLOR_RED"LA MESA NO ESTA DISPONIBLE"ANSI_COLOR_RESET"   |\n");
                        printf(" | ->                              |\n");
                        *flag = -1;//Iguala flag a -1 para que el bucle siga
                    }
                }else//Si no la encuentra la mesa no existe
                {
                    goTo(0,11);
                    printf(" |      "ANSI_COLOR_RED"LA MESA NO EXISTE"ANSI_COLOR_RESET"          |\n");
                    printf(" | ->                              |\n");
                }

            }
        }

    }while( (strlen(idMesa) != 4 && strcmp(idMesa,"0")!=0) || (*flag < 0 && strcmp(idMesa,"0")!=0));

    return m;
}

Ticket buscarYretornarTicketPorPosicionDesdeFinal(char archivoT[], int pos)//Busca y retorna un ticket empezando a buscarlo desde el final del archivo
{
    FILE *buff;

    Ticket t;

    buff = fopen(archivoT,"rb");

    if(buff)
    {
        fseek(buff,sizeof(Ticket)*(pos*-1),2);

        fread(&t,sizeof(Ticket),1,buff);

        fclose(buff);
    }else
    {
        mensajeErrorDePrograma();
    }

    return t;
}





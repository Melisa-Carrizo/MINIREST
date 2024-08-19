#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Empleado.h"
#include "funcionesAuxiliares.h"
#include "fecha.h"
#include "logs.h"
#include "mensajesError.h"

///Guardado de logs
void guardarLog(char archivo[],char inicioID[])///Configura el log cuando se crea y lo manda a guardarLogEnArchivo
{
    Logs l;

    conseguirFechaActual(&l.fecha.dia,&l.fecha.mes,&l.fecha.anio);  //consigue la fecha actual para el log

    obtenerHoraActual(&l.fecha.hora,&l.fecha.minutos);  //consigue la hora y minutos actuales para el log

    strcpy(l.id,inicioID);  //copia el id ingresado al log

    guardarLogEnArchivo(archivo,l);   //guarda el log

}

void guardarLogEnArchivo(char archivo[],Logs l)///Guarda el Log recibido por parametros
{

    FILE* buff = fopen(archivo,"ab");   //abre el archivo

    if(buff){

        fwrite(&l,sizeof(Logs),1,buff); //escribe el archivo

        fclose(buff);

    }else{

        mensajeErrorDePrograma();   //mensaje de error si no se abre correctamente el archivo

    }
}

///Muestra de logs

void mostrarLogsDelDia(char archivo[])///Muestra los logs del dia guardandolo a una pila
{

    Pila pilaId;
    inicpila(&pilaId);
    Pila hora;
    inicpila(&hora);
    Pila minutos;
    inicpila(&minutos);

    Fecha f;
    Logs l;
    int id;
    int i=0;

    conseguirFechaActual(&f.dia,&f.mes,&f.anio);    //consigue la fecha actual

    FILE* buff= fopen(archivo,"rb");    //abre el archivo en lectura

    if(buff){

        while( fread(&l,sizeof(Logs),1,buff) > 0 ){ //lee los logs

            if(l.fecha.dia == f.dia && l.fecha.mes == f.mes && l.fecha.anio == f.anio){ //compara la fecha de los logs con la fecha guardada en f
                                                        //el id del log lo convierte en int y se guarda en la variable id que se guarda en la pilaId
                id = atoi(l.id);                        //y guarda la hora en la pila hora y los minutos en la pila minutos
                apilar(&pilaId,id);
                apilar(&hora,l.fecha.hora);
                apilar(&minutos,l.fecha.minutos);
                i++;

            }

        }

    }else{

        mensajeErrorDePrograma();

    }

    mostrarID(pilaId,hora,minutos,i);

    system("pause");
}

void mostrarID(Pila pila, Pila hora, Pila minutos, int i)///Muestra los logs del dia actual guardados en la pila con recursividad
{

    if(i<0){//i es condicion de corte

        printf("============================\n");
        printf("| ID: %d            |\n",desapilar(&pila));
        printf("| Hora: %d:%d               |\n",desapilar(&hora),desapilar(&minutos));
        printf("============================\n");
        i--;
    }else if(i>=1){

        i--;
        printf("============================\n");
        printf("| ID: %d             |\n",desapilar(&pila));
        printf("| Hora: %d:%d               |\n",desapilar(&hora),desapilar(&minutos));
        printf("============================\n\n");
        mostrarID(pila,hora,minutos,i);//llamada recursiva
    }
}

void mostrarLogDeAuno(Logs l)///Muestra los logs desde el archivo
{
    printf("============================\n");
    printf("| ID: %s             |",l.id);
    printf("\n| Fecha: ");
    if(l.fecha.dia < 10)
    {
        printf("0");
    }
    printf("%d/",l.fecha.dia);
    if(l.fecha.mes<10)
    {
        printf("0");
    }
    printf("%d",l.fecha.mes);
    printf("/%d        |\n",l.fecha.anio);
    printf("| Hora: ");
    if(l.fecha.hora<10)
    {
        printf("0");
    }
    printf("%d:",l.fecha.hora);
    if(l.fecha.minutos<10)
    {
        printf("0");
    }
    printf("%d              |\n",l.fecha.minutos);
    printf("============================\n\n");
}

void mostrarLogsPorFecha(char archivo[],Fecha f)///Utiliza arreglo dinamico para guardar los logs de una fecha
{

    Logs *arregloLogs=(Logs*)malloc(sizeof(Logs));//arreglo dinamico
    int validos=0;
    Logs l;
    FILE* buff = fopen(archivo,"rb");

    if(buff){

        while( fread(&l,sizeof(Logs),1,buff) > 0 ){ //lee los logs hasta que se termine

            if(l.fecha.dia == f.dia && l.fecha.mes == f.mes && l.fecha.anio == f.anio){ //guarda el log de la fecha que recibe por parametros
                validos++;
                arregloLogs=realloc(arregloLogs,sizeof(Logs)*validos);  //redimensiona el arreglo
                arregloLogs[validos-1]=l;
            }
        }

        fclose(buff);
    }else{

        mensajeErrorDePrograma();

    }

    if(validos!=0){ //si se cargo algo en el arreglo muestra el arreglo
    system("cls");
    mostrarArregloLogs(arregloLogs, validos);
    system("pause");

    }else if(validos==0){   //sino, muestra un mensaje de que no hay logs en la fecha indicada

       noRegistro();
    }

    free(arregloLogs);  //libera la memoria usada por el arreglo dinamico
    printf("\n");
}

void mostrarArregloLogs(Logs arregloLogs[], int validos)///Muestra el arreglo
{

    for(int i=0; i < validos; i++ ){

     mostrarLogDeAuno(arregloLogs[i]);

    }

}

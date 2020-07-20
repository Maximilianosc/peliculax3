#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "List.h"
#include "SortedMap.h"

//ESTRUCTURAS USADAS

typedef struct{
    char position[1024];
    char id[1024];
    char created[1024];
    char modified[1024];
    char description[1024];
    char title[1024];
    char url[1024];
    char title_type[1024];
    char rating[1024];
    char runtime[1024];
    char year[1024];
    char genres[1024];
    char votes[1024];
    char release[1024];
    char directors[1024];
    List* nombre_lista;
    int favorito;
}pelicula;

typedef struct{
    SortedMap *lista_peliculas;
    char nombre[30];
    char puntos[10];
}lista;

//FUNCION DEL MAPA ORDENADO

int cmpstring(const void * p1, const void * p2){
    const char * a = p1;
    const char * b = p2;
    return strcmp(b,a);
}

//PROTOTIPOS DE LAS FUNCIONES USADAS

const char *get_csv_field (char*,int);
void crear_mapapelis(FILE*,SortedMap*,SortedMap*,char*);
void mostrar_lista(lista*);
void mostrar_pelicula(pelicula*);
void marcar_pelicula(pelicula*,SortedMap*);
void recomendar_pelicula(SortedMap*);

int main(){
    int opcion=0,flag=0; //EL FLAG ES PARA CUANDO NO HAYAN LISTAS EN EL SISTEMA TODAS LAS OPCIONES QUE NO SEAN LA 1 Y 7 NO SE ACTIVEN
    char archivo[30],nombrecsv[30]; //ARCHIVO ES LA VARIABLE USADA PARA ALMACENAR NOMBRES O IDS PEDIDOS AL USUARIO
    FILE *fp;  //NOMBRE DEL FILE
    lista *aux;  //AUXILIAR PARA RECORRER LA LISTA DE PELICULAS
    pelicula *aux2;  //AUXILIAR PARA BUSCAR UNA PELICULA EN ESPECIFICO
    SortedMap *mapa_peliculas=createSortedMap(cmpstring),*mapa_listas_peliculas=createSortedMap(cmpstring); //MAPA DE PELICULAS Y MAPA DE LAS LISTAS DE LAS PELICULAS
    while (opcion!=7){ //MIENTRAS LA OPCION NO SEA 7 (SALIR) EL MENU SE VUELVE A MOSTRAR LUEGO DE TERMINAR UNA OPCION
        printf("-------------------------PELICULAX--------------------------\n");
        printf("Ingrese el numero de la opcion que desea que se realize:\n");
        printf("(1) Cargar Lista de Peliculas\n");
        printf("(2) Ver lista de Peliculas\n");
        printf("(3) Ver Peliculas de una lista\n");
        printf("(4) Ver informacion de una pelicula\n");
        printf("(5) Marcar Pelicula como preferida\n");
        printf("(6) Recomendar Pelicula\n");
        printf("(7) Salir\n");
        printf("------------------------------------------------------------\n");
        do{
            scanf("%d",&opcion);
            if ((opcion<=0)||(opcion>=8)){
                printf("Ingrese un numero valido\n");
            }
        }while ((opcion<=0)||(opcion>=8)); //VALIDACION PARA QUE EL NUMERO ESTE ENTRE 1 Y 7
        if (opcion==1){
            printf("------------------------------------------------------------\n");
            printf("Introduzca el nombre del archivo (excluyendo la extension):\n");
            do{
                scanf("%s",&archivo);
                strcpy(nombrecsv,archivo);  //SE GUARDA EL NOMBRE DEL ARCHIVO EN NOMBRECSV PARA POSTERIORMENTE AGREGARLE LA EXTENSION
                fp = fopen (strcat(nombrecsv,".csv"),"r");  //SE LE AGREGA LA EXTENSION.CSV A NOMBRECSV Y SE ABRE EL ARCHIVO
                if (fp==NULL){
                    printf("Archivo no encontrado... Ingrese un nombre valido:\n");
                }
            }while(fp==NULL); //COMPROBACION DE QUE EL ARCHIVO EXISTA
            if (searchSortedMap(mapa_listas_peliculas,archivo)==NULL){ //VALIDACION SI ES QUE LA LISTA NO ESTA EN EL SISTEMA
                crear_mapapelis(fp,mapa_peliculas,mapa_listas_peliculas,archivo); //FUNCION QUE ASIGNA ESTRUCTURAS, INSERTA A MAPAS Y LISTAS
                printf("\n***Archivo leido con exito***\n\n");
            }else{
                printf("\n***La lista ya esta cargada en el sistema***\n\n");
            }
            flag=1;  //SI SE CARGO UNA LISTA SE CONCEDE ACCESO A TODAS LAS DEMAS FUNCIONES DEL PROGRAMA
        }
        if (opcion==2){
            printf("------------------------------------------------------------\n");
            if (flag==1){
                aux=firstSortedMap(mapa_listas_peliculas);  //PRIMER ELEMENTO DEL MAPA LISTA DE PELICULAS
                printf("Las listas de peliculas cargadas son:\n\n");
                while(aux!=NULL){  //SE RECORRE EL MAPA IMPRIMIENDO SU CONTENIDO
                    printf("->%s\n",aux->nombre);
                    aux=nextSortedMap(mapa_listas_peliculas);  //SE AVANZA AL SIGUIENTE ELEMENTO DEL MAPA
                }
                printf("\n");
            }else{
                printf("\n***No hay ninguna Lista Cargada***\n\n");
            }
        }
        if (opcion==3){
            printf("------------------------------------------------------------\n");
            if (flag==1){
                printf("Introduzca el nombre de la lista:\n");
                do{
                    scanf("%s",&archivo);
                    aux=searchSortedMap(mapa_listas_peliculas,archivo); //SE BUSCA AL LISTA INGRESADA
                    if (aux==NULL){
                        printf("Lista no encontrada... Ingrese un nombre valido:\n");
                    }
                }while(aux==NULL); //VALIDACION DE QUE LA LISAT ESTE BIEN ESCRITA O ESTE EN EL SISTEMA
                printf("\n");
                mostrar_lista(aux);  //FUNCION QUE MUESTRA TODAS LAS PELICULAS DENTRO DE LA LISTA
            }else{
                printf("\n***No hay ninguna Lista Cargada***\n\n");
            }
        }
        if (opcion==4){
            printf("------------------------------------------------------------\n");
            if (flag==1){
                printf("Introduzca el ID de la pelicula:\n");
                do{
                    scanf("%s",&archivo);
                    aux2=searchSortedMap(mapa_peliculas,archivo);  //SE BSUCA LA PELICULA EN EL MAPA USANDO LA ID
                    if (aux2==NULL){
                        printf("Pelicula no encontrada... Ingrese un ID valido:\n");
                    }
                }while(aux2==NULL); //VALIDACION DE QUE EL ID EXISTA
                printf("\n");
                mostrar_pelicula(aux2);  //FUNCION QUE MUESTRA LOS DATOS DE LA PELICULA
            }else{
                printf("\n***No hay ninguna Lista Cargada***\n\n");
            }
        }
        if (opcion==5){
            printf("------------------------------------------------------------\n");
            if (flag==1){
                printf("Introduzca el ID de la pelicula:\n");
                do{
                    scanf("%s",&archivo);
                    aux2=searchSortedMap(mapa_peliculas,archivo); //SE BUSCA LA PELICULA
                    if (aux2==NULL){
                        printf("Pelicula no encontrada... Ingrese un ID valido:\n");
                    }
                }while(aux2==NULL);  //VALIDACION DE QUE EL ID EXISTA
                printf("\n");
                if (aux2->favorito==0){  //VALIDACION DE SI LA PELICULA YA ESTA EN FAVORITOS
                    marcar_pelicula(aux2,mapa_listas_peliculas);  //FUNCION QUE MARCA LA PELICULA COMO FAVORITA
                    printf("<%s> marcada como favorita exitosamente\n\n",aux2->title);
                }else{
                    printf("<%s> ya estaba marcada como favorita\n",aux2->title);
                }
            }else{
                printf("\n***No hay ninguna Lista Cargada***\n\n");
            }
        }
        if (opcion==6){
                printf("------------------------------------------------------------\n");
            if (flag==1){
                recomendar_pelicula(mapa_listas_peliculas);  //FUNCION QUE IMPRIME LAS 10 MEJORES PELIS DE LA LISTA CON MAS PUNTOS
            }else{
                printf("\n***No hay ninguna Lista Cargada***\n\n");
            }
        }
    }
    printf("--------------------------   -------------------------------\n");
    printf("-------------------- HAVE A NICE DAY --------------------------\n");
    printf("--------------------------   -------------------------------\n");

}

const char *get_csv_field (char * tmp, int k) {
    //se crea una copia del string tmp

    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void crear_mapapelis(FILE* fp,SortedMap* mapa_peliculas,SortedMap* mapa_lista_peliculas,char* archivo){
    pelicula *movie,*temp;  //VARIABLES PARA INSERTAR DENTRO DE LOS MAPAS DE TIPO PELICULA
    lista * listapeliculas=(lista*)malloc(sizeof(lista));  //VARIABLE TIPO LISTA
    listapeliculas->lista_peliculas=createSortedMap(cmpstring);  //SE CREA EL MAPA ORDENADO DE LA VARIABLE TIPO LISTA
    strcpy(listapeliculas->puntos,"0");  //SE INICIALIZAN LOS PUNTOS DE LA LISTA EN 0
    strcpy(listapeliculas->nombre,archivo);  //SE COPIA EL NOMBRE INGRESADO DE LA LISTA EN EL NOMBRE DE LA VARIABLE TIPO LISTA
    char linea[1024];  //ARREGLO QUE ALMACENA UNA LINEA DEL ARCHIVO
    char *aux;  //PUNTERO DONDE SE GUARDAN LOS PARAMETROS
    fgets (linea, 1023, fp); //SE LEE LA PRIMERA LINEA QUE NO CONTIENE DATOS DE PELICULAS
    while (fgets (linea, 1023, fp) != NULL) {  //SE LEE EL ARCHIVO LINEA POR LINEA HASTA EL FINAL
        movie=(pelicula*)malloc(sizeof(pelicula));  //SE LE ASIGNA MEMORIA A LA VARIABLE
        movie->favorito=0;  //SE INICIA EL FAVORITO DE LA PELICULA EN 0
        movie->nombre_lista=createList();  //SE CREA LA LISTA DENTRO DE LA VARIABLE
        aux = get_csv_field(linea, 0); //DE AQUI HACIA ABAJO SE VAN COPIANDO LOS PARAMETROS DENTRO DEL STRUCT DE RIPO PELICULA
        strcpy(movie->position,aux);
        aux = get_csv_field(linea, 1);
        strcpy(movie->id,aux);
        aux = get_csv_field(linea, 2);
        strcpy(movie->created,aux);
        aux = get_csv_field(linea, 3);
        strcpy(movie->modified,aux);
        aux = get_csv_field(linea, 4);
        strcpy(movie->description,aux);
        aux = get_csv_field(linea, 5);
        strcpy(movie->title,aux);
        aux = get_csv_field(linea, 6);
        strcpy(movie->url,aux);
        aux = get_csv_field(linea, 7);
        strcpy(movie->title_type,aux);
        aux = get_csv_field(linea, 8);
        strcpy(movie->rating,aux);
        aux = get_csv_field(linea, 9);
        strcpy(movie->runtime,aux);
        aux = get_csv_field(linea, 10);
        strcpy(movie->year,aux);
        aux = get_csv_field(linea, 11);
        strcpy(movie->genres,aux);
        aux = get_csv_field(linea, 12);
        strcpy(movie->votes,aux);
        aux = get_csv_field(linea, 13);
        strcpy(movie->release,aux);
        aux = get_csv_field(linea, 14);
        strcpy(movie->directors,aux);
        pushBack(movie->nombre_lista,listapeliculas);  //SE INGRESA LA LISTA A LA LISTA DE PELICULAS
        temp=searchSortedMap(mapa_peliculas,movie->id);  //VARIABLE PARA SABER SI LA PELICULA ESTA YA DENTRO DEL MAPA PELICULAS
        if (temp==NULL){ //SI LA PELICULA NO ESTABA EN EL MAPA PELICULAS
            insertSortedMap(mapa_peliculas,movie->id,movie);  //SE INSERTA EN EL MAPA PELIUCLAS
            insertSortedMap(listapeliculas->lista_peliculas,movie->rating,movie); //SE INSERTA EN EL MAPA DENTRO DE LA VARIABLE DE TIPO LISTA ORDENADA CON EL RATING COMO CLAVE
        }else{  //SI LA PELICULA YA SE ENCONTRABA EN EL MAPA PELICULAS
            pushBack(temp->nombre_lista,listapeliculas);  //SE INGRESA LA LISTA DE PELICULA A LA QUE TAMBIEN PERTENECE DENTRO DE LA LISTA DE PELICULAS
            insertSortedMap(listapeliculas->lista_peliculas,temp->rating,temp);  //SE INSERTA EN EL MAPA DENTRO DE LA VARIABLE DE TIPO LISTA ORDENADA CON EL RATING COMO CLAVE
            free(movie);  //SE LIBERA MEMORIA
        }
    }
    insertSortedMap(mapa_lista_peliculas,listapeliculas->nombre,listapeliculas);  //SE INSERTA LA LISTA EN EL MAPA DE LA LISTA DE PELICULAS
}

void mostrar_lista(lista* listapelis){
    pelicula *movie;  //VARIABLE DE TIPO PELICULA
    movie=firstSortedMap(listapelis->lista_peliculas);  //SE IGUALA AL PRIMER ELEMENTO DEL MAPA
    while(movie!=NULL){  //MIENTRAS NO SE LLEGUE AL ULTIMO ELEMENTO SE IMPRIMEN LOS DATOS DE LAS PELICULAS
        printf("Nombre Pelicula: %s\n",movie->title);
        printf("ID: %s\n",movie->id);
        printf("Rating: %s\n",movie->rating);
        printf("\n");
        movie=nextSortedMap(listapelis->lista_peliculas); //SE PASA AL SIGUIENTE ELEMENTO
    }
}

void mostrar_pelicula(pelicula* movie){
    lista *aux;  //VARIABLE TIPO LISTA
    printf("Nombre Pelicula: %s\n",movie->title);  //SE IMPRIMEN LOS DATOS DE LA PELICULA
    printf("Anio: %s\n",movie->year);
    printf("Director: %s\n",movie->directors);
    printf("Rating: %s\n",movie->rating);
    printf("Generos: %s\n",movie->genres);
    aux=firstList(movie->nombre_lista);  //SE IGUALA AL PRIMER ELEMENTO DE LA LISTA DE LAS LISTAS A LA QUE LA PELICULA PERTENECE
    printf("Listas asociadas a la pelicula:\n");
    while (aux!=NULL){  //SE IMPRIMEN LOS NOMBRES DE LAS LISTAS A LAS QUE LA PELI PERTENECE HASTA QUE SE ACABEN
        printf("-%s\n",aux->nombre);
        aux=nextList(movie->nombre_lista);  //SE PASA AL SIGUIENTE ELEMENTO
    }
    printf("\n");
}

void marcar_pelicula(pelicula* movie,SortedMap* mapa_listas){
    movie->favorito=1; //SE MODIFICA EL FAVORITO DENTRO DEL STRUCT DE TIPO PELICULA A 1
    lista * aux; //VARIABLE DE TIPO LISTA
    int trans;  //VARIABLE PARA TRANSFORMAR LOS PUNTOS DENTRO DE LA LISTA DE LA PELICULA
    aux=firstList(movie->nombre_lista); //SE IGUALA AL PRIMER ELEMENTO DE LAS LISTAS A LA QUE LA PELICULA PERTENECE
    while(aux!=NULL){  //SE REALIZA HASTA QUE LA LISTA ACABE
        trans=atoi(aux->puntos);  //SE TRANSFORMA EL STRING A INT
        trans++; //SE LE AUMENTA EN 1
        sprintf(aux->puntos,"%d",trans);  //SE LE VUELVE A TRANSFORMAR A INT
        aux=nextList(movie->nombre_lista);  //SE PASA AL SIGUIENTE ELEMENTO
    }
}

void recomendar_pelicula(SortedMap* mapa_lista){
    lista* aux,*temp; //AUXILIARES DE TIPO LISTA
    pelicula *aux2;  //AUXILIAR DE TIPO PELICULA
    int i=0; //VARIABLE PARA IMPRIMIR 10 ELEMENTOS SOLO
    aux=firstSortedMap(mapa_lista);  //SE IGUALA AL PRIMER ELEMENTO DEL MAPA DE LAS LISTAS
    temp=aux;  //VARIABLE PARA GUARDAR LA LISTA CON MAS PUNTOS
    while(aux!=NULL){
        if (atoi(aux->puntos)>atoi(temp->puntos)){  //SI LOS PUNTOS DE LA NUEVA LISTA SON MAYORES A LOS DE LA GUARDADA COMO MAYOR
            temp=aux;  //SE REEMPLAZA
        }
        aux=nextSortedMap(mapa_lista);  //SE PASA AL SIGUIENTE ELEMENTO DEL MAPA
    }
    aux2=firstSortedMap(temp->lista_peliculas);  //PRIMER ELEMENTO DEL MAPA CON MAS PUNTOS (OSEA LA PRIMERA PELICULA)
    printf("Lista con mas Puntos: %s\n",temp->nombre);
    printf("Puntos: %s\n",temp->puntos);
    printf("\nTop 10 mejores peliculas de la lista:\n\n");
    while((i<10)&&(aux2!=NULL)){  //SE IMRPIMEN LAS 10 PELICULAS DE LA LISTA CON MAS PUNTOS
        if(aux2->favorito!=1){
            printf("Nombre: %s\n",aux2->title);
            printf("Rating: %s\n",aux2->rating);
            printf("\n");
            i++;
        }
        aux2=nextSortedMap(temp->lista_peliculas);  //SE PASA AL SIGUIENTE ELEMENTO
    }
}

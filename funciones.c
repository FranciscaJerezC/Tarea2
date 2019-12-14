#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "funciones.h"

 struct Cancion{
 char *titulo;
 char *artista;
 char *duracion;
 char *album;
};


void cargar_datos_csv(FILE * fp, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    char * linea = (char*)calloc(1024,sizeof(char));
    fgets(linea,1024,fp); //elimina la linea inicial no util
    /*int cont = 0;*/

    while (fgets(linea,1024,fp) != NULL)
    {
        linea = strtok(linea,"\r");
        linea = _strdup(linea);

        Cancion * nuevaCancion = crearCancion(linea);
        if (searchMap(mapa_canciones, nuevaCancion->titulo) == NULL)
        {
             insertMap(mapa_canciones, nuevaCancion->titulo, nuevaCancion); //Se inserta la cancion al mapa canciones
        }
        if (searchMap(mapa_artistas, nuevaCancion->artista) == NULL)
        {
            Map * mapa_canciones_aux = createMap(stringHash, stringEqual);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //Se inserta la cancion en mapa auxiliar
            insertMap(mapa_artistas, nuevaCancion->artista, mapa_canciones_aux); //Se inserta el mapa aux artista en el mapa artista
        }
        else //Si artista ya se encuentra en mapa_artista entonces
        {
            Map *mapa_canciones_aux = searchMap(mapa_artistas,nuevaCancion->artista);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion);
        }

        if (searchMap(Mapa_album, nuevaCancion->album) == NULL)
        {
            Map * mapa_canciones_aux = createMap(stringHash, stringEqual);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //inserto cancion en mapa auxiliar
            insertMap(Mapa_album, nuevaCancion->album, mapa_canciones_aux); //inserto mapa con cancion dentro en el mapa de albumes
        }
        else //Si artista ya se encuentra en mapa_artista entonces
        {
            Map * mapa_canciones_aux = searchMap(Mapa_album,nuevaCancion->album);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion);
        }
        linea = (char*)calloc(1024,sizeof(char));
    }
}

/*-----------------------------------------------------------------------------------------------------------*/

void Exportar_canciones(Map * mapa_canciones){
   FILE *fb = fopen("listacanciones.csv","w");
   Cancion * nuevaCancion = (Cancion*)calloc(1,sizeof(Cancion));
   nuevaCancion = firstMap(mapa_canciones); //NuevaCancion toma el valor de la primera cancion en el mapa canciones
   while(nuevaCancion)
   {
        fprintf(fb,"%s,%s,%s,%s\n",nuevaCancion->titulo,nuevaCancion->artista,nuevaCancion->duracion,nuevaCancion->album); //Se imprime la cancion en el archivo
        nuevaCancion = nextMap(mapa_canciones);
   }
  fclose(fb);
}

/*-----------------------------------------------------------------------------------------------------------*/

Cancion * CrearCancionNueva(char *nombre_cancion,char *nombre_artista,char *duracion, char *nombreAlbum)
{
    Cancion * nuevaCancion = (Cancion*)calloc(1,sizeof(Cancion));
    nuevaCancion->titulo = (char*)calloc(100,sizeof(char));
    nuevaCancion->artista = (char*)calloc(100,sizeof(char));
    nuevaCancion->duracion = (char*)calloc(100,sizeof(char));
    nuevaCancion->album = (char*)calloc(100,sizeof(char));
    strcpy(nuevaCancion->titulo, nombre_cancion);
    strcpy(nuevaCancion->artista, nombre_artista);
    strcpy(nuevaCancion->duracion, duracion);
    strcpy(nuevaCancion->album, nombreAlbum);
    return nuevaCancion;
}

/*-----------------------------------------------------------------------------------------------------------*/

void agregarCancionExtra(char *nombre_cancion,char *nombre_artista,char *duracion, char *nombreAlbum, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
        Cancion * nuevaCancion = CrearCancionNueva(nombre_cancion,nombre_artista,duracion,nombreAlbum);
        if (searchMap(mapa_canciones,nuevaCancion->titulo) == NULL)
        {
            insertMap(mapa_canciones,nuevaCancion->titulo,nuevaCancion);
        }
       if (searchMap(mapa_artistas,nuevaCancion->artista) == NULL)
        {
            Map * mapa_aux =createMap(stringHash,stringEqual);
            insertMap(mapa_aux,nuevaCancion->titulo,nuevaCancion);
            insertMap(mapa_artistas,nuevaCancion->artista,mapa_aux);
        }
        else
        {
            insertMap(searchMap(mapa_artistas,nuevaCancion->artista),nuevaCancion->titulo,nuevaCancion);
        }

        if (searchMap(Mapa_album,nuevaCancion->album) == NULL)
        {
            Map * mapa_aux_2 = createMap(stringHash,stringEqual);
            insertMap(mapa_aux_2,nuevaCancion->album,nuevaCancion);
            insertMap(Mapa_album,nuevaCancion->album,mapa_aux_2);
        }
        else
        {
            insertMap(searchMap(Mapa_album,nuevaCancion->album),nuevaCancion->album,nuevaCancion);
        }
}

/*-----------------------------------------------------------------------------------------------------------*/

void agregarAlbumExtra(Map * mapa_album,Map * mapa_artistas,Map * mapa_canciones,char * nombreAlbum){
    int eleccion = 0; //para verificar que elige el usuario
    char nombreCancion[200];
    char nombreArtista[200];
    char duracion[100];
    Map * map_aux = createMap(stringHash,stringEqual);
    map_aux = searchMap(mapa_album,nombreAlbum);
    if(map_aux == NULL)
    {
        while (eleccion == 0)
        {
            printf("Desea Añadir una Cancion\n");
            scanf("%i",eleccion);
            if(eleccion != 0)
            {
                break;
            }
            system("cls");
            printf("Ingrese Nombre de la Cancion\n");
            getchar();
            scanf("%[^\n]s", nombreCancion);
            if ( *nombreCancion == NULL ) //Verifica que se ingrese un nombre
            {
                system("cls");
                do
                {
                    printf("Ningun Nombre Ingresado, Ingrese Nombre de Cancion a Ingresar \n");
                    getchar();
                    scanf("%[^\n]s", nombreCancion);
                    system("cls");
                } while (*nombreCancion == NULL); //While hasta que se ingrese un nombre
            }
            printf("Ingrese Artista\n");
            getchar();
            scanf("%[^\n]s", nombreArtista);
            printf("Ingrese la Duracion de la Cancion Ingresada\n");
            getchar();
            scanf("%[^\n]s",duracion);
            agregarCancionExtra(nombreCancion,nombreArtista,duracion,nombreAlbum,mapa_artistas,mapa_canciones,mapa_album);
        }
        insertMap(mapa_album,nombreAlbum,map_aux);

     }
    else
    {
        system("cls");
        printf("El album ya existe");
        getchar();
     }
}

/*-----------------------------------------------------------------------------------------------------------*/

void mostrarCancion(Map * mapa_canciones){  //SOLO PARA VERIFICAR QUE LAS CANCIONES SE GUARDARON
        Cancion * cancion = (Cancion*)calloc(1,sizeof(Cancion));
        cancion = firstMap(mapa_canciones);
        int cont = 0;
        while (cancion != NULL)
        {
            printf("ESTE ES: %s %s %s %s\n",cancion->titulo,cancion->artista,cancion->duracion,cancion->album);
            getchar();
            cancion = nextMap(mapa_canciones);
            cont++;
            printf("%i\n",cont);
        }
        printf("CONTADOR FINAL %i \n",cont);
        getchar();
        getchar();
}

/*-----------------------------------------------------------------------------------------------------------*/

Cancion * crearCancion(char * linea){
    Cancion * nuevaCancion = (Cancion*)calloc(1,sizeof(Cancion));
    nuevaCancion->titulo = (char*)calloc(100,sizeof(char));
    nuevaCancion->artista = (char*)calloc(100,sizeof(char));
    nuevaCancion->duracion = (char*)calloc(100,sizeof(char));
    nuevaCancion->album = (char*)calloc(100,sizeof(char));

    strcpy(nuevaCancion->titulo, get_csv_field(linea,1));
    strcpy(nuevaCancion->artista, get_csv_field(linea,2));
    strcpy(nuevaCancion->duracion, get_csv_field(linea,3));
    strcpy(nuevaCancion->album, get_csv_field(linea,4));
    return nuevaCancion;
}

/*-----------------------------------------------------------------------------------------------------------*/

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    if (searchMap(mapa_artistas, nombre_artista) != NULL)
    {
        Map *mapa_canciones_artista = searchMap(mapa_artistas, nombre_artista); //Se crea un mapa que toma el valor del artista indicado
        Cancion *cancion = firstMap(mapa_canciones_artista); //se crea un dato tipo cancion que toma el valor de la primera cancion del artista
        while (cancion != NULL)
        {
            eraseKeyMap(mapa_canciones,cancion->titulo); //elimina del mapa canciones
            eraseKeyMap(Mapa_album,cancion->album); //elimina del mapa album
            cancion=nextMap(mapa_canciones_artista); //avanza a la siguiente cancion
        }
        eraseKeyMap(mapa_artistas,nombre_artista); //elimina el artista del mapa artista
        printf("Canciones y Artista Eliminados Correctamente");
        getchar();
        getchar();
    }
    else
    {
        printf("NO EXISTE ARTISTA CON ESE NOMBRE");
        getchar();
        getchar();
    }
}

/*-----------------------------------------------------------------------------------------------------------*/

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones){
    Cancion * nuevaCancion = searchMap(mapa_canciones,nombre_cancion); //Se crea un dato de tipo cancion que toma el valor de la cancion indicada
    if (nuevaCancion != NULL)
    {
        printf("%s %s %s %s\n", nuevaCancion->titulo, nuevaCancion->artista, nuevaCancion->duracion, nuevaCancion->album);
        getchar();
        getchar();
    }
    else
    {
        printf("NO EXISTE CANCION CON ESE NOMBRE\n");
        getchar();
        getchar();
    }


}

/*-----------------------------------------------------------------------------------------------------------*/

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas){
    if (searchMap(mapa_artistas, nombre_artista) != NULL)
    {
        Map * mapa_aux = searchMap(mapa_artistas, nombre_artista);
        Cancion *nuevaCancion = firstMap(mapa_aux);
        while(nuevaCancion)
        {
            printf("%s %s %s %s\n", nuevaCancion->titulo, nuevaCancion->artista, nuevaCancion->duracion, nuevaCancion->album);
            nuevaCancion = nextMap(mapa_aux);
        }
        getchar();
        getchar();
    }
    else
    {
        printf("NO EXISTE ARTISTA CON ESE NOMBRE\n");
        getchar();
        getchar();
    }
}

/*-----------------------------------------------------------------------------------------------------------*/

void buscar_album(char * nombreAlbum, Map * mapa_album){
    if (searchMap(mapa_album,nombreAlbum) != NULL)
    {
        Map * mapa_aux = searchMap(mapa_album,nombreAlbum);// se crea un dato de tipo mapa el cual toma el valor del album indicado
        Cancion *nuevaCancion = firstMap(mapa_aux); //se crea un dato de tipo cancion que toma el valor del primer dato del mapa aux
        while (nuevaCancion)
        {
            printf("%s %s %s %s\n", nuevaCancion->titulo, nuevaCancion->artista, nuevaCancion->duracion, nuevaCancion->album);
            nuevaCancion = nextMap(mapa_aux);
        }
        getchar();
        getchar();

    }
    else
    {
        printf("NO EXISTE ALBUM CON ESE NOMBRE\n");
        getchar();
        getchar();
    }
}

/*-----------------------------------------------------------------------------------------------------------*/

char * _strdup (const char *s){
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}

/*-----------------------------------------------------------------------------------------------------------*/

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

/*-----------------------------------------------------------------------------------------------------------*/

long long stringHash(const void * key) {
    long long hash = 5381;
    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

/*-----------------------------------------------------------------------------------------------------------*/

int stringEqual(const void * key1, const void * key2) { //compara las strings
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}



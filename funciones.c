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


void cargar_datos_csv(FILE * fp, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){ //ERROR EN ALGO, EN EL ORIGINAL ZOZI
    char * linea = (char*)calloc(1024,sizeof(char));
    fgets(linea,1024,fp);
    int cont = 0;

    while (fgets(linea,1024,fp) != NULL)
    {
        linea = strtok(linea,"\r");
        linea = _strdup(linea);

        Cancion * nuevaCancion = crearCancion(linea);
        if (searchMap(mapa_canciones, nuevaCancion->titulo) == NULL)
        {
             insertMap(mapa_canciones, nuevaCancion->titulo, nuevaCancion); //Value es nuevaCancion?
        }
        if (searchMap(mapa_artistas, nuevaCancion->artista) == NULL)
        {
             Map * mapa_canciones_aux = createMap(stringHash, stringEqual); //se pone aca o adentro?
             insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //inserto cancion en mapa auxiliar

                 insertMap(mapa_artistas, nuevaCancion->artista, mapa_canciones_aux);
        }
        else //Si artista ya se encuentra en mapa_artista entonces
        {
            Map *mapa_canciones_aux = searchMap(mapa_artistas,nuevaCancion->artista);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion);
        }

        if (searchMap(Mapa_album, nuevaCancion->album) == NULL)
        {
             Map * mapa_canciones_aux = createMap(stringHash, stringEqual); //se pone aca o adentro?
             insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //inserto cancion en mapa auxiliar

              insertMap(Mapa_album, nuevaCancion->album, mapa_canciones_aux);
        }
        else //Si artista ya se encuentra en mapa_artista entonces
        {
            Map * mapa_canciones_aux = searchMap(Mapa_album,nuevaCancion->album);
            insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion);
        }
        linea = (char*)calloc(1024,sizeof(char));
        cont++;
        //printf("%i\n", cont);
        //printf("%s %s %s %s \n", nuevaCancion->titulo, nuevaCancion->artista, nuevaCancion->duracion, nuevaCancion->album);
    }
printf("CONTADOR FINAL %i\n", cont);
}

void mostrarCancion(Map * mapa_canciones){  //SOLO PARA VERIFICAR QUE LAS CANCIONES SE GUARDARON
        Cancion * cancion = (Cancion*)calloc(1,sizeof(Cancion));
        cancion = firstMap(mapa_canciones);
        int cont = 0;
        while (cancion != NULL)
        {
            printf("%s %s %s %s \n", cancion->titulo, cancion->artista, cancion->duracion, cancion->album);
            cancion = nextMap(mapa_canciones);
            cont++;
            printf("%i\n",cont);
        }
        printf("CONTADOR FINAL %i \n",cont);
}

void agregarCancionExtra(char *nombre_cancion,char *nombre_artista,char *duracion, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    Cancion *nuevaCancion = malloc(sizeof(Cancion));
        nuevaCancion->titulo = nombre_cancion;
        nuevaCancion->artista = nombre_artista;
        nuevaCancion->duracion = duracion;
        nuevaCancion->album = "-";

        if (searchMap(mapa_canciones, nuevaCancion->titulo) == NULL)
        {
             insertMap(mapa_canciones, nuevaCancion->titulo, nuevaCancion);
        }
        if (searchMap(mapa_artistas, nuevaCancion->artista) == NULL)
        {
             Map * mapa_canciones_aux = createMap(stringHash, stringEqual);
             insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion);
             if ( searchMap(mapa_artistas, nuevaCancion->artista) == NULL)
             {
                 insertMap(mapa_artistas, nuevaCancion->artista, mapa_canciones_aux);
             }
             else //Si artista ya se encuentra en mapa_artista entonces
             {

                insertMap(searchMap(mapa_artistas, nuevaCancion->artista), nuevaCancion->artista, nuevaCancion);
             }
        }



        if (searchMap(Mapa_album, nuevaCancion->album) == NULL)
        {
             Map * mapa_canciones_aux = createMap(stringHash, stringEqual); //se pone aca o adentro?
             insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //inserto cancion en mapa auxiliar
             if ( searchMap(Mapa_album, nuevaCancion->album) == NULL)
             {
                 insertMap(Mapa_album, nuevaCancion->album, mapa_canciones_aux);
             }
             else //Si artista ya se encuentra en mapa_artista entonces
             {

                insertMap(searchMap(Mapa_album, nuevaCancion->album), nuevaCancion->album, nuevaCancion);
             }
        }



}

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

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
    if (searchMap(mapa_artistas, nombre_artista) != NULL)
    {
        Map *mapa_canciones_artista = searchMap(mapa_artistas, nombre_artista);
        Cancion *cancion = firstMap(mapa_canciones_artista);
        while (cancion != NULL)
        {
            eraseKeyMap(mapa_canciones,cancion->titulo); //elimina del mapa canciones
            Map * mapaAux = searchMap(Mapa_album,cancion->album);
            eraseKeyMap(mapaAux,cancion->titulo); //elimina del mapa album
            cancion=nextMap(mapa_canciones_artista);
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

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones){
    if (searchMap(mapa_canciones, nombre_cancion) != NULL)
    {
        Cancion * nuevaCancion = searchMap(mapa_canciones, nombre_cancion);
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

char * _strdup (const char *s){
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}

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

long long stringHash(const void * key) {
    long long hash = 5381;
    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}



//void mostrarCancion(Map * mapa_canciones)  //SOLO PARA VERIFICAR QUE ESTA GUARDADO, YYZ explota
//{
  //  Cancion * caught = searchMap(mapa_canciones, "YYZ");
   // printf("%s %s %s %s\n", caught->titulo, caught->artista, caught->duracion, caught->album);
//}


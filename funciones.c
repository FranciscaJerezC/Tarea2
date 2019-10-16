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
    char * linea = (char*) malloc (1024*sizeof(char));
    Cancion *nuevaCancion = malloc(sizeof(Cancion));
    while (fgets(linea,1024,fp) != NULL)
    {
        linea = strtok(linea,"\r");
        linea = _strdup(linea);
        char * lineaAux = (char*) malloc (1024*sizeof(char));
        strcpy(lineaAux,linea);
        nuevaCancion = crearCancion(lineaAux);
        if (searchMap(mapa_canciones, nuevaCancion->titulo) == NULL)
        {
             insertMap(mapa_canciones, nuevaCancion->titulo, nuevaCancion); //Value es nuevaCancion?
        }
        if (searchMap(mapa_artistas, nuevaCancion->artista) == NULL)
        {
             Map * mapa_canciones_aux = createMap(stringHash, stringEqual); //se pone aca o adentro?
             insertMap(mapa_canciones_aux, nuevaCancion->titulo, nuevaCancion); //inserto cancion en mapa auxiliar
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

}



void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album){
        Map *mapa_canciones_artista = searchMap(mapa_artistas, nombre_artista);
        Cancion *cancion = firstMap(mapa_canciones_artista);
        while (cancion != NULL)
        {
            eraseKeyMap(mapa_canciones,cancion->titulo); //elimina del mapa canciones
            eraseKeyMap(Mapa_album,cancion->album); //elimina del mapa album
            cancion=nextMap(mapa_canciones_artista);
        }
        eraseKeyMap(mapa_artistas,nombre_artista); //elimina el artista del mapa artista
}


Cancion * buscar_cancion(char * nombre_cancion, Map * mapa_canciones){
    if (searchMap(mapa_canciones, nombre_cancion) != NULL)
    {
        return searchMap(mapa_canciones, nombre_cancion);
    }
    else
    {
        return NULL;
    }

}



Map * buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas){
    if (searchMap(mapa_artistas, nombre_artista) != NULL)
    {
        return searchMap(mapa_artistas, nombre_artista);
    }
    else
    {
        return NULL;
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

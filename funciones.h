#ifndef funciones_h
#define funciones_h

typedef struct Cancion Cancion;

void cargar_datos_csv(FILE * fp, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void mostrarCancion(Map * mapa_canciones );  //SOLO PARA VERIFICAR QUE LAS CANCIONES SE GUARDARON

void agregarCancionExtra(char * nombre_cancion ,char * nombre_artista , char * duracion, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones);

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Cancion * crearCancion(char * linea);

const char *get_csv_field (char * tmp, int i);

char * _strdup (const char *s);

#endif

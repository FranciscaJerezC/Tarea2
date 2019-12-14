#ifndef funciones_h
#define funciones_h

typedef struct Cancion Cancion;

void cargar_datos_csv(FILE * fp, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void mostrarCancion(Map * mapa_canciones );  //SOLO PARA VERIFICAR QUE LAS CANCIONES SE GUARDARON

void agregarCancionExtra(char * nombre_cancion ,char * nombre_artista , char * duracion, char *nombreAlbum, Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

void buscar_cancion(char * nombre_cancion, Map * mapa_canciones);

void buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas);

void buscar_album(char * nombreAlbum, Map * mapa_album);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Cancion * crearCancion(char * linea);

const char *get_csv_field (char * tmp, int i);

char * _strdup (const char *s);

void Exportar_canciones(Map * mapa_canciones);

Cancion * CrearCancionNueva(char *nombre_cancion,char *nombre_artista,char *duracion, char *nombreAlbum);

void agregarAlbumExtra(Map * mapa_album,Map * mapa_artistas,Map * mapa_canciones,char * nombreAlbum);


#endif

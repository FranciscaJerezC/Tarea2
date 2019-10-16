#ifndef funciones_h
#define funciones_h

typedef struct Cancion Cancion;

void eliminar_canciones_artista(char * nombre_artista,Map * mapa_canciones , Map * mapa_artistas, Map * Mapa_album);

Cancion * buscar_cancion(char * nombre_cancion, Map * mapa_canciones);

Map * buscar_canciones_artista(char * nombre_artista, Map * mapa_artistas);
long long stringHash(const void * key);
int stringEqual(const void * key1, const void * key2);
#endif

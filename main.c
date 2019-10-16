#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "funciones.h"


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




int main()
{
    int op;

    char nombreCancion[100];
    char nombreArtista[100];
    FILE * fp = fopen("canciones.csv", "r");

    Map * mapa_canciones = createMap(stringHash, stringEqual);
    Map * mapa_artistas = createMap(stringHash, stringEqual);
    Map * mapa_album = createMap(stringHash, stringEqual);



    while(op) //Menu
    {
      printf("1.-Importar Música\n");
      printf("2.-Exportar Música\n");
      printf("3.-Agregar Álbum\n");
      printf("4.-Agregar Canción\n");
      printf("5.-Eliminar canción de un Artista\n");
      printf("6.-Buscar Canción\n");
      printf("7.-Buscar Canciones de un Artista\n");
      printf("8.-Buscar Álbum");
      printf("9.-Salir\n");
      printf("Escoja una opcion -> ");
      scanf("%i",&op);
      if( op < 1 || op > 9)
      {
        system("cls");  //Limpia pantalla
        printf("Ingrese un valor valido\n");
        getchar();
        getchar();
        system("cls");
      }

      switch (op)
      {
          case 1: //Importar musica

                system("cls");
                cargar_datos_csv(fp, mapa_canciones, mapa_artistas, mapa_album);

                break; //vuelve a la pantalla principal


          case 2: //Exportar musica

                system("cls");
                break;

          case 3: //agregar album

                system("cls");
                break;


          case 4:  //agregar cancion

                system("cls");
                break;

          case 5: //eliminar cancion de un artista

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA EL ARTISTA PRIMERO
                printf("Ingrese nombre del Artista");
                scanf("%[^\n]s",nombreArtista); //Lee el nombre del artista a borrar
                eliminar_canciones_artista(nombreArtista, mapa_canciones, mapa_artistas, mapa_album);  //Se puede usar los mapas para llamar la funcion si es que en el pdf (tarea2) no se usan?
                break;

          case 6: //buscar cancion

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA LA CANCION
                printf("Ingrese Nombre de Cancion");
                scanf("%[^\n]s",nombreCancion);

                buscar_cancion(nombreCancion, mapa_canciones);
                break;

          case 7: //Buscar Canciones de un Artista

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA EL ARTISTA
                printf("Ingrese Nombre del Artista");
                scanf("%[^\n]s",nombreArtista);

                buscar_canciones_artista(nombreArtista,mapa_artistas);

                break;

          case 8: //buscar album

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA ALBUM
                break;


          case 9: //salir
                system("cls");
                exit (1);
                break;

        }

    }
}

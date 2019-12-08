#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "funciones.h"






int main()
{
    int op;

    char nombreCancion[200];
    char nombreArtista[200];
    char duracion[100];
    FILE * fp = fopen("canciones.csv", "r");
//Consejo, fopen en modo write y fprintf

    Map * mapa_canciones = createMap(stringHash, stringEqual);
    Map * mapa_artistas = createMap(stringHash, stringEqual);
    Map * mapa_album = createMap(stringHash, stringEqual);


    while(op) //Menu
    {
      printf("1.-Importar Musica\n");
      printf("2.-Exportar Musica\n");
      printf("3.-Agregar Album\n");
      printf("4.-Agregar Cancion\n");
      printf("5.-Eliminar cancion de un Artista\n");
      printf("6.-Buscar Cancion\n");
      printf("7.-Buscar Canciones de un Artista\n");
      printf("8.-Buscar Album\n");
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
                //mostrarCancion(mapa_canciones);
                printf("Canciones Cargadas\n");
                getchar();
                getchar();
                system("cls");
                //mostrarCancion(mapa_canciones);
                break; //vuelve a la pantalla principal


          case 2: //Exportar musica

                system("cls");
                break;

          case 3: //agregar album

                system("cls");
                break;


          case 4:  //agregar cancion

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


                    printf("%s %s %s\n",nombreCancion,nombreArtista,duracion);
                    agregarCancionExtra(nombreCancion,nombreArtista,atoi(duracion),mapa_artistas,mapa_canciones,mapa_album);
                    system("cls");

                    getchar();
                    mostrarCancion(mapa_canciones);

                    getchar();
                    system("cls");

                //crearCancion() //Verificar que exista o no
                break;

          case 5: //eliminar cancion de un artista

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA EL ARTISTA PRIMERO
                printf("Ingrese nombre del Artista\n");
                getchar();
                scanf("%[^\n]s",nombreArtista); //Lee el nombre del artista a borrar
                system("cls");
                eliminar_canciones_artista(nombreArtista, mapa_canciones, mapa_artistas, mapa_album);  //Se puede usar los mapas para llamar la funcion si es que en el pdf (tarea2) no se usan?
                system("cls");
                break;

          case 6: //buscar cancion

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA LA CANCION
                printf("Ingrese Nombre de Cancion\n");
                getchar();
                scanf("%[^\n]s",nombreCancion);
                system("cls");
                buscar_cancion(nombreCancion, mapa_canciones);
                system("cls");
                break;

          case 7: //Buscar Canciones de un Artista

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA EL ARTISTA
                printf("Ingrese Nombre del Artista\n");
                getchar();
                scanf("%[^\n]s",nombreArtista);
                system("cls");
                buscar_canciones_artista(nombreArtista,mapa_artistas);
                system("cls");

                break;

          case 8: //buscar album

                system("cls"); //HAY QUE VERIFICAR QUE EXISTA ALBUM
                mostrarCancion(mapa_canciones);
                break;


          case 9: //salir
                system("cls");
                exit (1);
                break;

        }

    }
}

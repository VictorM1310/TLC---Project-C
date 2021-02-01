#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArregloTokens.h"

int CargaTokens(char *nomArchivo, arregloChar2D *aC)
{
    FILE *arch;
    arch = fopen (nomArchivo, "r");
	char linea[256];
    int i=0;
	if (arch != NULL)
	{

		while(fgets(linea, 255, arch)!=NULL)
        {
            char *s, *ptr;
            s = strtok_r(linea, " \t\n", &ptr);
            if (s[0])
            {
                do
                {   if (linea[0] == '#')
                    {
                        break;
                    }
                    if(s[0]=='"')
                    {
                        char arrayTemp[256];
                        do
                        {
                            strcat(arrayTemp,s);
                            s = strtok_r(NULL, " \t\n", &ptr);
                            strcat(arrayTemp, " ");

                        }while(s[0]!='"');
                        strcat(arrayTemp,s);
                        strncpy (aC->A[i], arrayTemp, 255);
                        memset(arrayTemp,0,256);
                        s = strtok_r(linea, " \t\n", &ptr);
                        printf("Esta es la posicion %d: %s\n",i,aC->A[i]);
                    }
                    i++;
                    strncpy (aC->A[i], s, 255);
                    printf("Esta es la posicion %d: %s\n",i,aC->A[i]);
                    s = strtok_r(NULL, " \t\n", &ptr);

                } while (s != NULL);
                printf("\n");
            }
            else
                printf("No hay token que leer\n");

        }
	}
	return 0;
}

int main(int argc, char **argv)
{
    arregloChar2D Q;
    unsigned int r = 40, c = 100;
    initArregloChar2D(&Q,r,c);

	if (argc>1)
    {
      if (CargaTokens(argv[1], &Q) < 0)
         exit(1);
    }
    else
    {
      fprintf(stderr, "Error: Se tiene que pasar como argumento el archivo que contiene la base de datos\n");
      exit(1);
    }
    imprimeArregloC2D(&Q);
    return 0;
}

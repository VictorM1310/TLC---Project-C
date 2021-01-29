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
                
            if (s)
            {
                do
                {   if (linea[0] == '#')
                    {
                        break;
                    }
                    strncpy (aC->A[i], s, 255);
                    printf("En esta posicion se encuentra: %s\n",aC->A[i]);
                    
                    

                    s = strtok_r(NULL, " \t\n", &ptr);
                    

                    i++;

                } while (s != NULL);
                printf("\n");
            }
            else
                printf("No hay token que leer\n");
        }   

        fclose(arch);
	}

	return 0;
}

void Comp(arregloChar2D *aC)
{
   char *palabras[] = {"PROGRAMA","factorial", "REPITE", "VECES", "FINREPITE", "LEE", "FINPROG", "IMPRIME"};

   for(int j = 0; j < 37; j++)
    for(int k = 0; k < 8; k++)
    {   
        printf("%s con %s \n\n",palabras[k], aC->A[j]);

        if(strncmp(aC->A[j], palabras[k],255) == 0)
        {
            printf("%s es palabra aceptada\n\n", aC->A[j]);

        }
    }
    
}



int main(int argc, char **argv)
{
    arregloChar2D Q;
    unsigned int r = 100, c = 100;
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

    Comp(&Q);
    imprimeArregloC2D(&Q);
    
   return 0;
}

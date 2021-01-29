#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArregloTokens.h"

int initArregloChar2D(arregloChar2D *aC, unsigned int r, unsigned int c)
{
	if (r && c) //Validamos que r y c sean diferentes de 0
	{
		unsigned int i;

		aC->A = malloc(r * sizeof (char *));
		if (aC->A != NULL) //equivalente a aI->A
		{
			aC->A[0] = malloc(r * c * sizeof (char));
			if (aC->A[0] != NULL) //equivalente a aI->A[0]
				for (i = 1; i < r; ++i)
					//aI->A[i] = &(aI->A[0][i * c]);//Aqui usamos el operador &
					aC->A[i] = aC->A[0] + i * c;//Aqui usamos aritmetica de apuntadores.
			else
			{
				free(aC->A);
				aC->A = NULL;
				aC->ren = aC->col = aC->tama = 0;
				return -1;
			}
		}
		else
		{
			aC->ren = aC->col = aC->tama = 0;
			return -1;
		}
		aC->ren = r;
		aC->col = c;
		aC->tama = r * c;
		return 0;
	}
	aC->ren = aC->col = aC->tama = 0;
	aC->A = NULL;
	return 0;
}



void liberaArregloChar2D(arregloChar2D *aC)
{
		if(aC->tama)
		{
			free(aC->A[0]);
			free(aC->A);
			aC->ren = aC->col = aC->tama = 0;
			aC->A = NULL;
		}
}

void fImprimeArregloC2D(FILE* arch, arregloChar2D *aC)
{
	unsigned int i;

	
	for (i = 0; i < aC->ren; ++i)
	{	
		fprintf(arch, "[");
		fprintf(arch, " %s ", aC->A[i]);
		fprintf(arch, "];\n");
	}
	
}

void imprimeArregloC2D(arregloChar2D *aC)
{
	fImprimeArregloC2D(stdout, aC);
}

/*void imprimeArregloC2D(arregloChar2D *aC)
{
	for(int i = 0; i < 50;i++)
	{		printf("C[%d] = %s\n\n",i,aC->A[i]);
			
	}
}*/	

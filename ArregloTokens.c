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
int initArregloInt2D(arregloInt2D *aI, unsigned int r1, unsigned int c1)
{
	if (r1 && c1) //Validamos que r y c sean diferentes de 0
	{
		unsigned int i;

		aI->B = malloc(r1 * sizeof (int *));
		if (aI->B != NULL) //equivalente a aI->A
		{
			aI->B[0] = malloc(r1 * c1 * sizeof (int));
			if (aI->B[0] != NULL) //equivalente a aI->A[0]
				for (i = 1; i < r1; ++i)
					//aI->A[i] = &(aI->A[0][i * c]);//Aqui usamos el operador &
					aI->B[i] = aI->B[0] + i * c1;//Aqui usamos aritmetica de apuntadores.
			else
			{
				free(aI->B);
				aI->B = NULL;
				aI->ren = aI->col = aI->tama = 0;
				return -1;
			}
		}
		else
		{
			aI->ren = aI->col = aI->tama = 0;
			return -1;
		}
		aI->ren = r1;
		aI->col = c1;
		aI->tama = r1 * c1;
		return 0;
	}
	aI->ren = aI->col = aI->tama = 0;
	aI->B = NULL;
	return 0;
}



void liberaArregloInt2D(arregloInt2D *aI)
{
		if(aI->tama)
		{
			free(aI->B[0]);
			free(aI->B);
			aI->ren = aI->col = aI->tama = 0;
			aI->B = NULL;
		}
}

void fImprimeArregloC2D(FILE* arch, arregloChar2D *aC)
{
	unsigned int i;


	for (i = 0; i < 50; ++i)
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


#ifndef __ARREGLO_TOKENS__
#define __ARREGLO_TOKENS__

#include <stdlib.h>


typedef struct
{
	char **A;           //Apuntador al arreglo.
	unsigned int ren;  //Numero de renglones de la matriz
	unsigned int col;  //Numero de columnas de la matriz
	unsigned int tama; //Numero de elementos de la matriz (ren x col).

} arregloChar2D;

typedef struct
{
	int **B;
	unsigned int ren;
	unsigned int col;
	unsigned int tama;

} arregloInt2D;

int initArregloChar2D(arregloChar2D *aC, unsigned int r, unsigned int c);

int initArregloInt2D(arregloInt2D *aI, unsigned int r1, unsigned int c1);

void liberaArregloChar2D(arregloChar2D *aC);

void liberaArregloInt2D(arregloInt2D *aI);

void fImprimeArregloC2D(FILE *arch, arregloChar2D *aC);

void imprimeArregloC2D(arregloChar2D *aC);

int CargaTokens(char *nomArchivo, char Tokens[][256], arregloInt2D *aI);


#endif

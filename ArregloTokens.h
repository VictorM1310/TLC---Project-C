#ifndef __ARREGLO_TOKENS__ 
#define __ARREGLO_TOKENS__

#include <stdlib.h>


typedef struct
{
	char **A;           //Apuntador al arreglo.
	unsigned int ren;  //N�mero de renglones de la matriz
	unsigned int col;  //N�mero de columnas de la matriz
	unsigned int tama; //N�mero de elementos de la matriz (ren x col).

} arregloChar2D;



int initArregloChar2D(arregloChar2D *aC, unsigned int r, unsigned int c);

void liberaArregloChar2D(arregloChar2D *aC);

void fImprimeArregloC2D(FILE *arch, arregloChar2D *aC);

void imprimeArregloC2D(arregloChar2D *aC);

int CargaTokens(char *nomArchivo, arregloChar2D *aC);

void Comp(arregloChar2D *aC);
#endif

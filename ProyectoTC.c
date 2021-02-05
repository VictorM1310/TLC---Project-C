#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
                        memset(arrayTemp,0,256);
                        strcat(arrayTemp,s);
                        do
                        {
                            strcat(arrayTemp, " ");
                            s = strtok_r(NULL, " \t\n", &ptr);
                            strcat(arrayTemp,s);

                        }while(s[0]!='"');
                        strncpy (aC->A[i], arrayTemp, 255);
                        printf("Esta es la posicion %d: %s\n",i,aC->A[i]);
                        i++;
                        s=NULL;
                    }
                    else
                    {
                        strncpy (aC->A[i], s, 255);
                        printf("Esta es la posicion %d: %s\n",i,aC->A[i]);
                        s = strtok_r(NULL, " \t\n", &ptr);
                        i++;
                    }
                } while (s != NULL);
                printf("\n");
            }
            else
                printf("No hay token que leer\n");

        }
        printf("i vale: %d\n",i);
	}
	return 0;
}
int CompPalabraReserv(arregloChar2D *aC,unsigned int i)
{
    if(strcmp(aC->A[i],"PROGRAMA") != 0)
        return -1;
    if(strcmp(aC->A[i],"FINPROG") != 0)
        return -1;
    if(strcmp(aC->A[i],"SI") != 0)
        return -1;
    if(strcmp(aC->A[i],"ENTONCES") != 0)
        return -1;
    if(strcmp(aC->A[i],"SINO") != 0)
        return -1;
    if(strcmp(aC->A[i],"FINSI") != 0)
        return -1;
    if(strcmp(aC->A[i],"REPITE") != 0)
        return -1;
    if(strcmp(aC->A[i],"VECES") != 0)
        return -1;
    if(strcmp(aC->A[i],"FINREP") != 0)
        return -1;
    if(strcmp(aC->A[i],"IMPRIME") != 0)
        return -1;
    if(strcmp(aC->A[i],"LEE") != 0)
        return -1;

    return 0;
}
int CompOperRel(arregloChar2D *aC, unsigned i)
{
    if(strcmp(aC->A[i],">") != 0)
        return -1;
    if(strcmp(aC->A[i],"<") != 0)
        return -1;
    if(strcmp(aC->A[i],"==") != 0)
        return -1;

    return 0;
}
int CompOperArit(arregloChar2D *aC,unsigned int i)
{
    if(strcmp(aC->A[i],"+") != 0)
        return -1;
    if(strcmp(aC->A[i],"-") != 0)
        return -1;
    if(strcmp(aC->A[i],"*") != 0)
        return -1;
    if(strcmp(aC->A[i],"/") != 0)
        return -1;

    return 0;
}

int CompAsig(arregloChar2D *aC,unsigned int i)
{
    if(strcmp(aC->A[i],"=") != 0)
        return -1;

    return 0;
}

int CompLiteralNum(arregloChar2D *aC,unsigned int i)
{
    unsigned int tama = 0;
    unsigned int LiteralInvalida = 0;
    tama = strlen(aC->A[i]);
    for(int j=0; j<tama; j++)
    {
        if (isdigit(aC->A[i][j])==0)
            return -1;
        if(aC->A[i][j] == '8'||aC->A[i][j] == '9')
            LiteralInvalida = 1;
    }
    if(LiteralInvalida == 1)
    {
        printf("Es invalida\n");
        return -1;
    }
    return 0;
}
int CompIdent(arregloChar2D *aC,unsigned int i)
{
    if(isdigit(aC->A[i][0]) == 0)
        return -1;

    return 0;
}
void ClasificaTokens(arregloChar2D *aC, unsigned int i, char IDX[][256], char TXT[][256],char VALS[][256],char OPERAR[][256],char OPERREL[][256])
{
    if(CompPalabraReserv((aC->A[i]),i) == 0)
    {
        printf("Token %s en Token[%d] es palabra reservada\n",aC->A[i],i);
    }
    else
    {
        if(CompOperArit((aC->A[i]),i) == 0)
        {
            printf("Token %s en Token[%d] es operador aritmetico\n",aC->A[i],i);
        }
        else
        {
            if(CompOperRel((aC->A[i]),i) == 0)
            {
                printf("Token %s en Token[%d] es operador relacional\n",aC->A[i],i);
            }
            else
            {
                if(CompAsig((aC->A[i]),i) == 0)
                {
                    printf("Token %s en Token[%d] es operador de asignacion\n",aC->A[i],i);
                }
                else
                {
                    if(CompLiteralNum((aC->A[i]),i) == 0)
                    {
                        printf("Token %s en Token[%d] es literal numerica\n",aC->A[i],i);
                    }
                    else
                    {
                        if(CompIdent((aC->A[i]),i) == 0)
                        {
                            printf("Token %s en Token[%d] es identificador\n",aC->A[i],i);
                        }
                        else
                        {
                            printf("No es una token valido\n");
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    arregloChar2D Tokens;
    char IDX[50][256];
    char TXT[50][256];
    char VALS[50][256];
    char OPERAR[50][256];
    char OPERREL[50][256];

    unsigned int r = 50, c = 100;
    initArregloChar2D(&Tokens,r,c);

	if (argc>1)
    {
      if (CargaTokens(argv[1], &Tokens) < 0)
         exit(1);
    }
    else
    {
      fprintf(stderr, "Error: Se tiene que pasar como argumento el archivo que contiene la base de datos\n");
      exit(1);
    }

    imprimeArregloC2D(&Tokens);
    int i=0;
    while(Tokens.A[i])
    {
        ClasificaTokens(&Tokens, i, IDX, TXT, VALS, OPERAR, OPERREL);
        i++;
    }

    liberaArregloChar2D(&Tokens);
    printf("Este es el arreglo despues de liberarlo:\n");
    imprimeArregloC2D(&Tokens);
    return 0;
}

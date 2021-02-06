#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ArregloTokens.h"
int MAXT=0;
int CargaTokens(char *nomArchivo, char Tokens[][256])
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
                        strncpy (Tokens[i], arrayTemp, 255);
                        printf("Esta es la posicion %d: %s\n",i,Tokens[i]);
                        printf("La longitud de la cadena es: %ld\n",strlen(arrayTemp));
                        Tokens[i][strlen(arrayTemp)-1]='\0';
                        i++;
                        s=NULL;
                    }
                    else
                    {
                        strncpy (Tokens[i], s, 255);
                        printf("La longitud de la cadena es: %ld\n",strlen(s));
                        Tokens[i][strlen(s)] = '\0';
                        printf("Esta es la posicion %d: %s\n",i,Tokens[i]);
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
        MAXT=i;
	}
	return 0;
}
int CompPalabraReserv(char Tokens[][256], unsigned int i)
{

    if(strcmp(Tokens[i],"PROGRAMA") == 0)
        return 0;
    if(strcmp(Tokens[i],"SI") == 0)
        return 0;
    if(strcmp(Tokens[i],"ENTONCES") == 0)
        return 0;
    if(strcmp(Tokens[i],"SINO") == 0)
        return 0;
    if(strcmp(Tokens[i],"FINSI") == 0)
        return 0;
    if(strcmp(Tokens[i],"REPITE") == 0)
        return 0;
    if(strcmp(Tokens[i],"VECES") == 0)
        return 0;
    if(strcmp(Tokens[i],"FINREP") == 0)
        return 0;
    if(strcmp(Tokens[i],"IMPRIME") == 0)
        return 0;
    if(strcmp(Tokens[i],"LEE") == 0)
        return 0;
    if(strcmp(Tokens[i],"FINPROG") == 0)
        return 0;

    return -1;
}
int CompOperRel(char Tokens[][256], unsigned int i)
{
    if(strcmp(Tokens[i],">") == 0)
        return 0;
    if(strcmp(Tokens[i],"<") == 0)
        return 0;
    if(strcmp(Tokens[i],"==") == 0)
        return 0;

    return -1;
}
int CompOperArit(char Tokens[][256],unsigned int i)
{
    if(strcmp(Tokens[i],"+") == 0)
        return 0;
    if(strcmp(Tokens[i],"-") == 0)
        return 0;
    if(strcmp(Tokens[i],"*") == 0)
        return 0;
    if(strcmp(Tokens[i],"/") == 0)
        return 0;

    return -1;
}

int CompAsig(char Tokens[][256],unsigned int i)
{
    if(strcmp(Tokens[i],"=") == 0)
        return 0;

    return -1;
}

int CompLiteralNum(char Tokens[][256],unsigned int i)
{
    unsigned int tama = 0;
    unsigned int DigitoInvalido = 0;
    tama = strlen(Tokens[i]);
    for(int j=0; j<tama; j++)
    {
        if (isdigit(Tokens[i][j])==0)
            return -1;
        if(Tokens[i][j] == '8'||Tokens[i][j] == '9')
            DigitoInvalido = 1;
    }
    if(DigitoInvalido == 1)
    {
        printf("Es invalida\n");
        return -1;
    }

    return 0;
}
int CompIdent(char Tokens[][256],unsigned int i)
{
    if(isdigit(Tokens[i][0]) == 0)
        return 0;

    return -1;
}
void ClasificaTokens(char Tokens[][256], unsigned int i, char IDX[][256], char TXT[][256],char VALS[][256],char OPERAR[][256],char OPERREL[][256])
{
    if(CompPalabraReserv((Tokens),i) == 0)
    {
        printf("Token %s en Token[%d] es palabra reservada\n\n",Tokens[i],i);
    }
    else
    {
        if(CompOperArit((Tokens),i) == 0)
        {
            printf("Token %s en Token[%d] es operador aritmetico\n\n",Tokens[i],i);
        }
        else
        {
            if(CompOperRel((Tokens),i) == 0)
            {
                printf("Token %s en Token[%d] es operador relacional\n\n",Tokens[i],i);
            }
            else
            {
                if(CompAsig((Tokens),i) == 0)
                {
                    printf("Token %s en Token[%d] es operador de asignacion\n\n",Tokens[i],i);
                }
                else
                {
                    if(CompLiteralNum((Tokens),i) == 0)
                    {
                        printf("Token %s en Token[%d] es literal numerica\n\n",Tokens[i],i);
                    }
                    else
                    {
                        if(CompIdent((Tokens),i) == 0)
                        {
                            printf("Token %s en Token[%d] es identificador\n\n",Tokens[i],i);
                        }
                        else
                        {
                            printf("No es una token valido\n\n");
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    char Tokens[40][256] = {0};
    char IDX[50][256] = {0};
    char TXT[50][256] = {0};
    char VALS[50][256] = {0};
    char OPERAR[50][256] = {0};
    char OPERREL[50][256] = {0};

	if (argc>1)
    {
      if (CargaTokens(argv[1], Tokens) < 0)
         exit(1);
    }
    else
    {
      fprintf(stderr, "Error: Se tiene que pasar como argumento el archivo que contiene la base de datos\n");
      exit(1);
    }
    int i=0;
    printf("Inicia la comparacion \n\n");

    for(int i = 0; i<MAXT;i++)
    {
        if(Tokens[i][0] == '"')
        {
            if(isspace(Tokens[i][strlen(Tokens[i])]!= 0))
                Tokens[i][strlen(Tokens[i])] = '\0';
        }
        else
            for(int j=0; j < strlen(Tokens[i]);j++)
            {
                if(isspace(Tokens[i][j])!=0)
                    Tokens[i][j] = '\0';
            }
    }

    for (int i=0;i < MAXT;i++)
    {
        printf("El token en Tokens[%d] es %s\n",i,Tokens[i]);
        printf("La longitud de Tokens[%d] es %ld\n\n",i,strlen(Tokens[i]));
    }

     while(i<MAXT)
    {
        ClasificaTokens(Tokens, i, IDX, TXT, VALS, OPERAR, OPERREL);
        i++;
    }
    return 0;
}

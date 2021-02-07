#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ArregloTokens.h"
int MAXT=0;
int CPR = 0;
int COAR = 0;
int COR = 0;
int CASG = 0;
int CLN = 0;
int CIDX = 0;
int CTXT = 0;

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
                        arrayTemp[strlen(arrayTemp)-1]='\0';
                        strncpy (Tokens[i], arrayTemp, 255);

                        printf("Esta es la posicion %d: %s\n",i,Tokens[i]);
                        printf("La longitud de la cadena es: %ld\n",strlen(arrayTemp));
                        Tokens[i][strlen(arrayTemp)]='\0';
                        i++;
                        s=NULL;
                    }
                    else
                    {
                        if(isspace(s[strlen(s)-1])!=0)
                            s[strlen(s)-1] = '\0';

                        strncpy (Tokens[i], s, 255);
                        printf("La longitud de la cadena es: %ld\n",strlen(s));
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
        MAXT = i;
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
    if((isdigit(Tokens[i][0]) == 0)&&(isalpha(Tokens[i][0])!=0))
        return 0;

    return -1;
}
int BuscaIndice(int i, char Tokens[][256], arregloChar2D *IDX)
{
    int k=0;
    while(k<=CIDX)
    {
        if (strncmp(IDX->A[k],IDX->A[i],strlen(IDX->A[i])) == 0)
        {
            return k+1;
        }
        k++;
    }
    return -1;
}
void ClasificaTokens(FILE *ArchivoLex, char Tokens[][256], unsigned int i, arregloChar2D *PR, arregloChar2D *OAR, arregloChar2D *OR,arregloChar2D *ASG, arregloChar2D *LN, arregloChar2D *IDX, arregloChar2D *TXT)
{
    if(CompPalabraReserv((Tokens),i) == 0)
    {
        strncpy(PR->A[CPR], Tokens[i],strlen(Tokens[i]));
        CPR++;
        fprintf(ArchivoLex,"%s\n",Tokens[i]);
    }
    else
    {
        if(CompOperArit((Tokens),i) == 0)
        {
            strncpy(OAR->A[COAR], Tokens[i],strlen(Tokens[i]));
            COAR++;
            fprintf(ArchivoLex,"[op_ar]\n");
        }
        else
        {
            if(CompOperRel((Tokens),i) == 0)
            {
                strncpy(OR->A[COR], Tokens[i],strlen(Tokens[i]));
                COR++;
                fprintf(ArchivoLex,"[op_r]\n");
            }
            else
            {
                if(CompAsig((Tokens),i) == 0)
                {
                    strncpy(ASG->A[CASG], Tokens[i],strlen(Tokens[i]));
                    CASG++;
                    fprintf(ArchivoLex,"=\n");
                }
                else
                {
                    if(CompLiteralNum((Tokens),i) == 0)
                    {
                        strncpy(LN->A[CLN], Tokens[i],strlen(Tokens[i]));
                        CLN++;
                        fprintf(ArchivoLex,"[val]\n");
                    }
                    else
                    {
                        if(CompIdent((Tokens),i) == 0)
                        {
                            const char *ET = "[id]";
                            const char *ID1 = "ID0";
                            const char *ID2 = "ID";
                            strncpy(IDX->A[CIDX],Tokens[i],strlen(Tokens[i]));
                            int Valor = 0;
                            Valor = BuscaIndice(CIDX,Tokens,IDX);

                            if(Valor>0 && Valor<9)
                                fprintf(ArchivoLex,"%s%s%d\n",ET,ID1,Valor);
                            else
                            {
                               if(Valor>9)
                                    fprintf(ArchivoLex,"%s%s%d\n",ET,ID2,Valor);
                            }
                            CIDX++;

                        }
                        else
                        {
                            if(Tokens[i][0]=='"')
                            {
                                const char *ETQ = "[txt]";
                                const char *TX1 = "TX0";
                                const char *TX2 = "TX";
                                strncpy(TXT->A[CTXT], Tokens[i],strlen(Tokens[i]));
                                if(CTXT<9)
                                    fprintf(ArchivoLex,"%s%s%d\n",ETQ,TX1,CTXT+1);
                                else
                                    fprintf(ArchivoLex,"%s%s%d\n",ETQ,TX2,CTXT+1);
                                CTXT++;
                            }
                            else
                            {
                                //Meter a una matriz de errores printf("No es una token valido\n\n");
                            }
                        }
                    }
                }
            }
        }
    }
}
void ImprimeSim(FILE *ArchivoSim,int CIDXNR,arregloChar2D *IDXNR,arregloChar2D *LN, arregloChar2D *TXT)
{
    const char *ID1 = "ID0";
    const char *ID2 = "ID";
    const char *TX1 = "TX0";
    const char *TX2 = "TX";

    fprintf(ArchivoSim,"IDS\n");
    for(int i = 0; i<CIDXNR;i++)
    {
        if(i<9)
            fprintf(ArchivoSim,"%s,%s%d\n",IDXNR->A[i],ID1,i+1);
        else
        {
            if(i>9)
                fprintf(ArchivoSim,"%s,%s%d\n",IDXNR->A[i],ID2,i+1);
        }
    }
    fprintf(ArchivoSim,"\n");

    fprintf(ArchivoSim,"TXT\n");
    for(int i = 0; i<CTXT;i++)
    {
        if(i<9)
            fprintf(ArchivoSim,"%s,%s%d\n",TXT->A[i],TX1,i+1);
        else
            fprintf(ArchivoSim,"%s,%s%d\n",TXT->A[i],TX2,i+1);

    }
    fprintf(ArchivoSim,"\n");

    fprintf(ArchivoSim,"VAL\n");
    for(int i = 0; i<CLN;i++)
    {
        fprintf(ArchivoSim,"%s\n",LN->A[i]);
    }
    fprintf(ArchivoSim,"\n");
}
int main(int argc, char **argv)
{
    FILE *ArchivoLex;
    FILE *ArchivoSim;
    char Tokens[60][256];
    int r = 50, c = 256;
    arregloChar2D PR;
    arregloChar2D OAR;
    arregloChar2D OR;
    arregloChar2D ASG;
    arregloChar2D LN;
    arregloChar2D IDX;
    arregloChar2D TXT;
    arregloChar2D IDXNR;

    initArregloChar2D(&PR,r,c);
    initArregloChar2D(&OAR,r,c);
    initArregloChar2D(&OR,r,c);
    initArregloChar2D(&ASG,r,c);
    initArregloChar2D(&LN,r,c);
    initArregloChar2D(&IDX,r,c);
    initArregloChar2D(&TXT,r,c);
    initArregloChar2D(&IDXNR,r,c);

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

    printf("Inicia la comparacion \n\n");

    for (int i=0;i <MAXT;i++)
    {
        printf("El token en Tokens[%d] es %s\n",i,Tokens[i]);
        printf("La longitud de Tokens[%d] es %ld\n\n",i,strlen(Tokens[i]));
    }

    int i=0;
    ArchivoLex = fopen("Archivo.lex","w");
    while(i<MAXT)
    {
        ClasificaTokens(ArchivoLex,Tokens, i,&PR,&OAR,&OR,&ASG,&LN,&IDX,&TXT);
        i++;
    }
    fclose(ArchivoLex);
    printf("\n\n");
    printf("Arreglo PR\n");
    for (int i; i < CPR;i++)
    {
        printf("En PR[%d] esta: %s\n",i,PR.A[i]);
    }
    printf("\n\n");

    printf("Arreglo OAR\n");
    for (int i; i < COAR;i++)
    {
        printf("En OAR[%d] esta: %s\n",i,OAR.A[i]);
    }
    printf("\n\n");

    printf("Arreglo OR\n");
    for (int i; i < COR;i++)
    {
        printf("En OR[%d] esta: %s\n",i,OR.A[i]);
    }
    printf("\n\n");

    printf("Arreglo ASG\n");
    for (int i; i < CASG;i++)
    {
        printf("En ASG[%d] esta: %s\n",i,ASG.A[i]);
    }
    printf("\n\n");

    printf("Arreglo LN\n");
    for (int i; i < CLN;i++)
    {
        printf("En LN[%d] esta: %s\n",i,LN.A[i]);
    }
    printf("\n\n");

    printf("Arreglo IDX\n");
    for (int i; i < CIDX;i++)
    {
        printf("En IDX[%d] esta: %s\n",i,IDX.A[i]);
    }
    printf("\n\n");

    printf("Arreglo TXT\n");
    for (int i; i < CTXT;i++)
    {
        printf("En TXT[%d] esta: %s\n",i,TXT.A[i]);
    }
    printf("\n\n");
    int TokenRep = 0;
    int CIDXNR=0;

    for (int i = 0; i < CIDX; i++)
    {
        TokenRep = 0;
        for(int j = 0; j<CIDXNR; j++)
            if (strncmp(IDXNR.A[j],IDX.A[i],strlen(IDX.A[i])) == 0)
                TokenRep=1;
        if(TokenRep==0)
        {
            strncpy(IDXNR.A[CIDXNR],IDX.A[i],strlen(IDX.A[i]));
            CIDXNR++;
        }
    }

    printf("Arreglo IDXNR\n");
    for (int i; i < CIDXNR;i++)
    {
        printf("En IDXNR[%d] esta: %s\n",i,IDXNR.A[i]);
    }

    printf("\n\n");
    ArchivoSim = fopen("Archivo.sim","w");
    ImprimeSim(ArchivoSim,CIDXNR,&IDXNR,&LN,&TXT);
    fclose(ArchivoSim);

    liberaArregloChar2D(&PR);
    liberaArregloChar2D(&OAR);
    liberaArregloChar2D(&OR);
    liberaArregloChar2D(&ASG);
    liberaArregloChar2D(&LN);
    liberaArregloChar2D(&IDX);
    liberaArregloChar2D(&TXT);
    liberaArregloChar2D(&IDXNR);
    return 0;
}

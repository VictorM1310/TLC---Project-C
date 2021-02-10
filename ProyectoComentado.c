#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "ArregloTokens.h"

int MAXT=0; //Contador de Tamaño maximo del arreglo estatico de la extraccion de tokens
int MAXTL = 0; //Contador de la cantidad maxima de tokens que hay en el archivo.lex
int CPR = 0; //Contador para las palabras reservadas
int COAR = 0; //Contador para los operadores aritmeticos
int COR = 0; //Contador para los operadores relacionales
int CASG = 0; //Contador de los signos de asignacion '='
int CLN = 0; //Contador de literales numericas
int CIDX = 0; //Contador de los identificadores
int CIDXNR = 0; //Contador de identificadores pero sin repetir
int CTXT = 0; //Contador de textos
int CER = 0; //Contador del arreglo de errores
int Err = 0; //Contador para saber si hay errores o no


//Funcion para tokenizar los lexemas e introducirlos a una matriz
int CargaTokens(char *nomArchivo, char Tokens[][256],arregloInt2D *aI); 

//Funcion para comparar las palabras reservadas
int CompPalabraReserv(char Tokens[][256], unsigned int i);

//Funcion para comparar los operadores relacionales
int CompOperRel(char Tokens[][256], unsigned int i);

//Funcion para comparar los operadores aritmeticos
int CompOperArit(char Tokens[][256],unsigned int i);

//Funcion para comparar las signos de asignacion '='
int CompAsig(char Tokens[][256],unsigned int i);

//Funcion para comparar las literales numericas
int CompLiteralNum(char Tokens[][256],unsigned int i, arregloInt2D *aI);

//Funcion para comparar los identificadores
int CompIdent(char Tokens[][256],unsigned int i, arregloChar2D *aC,arregloInt2D *MTokLin);

//Funcion que nos devuelve el indice de un token de acuerdo a la matriz de identificadores IDXNR, la matriz que contiene
//los identificadores no repetidos
int BuscaIndice(int i, char Tokens[][256], arregloChar2D *IDXNR);

//Funcion para transformar los valores octales a decimales 
int octalTOdecimal(arregloChar2D *LN, unsigned int i);

//Funcion para procesar y clasificar los tokens segun las funciones declaradas anteriormente 
void ClasificaTokens(FILE *ArchivoLex, char Tokens[][256], unsigned int i, arregloChar2D *PR, arregloChar2D *OAR, arregloChar2D *OR,arregloChar2D *ASG, arregloChar2D *LN, arregloChar2D *IDX, arregloChar2D *TXT,arregloChar2D *Errores, arregloInt2D *MTokLin,arregloChar2D *IDXNR);

//Funcion para imprimir el archivo.sim
void ImprimeSim(FILE *ArchivoSim,int CIDXNR,arregloChar2D *IDXNR,arregloChar2D *LN, arregloChar2D *TXT);

//Funcion para buscar el numero de linea, donde se presenta el error
int BuscaErroLinea(int i, arregloInt2D *aI, char Tokens[][256], arregloChar2D *aC);

//Funcion para tokenizar los lexemas del archivo.lex para el analizado sintactico
int CargaTokensLex(char *nomArchivo, arregloChar2D *TokensLex);

//Funcion para comprobar si hay errores con las palabras reservadas PROGRAMA y FINPROGRAMA
void BuscaProgFP(arregloChar2D *TokensLex,arregloInt2D *MTokLin);



int main(int argc, char **argv)
{
    FILE *ArchivoLex; //Variable para el archivo.lex
    FILE *ArchivoSim; //Variable para el archivo.sim
    char Tokens[100][256]; //Arreglo donde se almacenan los tokens 
    int r = 100, c = 256; //Renglones y columnas para las matrices
    int r1 = 100, c1 = 2; //Renglones y columnas para la matriz de MTokLin

    arregloChar2D PR; //Matriz para las palabras reservadas
    arregloChar2D OAR; //Matriz para los operadores aritmeticos
    arregloChar2D OR; //Matriz para las operadores relacionales
    arregloChar2D ASG; //Matriz para las asignacion 
    arregloChar2D LN; //Matriz para las literales numericas
    arregloChar2D IDX; //Matriz para los identificadores
    arregloChar2D TXT; //Matriz para las textos
    arregloChar2D IDXNR; //Matriz para las identificadores, pero sin identificadores repetidos
    arregloChar2D Errores; //Matriz para los errores
    arregloInt2D MTokLin; //Matriz para los indices de el codigo fuente

    //Incializaciones de las matrices declaradas anteriormente
    initArregloChar2D(&PR,r,c); 
    initArregloChar2D(&OAR,r,c);
    initArregloChar2D(&OR,r,c);
    initArregloChar2D(&ASG,r,c);
    initArregloChar2D(&LN,r,c);
    initArregloChar2D(&IDX,r,c);
    initArregloChar2D(&TXT,r,c);
    initArregloChar2D(&IDXNR,r,c);
    initArregloInt2D(&MTokLin,r1,c1);
    initArregloChar2D(&Errores,r,c);

    //Comprobamos que nos introduzcan el codigo fuente con el if
	if (argc>1)
    {
      if (CargaTokens(argv[1], Tokens,&MTokLin) < 0)
         exit(1);
    }
    else //En caso contrario devolvemos error y se sale el progama
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

    //La pasamos una variable tipo FILE para imprimir en un archivo
    ArchivoLex = fopen("Archivo.lex","w");
    //Un while para ir clasificando token por token
    while(i<MAXT)
    {
        ClasificaTokens(ArchivoLex,Tokens, i,&PR,&OAR,&OR,&ASG,&LN,&IDX,&TXT,&Errores,&MTokLin,&IDXNR);
        i++;
    }
    fclose(ArchivoLex);//Cerramos el archivo
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

    printf("Arreglo IDXNR\n");
    for (int i; i < CIDXNR;i++)
    {
        printf("En IDXNR[%d] esta: %s\n",i,IDXNR.A[i]);
    }

    printf("\n\n");
    //Variable FILE para imprimir en un archivo el archivo.sim
    ArchivoSim = fopen("Archivo.sim","w");
    ImprimeSim(ArchivoSim,CIDXNR,&IDXNR,&LN,&TXT);
    //Se cierra el archivo
    fclose(ArchivoSim);

    printf("Matriz de errores con la forma indice/linea\n");
    for (int i; i < MAXT;i++)
    {
        printf("%d %d\n",MTokLin.B[i][0],MTokLin.B[i][1]);
    }

    //Imprimimos los errores alfanumericos
    for (int i; i < CER;i++)
    {
        printf("Error: el token %s no es una variable alfanumerica, en la linea %d\n",Errores.A[i],BuscaErroLinea(i,&MTokLin,Tokens,&Errores));
    }

    //Comprobamos si hay o no errores
    if(Err != 1 && CER != 1)
        printf("El programa concluyo con exito\n");

    arregloChar2D TokensLex; //Variable para la matriz de Tokens para el analizador sintactico
    initArregloChar2D(&TokensLex,r,c); //Inicializacion de la matriz
    CargaTokensLex("Archivo.lex", &TokensLex); //Carga de tokens del archivo lex a la matriz de tokens 

    printf("\n\n");
    for (int i; i < MAXTL; i++)
    {
        printf("En TokensLex[%d] esta: %s\n",i,TokensLex.A[i]);
    }
    printf("\n\n");
    //Comprobacion de los errores para PROGRAMA y FINPROGRAMA
    BuscaProgFP(&TokensLex,&MTokLin);


    //Liberacion de todos los arreglos dinamicos utilizados
    liberaArregloChar2D(&PR);
    liberaArregloChar2D(&OAR);
    liberaArregloChar2D(&OR);
    liberaArregloChar2D(&ASG);
    liberaArregloChar2D(&LN);
    liberaArregloChar2D(&IDX);
    liberaArregloChar2D(&TXT);
    liberaArregloChar2D(&IDXNR);
    liberaArregloInt2D(&MTokLin);
    liberaArregloChar2D(&Errores);
    return 0;
}

//Funcion para cargar los tokens de un archivo a una matriz
int CargaTokens(char *nomArchivo, char Tokens[][256],arregloInt2D *aI)
{
    FILE *arch;
    arch = fopen (nomArchivo, "r"); //Abrimos el archivo
	char linea[256]; //Creamos un arreglo para almacenar las lineas del archivo
    int i=0; 
	if (arch != NULL) //Si el archivo no es vacio
	{
        int NumLinea = 1;
		while(fgets(linea, 255, arch)!=NULL)//Mientras haya algo que leer
        {
            char *s, *ptr;
            s = strtok_r(linea, " \t\n", &ptr); //Leemos la primera palabra de la linea
            if (s[0])//Si no es null
            {
                do
                {
                    if (linea[0] == '#') //Si la linea empieza con almohadilla lo ignoramos porque es un comentario
                    {
                        break;
                    }
                    if(s[0]=='"') //Si empieza con comillas
                    {
                        char arrayTemp[256]; //Creamos un arraytemporal para ir concatenando la palabra completa
                        memset(arrayTemp,0,256); //Limpiamos el array
                        strcat(arrayTemp,s); //Concatenamos la primera comilla y la introducimos al arreglo
                        do
                        {
                            strcat(arrayTemp, " "); //Le concatenamos un espacio
                            s = strtok_r(NULL, " \t\n", &ptr);//Y luego el resto de la palabra
                            if(!s)//Hacemos esto para saber si termina con comillas o no
                            {
                                break;
                            }
                            strcat(arrayTemp,s);//Concatenamos el resto de la palabra
                        }while(*s!='"'); //Mientras que S sea diferente de comillas
                        arrayTemp[strlen(arrayTemp)-1]='\0'; //Le concatenamos el caracter nulo para que no entre a memoria de otros tokens
                        if(isspace(arrayTemp[strlen(arrayTemp)-1])!= 0) //COmprobamos que no tenga un espacio al final para no generar errores de lectura
                            arrayTemp[strlen(arrayTemp)-1]='\0'; //Si tiene un espacio le introduce el caracter nulo
                        strncpy (Tokens[i], arrayTemp, 255); //Copia el token a la matriz de tokens
                        aI->B[i][1] = NumLinea;
                        aI->B[i][0] = i;
                        printf("Esta es la posicion %d: %s\n",i,Tokens[i]);
                        printf("La longitud de la cadena es: %ld\n",strlen(arrayTemp));
                        Tokens[i][strlen(arrayTemp)]='\0';
                        s=NULL;
                    }
                    else
                    {
                        if(isspace(s[strlen(s)-1])!=0) //Hacemos lo mismo de concatenar nulo y luego copiar
                            s[strlen(s)-1] = '\0';
                        strncpy (Tokens[i], s, 255);
                        aI->B[i][1] = NumLinea;
                        aI->B[i][0] = i;
                        printf("La longitud de la cadena es: %ld\n",strlen(s));
                        printf("Esta es la posicion %d: %s\n",i,Tokens[i]);
                        s = strtok_r(NULL, " \t\n", &ptr); //Leemos otra linea
                    }
                    i++;
                } while (s != NULL);
                printf("\n");
            }
            else
                printf("No hay token que leer\n");
            NumLinea++;
        }
        MAXT = i;//Igualamos la cantidad maxima de tokens al contador i
	}
	return 0;
}

//Todas estas funciones trabajan similar, compara y si devuelve 0, la palabra es identica, en caso contrario returna 0
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

int CompLiteralNum(char Tokens[][256],unsigned int i, arregloInt2D *aI)
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
        int Error = 0;
        int Ubi = 0;
        for (int k = 0; k < MAXT; k++)
        {
            if (strncmp(Tokens[i],Tokens[k],strlen(Tokens[i])) == 0)
            {
                Ubi = k;
                break;
            }
        }
        for(int j = 0; j<MAXT; j++)
        {
            if (aI->B[j][0] == Ubi)
            {
                Error = aI->B[j][1];
                break;
            }
        }
        printf("Error: notacion decimal no permitida en token (%s) en la linea %d\n",Tokens[i],Error);
        Err = 1;
        return -1;
    }

    return 0;
}
int CompIdent(char Tokens[][256],unsigned int i, arregloChar2D *aC,arregloInt2D *MTokLin)
{
    if(((Tokens[i][0] != '"') && (Tokens[i][strlen(Tokens[i])-1] == '"'))||((Tokens[i][0] == '"') && (Tokens[i][strlen(Tokens[i])-1] != '"')))
    {
        int Error = 0;
        int Ubi = 0;
        for (int k = 0; k < MAXT; k++)
        {
            if (strncmp(Tokens[i],Tokens[k],strlen(Tokens[k])) == 0)
            {
                Ubi = k;
                break;
            }
        }
        for(int j = 0; j<MAXT; j++)
        {
            if (MTokLin->B[j][0] == Ubi)
            {
                Error = MTokLin->B[j][1];
                break;
            }
        }
        printf("Error: faltan comillas de terminacion en el token (%s) ubicado en la linea %d\n",Tokens[i],Error);
        Err = 1;
    }

    if((isdigit(Tokens[i][0]) == 0)&&(isalpha(Tokens[i][0])!=0))
        return 0;
    return -1;
}

//Funcion para encontrar eliminar tokens repetidos 
int BuscaIndice(int i, char Tokens[][256], arregloChar2D *IDXNR)
{
    int TokenRep = 0;
    int IndiceNR = 0;
    if(IDXNR) //Si la matriz de identificadores no repetidos es difente de null
    {
        TokenRep = 0;
        for(int j = 0; j<CIDXNR; j++)
        {
            if (strncmp(IDXNR->A[j],Tokens[i],strlen(IDXNR->A[j])) == 0)//Si el token de IDXNR, se encuentra en Tokens
            {
                TokenRep=1; //Quiere decir que si esta repetido el token
                IndiceNR = j+1; //Indice de la matriz IDXNR
            }
        }
        if(TokenRep==0) //Si no se repite el token
        {
            strncpy(IDXNR->A[CIDXNR],Tokens[i],16); //Lo copiamos a la matriz de IDXNR
            IndiceNR = CIDXNR+1;
            CIDXNR++;
        }
    }
    else
    {
        strncpy(IDXNR->A[CIDXNR],Tokens[i],16);//Si la matriz IDXNR esta vacia, copiamos inmediatamente el token 
        CIDXNR++;
        return 1;
    }
    return IndiceNR;
}

//Convertimos el valor octal a decimal
int octalTOdecimal(arregloChar2D *LN, unsigned int i)
{
    int decimal = 0;
    int num = 0;
    int k = strlen(LN->A[i]); //k es igual a la longitud del valor a cambiar
    for(int j = 0; j < strlen(LN->A[i]); j++)
    {
        num = LN->A[i][j] - '0'; //Hacemos esto para convertir los char a enteros
        decimal = decimal + (num * pow(8,k-1)); 
        k--;
    }
    return decimal;
}


//Aquí se procesan y comparan todos los tokens utilizando las funciones ateriores
void ClasificaTokens(FILE *ArchivoLex, char Tokens[][256], unsigned int i, arregloChar2D *PR, arregloChar2D *OAR, arregloChar2D *OR,arregloChar2D *ASG, arregloChar2D *LN, arregloChar2D *IDX, arregloChar2D *TXT,arregloChar2D *Errores, arregloInt2D *MTokLin,arregloChar2D *IDXNR)
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
                    if(CompLiteralNum((Tokens),i,MTokLin) == 0)
                    {
                        strncpy(LN->A[CLN], Tokens[i],strlen(Tokens[i]));
                        CLN++;
                        fprintf(ArchivoLex,"[val]\n");
                    }
                    else
                    {
                        if(CompIdent((Tokens),i,Errores,MTokLin) == 0)
                        {
                            const char *ET = "[id]";
                            const char *ID1 = "ID0";
                            const char *ID2 = "ID";
                            if(Tokens[i][strlen(Tokens[i])-1]!='"')
                            {
                                if(strlen(Tokens[i])>16)
                                {

                                    printf("Advertencia: su identificador %s es mayor a 16 caracteres, solo se tomaran en cuenta los primeros 16\n",Tokens[i]);
                                    strncpy(IDX->A[CIDX],Tokens[i],16);

                                }
                                else
                                {
                                    strncpy(IDX->A[CIDX],Tokens[i],strlen(Tokens[i]));
                                }
                                int Valor = 0;
                                Valor = BuscaIndice(i,Tokens,IDXNR);

                                if(Valor>0 && Valor<=9)
                                    fprintf(ArchivoLex,"%s%s%d\n",ET,ID1,Valor);
                                else
                                {
                                    if(Valor>9)
                                        fprintf(ArchivoLex,"%s%s%d\n",ET,ID2,Valor);
                                }
                                CIDX++;
                            }
                        }
                        else
                        {
                            if((Tokens[i][0]=='"') && (Tokens[i][strlen(Tokens[i])-1]=='"'))
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
                                if(Tokens[i][0]!='"')
                                {
                                    int NoImp=0;
                                    for(int x=0; x<strlen(Tokens[i]);x++)
                                        if(Tokens[i][x]=='8'||Tokens[i][x]=='9')
                                        {
                                            NoImp=-1;
                                        }
                                    if(NoImp==0)
                                    {
                                        strncpy(Errores->A[CER],Tokens[i],strlen(Tokens[i]));
                                        CER++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//Funcion para imprimir el archivo.lex
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
            if(i>=9)
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
        fprintf(ArchivoSim,"%s,%d\n",LN->A[i],octalTOdecimal(LN,i));
    }
    fprintf(ArchivoSim,"\n");
}

//Funcion para buscar que linea tiene el error
int BuscaErroLinea(int i, arregloInt2D *aI, char Tokens[][256], arregloChar2D *aC)
{
    int ErrorLinea = 0;
    int Ubicacion = 0;
    for (int k = 0; k < MAXT; k++)
    {
        if (strncmp(aC->A[i],Tokens[k],strlen(aC->A[i])) == 0)
        {
            Ubicacion = k;
            break;
        }
    }
    for(int j = 0; j<MAXT; j++)
    {
        if (aI->B[j][0] == Ubicacion)
        {
            ErrorLinea = aI->B[j][1];
            break;
        }
    }
    return ErrorLinea;
}

//Esta funcion trabaja igual a la declarada al inicio
int CargaTokensLex(char *nomArchivo, arregloChar2D *TokensLex)
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
                {
                    if(isspace(s[strlen(s)-1])!=0)
                        s[strlen(s)-1] = '\0';
                    strncpy (TokensLex->A[i], s, 255);
                    printf("La longitud de la cadena es: %ld\n",strlen(s));
                    printf("Esta es la posicion %d: %s\n",i,TokensLex->A[i]);
                    s = strtok_r(NULL, " \t\n", &ptr);
                    i++;
                } while (s != NULL);
                printf("\n");
            }
            else
                printf("No hay token que leer\n");

        }
	}
	MAXTL = i;
	return 0;
}

//Funcion para comprobar si hay errores con las palabras reservadas PROGRAMA y FINPROGRAMA
void BuscaProgFP(arregloChar2D *TokensLex,arregloInt2D *MTokLin)
{
    int ErrorP = 0;
    int NProg = 0;
    for(int i=0;i<MAXTL;i++)
    {
        if(strcmp(TokensLex->A[i],"PROGRAMA")==0)
        {
            NProg++;
            if(i !=0)
            {
                int ErrorLinea = 0;
                int Ubicacion = i;
                for(int j = 0; j<MAXT; j++)
                {
                    if (MTokLin->B[j][0] == Ubicacion)
                    {
                        ErrorLinea = MTokLin->B[j][1];
                    }
                }
                printf("Error: Ubicacion de la palabra reservada (PROGRAMA) incorrecta en la linea %d\n",ErrorLinea);

                if(NProg>1)
                    printf("Error: Multiples definiciones de la palabra reservada (PROGRAMA) en la linea %d\n",ErrorLinea);
            }
            else
                ErrorP = 1;
        }
    }
    if (ErrorP == 0)
        printf("Error: No se encontro la palabra reservada (PROGRAMA) en la linea 1\n");

    ErrorP = 0;
    int NFProg = 0;
    for(int i=0;i<MAXTL;i++)
    {
        if(strcmp(TokensLex->A[i],"FINPROG")==0)
        {
            NFProg++;
            if(i != (MAXTL-1))
            {
                int ErrorLinea = 0;
                int Ubicacion = i;
                for(int j = 0; j<MAXT; j++)
                {
                    if (MTokLin->B[j][0] == Ubicacion)
                    {
                        ErrorLinea = MTokLin->B[j][1];
                    }
                }
                printf("Error: Ubicacion de la palabra reservada (FINPROG) incorrecta en la linea %d\n",ErrorLinea);
                if(NFProg>1)
                    printf("Error: Multiples definiciones de la palabra reservada (FINPROG) en la linea %d\n",ErrorLinea);
            }
            else
                ErrorP = 1;
        }
    }
    if (ErrorP == 0)
        printf("Error: No se encontro la palabra reservada (FINPROG) en la linea %d\n",MTokLin->B[MAXTL-1][1]);

}

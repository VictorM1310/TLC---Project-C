int CargaTokens(char *nomArchivo, char Tokens[][256],arregloInt2D *aI);

int CompPalabraReserv(char Tokens[][256], unsigned int i);

int CompOperRel(char Tokens[][256], unsigned int i);

int CompOperArit(char Tokens[][256],unsigned int i);

int CompAsig(char Tokens[][256],unsigned int i);

int CompLiteralNum(char Tokens[][256],unsigned int i, arregloInt2D *aI);

int CompIdent(char Tokens[][256],unsigned int i, arregloChar2D *aC,arregloInt2D *MTokLin);

int BuscaIndice(int i, char Tokens[][256], arregloChar2D *IDXNR);

int octalTOdecimal(arregloChar2D *LN, unsigned int i);

void ClasificaTokens(FILE *ArchivoLex, char Tokens[][256], unsigned int i, arregloChar2D *PR, arregloChar2D *OAR, arregloChar2D *OR,arregloChar2D *ASG, arregloChar2D *LN, arregloChar2D *IDX, arregloChar2D *TXT,arregloChar2D *Errores, arregloInt2D *MTokLin,arregloChar2D *IDXNR);

void ImprimeSim(FILE *ArchivoSim,int CIDXNR,arregloChar2D *IDXNR,arregloChar2D *LN, arregloChar2D *TXT);

int BuscaErroLinea(int i, arregloInt2D *aI, char Tokens[][256], arregloChar2D *aC);

int CargaTokensLex(char *nomArchivo, arregloChar2D *TokensLex);

void BuscaProgFP(arregloChar2D *TokensLex,arregloInt2D *MTokLin);

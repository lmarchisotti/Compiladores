#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <stdbool.h>
 
#ifndef LEX
#define LEX

#define TAM_BUFFER 1024

 // ------------------------------- Estruturas para armazenamento de Tokens -------------------------------

    struct Estrutura_TOKEN{
        char token[25];
        int Type, LineNumber, PosInLine;
        bool error;
    }Arraytokens[TAM_BUFFER];

    struct Conj_Reservadas{
        char token[25];
    }ArrayReservadas[100];

 // ------------------------------------------ Variáveis Globais ------------------------------------------

    char buffer[TAM_BUFFER];
    int buffersize, Qreserved;
    int TKlen, TKcount;
    int PosInLine, LCount;
    int lineSize, LinePos;
    char atual, sentinelA, sentinelB;
    bool blockcomment;

 // ---------------------------------------- Cabeçalho das Funções ----------------------------------------

    int setype(char atual, int pos);
    void newToken(FILE *read, int type, int FTKcount, int LineCount ,int LinePos);

#endif

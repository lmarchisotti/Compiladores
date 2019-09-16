#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <stdbool.h>
 
#define TAM_BUFFER 1024

struct Estrutura_TOKEN{
    char token[25];
    int Type, LineNumber, PosInLine;
    bool error;
}Arraytokens[100] = {0};

char buffer[TAM_BUFFER];
int buffersize=0;
int TOKlen=0, TOKcount=0;
int PosInLine=0, LCount=1;
int tamFILE=0, sentinel=0;
char atual;

int setype(char atual);
char newToken(FILE *read, int type, int TOKcount, int LCount ,int PosInLine);
 
int main(int argc, char **argv){                                // Main - Somente um switch para as modularizacoes

FILE *read;                                         // Ponteiro que irá ler o arquivo.
    read = fopen ("test.c","r");                                // Ponteiro "read" abre o arquivo de entrada e fará a leitura dos caracteres do arquivo
    if (!read){                                                 // Caso o ponteiro "read" não ler nada, aparecerá a mensagem de erro.
        printf (" Não é possível abrir o arquivo! \n");
        exit (1);
    }
         
    while(!feof(read)){
        setbuf(stdin,NULL);
        fgets(buffer, TAM_BUFFER, read);
        buffersize = strlen(buffer);
        PosInLine=0;
        atual = buffer[PosInLine];

        for( PosInLine = 0; PosInLine<=buffersize ; PosInLine++){
            atual = buffer[PosInLine];
            while(atual == ' ' || atual == '\t' || atual == '\n' ) {
                if( atual == '\n' ){            
                    setbuf(stdin,NULL);
                    fgets(buffer, TAM_BUFFER, read);
                    buffersize = strlen(buffer);
                    PosInLine = 0;
                    LCount++;
                }else if( atual == ' ' || atual == '\t' ){
                    PosInLine++;
                }
                atual = buffer[PosInLine];
            }

            Arraytokens[TOKcount].Type = setype(atual);
            Arraytokens[TOKcount].LineNumber = LCount;
            Arraytokens[TOKcount].PosInLine = PosInLine;

            newToken(read, Arraytokens[TOKcount].Type, TOKcount, LCount, PosInLine);
            //printf("%c %d:%d\n", atual, LCount, PosInLine);
            // TOKcount++;
            //printf("Token [%d] | %s ---> Type [%d] - Linha [%d na pos %d]\n",TOKcount , Arraytokens[TOKcount].token, Arraytokens[TOKcount].Type,Arraytokens[TOKcount].LineNumber,Arraytokens[TOKcount].PosInLine);
            for ( int i=0 ; i<=TOKcount ; i++ ){
                printf("Token [%d] | %s ---> Type [%d] - Pos [%d:%d]\n",TOKcount , Arraytokens[TOKcount].token, Arraytokens[TOKcount].Type,Arraytokens[TOKcount].LineNumber,Arraytokens[TOKcount].PosInLine);
            }
        
        }
    }
}
 
int setype(char c){         // Identifica o Type de caracter lido
    
    printf("%c %d:%d\n", atual, LCount, PosInLine);
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$' ){   // Identificador
        return 1;
    } else if ( c >= '0' && c <= '9'){      // Numeral
        return 2;
    } else if ( c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '=' || c == ';' || c == ','){        // Separador
        return 3;
    } else if ( c == '+' || c == '-' || c == '*' || c == '/'){      // Operador
        return 4;
    } else if ( c == '#' ){     // Especial
        return 5;
    }else if (c == '"'){    // Literal
        return 6;
    }else if ( c == '#' ){  // Diretiva
        return 7;
    }else if ( c == '@' || c == '~' || c == '^' ){  // Erro
        return 8;
    }else{
        return 0;
    }
}
 
char newToken(FILE *read, int type, int TOKcount, int LCount ,int toklen){      // Função para coletar palavras ou tokens
    
    switch (Arraytokens[TOKcount].Type){
        case 0:             // Erro
            printf("ERRO ---> Case 0\n");
            break;
        case 1:             // Identificador
            printf("IN [1]\n");
            TOKcount++;
            TOKlen=0;
            Arraytokens[TOKcount].LineNumber=LCount;
            Arraytokens[TOKcount].PosInLine=PosInLine;
            Arraytokens[TOKcount].error=0;
            do{
                Arraytokens[TOKcount].token[TOKlen] = atual;
                PosInLine++;
                TOKlen++;
                atual = buffer[PosInLine];
            }while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$');
            printf("Token [%d] | %s ---> Type %d --- [LCount %d na pos %d]\n", TOKcount, Arraytokens[TOKcount].token, Arraytokens[TOKcount].Type, Arraytokens[TOKcount].LineNumber, Arraytokens[TOKcount].PosInLine);
            break;
        case 2:             // Numeral
            printf("IN [2]\n");
            Arraytokens[TOKcount].LineNumber=LCount;
            Arraytokens[TOKcount].PosInLine=PosInLine;
            Arraytokens[TOKcount].error=0;
            do {
                Arraytokens[TOKcount].token[TOKlen] = atual;
                PosInLine++;
                TOKlen++;
                atual = buffer[PosInLine];
            } while( atual >= '0' && atual <= '9');
            TOKcount++;
            break;
        case 3:             // Separadores
            do {
                printf("IN [3]\n");
                printf("Atual --> [%c]\n",atual);
                TOKlen=0;
                atual = buffer[PosInLine];
                Arraytokens[TOKcount].token[TOKlen] = atual;
                Arraytokens[TOKcount].LineNumber = LCount;
                Arraytokens[TOKcount].PosInLine = PosInLine;
                Arraytokens[TOKcount].error=0;
                PosInLine++;
                TOKcount++;
                printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", TOKcount, Arraytokens[TOKcount].token, Arraytokens[TOKcount].Type, Arraytokens[TOKcount].LineNumber, Arraytokens[TOKcount].PosInLine);
            } while( atual == '(' || atual == ')' || atual == '[' || atual == ']' || atual == '{' || atual == '}' || atual == '=' || atual == ';' || atual == ',' );
            break;
        case 4:             // Operadores
            printf("IN [4]\n");
            do {
                Arraytokens[TOKcount].token[toklen] = atual;
                toklen++;
                PosInLine++;
                TOKcount++;
                atual = buffer[PosInLine];
            } while( atual == '+' || atual == '-' || atual == '*' || atual == '/' );
            TOKcount++;
            break;
        case 5:             // Especial
            printf("IN [5]\n");
            TOKlen=0;
            if( atual == '#' ){
                do{
                Arraytokens[TOKcount].token[toklen] = atual;
                toklen++;
                PosInLine++;        
                atual = buffer[PosInLine];
                }while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$' );
                TOKcount++; 
            }
            break;
        case 6:             // Literal
            printf("IN - Case [6]\n");
            do {
                Arraytokens[TOKcount].token[toklen] = atual;
                toklen++;

                if( atual == '\n' ){
                    setbuf(stdin,NULL);
                    fgets(buffer, TAM_BUFFER, read);
                    buffersize = strlen(buffer);
                    PosInLine = 0;
                    LCount++;
                }else if(PosInLine < buffersize){
                    PosInLine++;
                }
                atual = buffer[PosInLine];

            } while( atual == '"' );
            break;
        case 7:             // Diretiva
            printf("IN - Case [7]\n");
            do {
                Arraytokens[TOKcount].token[toklen] = atual;
                toklen++;

                if( atual == '\n' ){
                    setbuf(stdin,NULL);
                    fgets(buffer, TAM_BUFFER, read);
                    buffersize = strlen(buffer);
                    PosInLine = 0;
                    LCount++;
                }else if(PosInLine < buffersize){
                    PosInLine++;
                }
                atual = buffer[PosInLine];

            } while( atual == '#' );
            break;
        case 8:             // Erro
            printf("IN - Case [8]\n");
            do {
                Arraytokens[TOKcount].token[toklen] = atual;
                toklen++;

                if( atual == '\n' ){
                    setbuf(stdin,NULL);
                    fgets(buffer, TAM_BUFFER, read);
                    buffersize = strlen(buffer);
                    PosInLine = 0;
                    LCount++;
                }else if(PosInLine < buffersize){
                    PosInLine++;
                }
                atual = buffer[PosInLine];

            } while( atual == '@' || atual == '~' || atual == '^' );
            TOKcount++;
            break;  
    
    }
    return atual;
}
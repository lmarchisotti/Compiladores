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

struct Conj_Reservadas{
    char token[25];
}ArrayReservadas[100];


char buffer[TAM_BUFFER];
int buffersize=0;
int TKlen=0, TKcount=0;
int PosInLine=0, LCount=0;
int tamFILE=0, sentinel=0;
char atual;

int setype(char atual);
char newToken(FILE *read, int type, int FTKcount, int LineCount ,int LinePos);
 
int main(int argc, char **argv){                                // Main - Somente um switch para as modularizacoes

    FILE *read;                                                 // Ponteiro que irá ler o arquivo.
    read = fopen ("test.c","r");                                // Ponteiro "read" abre o arquivo de entrada e fará a leitura dos caracteres do arquivo
    if (!read){                                                 // Caso o ponteiro "read" não ler nada, aparecerá a mensagem de erro.
        printf (" Não é possível abrir o arquivo! \n");
        exit (1);
    }
         
    while(!feof(read)){
        setbuf(stdin,NULL);
        fgets(buffer, TAM_BUFFER, read);
        buffer[strlen(buffer)-1] = '\0';
        buffersize = strlen(buffer);
        LCount++;
        PosInLine=0;
        atual = buffer[PosInLine];
        // printf("Tam linha [%d] ---> %s\n",buffersize,buffer);
        // printf("Ant Pen %c --- Pen %c --- Ult %c \n",buffer[buffersize-2],buffer[buffersize-1],buffer[buffersize]);

        for( PosInLine = 0; PosInLine<=buffersize ; PosInLine++){
            atual = buffer[PosInLine];
            while(atual == ' ' || atual == '\t' || atual == '\n' || atual == '\0' ) {
                if( atual == '\n' || atual == '\0' ){            
                    setbuf(stdin,NULL);
                    fgets(buffer, TAM_BUFFER, read);
                    buffer[strlen(buffer)-1] = '\0';
                    buffersize = strlen(buffer);
                    LCount++;
                    PosInLine = 0;
                }else if( atual == ' ' || atual == '\t' ){
                    PosInLine++;
                }
                atual = buffer[PosInLine];
            }
            // printf("Atual %c---%d,%d\n",atual, LCount, PosInLine);
            Arraytokens[TKcount].Type = setype(atual);
            Arraytokens[TKcount].LineNumber = LCount;
            Arraytokens[TKcount].PosInLine = PosInLine;

            newToken(read, Arraytokens[TKcount].Type, TKcount, LCount, PosInLine);

        }
    }
}
 
int setype(char c){         // Identifica o Type de caracter lido
    int s=0;
    s = buffer[PosInLine+1];
    if ( (c == '/' && s == '/') || (c == '/' && s == '*')){          // Comentario
        return 0;
    } else if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$' ){   // Identificador
        return 1;
    } else if ( c >= '0' && c <= '9'){      // Numeral
        return 2;
    } else if ( c == ' ' || c == '\t' || c == '\n' || c == '\0' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '=' || c == ';' || c == ','){        // Separador
        return 3;
    } else if ( c == '+' || c == '-' || c == '*' || c == '/'){      // Operador
        return 4;
    } else if ( c == '#' ){     // Especial
        return 5;
    } else if (c == '"'){    // Literal
        return 6;
    } else if ( c == '@' || c == '~' || c == '^' ){  // Erro
        return 7;
    } else 
        return 8;
}
 
char newToken(FILE *read, int type, int FTKcount, int LineCount ,int LinePos){      // Função para coletar palavras ou tokens
    int FTKlen=0;
    int sentinel=0;
    

    switch (type){
        case 0:             // Comentarios
            FTKlen=0;
            sentinel = buffer[LinePos+1];
            Arraytokens[FTKcount].Type = type;
            if( atual == '/' && sentinel == '/' ){
                do{
                LinePos++;
                PosInLine = LinePos - 1;
                atual = buffer[LinePos];
                sentinel = buffer[LinePos+1];
                }while( atual == '\0' || sentinel == '\n' );
            }
            if( atual == '/' && sentinel == '*' ){
                do{
                    if( atual == '\n' || atual == '\0' ){            
                        setbuf(stdin,NULL);
                        fgets(buffer, TAM_BUFFER, read);
                        buffer[strlen(buffer)-1] = '\0';
                        buffersize = strlen(buffer);
                        LineCount++;
                        LinePos = 0;
                    }
                    atual = buffer[LinePos];
                    LinePos++;
                    PosInLine = LinePos - 1;
                    sentinel = buffer[LinePos+1];
                }while( atual == '*' && sentinel == '/');
            }
            break;
        case 1:             // Identificador
            FTKlen=0;
            FTKcount++;
            TKcount = FTKcount;
            Arraytokens[FTKcount].Type = type;
            Arraytokens[FTKcount].LineNumber = LineCount;
            Arraytokens[FTKcount].PosInLine = LinePos;
            Arraytokens[FTKcount].error = 0;
            do{
                Arraytokens[FTKcount].token[FTKlen] = atual;
                LinePos++;
                PosInLine = LinePos-1;
                FTKlen++;
                TKlen = FTKlen;
                atual = buffer[LinePos];
            }while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$');
            printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            break;
        case 2:             // Numeral
            FTKlen=0;
            FTKcount++;
            TKcount = FTKcount;
            Arraytokens[FTKcount].Type = type;
            Arraytokens[FTKcount].LineNumber=LineCount;
            Arraytokens[FTKcount].PosInLine=LinePos;
            Arraytokens[FTKcount].error=0;
            do {
                Arraytokens[FTKcount].token[FTKlen] = atual;
                LinePos++;
                PosInLine = LinePos-1;
                FTKlen++;
                TKlen = FTKlen;
                atual = buffer[LinePos];
            } while( atual >= '0' && atual <= '9');
            printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            break;
        case 3:             // Separadores
            do {
                FTKlen=0;
                FTKcount++;
                TKcount = FTKcount;
                Arraytokens[FTKcount].token[FTKlen] = atual;
                Arraytokens[FTKcount].Type = type;
                Arraytokens[FTKcount].LineNumber = LineCount;
                Arraytokens[FTKcount].PosInLine = LinePos;
                Arraytokens[FTKcount].error=0;
                FTKlen++;
                TKlen = FTKlen;
                LinePos++;
                PosInLine = LinePos-1;
                atual = buffer[LinePos];
                printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            } while( atual == '(' || atual == ')' || atual == '[' || atual == ']' || atual == '{' || atual == '}' || atual == '=' || atual == ';' || atual == ',' );
            break;
        case 4:             // Operadores
            do {
                FTKlen=0;
                FTKcount++;
                TKcount = FTKcount;
                Arraytokens[FTKcount].token[FTKlen] = atual;
                Arraytokens[FTKcount].Type = type;
                Arraytokens[FTKcount].LineNumber = LineCount;
                Arraytokens[FTKcount].PosInLine = LinePos;
                Arraytokens[FTKcount].error=0;
                FTKlen++;
                TKlen = FTKlen;
                LinePos++;
                PosInLine = LinePos - 1;
                atual = buffer[LinePos];
                printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            } while( atual == '+' || atual == '-' || atual == '*' || atual == '/' );
            break;
        case 5:             // Diretiva
            FTKlen=0;
            FTKcount++; 
            TKcount = FTKcount;
            Arraytokens[FTKcount].Type = type;
            sentinel = buffer[LinePos+1];
            if ( atual == '#' ){
                if ( sentinel == '<' ){
                    // do{
                    Arraytokens[FTKcount].token[FTKlen] = atual;
                    Arraytokens[FTKcount].LineNumber = LineCount;
                    Arraytokens[FTKcount].PosInLine = LinePos;
                    FTKlen++;
                    TKlen = FTKlen;
                    LinePos++;
                    PosInLine = LinePos - 1;
                    atual = buffer[LinePos];
                    }while(atual == '#' );
                    // }while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$' || atual == '<' || atual =='>' );
                // }
            }
            printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            break;
        case 6:             // Literal
            printf("Atual --- %c\n",atual);
            do {
                LinePos++;
                PosInLine = LinePos -1;
            } while( atual  == '"');
            printf("Token [%d] | %s ---> Type %d --- [Linha %d na pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
            break;
        case 7:             // Erro
            do {
                printf("Token [%c] nao permitido\n",atual);
                Arraytokens[FTKcount].token[FTKlen] = atual;
                Arraytokens[FTKcount].Type = type;
                Arraytokens[FTKcount].LineNumber = LineCount;
                Arraytokens[FTKcount].PosInLine = LinePos;
                Arraytokens[FTKcount].error=1;                
                LinePos++;
                PosInLine = LinePos -1;
                atual = buffer[LinePos];
            } while( atual == '@' || atual == '~' || atual == '^' || atual == 128 || atual == 135 );
            break; 
        case 8:             // Erro
            // printf("Caracter desconhecido --- ERRO\n");
            break; 
    }
}
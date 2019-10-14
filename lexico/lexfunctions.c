#include "lexico.h"

// --------------------------------------- Classificação do tipo de tokens ---------------------------------------

    int setype(char c, int pos){         // Identifica o Type de caracter lido
        char s = buffer[pos+1];
        // printf("Atual %c --- Seguinte %c\n",c,s);
        if ( (c == '/' && s == '/') || (c == '/' && s == '*')){          // Comentario
            return 0;
        } else if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$' ){   // Identificador
            return 1;
        } else if ( c >= '0' && c <= '9'){      // Numeral
            return 2;
        } else if ( c == ' ' || c == '\t' || c == '\n' || c == '\0' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '=' || c == ';' || c == ','|| c == '.'){        // Separador
            return 3;
        } else if ( c == '+' || c == '-' || c == '*' || (c == '/' && ( s != '/' || s != '*' ))){      // Operador
            return 4;
        } else if ( c == '#' && s == 'i'){     // Diretiva
            return 5;
        } else if (c == '"'){    // Literal
            return 6;
        } else if ( c == '@' || c == '~' || c == '^' || c == -89 || c == -121 ){  // Erro
            return 7;
        } else 
            return 8;
    }


// ---------------------------------------- Função de separação de tokens ----------------------------------------

    void newToken(FILE *read, int type, int FTKcount, int LineCount ,int LinePos){      // Função para coletar palavras ou tokens
        int FTKlen = 0;
        switch (type){
            case 0:             // Empty
                
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
                }while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$' || atual == '.' );
                printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
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
                printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
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
                    printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
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
                    printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
                } while( atual == '+' || atual == '-' || atual == '*' || atual == '/' );
                break;
            case 5:             // Diretiva
                FTKlen=0;
                FTKcount++; 
                TKcount = FTKcount;
                Arraytokens[FTKcount].Type = type;
                Arraytokens[FTKcount].LineNumber = LineCount;
                Arraytokens[FTKcount].PosInLine = LinePos;
                if ( atual == '#' && sentinelB == 'i' ){
                    do{
                        Arraytokens[FTKcount].token[FTKlen] = atual;
                        FTKlen++;
                        TKlen = FTKlen;
                        PosInLine = LinePos;
                        LinePos++;
                        atual = buffer[LinePos];
                        sentinelA = buffer[LinePos];
                        sentinelB = buffer[LinePos + 1];
                    }while( atual != ' ');
                }
                printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
                FTKlen=0;
                FTKcount++; 
                TKcount = FTKcount;
                PosInLine = LinePos;
                LinePos++;
                Arraytokens[FTKcount].Type = type;
                Arraytokens[FTKcount].LineNumber = LineCount;
                Arraytokens[FTKcount].PosInLine = LinePos;
                if ( atual == '<' ){
                    do{
                        Arraytokens[FTKcount].token[FTKlen] = atual;
                        FTKlen++;
                        TKlen = FTKlen;
                        PosInLine = LinePos;
                        LinePos++;
                        atual = buffer[LinePos];
                        sentinelA = buffer[LinePos];
                        sentinelB = buffer[LinePos + 1];
                    }while( atual != '>' );
                }
                printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
                break;
            case 6:             // Literal
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
                    printf("Token [%d] | %s ---> Type %d --- [Line %d in pos %d]\n", FTKcount, Arraytokens[FTKcount].token, Arraytokens[FTKcount].Type, Arraytokens[FTKcount].LineNumber, Arraytokens[FTKcount].PosInLine);
                } while( atual == '"' );
                break;
            case 7:             // Erro
                do {
                    printf("ERRO ---> Token [%c] nao permitido\n",atual);
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
            case 8:             // Empty
                // printf("Caracter desconhecido --- ERRO\n");
                break; 
        }
    }
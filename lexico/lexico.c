#include "lexico.h"
 
int main(int argc, char **argv){    // Main - Leitura de arquivos, ignora comentarios e chama a coleta de tokens

 // ---------------------------------- Arquivo de palavras reservadas --------------------------------

    FILE *reserved;                                             // Criação do ponteiro para leitura.
    // reserved = fopen (argv[2],"r");                          // Atribuição do ponteiro leitura para o arquivo de palavras reservadas.
    reserved = fopen ("reservadas.txt","r");                    // Atribuição do ponteiro leitura para o arquivo de palavras reservadas.
    if (!reserved){                                             // Verificação da existencia do arquivo.
        printf (" ---> ARQUIVO NAO ENCONTRADO <--- \n");
        exit (1);                                               // Se nao encontra o arquivo, fecha do programa.
    }

    Qreserved=0;                                                // Contador de palavras reservadas
    while(!feof(reserved)){                                     // Percorre o arquivo coletando e contando as palavras reservadas.
        fgets( ArrayReservadas[Qreserved].token, TAM_BUFFER, reserved );
        ArrayReservadas[Qreserved].token[strlen(ArrayReservadas[Qreserved].token)-1] = '\0';
        Qreserved++;
    }
    
 // --------------------------------------- Leitura de Arquivo ---------------------------------------

    FILE *read;                                                 // Criação do ponteiro para leitura.
    read = fopen (argv[1],"r");                                 // Atribuição do ponteiro leitura para o arquivo que será analisado.
    if (!read){                                                 // Verificação da existencia do arquivo.
        printf (" ---> ARQUIVO NAO ENCONTRADO <--- \n");
        exit (1);                                               // Se nao encontra o arquivo, fecha do programa.
    }

 // -------------------------------------- Varredura do Arquivo --------------------------------------

    blockcomment = 0;                       // Inicializa a flag comentario de bloco com falso
    while(!feof(read)){                     // Enquanto nao encontrar o fim do arquivo... faça
        fgets(buffer, TAM_BUFFER, read);    // Capta a proxima linha do arquivo e coloca em uma big string
        buffersize = strlen(buffer);        // Mensura o tamanho da string captada

        for( PosInLine = 0; PosInLine <= buffersize  ; PosInLine++ ){   // Percorre a linha coletada do arquivo
            
            atual = buffer[PosInLine];                          // 
            sentinelA = buffer[PosInLine];
            sentinelB = buffer[PosInLine + 1];
            
            if( sentinelB == '\n' || sentinelB == '\0' || (sentinelA == '/' && sentinelB == '/')) {            
                LCount++;
                break;
            }else if( sentinelA == '/' && sentinelB == '*' ){
                blockcomment = 1;
            }else if ( sentinelA == '*' && sentinelB == '/' ){
                blockcomment = 0;
                PosInLine = PosInLine + 1;
            }else if( atual == ' ' || atual == '\t' ){
                continue;
            }
           
 // ---------------------------------------- Coleta de Tokens ----------------------------------------
            if (blockcomment != 1){
                Arraytokens[TKcount].Type = setype(atual, PosInLine);          // Classifica 
                Arraytokens[TKcount].LineNumber = LCount;
                Arraytokens[TKcount].PosInLine = PosInLine;
                newToken(read, Arraytokens[TKcount].Type, TKcount, LCount, PosInLine);  // Chama a funcao de coleta de tokens
            }

        }
    }
    free(reserved);
    free(read);
}

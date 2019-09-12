#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#define TAM_BUFFER 1024

struct Estrutura_TOKEN{
    char token[25];
    int tipo, LPos, CPos;
}Arraytokens[100] = {0};

int toklen=0, tokcount=0;
int linPOS=0, colPOS=0; 

int setype(char c);
char newToken(FILE *read, int type, int tokcount, int linPOS);

// char letrasm [30] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};  // Alfabeto minusculo
// char letrasM [30] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};  // Alfabeto maiusculo
// char numeros [10] = {'0','1','2','3','4','5','6','7','8','9'};  // Numerais
// char op [10] = {'+','-','*','/'};                               // Operardores aritmeticos
// char especiais [10] = {'(',')','[',']','{','}'};                // Caracteres especias
// //char relacional [10] = {'<','>','<=','>=','==','!='};           // Operadores relacionais
// //char logicos [10] = {'&&','||','&','|','!'};                    // Operadores Logicos
// char atribuicao = '=';                                          // Caracter de atribuicao
// //char delimitadores = {';',','};                                 // Caracteres delimitadores
char listaTokens[100][20];                                      // Lista de tokens
int tokenPOS[100];
int errorPOS[100];
char sentinela;
int CSentinel=0;
int CTokens=0;                                                   // Sentinela


int main(int argc, char **argv){                                                     // Main - Somente um switch para as modularizacoes

    //verifyArgs(argc);
    int i=1, id=0;
    char c;

    FILE *read, *descritor;                                                 // Ponteiro que irá ler o arquivo.
    read = fopen ("test.c","r");                                // Ponteiro "read" abre o arquivo de entrada e fará a leitura dos caracteres do arquivo
    if (!read){                                                 // Caso o ponteiro "read" não ler nada, aparecerá a mensagem de erro.
        printf (" Não é possível abrir o arquivo! \n");
        exit (1);
    }

    char buffer[TAM_BUFFER], acumulador[TAM_BUFFER]; 
    int coluna = 0, linha = 1;
    int buffersize = 0;

    while(!feof(read)){
        fgets(buffer, TAM_BUFFER, read);
        buffer[strlen(buffer)-1] = '\0';
        buffersize = strlen(buffer)-1;   
        // printf("Tam linha [%d]\n",buffersize);
        printf("Linha [%d] - [%s]\n",linha ,buffer);
        char atual = buffer[coluna];

        while(atual == 32 || atual == '\t' || atual == '\n' || atual == '\0') {
            if(coluna < buffersize){
                coluna++;
            } else {
                fgets(buffer, TAM_BUFFER, read);
                buffersize = strlen(buffer);
                coluna = 0;
                linha++;
            }
            atual = buffer[coluna];
        }

        Arraytokens[i].tipo = setype(atual);
        Arraytokens[i].LPos = linha;
        Arraytokens[i].CPos = coluna;

        int toklen = 0;
        switch (Arraytokens[i].tipo){
            case 1:             // Identificador
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z') || (atual >= '0' && atual <= '9')|| atual == '_' || atual == '$');
                break;
            case 2:             // Numeral
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual >= '0' && atual <= '9');
                break;
            case 3:             // Separadores
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual == '(' || atual == ')' || atual == '[' || atual == ']' || atual == '{' || atual == '}' || atual == '=' || atual == ';' || atual == ',' );
                break;
            case 4:             // Operadores
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual == '+' || atual == '-' || atual == '*' || atual == '/' );
                break;
            case 5:             // Especial
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual == '#' );
                break;
            case 6:             // Literal
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual == '"' );
                break;
            case 7:             // Erro
                do {
                    Arraytokens[i].token[toklen] = atual;
                    toklen++;

                    if(coluna < buffersize){
                        coluna++;
                    } else {
                        fgets(buffer, TAM_BUFFER, read);
                        buffersize = strlen(buffer);
                        coluna = 0;
                        linha++;
                    }

                    atual = buffer[coluna];

                } while( atual == '@' || atual == '~' || atual == '^' );
                break;
        }
        
        printf("Token [%d] | %s -> Tipo [%d] - Linha [%d](%d_caracteres) - Pos na linha [%d]\n",i , Arraytokens[i].token, Arraytokens[i].tipo,Arraytokens[i].LPos,buffersize,Arraytokens[i].CPos);
        i++;
        // printf("%c %d:%d\n", atual, linha, coluna);
    }

}

int setype(char c){
	
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')|| c == '_' || c == '$' ){   // Identificador
        return 1;
    } else if ( c >= '0' && c <= '9'){      // Numeral
        return 2;
    } else if ( c == 32 || c == '\t' || c == '\n' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '=' || c == ';' || c == ','){        // Separador
        return 3;
    } else if ( c == '+' || c == '-' || c == '*' || c == '/'){      // Operador
        return 4;
    } else if ( c == '#' ){     // Especial
        return 5;
    }else if (c == '"'){    // Literal
        return 6;
    }else if ( c == '@' || c == '~' || c == '^' ){  // Erro
        return 7;
    }
}

char newToken(FILE *read, int type, int tokcount, int linPOS){                                                // Função para coletar palavras ou tokens
    toklen=0;
    char d;

    switch (type){
        case 0:

        case 1:
            tokcount++;
            do{
                d = getc(read);
                Arraytokens[tokcount].token[toklen] = d;
                linPOS++;
                toklen++;
        	}while((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z') || (d >= '0' && d <= '9')|| d == '_' || d == '$');
            break;
        case 2:
            do{
                d = getc(read);
                Arraytokens[tokcount].token[toklen] = d;
                linPOS++;
                toklen++;
            }while( d >= '0' && d <= '9');
            break;
        case 3:
            do{
                if ( d == 32 || d == '\t'){

                }
                getc(read);
                linPOS++;
                toklen++;
            }while( d != 32 || d != '\t' || d != '\n' || d == '(' || d == ')' || d == '[' || d == ']' || d == '{' || d == '}' || d == '=' || d == ';' || d == ',');
            break;
        case 4:
            do{
                d = getc(read);
                Arraytokens[tokcount].token[toklen] = d;
                linPOS++;
                toklen++;
            }while( d == '+' || d == '-' || d == '*' || d == '/');
            break;
        case 5:
            do{
                d = getc(read);
                Arraytokens[tokcount].token[toklen] = d;
                linPOS++;
                toklen++;
            }while( d == '#' );
            break;
        case 6:
            do{
                d = getc(read);
                Arraytokens[tokcount].token[toklen] = d;
                linPOS++;
                toklen++;
            }while( d == '@' || d == '~' || d == '^');
            break;
        default:
        break;
    }
    /*
    while(!feof(read)){
        c = getc(read);
        printf("Linha %d_[POS-%d] - %c\n", linhas, i, c);
        i++;
        linhas++;

    }
    rewind(read);
    */

    /*
    do{
        c = fgetc(read);
        CSentinel++;
        CTokens+=1;
    }while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')|| c == '_' || c == '$');

    fseek(read,-CSentinel,SEEK_CUR);
    for ( int i=0 ; i<CSentinel ; i++ ){
        //listaTokens[linhas][i] = fgetc(read);
    }

    for ( i=0 ; i<=CTokens ; i++){
        printf("Total - %d | Token[%d] - %s\n",CTokens ,i ,listaTokens[i]);
    }
    
    for ( i=0 ; i<!feof(read) ; i++ ){
        c = fgetc(read);
        printf("Linha %d_[N-%d] - %c\n", linhas, i, c);
        linhas++;
    }
 
    do{
        if(fread(&lc, sizeof(char), 1, read));
        if(lc == '\n'){
            aux++;
        }
    }while(aux<=1);
 
    for( i=3 ; i<=lcounter ; i++ ){
        if(fscanf(read, "%d %d %d %c", &a, &b, &c, &d));
        automato[a][b].saidas[c] = d;
    }
 
    rewind(read);
      

    while (palavra != NULL){                    //se já chegou ao fim devolve NULL
        listaTokens[j++] = palavra;                //guardar a palavra corrente e avançar
        palavra = strtok(NULL, " ");            //achar a próxima palavra
    }
    */
}




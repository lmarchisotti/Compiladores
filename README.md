# Lexico
Analisador Léxico

Quando analisamos uma palavra, podemos definir através da análise léxica se existe ou não algum caractere que não faz parte do nosso alfabeto ou de um alfabeto inventado por nós.

É a primeira etapa do processo de compilação e seu objetivo é dividir o código fonte em símbolos, preparado-o para a Análise Sintática. Neste processo pode-se destacar três atividades como fundamentais:

->Extração e classificação dos tokens.

->Eliminação de delimitadores e comentários.

->Recuperação de Erros.

O analisador léxico funciona de duas maneiras:

Primeiro estado da análise: 

A primeira etapa lê a entrada de caracteres, um de cada vez, mudando o estado em que os caracteres se encontram. Quando o analisador encontra um caracter que ele não identifica como correto classificamos como ERRO então, registra o erro e passa para o proximo caracter.

Segundo estado da análise: 

Nesta etapa são repassados os caracteres do léxico para produzir um valor. O tipo do léxico combinado com seu valor é o que adequadamente constitui um símbolo, que pode ser dado a um parser. 
(Alguns símbolos tais como parênteses não têm valores, e então a função da análise pode retornar nada).
A análise léxica escreve um parser muito mais fácil. Em vez de ter que acumular, renomeia seus caracteres individualmente. 
O parser não mais se preocupa com símbolos e passa a preocupar-se só com questões de sintática. 
Isto leva a eficiência de programação, e não eficiência de execução. 

# Lista de Simbolos

Identificadores = {( 'a' até 'z' ) ou ( 'A' até 'Z' ) ou ( '0' até '9' )} Obs: os tokens identificadores não podem iniciar com numerais

Numerais = { ( '0' até '9' ) }

Separadores = { ' ' , '\t' , '\n' , '(' , ')' , '[' , ']' , '{' , '}' , '=' , ';' , ',' }

Operadores = { '+' , '-' , '*' , '/' }

Diretiva = { '#' }

Literal = { '"' }

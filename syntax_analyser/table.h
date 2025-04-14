#define PROGRAMA 0            
#define ID 1                  
#define OPEN_CURLY_PERCENT 2  
#define CLOSE_PERCENT_CURLY 3 
#define OPEN_PAREN 4          
#define CLOSE_PAREN 5         
#define OPEN_BRACKET 6        
#define CLOSE_BRACKET 7       
#define IF 8                  
#define THEN 9                
#define ELSEIF 10             
#define ELSE 11               
#define WHILE 12              
#define DO 13                 
#define ASSIGN 14             
#define COLON 15              
#define SEMICOLON 16          
#define COMMA 17              
#define ARITOP_ADD 18         
#define ARITOP_MULT 19        
#define ARITOP_POT 20         
#define RELOP 21              
#define CONST_CHAR 22         
#define CONST_INT 23          
#define CONST_FLOAT 24        
#define CHAR 25               
#define INT 26                
#define FLOAT 27              
#define SPACE 28              
#define TAB 29                
#define NEWLINE 30            
#define DOLLAR 31             


#define ESTADO_INICIAL 0
#define ESTADO_NOME_PROGRAMA 1
#define ESTADO_BLOCO 2
#define ESTADO_DECLARACOES 3
#define ESTADO_LISTA_IDS 4
#define ESTADO_LISTA_IDS_LINHA 5
#define ESTADO_PRIMITIVO 6
#define ESTADO_COMANDOS 7
#define ESTADO_COMANDOS_LINHA 8
#define ESTADO_COMANDO 9
#define ESTADO_COMANDO_LINHA 10
#define ESTADO_ELSEIFS 11
#define ESTADO_ELSEIFS_LINHA 12
#define ESTADO_CONDICAO 13
#define ESTADO_EXPRESSAO 14
#define ESTADO_EXPRESSAO_LINHA 15
#define ESTADO_TERMO 16
#define ESTADO_TERMO_LINHA 17
#define ESTADO_POTENCIA 18
#define ESTADO_POTENCIA_LINHA 19
#define ESTADO_FATOR 20
#define ESTADO_WS 21

#define NUM_ESTADOS 22  
#define NUM_SIMBOLOS 32 


const int TABELA[NUM_ESTADOS][NUM_SIMBOLOS] = {

    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    
    {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    
    {0, 5, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0},

    
    {0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 11, 0, 0, 0, 0},

    {0, 12, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 12, 12, 0, 0,
     0, 0,  0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0},


    {0, 13, 13, 14, 0, 0, 0, 0, 13, 0, 0, 0, 13, 13, 0, 0,
     0, 0,  0,  0,  0, 0, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0},


    {0, 18, 19, 0, 0, 0, 0, 0, 15, 0, 0, 0, 16, 17, 0, 0,
     0, 0,  0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0},


    {0,  22, 22, 22, 0, 0, 0, 0, 22, 0, 21, 20, 22, 22, 0, 0,
     22, 0,  0,  0,  0, 0, 0, 0, 0,  0, 0,  0,  0,  0,  0, 0},

    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0},


    {0,  26, 26, 26, 0, 0, 0, 0, 26, 0, 25, 24, 26, 26, 0, 0,
     26, 0,  0,  0,  0, 0, 0, 0, 0,  0, 0,  0,  0,  0,  0, 0},


    {0, 27, 0,  0, 27, 0, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
     0, 0,  27, 0, 0,  0, 27, 27, 27, 0, 0, 0, 0, 0, 0, 0},


    {0, 28, 0,  0, 28, 0, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
     0, 0,  28, 0, 0,  0, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0},


    {0,  0, 0,  0, 0, 0,  0, 30, 0, 0, 0, 0, 0, 0, 0, 0,
     30, 0, 29, 0, 0, 30, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},


    {0, 31, 0,  0, 31, 0, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
     0, 0,  31, 0, 0,  0, 31, 31, 31, 0, 0, 0, 0, 0, 0, 0},


    {0,  0, 0,  0,  0, 0,  0, 33, 0, 0, 0, 0, 0, 0, 0, 0,
     33, 0, 33, 32, 0, 33, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},


    {0, 34, 0,  0, 34, 0, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
     0, 0,  34, 0, 0,  0, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0},


    {0,  0, 0,  0,  0,  0,  0, 36, 0, 0, 0, 0, 0, 0, 0, 0,
     36, 0, 36, 36, 35, 36, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},


    {0, 39, 0,  0, 38, 0, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
     0, 0,  37, 0, 0,  0, 40, 41, 42, 0, 0, 0, 0, 0, 0, 0},


    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 44, 45, 0}};

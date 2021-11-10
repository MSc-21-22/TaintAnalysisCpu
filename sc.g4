grammar sc;

prog 
    : functionDef* EOF
    ;

functionDef 
    : 'void' ID LPAREN opt_parameters RPAREN '{' statements '}'
    | type ID LPAREN opt_parameters RPAREN '{' statements 'return' expression';' '}'
    ;
        
statements 
    : statement ';' statements
    | whileloop statements
    | statementif statements
    | /* e */
    ;
            
statement
    :  statementinit
    |  statementassign
    |  functionCallInit
    ;

statementassign
    : ID '=' expression
    ;

statementinit
    : type ID '=' expression
    ;
            
whileloop
    : 'while' LPAREN expression RPAREN '{' statements '}'
    ;

statementif
    :  'if' LPAREN expression RPAREN '{' statements '}' 'else' '{' statements '}'  
    ;

args
    : expression',' args
    | expression
    ;

expression
    : LPAREN expression RPAREN expressionM
    | INTEGER expressionM
    | ID expressionM
    ;

expressionM
    : op=(PLUS | MINUS | DIVISION | MULTIPLICATION) expression expressionM
    | /* e */
    ;

functionCallInit
    : type ID '=' functionCall
    ;

functionCall
    : ID '(' ')' 
    | ID '(' args ')'
    ;

opt_parameters
    : parameters
    | /* e */
    ;

parameters 
    : parameter ',' parameters
    | parameter
    ;

parameter
    : type ID
    ; 

type
    : 'int'
    ;

// Literals
INTEGER            : '0'|[1-9][0-9]* ;

// Operators
PLUS               : '+' ;
MINUS              : '-' ;
DIVISION           : '/' ;
MULTIPLICATION     : '*' ;
ASSIGN             : '=' ;
LPAREN             : '(' ;
RPAREN             : ')' ;
LEQ                : '<=';
GEQ                : '>=';
LT                 : '<' ;
GT                 : '>' ;

// Identifiers
ID                  : [_]*[a-z][A-Za-z0-9_]*
                    | '£';

WS : (' ' | '\t' | '\n')+ -> channel(HIDDEN);
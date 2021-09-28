grammar sc;

prog 
    : functionDef* EOF
    ;

functionDef 
    : 'void' ID LPAREN opt_parameters RPAREN '{' statements '}'
    | type ID LPAREN opt_parameters RPAREN '{' statements ';' 'return' expression';' '}'
    ;
        
statements 
    : statement';' statements
    | /* e */
    ;
            
statement
    :  statementinit
    |  statementassign
    ;

statementassign
    : ID '=' expression
    ;

statementinit
    : type ID '=' expression
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
    : op=(PLUS | MINUS | DIVISION) expression expressionM
    | /* e */
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
ASSIGN             : '=' ;
LPAREN             : '(' ;
RPAREN             : ')' ;

// Identifiers
ID                 : [_]*[a-z][A-Za-z0-9_]* ;

WS : (' ' | '\t' | '\n')+ -> channel(HIDDEN);
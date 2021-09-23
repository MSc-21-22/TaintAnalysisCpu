grammar sc;

prog 
    : functionDef EOF
    | functionDef prog
    ;

functionDef 
    : 'void' ID ( parameters ) { statements }
    | type ID ( parameters ) { statements ';' 'return' expression; }
    ;
        
statements 
    : statement';' statements
    | /* e */
    ;
            
statement   
    :  ID ( )
    |  ID ( args )
    |  type ID '=' expression
    |  ID '=' expression
    ;
            
args
    : expression',' args
    | expression
    ;

expression
    : LPAREN expression RPAREN expressionM
    | INTEGER expressionM
    ;

expressionM
    : (PLUS | MINUS | DIVISION) expression expressionM
    | /* e */
    ;

parameters 
    : parameter
    | parametersM
    | /* e */
    ;

parametersM
    : parameter',' parametersM
    | /* e */
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
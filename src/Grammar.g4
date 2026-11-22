grammar Grammar;

program: expr EOF ;

expr: '-' expr                          # Neg
    | <assoc=right> expr '^' expr       # Pow
    | expr op=('*' | '/' | '%') expr    # MulDiv
    | expr op=('+' | '-') expr          # AddSub
    | '(' expr ')'                      # Paren
    | NUMBER                            # Num
    ;

NUMBER: [0-9]+ ('.' [0-9]+)? ;
WS: [ \t\r\n]+ -> skip ;

// Define a grammar called Expr
grammar Expr;
expr  : ID '=' Floatingliteral unit? ;
ID : [a-z]+ ;             // match lower-case identifiers
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
Floatingliteral
    : Fractionalconstant Exponentpart?
    | Digitsequence Exponentpart
    ;
unit
    : length
    | velocity
    | acceleration
    ;
velocity
    : 'm/s'
    | 'ms^-1'
    ;
acceleration
    : 'ms^-2'
    | 'm/s/s'
    ;
length
    : 'm'
    | 'ft'
    ;
fragment Fractionalconstant
    : Digitsequence? '.' Digitsequence
    | Digitsequence '.'
    ;
fragment Exponentpart
    : 'e' SIGN? Digitsequence
    | 'E' SIGN? Digitsequence
    ;

fragment SIGN
    : [+-]
    ;

fragment Digitsequence
    : DIGIT ('\''? DIGIT)*
    ;

fragment Floatingsuffix
    : [flFL]
    ;
fragment DIGIT
    : [0-9]
    ;
fragment METRE
    : [m]
    ;

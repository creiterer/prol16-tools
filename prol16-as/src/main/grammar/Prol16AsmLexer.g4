/**
 * Lexer grammar of the PROL16 assembler.
 */
lexer grammar Prol16AsmLexer;

/**
 * Fragment definitions
 */
fragment Letter : [a-zA-Z] ;
fragment Dot : '.' ;

fragment BinaryDigit : [0-1] ;
fragment DecimalDigit : [0-9] ;
fragment HexDigit : [0-9a-fA-F] ;

fragment BinaryNumberSuffix : 'b' ;
fragment DecimalNumberSuffix : 'd' ;
fragment HexNumberSuffix : 'h' ;

fragment BinaryNumber : BinaryDigit ('_'? BinaryDigit)* BinaryNumberSuffix ;
fragment DecimalNumber : DecimalDigit ('_'? DecimalDigit)* DecimalNumberSuffix? ;
fragment HexNumber : HexDigit ('_'? HexDigit)* HexNumberSuffix ;

fragment RegisterPrefix : [rR] ;
fragment RegisterNumber : DecimalDigit+ ;
fragment ProgramCounterRegister : 'rpc' | 'RPC' ;
fragment ReturnAddressRegister : 'rra' | 'RRA' ;
fragment StackPointerRegister : 'rsp' | 'RSP' ;
fragment FramePointerRegister : 'rfp' | 'RFP' ;
fragment GeneralPurposeRegister : RegisterPrefix RegisterNumber ;

/**
 * Token definitions
 */
NOP		: 'nop' | 'NOP' ;
SLEEP	: 'sleep' | 'SLEEP' ;
LOADI	: 'loadi' | 'LOADI' ;
LOAD	: 'load' | 'LOAD' ;
STORE	: 'store' | 'STORE' ;
MOVE	: 'move' | 'MOVE' ;
JUMP	: 'jump' | 'JUMP' ;
JUMPC	: 'jumpc' | 'JUMPC' ;
JUMPZ	: 'jumpz' | 'JUMPZ' ;
AND		: 'and' | 'AND' ;
OR		: 'or' | 'OR' ;
XOR		: 'xor' | 'XOR' ;
NOT		: 'not' | 'NOT' ;
ADD		: 'add' | 'ADD' ;
ADDC	: 'addc' | 'ADDC' ;
SUB		: 'sub' | 'SUB' ;
SUBC	: 'subc' | 'SUBC' ;
COMP	: 'comp' | 'COMP' ;
INC		: 'inc' | 'INC' ;
DEC		: 'dec' | 'DEC' ;
SHL		: 'shl' | 'SHL' ;
SHR		: 'shr' | 'SHR' ;
SHLC	: 'shlc' | 'SHLC' ;
SHRC	: 'shrc' | 'SHRC' ;
PRINT	: '_print' | '_PRINT' ;

ORG		: 'org' | 'ORG' ;
DB		: 'db' | 'DB' ;
EQU		: 'equ' | 'EQU' ;
MACRO	: 'macro' | 'MACRO' ;
ENDM	: 'endm' | 'ENDM' ;

Comma : ',' ;
Colon : ':' ;
MacroCallOperator : '()' ;

NEWLINE : '\r'? '\n' ;	// return newlines to the parser because they are the end-statement signal!

Number : BinaryNumber | DecimalNumber | HexNumber ;

Register : ProgramCounterRegister | ReturnAddressRegister | StackPointerRegister | FramePointerRegister | GeneralPurposeRegister ;

String : ('"' ~["]+ '"') | ('\'' ~[\u0027]+ '\'') ;	// \u0027 is the character '

Identifier : (Letter | Dot | '_') ('_'? (Letter | Dot | DecimalDigit))* ;

/**
 * Definition of things that should be skipped
 */
//LineComment : ';' ~[\r\n]* '\r'? '\n' -> skip ;
LineComment : ';' ~[\r\n]* -> skip ;
BlockComment : '/*' .*? '*/' -> skip ;
Whitespace : [ \t]+ -> skip ;

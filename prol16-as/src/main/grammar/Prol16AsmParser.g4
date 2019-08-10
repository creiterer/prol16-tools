/**
 * Parser grammar of the PROL16 assembler.
 */
parser grammar Prol16AsmParser;

options {
	tokenVocab = Prol16AsmLexer;
}

/**
 * EOF -> don't stop early. must match all input
 * see https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#start-rules-and-eof
 */
prol16AsmFile : statement* EOF;

expression : number=Number | identifier=Identifier ;

statement : mnemonicStatement | assemblerStatement | labelStatement ;

mnemonicStatement
	: (nopInstruction
	| sleepInstruction
	| loadiInstruction
	| loadInstruction
	| storeInstruction
	| moveInstruction
	| jumpInstruction
	| jumpcInstruction
	| jumpzInstruction
	| andInstruction
	| orInstruction
	| xorInstruction
	| notInstruction
	| addInstruction
	| addcInstruction
	| subInstruction
	| subcInstruction
	| compInstruction
	| incInstruction
	| decInstruction
	| shlInstruction
	| shrInstruction
	| shlcInstruction
	| shrcInstruction
	| printInstruction)? NEWLINE
	;

assemblerStatement
	: (commandCounterLoad
	| dataWordStore
	| symbolicConstantDefinition
	| macroDefinition
	| macroCall)? NEWLINE
	;
	
/**
 * If we are at the end of the file, no newline should be necessary.
 */
/*
mnemonicStatement
	: mnemonicStatementHelper? {_input->LT(1)->getType() != Token::EOF }? NEWLINE
	| mnemonicStatementHelper {_input->LT(1)->getType() == Token::EOF }?
	;

mnemonicStatementHelper
	: nopInstruction
	| sleepInstruction
	| loadiInstruction
	| loadInstruction
	| storeInstruction
	| moveInstruction
	| jumpInstruction
	| jumpcInstruction
	| jumpzInstruction
	| andInstruction
	| orInstruction
	| xorInstruction
	| notInstruction
	| addInstruction
	| addcInstruction
	| subInstruction
	| subcInstruction
	| compInstruction
	| incInstruction
	| decInstruction
	| shlInstruction
	| shrInstruction
	| shlcInstruction
	| shrcInstruction
	;
*/

/**
 * If we are at the end of the file, no newline should be necessary.
 */
/* 
assemblerStatement
	: assemblerStatementHelper? {_input->LT(1)->getType() != Token::EOF }? NEWLINE
	| assemblerStatementHelper {_input->LT(1)->getType() == Token::EOF }?
	;

assemblerStatementHelper
	: ORG expression
	| DB (Number | String) (Comma Number | String)*
	| EQU Identifier Comma Number
	| macroDefinition
	| macroCall
	;
*/

labelStatement : identifier=Identifier Colon ;

nopInstruction 		: NOP ;
sleepInstruction 	: SLEEP ; 
loadiInstruction	: LOADI ra=Register Comma immediate=expression ;
loadInstruction		: LOAD ra=Register Comma rb=Register ;
storeInstruction	: STORE ra=Register Comma rb=Register ;
moveInstruction		: MOVE ra=Register Comma rb=Register ;
jumpInstruction		: JUMP ra=Register ;
jumpcInstruction	: JUMPC ra=Register ;
jumpzInstruction	: JUMPZ ra=Register ;
andInstruction		: AND ra=Register Comma rb=Register ;
orInstruction		: OR ra=Register Comma rb=Register ;
xorInstruction		: XOR ra=Register Comma rb=Register ;
notInstruction		: NOT ra=Register ;
addInstruction		: ADD ra=Register Comma rb=Register ;
addcInstruction		: ADDC ra=Register Comma rb=Register ;
subInstruction		: SUB ra=Register Comma rb=Register ;
subcInstruction		: SUBC ra=Register Comma rb=Register ;
compInstruction		: COMP ra=Register Comma rb=Register ;
incInstruction		: INC ra=Register ;
decInstruction		: DEC ra=Register ;
shlInstruction		: SHL ra=Register ;
shrInstruction		: SHR ra=Register ;
shlcInstruction		: SHLC ra=Register ;
shrcInstruction		: SHRC ra=Register ;
printInstruction	: PRINT (ra=Register | immediate=expression | string=String) ;

commandCounterLoad : ORG address=expression ;
dataWordStore : DB (Number | String) (Comma Number | String)* ;
symbolicConstantDefinition : EQU identifier=Identifier Comma number=Number ;
macroDefinition : MACRO Identifier NEWLINE mnemonicStatement* ENDM ;
macroCall : Identifier MacroCallOperator;

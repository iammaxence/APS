%{
	/* tpc.y */
	#include <stdio.h>
	#include <ctype.h>
	#include "Enum.h"
	#include "Env.h"
	#include "Ast.h"
	#include "ASTParc.h"
	int yylex();
	void yyerror(const char* s);
	extern int cmp_ligne;
	int error_code = 0;
	AST node = NULL;

%}

%define parse.error verbose


%union{
	int cbool;
	int num;
	char ident[65];
	TypeComp type;
	ClefEnum clef;
	AST node;
}

%token <cbool> CBOOL
%token <num> NUM
%token <ident> IDENT
%token <type> TYPE
%token <clef> CLEF

%token IF
%token CONST
%token FUN
%token REC
%token _ECHO

%type <node> Progs Cmds States Dec Type Types Args Arg Expr Exprs
%%

Progs: '[' Cmds ']' 													{$$ = createNode(ASTProg, 1, $2);
																		node = $$;
																		}
	;

Cmds: States															{$$ = createNode(ASTCMDS0, 1, $1);}
	| Dec ';' Cmds														{$$ = createNode(ASTCMDS1, 2, $1, $3);}
	| States ';' Cmds													{$$ = createNode(ASTCMDS2, 2, $1, $3);}
	;

States: _ECHO Expr														{$$ = createNode(ASTStates, 1, $2);}
	;

Dec:
	  CONST IDENT Type '[' Args ']' Expr								{$$ = createNode(ASTDEC1, 4, createIdent($2), $3, $5, $7);}
    | CONST IDENT TYPE Expr												{$$ = createNode(ASTDEC0, 3, createIdent($2), createPrimitiveType($3), $4);}
	| FUN IDENT Type '[' Args ']' Expr									{$$ = createNode(ASTDEC1, 4, createIdent($2), $3, $5, $7);}
	| FUN REC IDENT Type '[' Args ']' Expr								{$$ = createNode(ASTDEC2, 4, createIdent($3), $4, $6, $8);}
	;

Type: TYPE																{$$ = createPrimitiveType($1);}
	| '(' Types ')' '-' '>' Type										{$$ = createNode(ASTTYPECompo, 2, $2, $6);}
	;

Types: Type																{$$ = createNode(ASTTYPES0, 1, $1);}
	| Type '*' Types													{$$ = createNode(ASTTYPES1, 2, $1, $3);}
	;

Args: Arg																{$$ = createNode(ASTARGS0, 1, $1);}
	| Arg ';' Args														{$$ = createArrayFromList(ASTARGS1, $1, $3);}
	;

Arg: IDENT ':' Type														{$$ = createNode(ASTARG0, 2, createIdent($1), $3);}
	;

Expr: NUM 																{$$ = createInt($1);}
	| CBOOL 															{$$ = createBool($1);}
	| IDENT																{$$ = createIdent($1);}
	| '(' IF Expr Expr Expr ')'											{$$ = createNode(ASTEXPR0, 3, $3, $4, $5);}
	| '(' CLEF Exprs ')'												{$$ = createNode(ASTEXPR1, 2, createClef($2), $3);}
	| '[' Args ']' Expr													{$$ = createNode(ASTEXPR2, 2, $2, $4);}
	| '(' Expr Exprs ')'												{$$ = createNode(ASTEXPR3, 2, $2, $3);}
	| '(' Expr ')' 														{$$ = $2;}
	;
	
Exprs: Expr																{$$ = createNode(ASTEXPRS1, 1, $1);}
	| Expr Exprs														{$$ = createArrayFromList(ASTEXPRS0, $1, $2);}
	;

%%


void yyerror(const char* s){
	fprintf(stderr, "%sERROR: %s%s\nline %d\n", KRED, KWHT, s, cmp_ligne);
	error_code += 1;
}

int main(void){
	Env env = empty_env();
	node = NULL;
	yyparse();

	displayProlog(node, 0);
	printf("\n");
	eval(node, env);

	freeAst(node);

	return error_code;
}

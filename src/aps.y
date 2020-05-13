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
%token <type> VOID
%token <clef> CLEF

%token IF
%token CONST
%token FUN
%token REC
%token _ECHO
%token VAR
%token PROC
%token SET
%token WHILE
%token CALL

%type <node> Progs Cmds States Dec Type Types Args Arg Expr Exprs
%%

Progs: '[' Cmds ']' 													{$$ = createNode(ASTProg, 1, $2);
																		node = $$;
																		}
	 | error
	;

Cmds: States															{$$ = createNode(ASTCMDS0, 1, $1);}
	| Dec ';' Cmds														{$$ = createNode(ASTCMDS1, 2, $1, $3);}
	| States ';' Cmds													{$$ = createNode(ASTCMDS2, 2, $1, $3);}
	;

States: _ECHO Expr														{$$ = createNode(ASTStates, 1, $2);}
	  | SET IDENT Expr													{$$ = createNode(ASTStates1, 2, createIdent($2), $3);}
	  | IF Expr Progs Progs												{$$ = createNode(ASTStates2, 3, $2, $3, $4);}
	  | WHILE Expr Progs												{$$ = createNode(ASTStates3, 2, $2, $3);}
	  | CALL IDENT Exprs												{$$ = createNode(ASTStates4, 2, createIdent($2), $3);}
	;

Dec:
	  CONST IDENT Type '[' Args ']' Expr								{$$ = createNode(ASTDEC1, 4, createIdent($2), $3, $5, $7);}
    | CONST IDENT TYPE Expr												{$$ = createNode(ASTDEC0, 3, createIdent($2), createPrimitiveType($3), $4);}
	| FUN IDENT Type '[' Args ']' Expr									{$$ = createNode(ASTDEC1, 4, createIdent($2), $3, $5, $7);}
	| FUN REC IDENT Type '[' Args ']' Expr								{$$ = createNode(ASTDEC2, 4, createIdent($3), $4, $6, $8);}
	
	| VAR IDENT Type													{$$ = createNode(ASTDEC3, 2, createIdent($2), $3);}
	| PROC IDENT '[' Args ']' Progs										{$$ = createNode(ASTDEC4, 3, createIdent($2), $4, $6);}
	| PROC REC IDENT '[' Args ']' Progs									{$$ = createNode(ASTDEC5, 3, createIdent($3), $5, $7);}
	;

Type: TYPE																{$$ = createPrimitiveType($1);}
	| '(' Types ')' '-' '>' Type										{$$ = createNode(ASTTYPECompo, 2, $2, $6);}
	| VOID																{$$ = createPrimitiveType($1);}
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

int main(int argc, char **argv){
	Env env = empty_env();
	node = NULL;
	yyparse();
	
	if(argc != 2){
		return 1;
	}
	
	if(argv[1][1] == 's'){ // syntaxe
		printf("%d\n", error_code);
		return error_code;
	}
	else if(argv[1][1] == 't'){ // typage
		displayProlog(node, 0);
		printf(".");
	}
	else if(argv[1][1] == 'e'){ // eval
		eval(node, env);
	}
	

	freeAst(node);	
	purge_env(env);

	return error_code;
}


/*		### BIBLIOTHEQUE ###		*/
#include "ASTParc.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
/*		### DECLARATION FONCTION PRIVEE###	*/
static void displayNTab(unsigned int n);
static Value evalClef(AST node, Env env);
/*		### DEFINITION FONCTION ###		*/

Value evalClef(AST node, Env env){
	ClefEnum en = *(ClefEnum*)(node->child[0]->bonus);
	int i1, i2;
	Value v;
	i1 = eval(node->child[1]->child[0], env).num;
	
	if(_not != en){
		i2 = eval(node->child[1]->child[1], env).num;
	}
		
	switch(en){
		case(_not):
			v.num = ! i1;
			break;
		case(_and):
			v.num = i1 && i2;
			break;
		case(_or):
			v.num = i1 || i2;
			break;
		case(_eq):
			v.num = i1 == i2;
			break;
		case(_lt):	
			v.num = i1 < i2;
			break;
		case(_add):
			v.num = i1 + i2;
			break;
		case(_sub):
			v.num = i1 - i2;
			break;
		case(_mul):
			v.num = i1 * i2;
			break;
		case(_div):
			v.num = i1 / i2;
			break;
	}
	
	return v;
	
}

void display(AST node, int n){

	switch(node->tag){
		case(ASTProg):  	displayNTab(n);
							printf("PROG:\n");
							display(node->child[0], n+1);
							break;

		case(ASTCMDS0):		displayNTab(n);
							printf("STATES\n");
							display(node->child[0], n+1);
							break;

		case(ASTCMDS1): 	displayNTab(n);
							printf("DEC\n"); display(node->child[0], n+1);
							displayNTab(n);
							printf("CMDS\n"); display(node->child[1], n+1);
							break;

		case(ASTCMDS2): 	displayNTab(n);
							printf("STATES\n"); display(node->child[0], n+1);
							displayNTab(n);
							printf("CMDS\n"); display(node->child[1], n+1);
							break;
		case(ASTStates):	displayNTab(n);
							printf("ECHO\n"); display(node->child[0], n+1);
							break;
		
		case(ASTStates1):	displayNTab(n);
							display(node->child[0], n);
							display(node->child[1], n);
							break;

		case(ASTDEC0): 		displayNTab(n);
							printf("CONST\n");
							display(node->child[0], n);
							display(node->child[1], n);
							display(node->child[2], n);
							break;

		case(ASTDEC1): 		displayNTab(n);
							printf("FUN\n");
							display(node->child[0], n);
							display(node->child[1], n);
							display(node->child[2], n);
							display(node->child[3], n);
							break;

		case(ASTDEC2): 		displayNTab(n);
							printf("FUN\nRED\n");
							display(node->child[0], n);
							display(node->child[1], n);
							display(node->child[2], n);
							break;
		
		case(ASTDEC3): 		displayNTab(n);
							printf("VAR\n");
							display(node->child[0], n);
							display(node->child[1], n);
							break;
		
		case(ASTDEC4): 		displayNTab(n);
							printf("PROC\n");
							display(node->child[0], n);
							display(node->child[1], n);
							display(node->child[2], n);
							break;
		
		case(ASTDEC5): 		displayNTab(n);
							printf("PROC\nRED\n");
							display(node->child[0], n);
							display(node->child[1], n);
							display(node->child[2], n);
							break;

		case(ASTTYPECompo): displayNTab(n);
							printf("Type\n");
							display(node->child[0], n+1);
							break;

		case(ASTTYPES0): 	displayNTab(n);
							printf("Types\n");
							display(node->child[0], n+1);
							break;

		case(ASTTYPES1): 	displayNTab(n);
							printf("Types\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							break;

		case(ASTARGS0): 	displayNTab(n);
							printf("Args\n");
							display(node->child[0], n+1);
							break;

		case(ASTARGS1):		displayNTab(n);
							printf("Args\n");
							for(int i = 0; i < node->size; i++)
								display(node->child[i], n+1);
							break;

		case(ASTARG0): 		displayNTab(n);
							printf("Arg\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							break;

		case(ASTEXPR0): 	displayNTab(n);
							printf("if\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							display(node->child[2], n+1);
							break;

		case(ASTEXPR1): 	displayNTab(n);
							printf("appli prim\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							break;

		case(ASTEXPR2): 	displayNTab(n);
							printf("decl fun\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							break;

		case(ASTEXPR3): 	displayNTab(n);
							printf("appli fun\n");
							display(node->child[0], n+1);
							display(node->child[1], n+1);
							break;

		case(ASTEXPRS0):
							displayNTab(n);
							printf("Exprs\n");
							for(int i = 0; i < node-> size; i++)
								display(node->child[i], n);
							break;

		case(ASTEXPRS1):
					displayNTab(n);
					printf("Exprs\n");
					display(node->child[0], n+1);

		case(PrimInt): 		displayNTab(n);
							printf("%d\n", *((int*)node->bonus));
							break;

		case(PrimBool): 	displayNTab(n);
							printf("%s\n", (*((int*)node->bonus))?"true":"false");
							break;

		case(PrimIdent): 	displayNTab(n);
							printf("%s\n", (char*)node->bonus);
							break;

		case(PrimType): 	displayNTab(n);
							displayTypeComp(*((TypeComp*)node->bonus));
							printf("\n");
							break;

		case(PrimClef): 	displayNTab(n);
							displayClefEnum(*((ClefEnum*)node->bonus));
							printf("\n");
							break;

	}
}

void displayNTab(unsigned int n){

	for(int i = 0; i < n; i++){
		printf(" ");
	}
}

void displayProlog(AST node, int n){

	switch(node->tag){
		case(ASTProg):
							printf("prog([");
							displayProlog(node->child[0], n);
							printf("])");
							break;

		case(ASTCMDS0):
							printf("states(");
							displayProlog(node->child[0], n);
							printf(")");
							break;

		case(ASTCMDS1):
							printf("dec("); displayProlog(node->child[0], n);
							printf("),");
							displayProlog(node->child[1], n);
							break;

		case(ASTCMDS2):
							printf("states("); displayProlog(node->child[0], n);
							printf("),");
							displayProlog(node->child[1], n);
							break;
		case(ASTStates):
							printf("echo("); displayProlog(node->child[0], n);
							printf(")");
							break;
		
		case(ASTStates1):
							printf("set(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(")");
							break;
		
		case(ASTStates2):
							printf("if(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(")");
							break;
		
		case(ASTStates3):
							printf("while(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(")");
							break;
		
		case(ASTStates4):
							printf("call(");
							displayProlog(node->child[0], n);
							printf(",[");
							displayProlog(node->child[1], n);
							printf("])");
							break;

		case(ASTDEC0):
							printf("const(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(")");
							break;

		case(ASTDEC1):
							printf("fun(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(",");
							displayProlog(node->child[3], n);
							printf(")");
							break;

		case(ASTDEC2):
							printf("funrec(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(",");
							displayProlog(node->child[3], n);
							printf(")");
							break;
		
		case(ASTDEC3):
							printf("var(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(")");
							break;
		
		case(ASTDEC4):
							printf("proc(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(")");
							break;
		
		case(ASTDEC5):
							printf("procrec(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(")");
							break;

		case(ASTTYPECompo):
							//printf("types(")
							printf("[[");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf("]");
							//printf(")");
							break;

		case(ASTTYPES0):
							//printf("types(");
							displayProlog(node->child[0], n);
							printf("]");
							break;

		case(ASTTYPES1):
							//printf("types(");
							//printf("(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							//printf(")");
							break;

		case(ASTARGS0):
							printf("args([");
							displayProlog(node->child[0], n);
							printf("])");
							break;

		case(ASTARGS1):
							printf("args([");
							for(int i = 0; i < node->size; i++){
								if(i != 0)
									printf(",");
								displayProlog(node->child[i], n);

							}
							printf("])");
							break;

		case(ASTARG0):
							//printf("arg(");
							printf("(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(")");
							break;

		case(ASTEXPR0):
							printf("if(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(",");
							displayProlog(node->child[2], n);
							printf(")");
							break;

		case(ASTEXPR1):
							//printf("prim(");
							displayProlog(node->child[0], n);
							printf("(");
							displayProlog(node->child[1], n);
							printf(")");
							break;

		case(ASTEXPR2):
							printf("closure(");
							displayProlog(node->child[0], n);
							printf(",");
							displayProlog(node->child[1], n);
							printf(")");
							break;

		case(ASTEXPR3):
							printf("apply(");
							displayProlog(node->child[0], n);
							printf(",[");
							displayProlog(node->child[1], n);
							printf("])");
							break;

		case(ASTEXPRS0):
							printf("");

							for(int i = 0; i < node->size; i++){
								if(i != 0)
									printf(",");
								displayProlog(node->child[i], n);

							}
							printf("");
					
							break;

		case(ASTEXPRS1):
							displayProlog(node->child[0], n);
				
							break;

		case(PrimInt):
							printf("int(%d)", *((int*)node->bonus));
							break;

		case(PrimBool):
							printf("%s", (*((int*)node->bonus))?"true":"false");
							break;

		case(PrimIdent):
							printf("ident(%s)", (char*)node->bonus);
							break;

		case(PrimType):
							displayTypeComp(*((TypeComp*)node->bonus));
							break;

		case(PrimClef):
							displayClefEnum(*((ClefEnum*)node->bonus));
							break;

	}
}

Value eval(AST node, Env env){
	Value v;
	v.closure.args = NULL;
	
	switch(node->tag){
		case(ASTProg): 
			eval(node->child[0], env);	
			break;

		case(ASTCMDS0): 
			eval(node->child[0], env);	
			break;

		case(ASTCMDS1): 
			eval(node->child[0], env);	
			eval(node->child[1], env);	
			break;
		case(ASTCMDS2): 
			eval(node->child[0], env);	
			eval(node->child[1], env);	
			break;
		
		case(ASTStates): 
			printf("%ld\n", eval(node->child[0], env).num);	
			break;
	  
		case(ASTStates1): 
			edit_var(env, (char*)(node->child[0]->bonus), eval(node->child[1], env));
			break; // | SET IDENT Expr	{$$ = createNode(ASTStates1, 2, createIdent($2), $3);}

		case(ASTStates2):  // | IF Expr Progs Progs	{$$ = createNode(ASTStates2, 3, $2, $3, $4);}
			if(eval(node->child[0], env).num){
				eval(node->child[1], env);
			} 
			else{
				eval(node->child[2], env);
			}
			break;
		case(ASTStates3): // | WHILE Expr Progs	{$$ = createNode(ASTStates3, 2, $2, $3);}
			while(eval(node->child[0], env).num){
				eval(node->child[1], env);
			}
			break;
		case(ASTStates4):  // | CALL IDENT Exprs	{$$ = createNode(ASTStates4, 2, createIdent($2), $3);}
			return apply(eval, eval(node->child[0], env).closure, node->child[1]);
		case(ASTDEC0): 
			push_global_var(env, (char*)(node->child[0]->bonus), eval(node->child[2], env));
			break;

		case(ASTDEC1): 
			v.closure = create_closure(node->child[3], env, node->child[2]);
			push_global_var(env, (char*)(node->child[0]->bonus), v);
			push_closure(env, v.closure);
			break;
		

		case(ASTDEC2): 
			v.closure = create_closure(node->child[3], env, node->child[2]);
			push_global_var(v.closure.env, (char*)(node->child[0]->bonus), v);
			push_global_var(env, (char*)(node->child[0]->bonus), v);
			push_closure(env, v.closure);
			break;

		case(ASTDEC3):  // | VAR IDENT Type {$$ = createNode(ASTDEC3, 2, createIdent($2), $3);}
			push_global_var(env, (char*)(node->child[0]->bonus), (Value)(-42l));
			break;
		case(ASTDEC4):  // | PROC IDENT '[' Args ']' Progs {$$ = createNode(ASTDEC4, 3, createIdent($2), $4, $6);}
			v.closure = create_closure(node->child[2], env, node->child[1]);
			push_global_var(env, (char*)(node->child[0]->bonus), v);
			push_closure(env, v.closure);
			break;
		case(ASTDEC5):  // | PROC REC IDENT '[' Args ']' Progs {$$ = createNode(ASTDEC4, 3, createIdent($2), $4, $6);}
			v.closure = create_closure(node->child[2], env, node->child[1]);
			push_global_var(v.closure.env, (char*)(node->child[0]->bonus), v);
			push_global_var(env, (char*)(node->child[0]->bonus), v);
			push_closure(env, v.closure);
			break;
		case(ASTTYPECompo): break;

		case(ASTTYPES0): break;

		case(ASTTYPES1): break;

		case(ASTARGS0): break;

		case(ASTARGS1): break;

		case(ASTARG0): break;

		case(ASTEXPR0): 
			if(eval(node->child[0], env).num){
				return eval(node->child[1], env);
			}
			return eval(node->child[2], env);
		
		case(ASTEXPR1): 
			return evalClef(node, env);
			
		case(ASTEXPR2): 			
			v.closure = create_closure(node->child[1], env, node->child[0]);
			push_closure(env, v.closure);
			return v;

		case(ASTEXPR3): 
			return apply(eval, eval(node->child[0], env).closure, node->child[1]);

		case(ASTEXPRS0): break;

		case(ASTEXPRS1): break;

		case(PrimInt): 
			v.num = *((int*)node->bonus);
			return v;

		case(PrimBool): 
			v.num = *((int*)node->bonus);
			return v;

		case(PrimIdent):
		
			return acces_env(env, (char*)node->bonus);

		case(PrimType): break;

		case(PrimClef): break;

	}
}

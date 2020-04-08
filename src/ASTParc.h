#ifndef __ASTPARC__
#define __ASTPARC__

#include "Ast.h"
#include "Env.h"
#include "Closure.h"
#include <stdarg.h>


void display(AST node, int n);
void displayProlog(AST node, int n);
Value eval(AST node, Env env);
#endif /* __ENUM__ */

/*

switch(tag){
	case(ASTProg): break;
	case(ASTCMDS0): break;
	case(ASTCMDS1): break;
	case(ASTCMDS2): break;
	case(ASTStates): break;
	case(ASTDEC0): break;
	case(ASTDEC1): break;
	case(ASTDEC2)): break;
	case(ASTTYPEPrim): break;
	case(ASTTYPECompo): break;
	case(ASTTYPES0): break;
	case(ASTTYPES1): break;
	case(ASTARGS0): break;
	case(ASTARGS1): break;
	case(ASTARG0): break;
	case(ASTEXPRNum): break;
	case(ASTEXPRIdent): break;
	case(ASTEXPR0): break;
	case(ASTEXPR1): break;
	case(ASTEXPR2): break;
	case(ASTEXPR3): break;
	case(ASTEXPRS0): break;
	case(ASTEXPRS1): break;
	
}

*/
 
 
 

#ifndef __CLOSURE__
#define __CLOSURE__

/*		### BIBLIOTHEQUE ###		*/
#include <assert.h>
#include "Env.h"
#include "Ast.h"

/*		### MACRO ###		*/


/*		### STRUCTURE ###		*/
/**
typedef struct{
	AST body;
	Env env;
	String* args;
}Closure;
*/
/*		### DECLARATION FONCTION ###	*/
Closure create_closure(AST body, Env env, AST arg);

Value apply(Value (*eval)(AST, Env), const Closure, AST args);

void free_closure(Closure closure);

#endif /* __CLOSURE */

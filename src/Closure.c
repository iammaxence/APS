/*		### BIBLIOTHEQUE ###		*/
#include "Closure.h"
#include <stdio.h>
#include <assert.h>

/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/

Closure create_closure(AST body, Env env, AST arg){
	Closure ret = {body, surface_copy(env), NULL};
	return ret;
}

Value apply(Value (*eval)(AST, Env), const Closure closure, AST args){
	// add agr to env
	Value ret = eval(closure.body, closure.env);
	// remove agr to env
	return ret;
}

void free_closure(Closure closure){
	// todo
}

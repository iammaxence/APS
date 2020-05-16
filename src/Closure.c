/*		### BIBLIOTHEQUE ###		*/
#include "Closure.h"
#include <stdio.h>
#include <assert.h>

/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/

Closure create_closure(AST body, Env env, AST arg){
	Closure ret = {body, deep_copy(env), NULL};
	ret.args = (String*)malloc(sizeof(String*)*(1+arg->size));
	for(int i = 0; i < arg->size; i++){
		ret.args[i] = (char*)arg->child[0]->child[i]->bonus;
	}
	ret.args[arg->size] = NULL;
	return ret;
}

Value apply(Value (*eval)(AST, Env), Closure closure, AST args){
	// add agr to env
	for(int i = 0; i < args->size; i++){
		push_local_var(closure.env, closure.args[i], eval(args->child[0], closure.env));
	}

	Value ret = eval(closure.body, closure.env);
	// remove agr to env
	for(int i = 0; i < args->size; i++){
		purge_head(&(closure.env->local_env));
	}

	//~ purge_local_env(closure.env);
	return ret;
}

void free_closure(Closure closure){
	free(closure.args);
	purge_local_env(closure.env);
	free(closure.env);
}

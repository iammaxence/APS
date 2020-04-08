#ifndef __ENV__
#define __ENV__

/*		### BIBLIOTHEQUE ###		*/

#include "Ast.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

typedef char* String;

typedef struct{
	AST body;
	struct _env *env;
	String* args;
}Closure;

typedef enum{
	IsNum,
	IsFun
}ValueType;

typedef union{
	Closure closure;
	int num;
}Value;

typedef struct _f{
	struct _f *next;
	Value value;
	char *name;
}Cell, *List;


typedef struct _env{
	List global_env;
	List local_env;
}*Env;

/*		### DECLARATION FONCTION ###	*/
Env empty_env();

void push_local_var(Env env, const char* ident, Value value);

void push_global_var(Env env, const char* ident, Value value);

Env deep_copy(Env env);

Env surface_copy(Env env);

void purge_local_env(Env env);

void purge_env(Env env);

Value acces_env(const Env env, const char* name);

void display_env(const Env env);
#endif

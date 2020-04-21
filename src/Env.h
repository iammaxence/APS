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
	AST body; // 8 octets 
	struct _env *env; // 8 octets 
	String* args; // 8 octets 
}Closure;

typedef enum{
	IsNum,
	IsFun
}ValueType;

typedef union{
	Closure closure; // env 24 octets 
	long int num; // 8 octets 
}Value;

typedef struct _f{
	struct _f *next;
	Value value;
	char *name;
}Cell, *List;


typedef struct _lc{
	struct _lc* next;
	Closure closure;
}Closure_cell, *Closure_list;

typedef struct _env{
	List global_env;
	List local_env;
	Closure_list list_to_pg;
	Value rax; // pas encore utilisé
}*Env;

/*		### DECLARATION FONCTION ###	*/
Env empty_env();

void push_local_var(Env env, const char* ident, Value value);

void push_global_var(Env env, const char* ident, Value value);

void edit_var(Env env, const char* ident, Value value);

Env deep_copy(Env env);

Env surface_copy(Env env);

void purge_local_env(Env env);

void purge_env(Env env);

Value acces_env(const Env env, const char* name);

void display_env(const Env env);

void push_closure(Env env, Closure cl);

void purge_head(List *lst);
#endif


/*		### BIBLIOTHEQUE ###		*/
#include "Env.h"
#include "Closure.h"

/*		### DECLARATION FONCTION PRIVEE###	*/
static void copy_global(Env env, List global);
static void copy_local(Env env, List local);
/*		### DEFINITION FONCTION ###		*/

Env empty_env(){
	Env e = malloc(sizeof(struct _env));
	e->global_env = NULL;
	e->local_env = NULL;
	e->list_to_pg = NULL;
	return e;
}

void push_local_var(Env env, const char* ident, Value value){
	/* create new cell*/

	Cell* cell = malloc(sizeof(Cell));
	cell->name = strdup(ident);
	cell->value = value;
	
	/*insertion in head*/
	cell->next = env->local_env;
	env->local_env = cell;
}

void push_global_var(Env env, const char* ident, Value value){
	/* create new cell*/
	Cell* cell = malloc(sizeof(Cell));
	cell->name = strdup(ident);
	cell->value = value;
	
	/*insertion in head*/
	cell->next = env->global_env;
	env->global_env = cell;	
	
	
	//~ display_env(env);
}

void edit_var(Env env, const char* name, Value value){
		for(List list = env->local_env; list != NULL; list = list->next){
		if(!strcmp(list->name, name)){
			list->value = value;
			return;
		}
	}
	
	for(List list = env->global_env; list != NULL; list = list->next){
		if(!strcmp(list->name, name)){
			list->value = value;
			return;
		}
	}
	
}

void push_closure(Env env, Closure cl){
	/* create new cell*/
	Closure_cell* cell = malloc(sizeof(Closure_cell));
	cell->closure = cl;
	
	/*insertion in head*/
	cell->next = env->list_to_pg;
	env->list_to_pg = cell;	
	
	
	//~ display_env(env);
}

Env deep_copy(Env env){
	Env ret = empty_env();
	copy_global(ret, env->global_env);
	copy_local(ret, env->local_env);
	return ret;
}

Env surface_copy(Env env){
	Env ret = empty_env();
	ret->global_env = env->global_env;
	ret->local_env = env->local_env;
	return ret;
}

void purge_local_env(Env env){
	List temp;
	
	for(List list = env->local_env; list != NULL; list = temp){
		temp = list->next;
		free(list->name);
		free(list);
	}
	env->local_env = NULL;
}

void purge_head(List *lst){
	// TODO check if head is an array or a closure and free it
	
	List next = (*lst)->next;
	free((*lst)->name);
	free(*lst);
	*lst = next;
}

void purge_env(Env env){
	List temp;
	
	for(List list = env->global_env; list != NULL; list = temp){
		temp = list->next;
		free(list->name);
		free(list);
	}
	
	for(List list = env->local_env; list != NULL; list = temp){
		temp = list->next;
		free(list->name);
		free(list);
	}
	Closure_list temp2;
	for(Closure_list list = env->list_to_pg; list != NULL; list = temp2){
		temp2 = list->next;
		free_closure(list->closure);
		free(list);
	}
	
	
	free(env);
}

Value acces_env(const Env env, const char* name){
	for(List list = env->local_env; list != NULL; list = list->next){
		if(!strcmp(list->name, name))
			return list->value;
	}
	
	for(List list = env->global_env; list != NULL; list = list->next){
		if(!strcmp(list->name, name))
			return list->value;
	}

	
	return (Value) -99999l; // ERRRRROR
}

void display_env(const Env env){
	printf("Global env:\n");
	for(List list = env->global_env; list != NULL; list = list->next){
		printf("\t%s\n", list->name);
	}
	
	printf("Local env:\n");
	for(List list = env->local_env; list != NULL; list = list->next){
		printf("\t%s\n", list->name);
	}
}

void copy_global(Env env, List global){
	if(NULL == global){
		return;
	}
	copy_global(env, global->next);
	push_global_var(env, global->name, global->value);
}

void copy_local(Env env, List local){
	if(NULL == local){
		return;
	}
	copy_local(env, local->next);
	push_local_var(env, local->name, local->value);
}

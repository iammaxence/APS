
/*		### BIBLIOTHEQUE ###		*/
#include "Ast.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*		### DECLARATION FONCTION PRIVEE###	*/
/*		### DEFINITION FONCTION ###		*/

AST createNode(AstTag tag, unsigned int nbElem, ...){
	AST ret = malloc(sizeof(struct _ast));
	ret->tag = tag;
	ret->size = nbElem;
	ret->child = malloc(sizeof(AST) * nbElem);
	ret->bonus = NULL;

	va_list intArgumentPointer;
	va_start(intArgumentPointer, nbElem);

	for(int i = 0; i < nbElem; i++){
		ret->child[i] = va_arg(intArgumentPointer, AST);
	}

	va_end(intArgumentPointer);

	return ret;
}
// ASTARGS1
AST createArrayFromList(AstTag tag , AST arg, AST args){
	AST ret = malloc(sizeof(struct _ast));
	ret->tag = tag;
	ret->size = 1 + args->size;
	ret->child = malloc(sizeof(AST) * (1+args->size));
	ret->bonus = NULL;
	
	ret->child[0]=arg;
	memcpy(&(ret->child[1]), &(args->child[0]), sizeof(AST)*args->size);

	free(args->child);
	free(args);

	return ret;
}



AST createInt(int value){
	AST ret = malloc(sizeof(struct _ast));

	ret->tag = PrimInt;
	ret->size = 0;
	ret->child = NULL;
	ret->bonus = malloc(sizeof(int));
	*((int*)ret->bonus) = value;
	
	return ret;
}

AST createBool(int value){
	AST ret = malloc(sizeof(struct _ast));

	ret->tag = PrimBool;
	ret->size = 0;
	ret->child = NULL;
	ret->bonus = malloc(sizeof(int));
	*((int*)ret->bonus) = value;
	
	return ret;
}

AST createPrimitiveType(TypeComp type){
	AST ret = malloc(sizeof(struct _ast));

	ret->tag = PrimType;
	ret->size = 0;
	ret->child = NULL;
	ret->bonus = malloc(sizeof(TypeComp));
	*((TypeComp*)ret->bonus) = type;
	
	return ret;
}

AST createClef(ClefEnum clef){
	AST ret = malloc(sizeof(struct _ast));

	ret->tag = PrimClef;
	ret->size = 0;
	ret->child = NULL;
	ret->bonus = malloc(sizeof(ClefEnum));
	*((ClefEnum*)ret->bonus) = clef;
	
	return ret;
}

AST createIdent(const char* str){
	AST ret = malloc(sizeof(struct _ast));

	ret->tag = PrimIdent;
	ret->size = 0;
	ret->child = NULL;
	ret->bonus = strdup(str);
	strcpy(ret->bonus, str);
	
	return ret;
}

void freeAst(AST ast){	
	for(int i = 0; i < ast->size; i++){
		freeAst(ast->child[i]);
	}
	free(ast->child);
	free(ast->bonus);
	free(ast);
}

#include "Ast.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main(){
  AST args= malloc(sizeof(AST));
  AST args0= malloc(sizeof(AST));

  args->child = malloc(sizeof(AST) * nbElem);

  AST arg=malloc(sizeof(AST));
  args->child[0]=arg;
  args->child[1]=args0;
}

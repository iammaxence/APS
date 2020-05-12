append([],Ys,Ys).
append([X|Xs],Ys,[X|Zs]) :- append(Xs,Ys,Zs).

assoc(X,[(X,V)|_],V).
assoc(X,[_|XVs],V) :- assoc(X,XVs,V).

/*Possible correction si problème 
 -> Test sur FUNREC
 -> test : ECHO f (f 31)
 -> test plus nombreux sur PROC
 -> test d'apply closure a faire
*/

/*PROG */
typeProg(E,prog(CMD),void):-
  typeCMDS(E,CMD,void).

/*****************CMD****************************/

/*Cas terminal CMDS*/
typeCMDS(_,[],void).

/*CMDS for State */
typeCMDS(E,[(states(EXPR))|CMDS],void):-
  typeState(E,EXPR,void),
  typeCMDS(E,CMDS,void).

/*CMDS for DEC */
typeCMDS(E,[(dec(EXPR))|CMDS],void):-
  typeDec(E,EXPR,VR),
  typeCMDS(VR,CMDS,void).

/********************DEC*************************/

/*CONST */
typeDec(G,const(C,TYPE,EXPR),VR):-
  typeExpr(G,EXPR,TYPE),
  VR=[(C,TYPE)|G].

/* FUN */

typeDec(E,fun(ID,[TARGS,TR],args(ARGS),EXPRS),ST):-
  append(ARGS,E,E2),
  typeExpr(E2,EXPRS,TR),
  ST=[(ID,[TARGS,TR])].

/* FUN REC */

typeDec(G,funrec(ID,[TARGS,TR],args(ARGS),EXPR),G1):-
	append(ARGS,G,G2),
	G3 = [(ID,[TARGS,TR])|G2],
	typeExpr(G3,EXPR,_), /* changement plus tard */
	G1=[(ID,[TARGS,TR])|G].


/*APS1 */

/* VAR */
typeDec(G, var(A,TYPE), G2):-
  G2=[(A,TYPE)|G].

/*PROC*/
typeDec(G,proc(ID,args(ARGS),BLOCK),VR):-
  append(ARGS,G,G1),
  typeProg(G1,BLOCK,void),
  typeArgs(ARGS,ARGSTYPE),
  VR=[(ID,ARGSTYPE)|G]. /* A verifier */

/*PROC REC*/
typeDec(G,procrec(ID,args(ARGS),BLOCK),VR):-
  typeArgs(ARGS,ARGSTYPE),
  append(ARGS,G,G1),
  G2=[(ID,ARGSTYPE)|G1], /* A verifier */
  typeProg(G2,BLOCK,void),
  VR=[(ID,ARGSTYPE)|G]. /* A verifier */


/*******************STATES**********************/

/*ECHO */
typeState(E,echo(EXPR),void):-
  typeExpr(E,EXPR,int). /* l’expression dont on veut afficher la valeur est de type int (Cours APS0) */

/* APS 1 */

/*SET */
typeState(E,set(ID, EXPR),void):-
  assoc(ID, E, TYPE),
  typeExpr(E, EXPR, TYPE).

/* IF BLOCK */
typeState(E, if(COND,BLOCK1,BLOCK2),void):-
  typeExpr(E,COND,bool),
  typeProg(E,BLOCK1,void),
  typeProg(E,BLOCK2,void).

/* WHILE */
typeState(E, while(COND,BLOCK),void):-
  typeExpr(E,COND,bool),
  typeProg(E,BLOCK,void).

/* CALL */
typeState(E,call(ID,ARGS),void):-
  assoc(ID,E,ARGSTYPE),
  verifArgs(E,ARGS,ARGSTYPE).

/*ABS */
typeExpr(G, closure(args(ARGS),EXPRS),RT) :-
  append(ARGS,G,G2),
  typeExpr(G2,EXPRS,RT).

/* APP */

typeExpr(E,apply(closure(args(LIST),EXPRS),exprs(ARGS)),TypeFunc):-
  fillEnv(E, LIST, E2),
  typeExpr(E2,closure(args(LIST),EXPRS),TypeFunc),
  typeArgs(ARGS,RESARGS),
  verifArgs(E2,E2,RESARGS).

typeExpr(G,apply(ident(A),ARGS),TF) :-
	assoc(ident(A),G,[ARGSTYPE,TF]),
	verifArgs(G,ARGS,ARGSTYPE).


/* Types Primitif */
typeExpr(_, true, bool).
typeExpr(_, false, bool).
typeExpr(_, int(_), int).

/* OPERATIONS BOOLEENNE */
typeExpr(G, not(A), bool) :- typeExpr(G, A, bool).
typeExpr(G, and(A, B), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).
typeExpr(G, or(A, B), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).
typeExpr(G, lt(A, B), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, eq(A, B), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).

/* OPERATIONS OPRIM*/
typeExpr(G, add(A,B), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, mul(A,B), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, div(A,B), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, sub(A,B), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

/* IDENT : renvoie le type d'un identifiant */
typeExpr(E,ident(X),Type):-
  assoc(ident(X),E,Type).

/* IF*/
typeExpr(G, if(A, B, C), X) :-
  typeExpr(G, A, bool),
  typeExpr(G, B, X),
  typeExpr(G, C, X).

/* Verification ARGS */
verifArgs(_,[],[]).
verifArgs(G,[ARG|ARGS],[ARGTYPE|ARGSTYPE]) :-
	typeExpr(G,ARG,ARGTYPE),
	verifArgs(G,ARGS,ARGSTYPE).

/* TYPE ARGS  a verifier
typeArgs(_,[]).
typeArgs(_,[(FI,TYPE)|REST]):-
  typeExpr(_,FI,TYPE),
  typeArgs(_,REST).
*/

typeArgs([],[]).
typeArgs([(FI,TYPE)|REST],[TYPE|TYPES]):-
  typeExpr(_,FI,TYPE),
  typeArgs(REST,TYPES).

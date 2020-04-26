append([],Ys,Ys).
append([X|Xs],Ys,[X|Zs]) :- append(Xs,Ys,Zs).

assoc(X,[(X,V)|_],V).
assoc(X,[_|XS],V) :- assoc(X,XS,V).

/*
Les problemes: - CONST f (int)->int [x:int] (add x 5); fonctionne pas
A faire : FUN REC, PROC REC
Or c'est ot ?

*/


/* Types Primitif */
typeExpr(_, true, bool).
typeExpr(_, false, bool).
typeExpr(_, int(_), int).

/* OPERATIONS BOOLEENNE */
typeExpr(G, not([A]), bool) :- typeExpr(G, A, bool).
typeExpr(G, and([A,B]), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).
typeExpr(G, or([A,B]), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).
typeExpr(G, lt([A,B]), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, eq([A,B]), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).

/* OPERATIONS OPRIM*/

typeExpr(G, add([A,B]), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, mul([A,B]), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, div([A,B]), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).

typeExpr(G, sub([A,B]), int):-
  typeExpr(G, A, int),
  typeExpr(G, B, int).


/* IDENT : renvoie le type d'un identifiant */
typeExpr(E,ident(X),Type):-
  assoc(ident(X),E,Type).

/*PROG */
typeProg(E,prog(CMD),void):-
  typeCMDS(E,CMD,void).

/*Cas terminal CMDS*/
typeCMDS(E,[],void).

/*CMDS for State */
typeCMDS(E,[(states(EXPR))|CMDS],void):-
  typeState(E,EXPR,void),
  typeCMDS(E,CMDS,void).
/*
typeCMDS(E,[cmds(states(EXPR))|CMDS],void):-
  typeState(E,EXPR,void),
  typeCMDS(E,CMDS,void).
*/

/*CMDS for DEC */
typeCMDS(E,[dec(EXPR)|CMDS],void):-
  typeDec(E,EXPR,VR),
  typeCMDS(VR,CMDS,void).

/*ECHO */
typeState(E,echo(EXPR),void):-
  typeExpr(E,EXPR,int). /* l’expression dont on veut afficher la valeur est de type int (Cours APS0) */

/*CONST */
typeDec(E,const(C,TYPE,EXPR),VR):-
  typeExpr(E,EXPR,TYPE),
  VR=[(C,TYPE)|E].

/* FUN */

typeDec(E,fun(ID,[TARGS,TR],args(ARGS),EXPRS),ST):-
  fillEnv(E,ARGS,RES),
  typeExpr(RES,EXPRS,TR),
  typeArgs(ARGS,RESARGS), /*probleme: arg(ident(n),int) au lieu de (ident(n),int)*/
  ST=[(ID,arrow(RESARGS,TR))].

/*FUN REC*/

/* IF*/
typeExpr(G, if(A, B, C), X) :-
  typeExpr(G, A, bool),
  typeExpr(G, B, X),
  typeExpr(G, C, X).

/*APS1 */

/* VAR */
typeDec(G, var(A,TYPE), G2):-
  G2=[(A,TYPE)|G].

/*PROC*/

typeDec(E,proc(ID,args(ARGS),BLOCK),VR):-
  fillEnv(E,ARGS,E2),
  typeProg(E2,BLOCK,void),
  typeArgs(ARGS,RESARGS),
  VR=[(ID,arrow(RESARGS,void))|E].

/*PROC REC*/

/*SET */

typeState(E,set(ID, EXPR),void):-
  assoc(ID, E, TYPE),
  typeExpr(E, EXPR, TYPE).

/* IF BLOCK */
typeState(E, if(bool(COND),BLOCK1,BLOCK2),void):-
  typeExpr(E,COND,bool),
  typeProg(E,BLOCK1,void),
  typeProg(E,BLOCK2,void).

/* WHILE */
typeState(E, while(bool(COND),BLOCK),void):-
  typeExpr(E,COND,bool),
  typeProg(E,BLOCK,void).

/* CALL */
typeState(E,call(ID,EXPR),void):-
  assoc(ID,E,arrow(ARGSTYPE,void)),
  typeExpr(E,EXPR,)

/*ABS */

typeExpr(E, closure(args(LIST),EXPRS),RT) :-
  fillEnv(E, LIST, E2),
  typeExpr(E2,EXPRS,RT).


/* APP */

typeExpr(E,apply(closure(args(LIST),EXPRS),exprs(ARGS)),TypeFunc):-
  fillEnv(E, LIST, E2),
  typeExpr(E2,closure(args(LIST),EXPRS),TypeFunc),
  typeArgs(ARGS,RESARGS),
  verifArgs(E2,E2,RESARGS).

/* Appel de fonction avec args ex: (f 39) */
typeExpr(E,apply(ident(F), ARGS),TYPEF) :-
  typeArgs(ARGS,ARGSTYPE),
  verifArgs(E,ARGS,ARGSTYPE).

/*Cas d'un prim dans une fonction */
typeExpr(E, apply(ident(ID), exprs([A,B])), TR):-
  typeExpr(E,A,TypeA),
  typeExpr(E,B,TypeB). /* Verifier si se sont bien des int */

/* Cas OPRIM */
typeExpr(E, apply(ident(ID), exprs([A,B,C])), TR):-
  typeExpr(E,ID(A,B,C),TR).

/* Fin APP */

/*Cas terminal pour les types args */
typeArgs([],[]).
typeArgs([],RESARGS).

/*cas où les args sont tel que : arg(ident(n),int) */
typeArgs([(ID,TYPEARG)|REST],TYPEARG):- /* Remplacer TYPEARG par RESARGS si probleme */
  typeExpr(_,ID,TYPE),
  typeArgs(REST,[TYPEARG|RESARGS]).

/* le cas des exprs : (ident(n),int) */
typeArgs([FI|REST],[TYPE|RESARGS]):-
  typeExpr(_,FI,TYPE),
  typeArgs(REST,RESARGS).

/*Autre cas si un seul element*/
typeArgs(FI,TYPE):-
  typeExpr(_,FI,TYPE).

verifArgs(_,[],[]).
verifArgs(_,_,[]).
verifArgs(_,[TFI|TREST],[TAFI|TAREST]):-
  typeExpr(_,TFI,TYPE),
  typeCheck(TYPE,TAFI),
  verifArgs(_,TREST,TAREST).

verifArgs(_,A,B):- /* cas pour un seul argument, pas ouf*/
  typeExpr(_,A,TYPE),
  typeCheck(TYPE,B).
/*
verifArgs(_,[(_,TYPE)|TREST],[TAFI|TAREST]):-
  typeCheck(TYPE,TAFI),
  verifArgs(_,TREST,TAREST).
*/
typeCheck(T,T).

fillEnv(G, [], G).
fillEnv(G, [(ID, TYPE)|TL], G2) :- fillEnv([(ID, TYPE)|G],TL, G2).
/*fillEnv(G, [arg(ident(ID), TYPE)|TL], G2) :- fillEnv([(ID, TYPE)|G],TL, G2).*/

statesEcho(G, echo(E)) :- typeExpr(G, E, int).

/* decl(G, arg(ident(NAME), TYPE)) :- append([(NAME,TYPE)],G, G3). */

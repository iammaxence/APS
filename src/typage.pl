append([],Ys,Ys).
append([X|Xs],Ys,[X|Zs]) :- append(Xs,Ys,Zs).

assoc(X,[(X,V)|_],V).
assoc(X,[_|XVs],V) :- assoc(X,XVs,V).


/* ================================================================== */

typeExpr(_, true, bool).
typeExpr(_, false, bool).

typeExpr(G, not(A), bool) :- typeExpr(G, A, bool).
typeExpr(G, and(A, B), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).
typeExpr(G, or(A, B), bool) :- typeExpr(G, A, bool), typeExpr(G, B, bool).

typeExpr(G,prim(OP)):-typeExpr(G,OP)

typeExpr(G, add(EXPR), int) :- typeExpr(G, A, int), typeExpr(G, B, int).


/* ================================================================== */

typeExpr(_, int(_), int).
typeExpr(G, lt(A, B), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, eq(A, B), bool) :- typeExpr(G, A, int), typeExpr(G, B, int).

typeExpr(G, add(A, B), int) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, mul(A, B), int) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, div(A, B), int) :- typeExpr(G, A, int), typeExpr(G, B, int).
typeExpr(G, sub(A, B), int) :- typeExpr(G, A, int), typeExpr(G, B, int).

typeExpr(G, if(A, B, C), X) :- typeExpr(G, A, bool), typeExpr(G, B, X), typeExpr(G, C, X).
typeExpr(G, closure(args([FIRST|REST]), EXPR), G2) :- fillEnv(G, [FIRST], G2).
typeExpr(G, ident(NAME), TYPE) :- assoc(NAME, G, TYPE).

fillEnv(G, [], G).
fillEnv(G, [arg(ident(ID), TYPE)|TL], G2) :- fillEnv([(ID, TYPE)|G],TL, G2).

/* ============================================================== */
typeProg(ENV, prog(CMDS), void) :- typeCmds(ENV, CMDS, void).


typeCmds(ENV, states(STATES), void) :- typeStates(ENV, STATES, void).
typeCmds(ENV, dec(DEC), cmds(CMDS), void) :- typeDec(ENV, DEC, void, ENV2), typeCmds(ENV2, CMDS, void).
typeCmds(ENV, states(STATES), cmds(CMDS), void) :- typeStates([], STATES), typeCmds(ENV, CMDS, void).

typeStates(G, echo(E), void) :- typeExpr(G, E, int).

typeDec(ENV, dec(ident(NAME), TYPE, VAL), void) :- fillEnv([NAME, TYPE], ENV, ENV2), typeExpr(ENV2, VAL, TYPE).

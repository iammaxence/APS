%{
/* tpc.lex */
#include "Enum.h"
#include "Ast.h"
#include "aps.tab.h"
int cmp_ligne = 1;
extern int error_code;

%}

%option nounput
%option noinput

%x commentaire


%%
\n 									cmp_ligne++;
\\\n 								cmp_ligne++;

"/*" 								BEGIN(commentaire);
<commentaire>"*"+"/" 				BEGIN(INITIAL);
<commentaire>. ;
<commentaire>\n 					cmp_ligne++;
"//"+.*\n 							cmp_ligne++;

IF 									return IF;
CONST								return CONST;
FUN									return FUN;
REC									return REC;
ECHO								return _ECHO;

true								{yylval.cbool = 1; 		return CBOOL;}
false								{yylval.cbool = 0; 		return CBOOL;}
not 								{yylval.clef = _not; 	return CLEF;}
and 								{yylval.clef = _and; 	return CLEF;}
or  								{yylval.clef = _or; 	return CLEF;}
eq  	   							{yylval.clef = _eq; 	return CLEF;}
lt  								{yylval.clef = _lt; 	return CLEF;}
add 								{yylval.clef = _add; 	return CLEF;}
sub 								{yylval.clef = _sub; 	return CLEF;}
mul 								{yylval.clef = _mul; 	return CLEF;}
div 								{yylval.clef = _div; 	return CLEF;}
bool								{yylval.type.primType = t_bool;
										return TYPE;}
int									{yylval.type.primType = t_int;
										return TYPE;}
									
									
[0-9]+ 								{sscanf(yytext, "%d", &(yylval.num)); return NUM;}	
[a-zA-Z_][_a-zA-Z0-9]*  			{strcpy(yylval.ident, yytext) ;return IDENT;}
						
						
						

[\[\]();:,*->] 					return yytext[0]; /*Autre truc autorisé*/


[ \t] /*truc qu'on ignore plus ou moins*/
. {fprintf(stderr, "Unrecognized caracter [%s%c%s] \nline %d\n",KRED, yytext[0],KWHT, cmp_ligne); error_code+=1; /*Truc pas autorisé*/ 
	error_code++;}


%%

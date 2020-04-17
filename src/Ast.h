#ifndef __AST__
#define __AST__

#include "Enum.h"
#include <stdarg.h>

typedef enum{
	ASTProg,
	ASTCMDS0,
	ASTCMDS1,
	ASTCMDS2,
	ASTStates,
	ASTStates1,
	ASTStates2,
	ASTStates3,
	ASTStates4,
	ASTDEC0,
	ASTDEC1,
	ASTDEC2,
	ASTDEC3,
	ASTDEC4,
	ASTDEC5,
	ASTTYPECompo,
	ASTTYPES0,
	ASTTYPES1,
	ASTARGS0,
	ASTARGS1,
	ASTARG0,
	ASTEXPR0,
	ASTEXPR1,
	ASTEXPR2,
	ASTEXPR3,
	ASTEXPRS0,
	ASTEXPRS1,
	PrimInt,
	PrimBool,
	PrimIdent,
	PrimType,
	PrimClef
}AstTag;

typedef struct _ast{
	AstTag tag;
	int size;
	struct _ast** child;
	void* bonus;
}*AST;

AST createNode(AstTag tag, unsigned int nbElem, ...);

AST createArrayFromList(AstTag tag , AST arg, AST args);

AST createInt(int value);

AST createBool(int value);

AST createPrimitiveType(TypeComp type);

AST createIdent(const char* str);

AST createClef(ClefEnum clef);

void freeAst(AST ast);

#endif /* __ENUM__ */

/*

switch(tag){
	case(ASTProg): break;
	case(ASTCMDS0): break;
	case(ASTCMDS1): break;
	case(ASTCMDS2): break;
	case(ASTStates): break;
	case(ASTDEC0): break;
	case(ASTDEC1): break;
	case(ASTDEC2)): break;
	case(ASTTYPECompo): break;
	case(ASTTYPES0): break;
	case(ASTTYPES1): break;
	case(ASTARGS0): break;
	case(ASTARGS1): break;
	case(ASTARG0): break;
	case(ASTEXPRNum): break;
	case(ASTEXPRIdent): break;
	case(ASTEXPR0): break;
	case(ASTEXPR1): break;
	case(ASTEXPR2): break;
	case(ASTEXPR3): break;
	case(PrimInt): break;
	case(PrimBool): break;
	case(PrimIdent): break;
	case(PrimType): break;
	case(PrimClef): break;

}

*/

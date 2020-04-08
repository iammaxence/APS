#ifndef __ENUM__
#define __ENUM__

/*		### BIBLIOTHEQUE ###		*/
#include <assert.h>

/*		### MACRO ###		*/
#ifndef KRED
#define KRED  "\033[1m\033[31m"
#define KWHT  "\x1B[0m"
#define KMAG  "\033[1m\033[35m"
#endif


/*		### STRUCTURE ###		*/

typedef enum{
	t_int,
	t_bool
}TypeEnum;

typedef struct{
	TypeEnum primType;
}TypeComp;

typedef enum{
	_not,
	_and,
	_or,
	_eq,
	_lt,
	_add,
	_sub,
	_mul,
	_div
}ClefEnum;

/*		### DECLARATION FONCTION ###	*/

void displayClefEnum(ClefEnum clef);

void displayTypeComp(TypeComp comp);

#endif /* __ENUM__ */

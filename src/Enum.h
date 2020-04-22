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
	t_bool,
	t_void,
	t_array
}TypeEnum;

typedef struct _tc{
	TypeEnum primType;
	
	// if t_array
	unsigned long int size;
	struct _tc* sub_array;
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

TypeComp createTypeComp(TypeEnum primType, unsigned long int size, TypeComp* sub_array);

void displayClefEnum(ClefEnum clef);

void displayTypeComp(TypeComp comp);

#endif /* __ENUM__ */

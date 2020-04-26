/*		### BIBLIOTHEQUE ###		*/
#include "Enum.h"
#include <stdio.h>
#include <assert.h>

/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/

void displayClefEnum(ClefEnum clef){
	switch(clef){
		case(_not): printf("not"); break;
		case(_and): printf("and"); break;
		case(_or):  printf("or");  break;
		case(_eq):  printf("eq");  break;
		case(_lt):  printf("lt");  break;
		case(_add): printf("add"); break;
		case(_sub): printf("sub"); break;
		case(_mul): printf("mul"); break;
		case(_div): printf("div"); break;
		default:
			printf("ERR ");
	}
}

void displayTypeComp(TypeComp comp){
	switch(comp.primType){
		case(t_int): printf("int"); break;
		case(t_bool): printf("bool"); break;

	}
}

TypeComp createTypeComp(TypeEnum primType, unsigned long int size, TypeComp* sub_array){
	TypeComp tc;
	
	tc.primType = primType;
	
	if(primType == t_array){
		tc.size = size;
		tc.sub_array = sub_array;
	}
	else{
		tc.size = 0;
		tc.sub_array = NULL;
	}
	
}

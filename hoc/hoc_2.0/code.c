/**
 *	\file		code.c
 *	\brief		G E N E R A T I O N   DE   C O D E   &&
 *				M A C H I N E  D' E X E C U T I O N
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 */
#define _CODE_C_
#include "hoc.h"
/*********_********_*********_********_*********_********_***********_*********/
/*                  M A C H I N E  D' E X E C U T I O N                       */
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
/*********_********_*********_********_*********_********_***********_*********/
//					MANIPULATION DE LA PILE DES DONNEES
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
// Pile de données
static data_t pile[MAX_PILE];
// Sommet de la pile : pointe sur une adresse libre
static data_t *pilePtr = pile;
////////////////////////////////////////////////////////////////////////////////
// PILE-DATA-EXECUTION :    push(), pop()
/*********_********_*********_********_*********_********_***********_*********/
// Empiler une donnée sur la pile de données
void push(data_t d)
{
	if (pilePtr >= &pile[MAX_PILE])
		printMessageTag(17);
	*pilePtr++ = d;
}
/*********_********_*********_********_*********_********_***********_*********/
// Dépiler une donnée depuis la pile de données : sommet
data_t pop(void)
{
	data_t d;
	if (pilePtr <= pile)
		printMessageTag(18);
	d = *--pilePtr;
	return d;
}
////////////////////////////////////////////////////////////////////////////////
/*********_********_*********_********_*********_********_***********_*********/
//					MANIPULATION DE LA PILE D'INSTRUCTIONS
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS

static instr_t prog[MAX_PROG]; // La machine d'execution
static instr_t *progPtr;	   // Prochain emplacement libre
////////////////////////////////////////////////////////////////////////////////
// CODE-GENERATION :    code(), codeSy(), codeOp(), jump()
/*********_********_*********_********_*********_********_***********_*********/
// Installer une instruction machine dans la pile d'instructions
instr_t *code(instr_t frame)
{
	instr_t *adr = progPtr;
	if (progPtr >= &prog[MAX_PROG])
		printMessageTag(19);
	*progPtr++ = frame;
#ifdef DBG_CODE
	printf("Debug code %p\n", frame);
#endif
	return adr;
}
/////////////////////////////////////////////////////////////////////////////////
// CODE-EXECUTION:  execute(), parcoursPROG(), offsetPROG(), dbgAddrsMAC,
//                  _prompt(), initCode(), clearInput()
/*********_********_*********_********_*********_********_***********_*********/
extern int isFloat; // Nature de l'expression en cous d'analyse
/**
 *	\var		myError
 *	\brief	Numéro d'erreur
 *	\note		A déclarer avec l'attribut "extern" par les utilisateurs
 */
extern int myError;
// Executer un programme situé à l'adresse p dans la pile d'instructions
#include <stdio.h>
void execute(instr_t *p)
{
	for (PC = p; *PC != STOP;)
	{
		(*(*PC++))();
		if (myError)
			break;
	}
}
/*********_********_*********_********_*********_********_***********_*********/
// Initialiser les différents adresses :
//		pointeur pile de données : stackPtr
//		pointeur pile d'instructions : progPtr
// afficher prompt, etc
void initCode(void)
{
	pilePtr = pile;
	progPtr = prog;
	PC = prog;
	isFloat = 0;
	myError = 0;
	prompt();
}
////////////////////////////////////////////////////////////////////////////////

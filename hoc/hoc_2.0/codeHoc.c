/**
 *	\file		codeHoc.c
 *	\brief		G E N E R A T I O N   DE   C O D E
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 *  \brief      Fichier d'implémentations pour la génération de code
 *              <LI> Symboles Numériques : nombres, constantes, variables</LI>
 *              <LI> Opérations Algébriques</LI>
 *              <LI> Appels Fonctions prédéfinies</LI>
 *              <LI> Affichage résultat</LI>
 */
#define _CODE_HOC_C_
#include "hoc.h"
extern int isFloat;
/******************************************************************************/
/**
 *	\part	S Y M B O L E S   N U M E R I Q U E S 
 */
/**
 *  \fn         void intPush(void);
 *  \brief      Empiler la valeur d'un entier sur la pile d'exécution
 */
void intPush(void)
{
	data_t d;
	d.value = *(int *)(((pSymbol_t)*PC++)->U.pValue);
	push(d);
}
/**
 *  \fn         void floPush(void);
 *  \brief      Empiler la valeur d'un réel sur la pile d'exécution
 */
void floPush(void)
{
	data_t d;
	isFloat = 1;
	d.value = *(double *)((pSymbol_t)*PC++)->U.pValue;
	push(d);
}
/**
 *  \fn         void varPush(void);
 *  \brief      Empiler le symbole adressant une variable sur la pile d'exécution
 */
void varPush(void)
{
	data_t d;
	d.pSymb = ((pSymbol_t)*PC++);

	if (d.pSymb->clas != VAR)
		exeError("EXEC-E-301: varPush -- [%s] is not a variable", d.pSymb->name);
	push(d);
}
/**
 *  \fn         void varEval(void);
 *  \brief      Dépiler le symbole se trouvant au sommet de la pile d'exécution
 *              et empiler sa valeur
 */
void varEval(void)
{
	data_t d;
	d = pop();
	isFloat = d.pSymb->type == FVAR;
	if (d.pSymb->type == UNDEF)
		exeError("EXEC-E-302: varEval -- [%s] is undefined variable", d.pSymb->name);
	else if (isFloat)
		d.value = *(double *)(d.pSymb->U.pValue);
	else
		d.value = *(int *)(d.pSymb->U.pValue);
	push(d);
}
/**
 *  \fn         void varAssign(void);
 *  \brief      Dépiler le symbole se trouvant au sommet de la pile d'exécution
 *              et lui affecter la valeur du nouveau sommet
 */
void varAssign(void)
{
	data_t d1 = pop(), d2 = pop();
	if (d1.pSymb->clas != VAR)
		exeError("[%s] is not a variable, can't assign", d1.pSymb->name);
	else if (d1.pSymb->type == IVAR)
		*(int *)(d1.pSymb->U.pValue) = (int)d2.value;
	else if (d1.pSymb->type == FVAR)
		*(double *)(d1.pSymb->U.pValue) = d2.value;
	else
	{ // UNDEF
		d1.pSymb->type = (isFloat) ? FVAR : IVAR;
		d1.pSymb->size = (isFloat) ? sizeof(double) : sizeof(int);
		if (isFloat)
			d1.pSymb->U.pValue = allocFlo(d2.value);
		else
			d1.pSymb->U.pValue = allocInt((int)d2.value);
	}
	push(d2);
}
/******************************************************************************/
/**
 *	\part	O P E R A T I O N S   A L G E B R I Q U E S
 */
/**
 *  \fn         void add(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une addition et empiler le résultat
 */
void add(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value + d2.value;
	push(d1);
}
/**
 *  \fn         void sub(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une soustraction et empiler le résultat
 */
void sub(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value - d2.value;
	push(d1);
}
/**
 *  \fn         void mul(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une multiplication et empiler le résultat
 */
void mul(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d1.value * d2.value;
	push(d1);
}
/**
 *  \fn         void Div(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une division et empiler le résultat
 */
void Div(void)
{
	data_t d2 = pop(), d1 = pop();
	if (d2.value == 0.0)
		exeError("FPE***Division par zéro");
	d1.value = d1.value / d2.value;
	push(d1);
}
/**
 *  \fn         void negate(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, inverser le signe et empiler le résultat
 */
void negate(void)
{
	data_t d = pop();
	d.value = -d.value;
	push(d);
}
/**
 *  \fn         void power(void);
 *  \brief      Dépiler les deux nombres se trouvant au sommet de la pile
 *              d'exécution, effectuer une élévation à la puissance et empiler
 *              le résultat
 */
void power(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = pow(d1.value, d2.value);
	push(d1);
}

/******************************************************************************/
/**
 *	\part	A P P E L   DE   F O N C T I O N S   P R E D E F I N I E S 
 */
/**
 *  \fn         void predef(void);
 *  \brief      Dépiler le paramètre (se trouvant au sommet de la pile) de la
 *              fonction pointée par PC et empiler le résultat
 */
void predef(void)
{
	data_t d = pop();
	d.value = (*(pFctMath_t)((pSymbol_t)*PC++)->U.pFct)(d.value);
	push(d);
}

void equal(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d2.value == d1.value;
	push(d1);
}

void diff(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d2.value != d1.value;
	push(d1);
}

void inf(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d2.value > d1.value;
	push(d1);
}

void sup(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d2.value < d1.value;
	push(d1);
}

void infEqual(void)
{
	data_t d2 = pop(), d1 = pop();
	d1.value = d2.value >= d1.value;
	push(d1);
}

/******************************************************************************/
/**
 *	\part	A F F I C H A G E 
 */
/**
 *  \fn         void printExprCode(void);
 *  \brief      Dépiler le nombre se trouvant au sommet de la pile et l'afficher
 */
void printExprCode(void)
{
	data_t d = pop();
	printExpr(isFloat, d.value);
}
/*------\\//------\\//------\\//------\\//------\\//------\\//------\\/ F I N */

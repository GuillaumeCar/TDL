/**
 *	\file		symbol.c
 *	\brief		G E S T I O N   DES  S Y M B O L E S
 *	\brief	Implémentation de la gestion des symboles
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 */
#define _SYMBOL_C_
#include "hoc.h"
/**
 *	\var		_symbolList
 *	\brief		Liste des symboles
 */
pSymbol_t _symbolList = SYMBOL_NULL;
/**
 *	\fn			symbol_t* installSymbol (char* tokenName, short tokenClas, short tokenType,
 								short tokenSize, generic tokenPtrValue, char* tokenDesc) 
 *	\brief		Insérer un nouveau symbole en tête de la liste des symboles
 *	\return		pointeur sur symbole inséré
 */
symbol_t *installSymbol(char *tokenName, short tokenClas, short tokenType,
						short tokenSize, generic tokenPtrValue, char *tokenDesc)
{
	symbol_t *mySp = (symbol_t *)malloc(sizeof(symbol_t));
	mySp->clas = tokenClas;
	mySp->type = tokenType;
	mySp->size = tokenSize;
	if (tokenClas == PRG)
		mySp->U.pFct = tokenPtrValue;
	else
		mySp->U.pValue = tokenPtrValue;
	mySp->name = NULL;
	if (tokenName != NULL)
	{
		mySp->name = (char *)malloc(strlen(tokenName) + 1);
		strcpy(mySp->name, tokenName);
	}
	if (tokenDesc == NULL)
		mySp->desc = mySp->name;
	else
	{
		mySp->desc = (char *)malloc(strlen(tokenDesc) + 1);
		strcpy(mySp->desc, tokenDesc);
	}
	mySp->next = _symbolList;
	_symbolList = mySp;
	return mySp;
}
/**
 *	\fn			symbol_t* lookUpSymbol(const char* tokenName)
 *	\brief		Rechercher un symbole dans la liste des symboles
 *	\return		pointeur sur symbole recherché ou NULL si non trouvé
 */
symbol_t *lookUpSymbol(const char *tokenName)
{
	symbol_t *mySp = _symbolList;
	for (; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (strcmp(mySp->name, tokenName) == 0)
			return mySp;
	return SYMBOL_NULL; // Symbole non trouvé
}
/******************************************************************************/
/**
*	\fn         int* allocInt(int value); 
*	\brief		Alloue un esapce mémoire et range value dans cet espace. 
*	\return		Pointeur sur value
*/
int *allocInt(int value)
{
	int *pValue = (int *)malloc(sizeof(int));
	*pValue = value;
	return pValue;
}
/**
 *	\fn         pSymbol_t installIntSymbol(char *name, short clas, int value, char* desc)
 *	\brief		Installe un symbole de type ENTIER dans la table des symboles. 
 *	\param		name : nom de la variable ou NULL/"" pour les valeurs littérale
 *	\param		clas : DAT / VAR
 *	\param		value : valeur de l'entier installé
 *	\return		Pointeur sur le symbole installé
 */
pSymbol_t installIntSymbol(char *name, short clas, int value, char *desc)
{
	pSymbol_t mySp = installSymbol(name, clas, ENTIER, sizeof(int), allocInt(value), desc);
	return mySp;
}
/******************************************************************************/
/**
*	\fn         double* allocFlo(double value); 
*	\brief		Alloue un esapce mémoire et range value dans cet espace. 
*	\return		Pointeur sur value
*/
double *allocFlo(double value)
{
	double *pValue = (double *)malloc(sizeof(double));
	*pValue = value;
	return pValue;
}
/**
 *	\fn         pSymbol_t installFloSymbol(char *name, short clas, double value, char* desc) 
 *	\brief		Installe un symbole de type REEL dans la table des symboles. 
 *	\param		name : nom de la variable ou NULL/"" pour les valeurs littérale
 *	\param		clas : DAT / VAR
 *	\param		value : valeur du réel installé 
 *	\return		Pointeur sur le symbole installé
*/
pSymbol_t installFloSymbol(char *name, short clas, double value, char *desc)
{
	pSymbol_t mySp = installSymbol(name, clas, REEL, sizeof(double), allocFlo(value), desc);
	return mySp;
}

#include "defSymbols.c"

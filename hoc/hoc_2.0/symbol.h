/**
 *	\file		symbol.h
 *	\brief		G E S T I O N   DES  S Y M B O L E S
 *	\brief	Spécification de la gestion des symboles
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 */
#ifndef _SYMBOL_H_
#define _SYMBOL_H_
/**
 *	\typedef	generic
 *	\brief		Définition du type de donnéés générique
 */
typedef void *generic;
/**
 *	\typedef	pFctMath_t
 *	\brief		Définition du type pointeur de fonction
 */
typedef double (*pFctMath_t)();
/**
 *	\typedef	symbol_t
 * 	\brief		Définition du type de données "symbole" de type struct
 */
typedef struct symbol
{
    char *name; // Nom du symbole : identifiant
    short clas; // Classe du symbole : DAT, CST, VAR
    short type; // Type du symbole : ENTIER, REEL, UNDEF
    union
    {
        generic pValue;  // Pointeur générique sur la valeur du symbole
        pFctMath_t pFct; // Pointeur sur Fct
    } U;
    short size;          // Taille mémoire occupée par la valeur
    char *desc;          // Description du symbole
    struct symbol *next; // Pointeur sur symbole suivant
} symbol_t;
/**
 *	\typedef	pSymbol_t
 *	\brief		Définition du type de données "pointeur sur symbole"
 */
typedef struct symbol *pSymbol_t;
/**
 *	\def		SYMBOL_NULL
 *	\brief		Définition du symbole nul
 */
#define SYMBOL_NULL ((pSymbol_t)0)
/**
 *	\fn			symbol_t* installSymbol (char* tokenName, short tokenClas, short tokenType,
								short tokenSize, generic tokenPtrValue, char* tokenDesc) 
 * 	\brief		Insérer un nouveau symbole en tête de la liste des symboles
 *	\return		pointeur sur symbole inséré
 */
symbol_t *installSymbol(char *tokenName, short tokenClas, short tokenType,
                        short tokenSize, generic tokenPtrValue, char *tokenDesc);
/**
 *	\fn         symbol_t* lookUpSymbol (const char* tokenName)
 *	\brief		Rechercher un symbole dans la liste des symboles
 *	\return		pointeur sur symbole recherché ou NULL si non trouvé
 */
symbol_t *lookUpSymbol(const char *tokenName);
/******************************************************************************/
/**
*	\fn         int* allocInt(int value); 
*	\brief		Alloue un esapce mémoire et range value dans cet espace. 
*	\return		Pointeur sur value
*/
int *allocInt(int value);
/**
 *	\fn         pSymbol_t installIntSymbol(char *name, short clas, int value, char* desc)
 *	\brief		Installe un symbole de type ENTIER dans la table des symboles. 
 *	\param		name : nom de la variable ou NULL/"" pour les valeurs littérale
 *	\param		clas : DAT / VAR
 *	\param		value : valeur de l'entier installé
 *	\return		Pointeur sur le symbole installé
 */
pSymbol_t installIntSymbol(char *name, short clas, int value, char *desc);
/******************************************************************************/
/**
*	\fn         double* allocFlo(double value); 
*	\brief		Alloue un esapce mémoire et range value dans cet espace. 
*	\return		Pointeur sur value
*/
double *allocFlo(double value);
/**
 *	\fn         pSymbol_t installFloSymbol(char *name, short clas, double value, char* desc) 
 *	\brief		Installe un symbole de type REEL dans la table des symboles. 
 *	\param		name : nom de la variable ou NULL/"" pour les valeurs littérale
 *	\param		clas : DAT / VAR
 *	\param		value : valeur du réel installé 
 *	\return		Pointeur sur le symbole installé
*/
pSymbol_t installFloSymbol(char *name, short clas, double value, char *desc);
/**
 *	\fn         void installDefaultSymbols(void)
 *	\brief		Installe les symboles par défaut dans la table des symboles : 
 *				<UL><LI>Constantes : PI, E, ...</LI>
 *					<LI>Fonctions mathématiques : sin(), cos(), ...
 *				</UL>
 */
void installDefaultSymbols(void);
#endif /* _SYMBOL_H_ */

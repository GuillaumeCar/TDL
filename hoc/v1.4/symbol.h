/**
 *	\file		symbol.h
 *	\brief		Spécification de la gestion des symboles
 *	\date		22 Janvier 2021
 *	\author		Samir El Khattabi
 */
#ifndef _SYMBOL_H_
#define _SYMBOL_H_
/**
 *	\typedef	generic
 *	\brief		Définition du type de donnéés générique
 */
typedef void * generic;

typedef double (*pFctMath_t) ();

    /**
 *	\typedef	symbol_t
 * 	\brief		Définition du type de données "symbole" de type struct
 */
    typedef struct symbol
{
    char	*name;			// Nom du symbole : identifiant
    short	clas;			// Classe du symbole : DAT, CST, VAR
    short	type;			// Type du symbole : ENTIER, REEL, UNDEF
    char *  desc;
    union {
        generic pValue;     // Pointeur générique sur la valeur du symbole
        double (*pFct)();	// Pointeur sur Fct
    } U;
    short	size;			// Taille mémoire occupée par la valeur
    struct	symbol *next;	// Pointeur sur symbole suivant
} symbol_t;
/**
 *	\typedef	pSymbol_t
 *	\brief		Définition du type de données "pointeur sur symbole"
 */
typedef struct symbol* pSymbol_t;
/**
 *	\def		SYMBOL_NULL
 *	\brief		Définition du symbole nul
 */
#define SYMBOL_NULL ((pSymbol_t) 0)
/**
 * 	\fn			symbol_t* installSymbol (char* tokenName, short tokenClas, short tokenType,
                                            short tokenSize, generic pValue)
 * 	\brief		Insérer un nouveau symbole en tête de la liste des symboles
 *	\return		pointeur sur symbole inséré
 */
symbol_t* installSymbol (char* tokenName, short tokenClas, short tokenType, char * tokenDesc,
                        short tokenSize, generic tokenPtrValue);
/**
 *	\fn         symbol_t* lookUpSymbol (const char* tokenName)
 *	\brief		Rechercher un symbole dans la liste des symboles
 *	\return		pointeur sur symbole recherché ou NULL si non trouvé
 */
symbol_t* lookUpSymbol (const char* tokenName);
/**
 *	\fn         void installDefaultSymbols(void)
 *	\brief		Installe les symboles par défaut dans la table des symboles : 
 *				<UL><LI>Constantes : PI, E, ...</LI>
 *					<LI>Fonctions mathématiques : sin(), cos(), ...
 *				</UL>
 */
void installDefaultSymbols(void);
symbol_t *getSymbolList();
void printSymbolList();
#endif /* _SYMBOL_H_ */

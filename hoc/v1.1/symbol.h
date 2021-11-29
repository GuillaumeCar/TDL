#ifndef _SYMBOL_H_
#define _SYMBOL_H_

/**
* \struct generic
* \brief Définition du type de données générique
*/
typedef void *generic;
/**
* \typedef symbol_t
* \brief Définition du type de données "symbole" de type struct
*/
typedef struct symbol {
    char	*name;			// Nom du symbole : identifiant
    short	clas;			// Classe du symbole : DAT, CST, VAR
    short	type;			// Type du symbole : ENTIER, REEL, UNDEF
    union {
        generic pValue;     // Pointeur générique sur la valeur du symbole
        double (*pFct)();	// Pointeur sur Fct
    } U;
    short	size;			// Taille mémoire occupée par la valeur
    struct	symbol *next;	// Pointeur sur symbole suivant
} symbol_t;

/**
* \typedef pSymbol_t
* \brief Définition du type de données "pointeur sur symbole"
*/
typedef struct symbol *pSymbol_t;

/**
* \def SYMBOL_NULL
* \brief Définition du symbole nul
*/

#define SYMBOL_NULL ((pSymbol_t)0)

/**
* \fn symbol_t* installSymbol (char * tokenName, short tokenClas, short tokenType,
short tokenSize, generic pValue)
* \brief Insérer un nouveau symbole en tête de la liste des symboles
* \return Pointeur sur le symbole inséré */
symbol_t *installSymbol(char *tokenName, short tokenClas, short tokenType, short tokenSize, generic tokenPtrValue);

/**
* \fn symbol_t* lookUpSymbol (const char *tokenName)
* \brief Rechercher un symbole dans la liste des symboles
* \return pointeur sur symbole recherché ou NULL si non trouvé
*/
symbol_t *lookUpSymbol(const char *tokenName);

void installDefaultSymbols(void);

#endif
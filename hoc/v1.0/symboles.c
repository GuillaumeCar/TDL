#include "symboles.h"
#include <stdlib.h>
#include <string.h>

/**
* \var _symbolList
* \brief Liste des symboles
*/
static pSymbol_t _symbolList = SYMBOL_NULL;

/**
* \var _consts[]
* \brief Déclaration des variables (constantes mathématiques) prédéfinies
*/
static struct {
    char *cName; short cType;
    double cValue; char* cDesc;
}

_consts[] = {
    "PI",       REEL, 3.14159265358979323846, "Archimede's constant",
    "E",        REEL, 2.71828182845904523536, "Euler's constant",
    "GAMMA",    REEL, 0.57721566490153286060, "Another Euler's constant",
    "DEG",      REEL, 57.2957795130823208768, "360/2*Pi",
    "PHI",      REEL, 1.61803398874989484820, "Golden ratio",
    "MAXSTACK", ENTIER, 256, "Taille de la pile d'exe",
    "MAX_PROG", ENTIER, 2000, "Taille de la machine d'exe",
    NULL, 0, 0, NULL
};

symbol_t *installSymbol (char* tokenName, short tokenClas, short tokenType, short tokenSize, generic tokenPtrValue) {
    symbol_t *mySp = (symbol_t *) malloc(sizeof(symbol_t));
    mySp->clas = tokenClas;
    mySp->type = tokenType;
    mySp->size = tokenSize;
    mySp->pValue = tokenPtrValue;
    mySp->name = NULL; // Cas d’un symbole sans nom
    if (tokenName != NULL) {
        mySp->name = (char *) malloc(strlen(tokenName)+1);
        strcpy(mySp->name, tokenName); 
    }
    mySp->next = _symbolList;
    _symbolList = mySp;
    return mySp;
}


symbol_t *lookUpSymbol(const char *tokenName)
{
    symbol_t *mySp = _symbolList;
    for (; mySp != SYMBOL_NULL; mySp = mySp->next)
        if (strcmp(mySp->name, tokenName) == 0)
            return mySp;
    return SYMBOL_NULL; // token non trouvé
}

/**
* \fn void installDefaultSymbols (void)
* \brie fInstalle les symboles par défaut dans la table des symboles :
* <UL><LI>Constantes : PI, E, ...</LI>
* <LI>Fonctions mathématiques : sin(), cos(), ...
* </UL> 
*/
void installDefaultSymbols (void) {
    int * pInt;
    double *pFlo;
    for (int i = 0; _consts[i].cName!=NULL; i++) {
        if (_consts[i].cType == ENTIER) {
            pInt = (int *) malloc (sizeof(int));
            *pInt = (int) _consts[i].cValue;
            installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(int), pInt);
        }
        else if (_consts[i].cType == REEL) {
            pFlo = (double *) malloc (sizeof(double));
            *pFlo = _consts[i].cValue;
            installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(double), pFlo);
        }
    }
}


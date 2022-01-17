/**
 *	\file		symbol.c
 *	\brief		Implémentation de la gestion des symboles
 *	\date		22 Janvier 2021
 *	\author		Samir El Khattabi
 */
#define _SYMBOL_C_
#include "hoc.h"
/**
 *	\var		_symbolList
 *	\brief		Liste des symboles
 */
static pSymbol_t _symbolList = SYMBOL_NULL;
/**
 *	\fn			symbol_t* installSymbol (char* tokenName, short tokenClas, short tokenType,
                                            short tokenSize, generic pValue)
 *	\brief		Insérer un nouveau symbole en tête de la liste des symboles
 *	\return		pointeur sur symbole inséré
 */
symbol_t *installSymbol(char *tokenName, short tokenClas, short tokenType, char * tokenDesc,
                        short tokenSize, generic tokenPtrValue)
{
    symbol_t *mySp = (symbol_t *)malloc(sizeof(symbol_t));
    mySp->clas = tokenClas;
    mySp->type = tokenType;
    mySp->size = tokenSize;
    mySp->desc = tokenDesc;
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

symbol_t *getSymbolList() {
    symbol_t *mySp = _symbolList;
    return mySp;
}

void printSymbolList()
{
    pSymbol_t itr = _symbolList;
    printMessage(61);
    printMessage(60);
    printMessage(63);
    printMessage(60);
    char * str;
    do
    {
        // if (isPtrFunction(itr)) {
        //     printMessage(67, itr, strClas(itr->clas), strType(itr->type), itr->name, itr->U.pFct, itr->desc);
        // } else {
        //     char result[20];
        //     strValue(itr, result);
        //     printMessage(66, itr, strClas(itr->clas), strType(itr->type), itr->name, result, itr->desc);
        // }
        // printMessage(
        //     65, 
        //     itr, 
        //     itr->clas,
        //     itr->type, 
        //     itr->name, 
        //     "2",
        //     itr->desc
        // );
        printf(
            "\033[3G%14p\033[1C\033[22m%-8.8s\033[1C\033[1m%-7.7s\033[1C\033[22m %14.12s\033[1C\033[1m%14.14s\033[1C\033[22;3m%18.18s\n\n",
            itr,
            itr->clas,
            itr->type,
            itr->name,
            "-----",
            itr->desc
        );
        itr->U.pValue;
        itr = itr->next;
    } while (itr != SYMBOL_NULL);

    printMessage(62);
}

#include "defSymbols.c"

#include "symboles.h"
#include <stdlib.h>
#include <string.h>

/**
* \var _symbolList
* \brief Liste des symboles
*/
static pSymbol_t _symbolList = SYMBOL_NULL;



symbol_t *installSymbol(char *tokenName, short tokenType)
{
    symbol_t *mySp = (symbol_t *)malloc(sizeof(symbol_t));
    mySp->type = tokenType;
    mySp->name = (char *)malloc(strlen(tokenName) + 1);
    strcpy(mySp->name, tokenName);
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
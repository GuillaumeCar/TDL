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
symbol_t *installSymbol(char *tokenName, short tokenClas, short tokenType, char *tokenDesc,
                        short tokenSize, generic tokenPtrValue)
{
    symbol_t *mySp = (symbol_t *)malloc(sizeof(symbol_t));
    mySp->clas = tokenClas;
    mySp->type = tokenType;
    mySp->size = tokenSize;
    mySp->desc = tokenDesc;
    if (tokenClas == PRG) {
        mySp->U.pFct = tokenPtrValue;
    } else {
        mySp->U.pValue = tokenPtrValue;
    }

    mySp->name = NULL;

    if (tokenName != NULL) {
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
symbol_t *lookUpSymbol(const char *tokenName) {
    symbol_t *mySp = _symbolList;
    for (; mySp != SYMBOL_NULL; mySp = mySp->next) {
        if (strcmp(mySp->name, tokenName) == 0) {
            return mySp;
        }
    }

    return SYMBOL_NULL; // Symbole non trouvé
}

void printSymbolList() {
    pSymbol_t itr = _symbolList;

    while (itr != SYMBOL_NULL) {
        printMessage(68, itr->name, itr->desc);
        itr->U.pValue;
        itr = itr->next;
    }
}

void dbgSymbolList() {
    printMessage(61);
    printMessage(60);
    printMessage(63);
    printMessage(60);

    pSymbol_t itr = _symbolList;

    while (itr != SYMBOL_NULL) {
        if (isPRG(itr)) {
            printMessage(67, itr, strClas(itr->clas), strType(itr->type), itr->name, itr->U.pFct, itr->desc);
        } else {
            char result[20];
            strValue(itr, result);
            printMessage(66, itr, strClas(itr->clas), strType(itr->type), itr->name, result, itr->desc);
        }

        itr->U.pValue;
        itr = itr->next;
    }

    printMessage(62);
}

char *strClas(short clas) {
    if (clas == CST) {
        return "CST";
    } else if (clas == PRG) {
        return "PRG";
    }
    return "UNKNOWN";
}

char *strType(short type) {
    switch (type) {
    case REEL:
        return "REEL";
        break;
    case ENTIER:
        return "ENTIER";
        break;
    case PREDEF:
        return "PREDEF";
        break;
    case ADD:
        return "ADD";
        break;
    case SUB:
        return "SUB";
        break;
    case MUL:
        return "MUL";
        break;
    case DIV:
        return "DIV";
        break;
    case PO:
        return "PO";
        break;
    case PF:
        return "PF";
        break;
    default:
        return "DEFAULT";
        break;
    }
}

short isPRG(pSymbol_t symbol) {
    if (symbol->clas == PRG) {
        return 1;
    } else {
        return 0;
    }
}

void strValue(pSymbol_t symbol, char *resultat) {
    switch (symbol->type) {
        case REEL:
            snprintf(resultat, 14, "%f", *((double *)symbol->U.pValue));
            break;
        case ENTIER:
            snprintf(resultat, 14, "%d", *((int *)symbol->U.pValue));
            break;
        default:
            break;
    }
}

#include "defSymbols.c"

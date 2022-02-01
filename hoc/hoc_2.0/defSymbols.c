/**
 *	\file		defSymbols.c
 *	\brief		S Y M B O L E S     P R E D E F I N I S
 *	\brief	Déclaration des symboles prédéfinis et chargement dans la TS
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
*/
#include "hoc.tab.h"
/**
 *	\var		_consts[]
 *	\brief		Déclaration des variables (constantes mathématiques) prédéfinies
 */
static struct
{
    char *cName;
    short cType;
    double cValue;
    char *cDesc;
} _consts[] = {
    "PI", REEL, 3.14159265358979323846, "Archimede's constant",
    "E", REEL, 2.71828182845904523536, "Euler's constant",
    "GAMMA", REEL, 0.57721566490153286060, "Another Euler's constant",
    "DEG", REEL, 57.2957795130823208768, "360/2*Pi",
    "PHI", REEL, 1.61803398874989484820, "Golden ratio",
    "MAXSTACK", ENTIER, 256, "Taille de la pile d'exe",
    "MAX_PROG", ENTIER, 2000, "Taille de la machine d'exe",
    NULL, 0, 0, NULL};
/**
 *	\var		_predef[]
 *	\brief		Tableau des fonctions mathématiques prédéfinies
 *	\note		Ces fonctions utilisent des appels à la bibliothéque classique : libm
 *	\note		Certaines de ces fonctions utilisent une fonction wrapper qui permet
 *	\note		de gérer les erreurs de paramètres ou de résultat : Log, Log10, Exp, Pow, Sqrt
 */
static struct
{
    char *pdName;
    double (*pdPtrFunc)();
    char *pdDesc;
} _preDefs[] = {
    "sin", sin, "sinus",
    "cos", cos, "cosinus",
    "tg", tan, "tangente",
    "log", log, "logarithme neperien",    // gestion erreur
    "log10", log10, "logarithme base 10", // gestion erreur
    "exp", exp, "exponentielle",          // gestion erreur
    "pow", pow, "puissance",              // gestion erreur
    "sqrt", sqrt, "racine carree",        // gestion erreur
    "abs", fabs, "valeur absolue",
    NULL, 0};
/**
 *	\var		_opExpr[]
 *	\brief		Tableau des opérations arithmétiques
 *	\note		Les opérateurs sont gérés par des fonctions
 */
static struct
{
    char *opName;
    short opType;
    void (*opPtrFunc)();
    char *opDesc;
} _opExpr[] = {
    "+", ADD, add, "addition",
    "-", SUB, sub, "soustraction",
    "*", MUL, mul, "multiplication",
    "/", DIV, Div, "division",
    "#", POW, power, "expnentiation",
    "(", PO, 0, "(",
    ")", PF, 0, ")",
    //	Opérateurs non algébriques
    "?", PR_TS, printSymbolList, "affichage table des symboles",
    "print", PR_TS, printSymbolList, "affichage table des symboles",
    "??", PR_TS2, printSymbolListByClass, "affichage table des symboles par classe",
    "@", DBG_TS, dbgSymbolList, "affichage table des symboles et leurs informations",
    NULL, 0, NULL, NULL};

/**
 *	\var		_opLogi[]
 *	\brief		Tableau des opérations arithmétiques
 *	\note		Les opérateurs sont gérés par des fonctions
 */
static struct
{
    char *opName;
    short opType;
    void (*opPtrFunc)();
    char *opDesc;
} _opLogi[] = {
    "==", EQU, equal, "Equalité",
    "!=", DIFF, diff, "Différence",
    "<", INF, inf, "Inférieur",
    ">", SUP, sup, "Supérieur",
    "<=", INFEQU, infEqual, "Inférieur ou équal",
    NULL, 0, NULL, NULL};
/**
 *	\fn         void installDefaultSymbols (void)
 *	\brief		Installe les symboles par défaut dans la table des symboles : 
 *				<UL><LI>Constantes : PI, E, ...</LI>
 *					<LI>Fonctions mathématiques : sin(), cos(), ...
 *				</UL>
 */
void installDefaultSymbols(void)
{
    int i;
    int *pInt;
    double *pFlo;
    // Installation des constantes
    printMessage(3);
    for (i = 0; _consts[i].cName != NULL; i++)
        if (_consts[i].cType == ENTIER)
        {
            pInt = (int *)malloc(sizeof(int));
            *pInt = (int)_consts[i].cValue;
            installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(int), pInt, _consts[i].cDesc);
        }
        else if (_consts[i].cType == REEL)
        {
            pFlo = (double *)malloc(sizeof(double));
            *pFlo = _consts[i].cValue;
            installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(double), pFlo, _consts[i].cDesc);
        }
    // Installation des fonctions prédéfinies
    printMessage(4);
    for (i = 0; _preDefs[i].pdName != NULL; i++)
        installSymbol(_preDefs[i].pdName, PRG, PREDEF, sizeof(double), (generic)_preDefs[i].pdPtrFunc, _preDefs[i].pdDesc);
    // Installation des opérateurs
    printMessage(5);
    for (i = 0; _opExpr[i].opName != NULL; i++)
        installSymbol(_opExpr[i].opName, PRG, _opExpr[i].opType, sizeof(double), (generic)_opExpr[i].opPtrFunc, _opExpr[i].opDesc);
    for (i = 0; _opLogi[i].opName != NULL; i++)
        installSymbol(_opLogi[i].opName, PRG, _opExpr[i].opType, sizeof(double), (generic)_opLogi[i].opPtrFunc, _opLogi[i].opDesc);
    printMessage(9);
}

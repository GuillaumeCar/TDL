/**
 *	\file		defSymbols.c
 *	\brief		S Y M B O L E S     P R E D E F I N I S
 *	\brief		Déclaration des symboles prédéfinis et chargement dans la TS
 *	\date		22 Janvier 2021
 *	\author		Samir El Khattabi
*/                 
#include "hoc.tab.h"
/**
 *	\var		_consts[]
 *	\brief		Déclaration des variables (constantes mathématiques) prédéfinies
 */
static struct { char *cName; short cType; double cValue; char* cDesc;}
_consts[] = {
	"PI",       REEL,      3.14159265358979323846,     "Archimede's constant",
	"E",        REEL,      2.71828182845904523536,     "Euler's constant",
	"GAMMA",    REEL,      0.57721566490153286060,     "Another Euler's constant",
	"DEG",      REEL,      57.2957795130823208768,     "360/2*Pi",
	"PHI",      REEL,      1.61803398874989484820,     "Golden ratio",
	"MAXSTACK", ENTIER,    256,                        "Taille de la pile d'exe",
	"MAX_PROG", ENTIER,    2000,                       "Taille de la machine d'exe",
	NULL,       0,          0,                         NULL
};
/**
 *	\var		_predef[]
 *	\brief		Tableau des fonctions mathématiques prédéfinies
 *	\note		Ces fonctions utilisent des appels à la bibliothéque classique : libm
 *	\note		Certaines de ces fonctions utilisent une fonction wrapper qui permet
 *	\note		de gérer les erreurs de paramètres ou de résultat : Log, Log10, Exp, Pow, Sqrt
 */
static struct { char *pdName; double (*pdPtrFunc) ();  char* pdDesc; }
_preDefs[] = {
	"sin",      sin,    "sinus",
	"cos",      cos,    "cosinus",
	"tg",       tan,    "tangente",
	"log",      log,    "logarithme neperien",  // gestion erreur
	"log10",    log10,  "logarithme base 10",   // gestion erreur
	"exp",      exp,    "exponentielle",        // gestion erreur
	"pow",      pow,    "puissance",            // gestion erreur
	"sqrt",     sqrt,   "racine carree",        // gestion erreur
	"abs",      fabs,   "valeur absolue",
	NULL,       0
};
/**
 *	\fn         void installDefaultSymbols (void)
 *	\brief		Installe les symboles par défaut dans la table des symboles : 
 *				<UL><LI>Constantes : PI, E, ...</LI>
 *					<LI>Fonctions mathématiques : sin(), cos(), ...
 *				</UL>
 */
void installDefaultSymbols (void) {
	int i;
	int * pInt;
	double *pFlo;
	
	for (i = 0; _consts[i].cName!=NULL;  i++)
		if (_consts[i].cType==ENTIER) {
			pInt    = (int *) malloc (sizeof(int));
			*pInt   = (int) _consts[i].cValue;
			installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(int), pInt);
		} else if (_consts[i].cType==REEL) {
			pFlo    = (double *) malloc (sizeof(double));
			*pFlo   = _consts[i].cValue;
			installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(double), pFlo);
		}
	for (i = 0; _preDefs[i].pdName != NULL; i++)
		installSymbol(_preDefs[i].pdName, PRG, PREDEF,sizeof(double), (generic) _preDefs[i].pdPtrFunc);

}

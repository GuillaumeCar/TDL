/**
 *	\file		io.h
 *	\brief		G E S T I O N   DES   S O R T I E S  &   E R R E U R S
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
*/
#ifndef _IO_H_
#define _IO_H_
/**
 *	\part		G E S T I O N   DES  S O R T I E S
 */
/**
 *	\fn 		void prompt(void)
 *	\brief		Affichage du prompt et incrémentation de la ligne courante
 */
void prompt(void);
/**
 *	\fn 		void printExpr(int isFloat, double val)
 *	\brief		Affichage du résultat (val) d'une expression
 */
void printExpr(int isFloat, double val);
/**
 *	\fn 		void printMessage(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessage(int iMsg, ...);
/**
 *	\fn 		void printMessageTag(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini et son TAG avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessageTag(int iMsg, ...);
/**
 *	\part		G E S T I O N   DES  E R R E U R S
 */
/**
 *	\fn			void yyerror(char *strErr, ...)
 *	\brief		Fonction de gestion des erreurs de syntaxe
 *	\note		invoquée automatiquement par yyparse() sur l'unité syntaxique "error"
 *	\note		peut être invoquée explicitement
 */
void yyerror(char *strErr, ...);
/**
 *	\fn			void lexError(const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs lexicales
 *	\note		A invoquer explicitement depuis les règles de yylex()
 *	\note		Le prototype peut être adapté à votre besoin
 */
void lexError(const char *strErr, ...);
/**
 *	\fn			void exeError (const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs d'exécution de fonctions importées,
 *	\note		comme les fonctions mathématiques prédéfinies (à base de errno), 
 *	\note		et les futurs traitements qui seront implémentés
 *	\note		Le prototype peut être adapté à votre besoin
 */
void exeError(const char *strErr, ...);
/**
 *	\part		G E S T I O N   DES  T R A C E S
 */
/**
 *	\fn			void printSymbolList(void)
 *	\brief		Afficher les symboles définis par classe et type
 */
void printSymbolList(void);
/**
 *	\fn			void printSymbolListByClass(void)
 *	\brief		Afficher les symboles définis par classe et type
 */
void printSymbolListByClass(void);
/**
 *	\fn			void dbgSymbol(symbol_t * symbPtr)
 *	\brief		Afficher les attributs du symbole fourni en paramètre
 *	\note		symbPtr : pointeur sur le symbole
 */
void dbgSymbol(symbol_t *symbPtr);
/**
 *	\fn			dbgSymbolList(void)
 *	\brief		Afficher les attributs du tous les symboles
 *	\note		Les données seront affichées sous forme d'un tableau :
 *				entête/pied, 1 ligne par symbole (adresse mémoire, nom, classe,
 *				type, adresse mémoire valeur, valeur)
 */
void dbgSymbolList(void);

short isPRG(pSymbol_t symbol);
void strValue(pSymbol_t symbol, char *resultat);
#endif

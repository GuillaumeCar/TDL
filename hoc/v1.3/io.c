/**
 *	\file		io.c
 *	\brief		G E S T I O N   DES   S O R T I E S  &   E R R E U R S
 *	\date		26 Janvier 2021
 *	\author		Samir El Khattabi
 */
#define _IO_C_
#include "hoc.h"
#include "msgFmt.c"
/**
 *	\var        progName
 *	\brief		Nom du programme
 */
extern char *progName;
/**
 *	\var		lineNo
 *	\brief		Ligne courante
 *	\note		A déclarer avec l'attribut "extern" par les utilisateurs
 */
int lineNo = 0;
/**
 *	\part		G E S T I O N   DES  S O R T I E S
 */
/**
 *	\fn 		void prompt(void)
 *	\brief		Affichage du prompt et incrémentation de la ligne courante
 */
void prompt(void) {
	printMessage(10);
	lineNo++;
}
/**
 *	\fn 		void printExpr(int isFloat, double val)
 *	\brief		Affichage du résultat (val) d'une expression
 */
void printExpr(int isFloat, double val) {
    if (isFloat) printMessage(12, val);
    else printMessage(11,(int)val);
}
/**
 *	\fn 		void printMessage(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessage(int iMsg, ...) {
	va_list pArg;
		va_start(pArg, iMsg);
		prMsgFmtWithStyle(_msgFmt[iMsg].iStyle, _msgFmt[iMsg].msg, pArg);
	va_end(pArg);
}
/**
 *	\fn 		void printMessageTag(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini et son TAG avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessageTag(int iMsg, ...) {
	va_list pArg;
	va_start(pArg, iMsg);
		prTagAndMsgFmtWithStyle(_msgFmt[iMsg].iStyle, _msgFmt[iMsg].msg, pArg);
	va_end(pArg);
}
/**
 *	\part		G E S T I O N   DES  E R R E U R S
 */
/**
 *	\fn			void yyerror(char *strErr, ...)
 *	\brief		Fonction de gestion des erreurs de syntaxe
 *	\note		invoquée automatiquement par yyparse() sur l'unité syntaxique "error"
 *	\note		peut être invoquée explicitement
 */
void yyerror(char *strErr, ...) {
	va_list pArg;
	va_start(pArg, strErr);
    	prTagAndMsgFmtWithStyle(5, strErr, pArg);
	va_end(pArg);
	printLn();
    //printMessageTag(47, strErr);
}
/**
 *	\fn			void lexError(const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs lexicales
 *	\note		A invoquer explicitement depuis les règles de yylex()
 *	\note		Le prototype peut être adapté à votre besoin
 */
void lexError (const char* strErr, ...) {
	va_list pArg;
	va_start(pArg, strErr);
		prTagAndMsgFmtWithStyle(6, strErr, pArg);
	va_end(pArg);
	printLn();
	//printMessageTag(48, strErr);
}
/**
 *	\fn			void exeError (const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs d'exécution de fonctions importées,
 *	\note		comme les fonctions mathématiques prédéfinies (à base de errno), 
 *	\note		et les futurs traitements qui seront implémentés
 *	\note		Le prototype peut être adapté à votre besoin
 */
void exeError (const char* strErr, ...) {
	va_list pArg;
	va_start(pArg, strErr);
		prTagAndMsgFmtWithStyle(7, strErr, pArg);
	va_end(pArg);
	printLn();
	//printMessageTag(49, strErr);
}



/**
 *	\file		io.c
 *	\brief		G E S T I O N   DES   S O R T I E S  &   E R R E U R S
 *	\date		24 Janvier 2022
 *	\author		Guillaume Carlier
 */
#define _IO_C_
#include "hoc.h"
#include "msgFmt.c"
/**
 *	\var      progName
 *	\brief	Nom du programme
 */
extern char *progName;
/**
 *	\var		lineNo
 *	\brief	Ligne courante
 *	\note		A déclarer avec l'attribut "extern" par les utilisateurs
 */
int lineNo = 0;
/**
 *	\var		myError
 *	\brief	Numéro d'erreur
 *	\note		A déclarer avec l'attribut "extern" par les utilisateurs
 */
int myError = 0;
/**
 *	\part		G E S T I O N   DES  S O R T I E S
 */
/**
 *	\fn 		void prompt(void)
 *	\brief		Affichage du prompt et incrémentation de la ligne courante
 */
void prompt(void)
{
	printMessage(10);
	lineNo++;
}
/**
 *	\fn 		void printExpr(int isFloat, double val)
 *	\brief		Affichage du résultat (val) d'une expression
 */
void printExpr(int isFloat, double val)
{
	if (isFloat)
		printMessage(12, val);
	else
		printMessage(11, (int)val);
}
/**
 *	\fn 		void printMessage(int iMsg, ...)
 *	\brief		Affichage d'un message formaté prédéfini avec un style prédéfini
 *	\param		iMsg : indice dans _msgFmt[] qui fournit
 *					   le message formaté ainsi que son sytle
 */
void printMessage(int iMsg, ...)
{
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
void printMessageTag(int iMsg, ...)
{
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
void yyerror(char *strErr, ...)
{
	va_list pArg;
	va_start(pArg, strErr);
	prTagAndMsgFmtWithStyle(5, strErr, pArg);
	va_end(pArg);
	printLn();
	//	myError = 200;
	//printMessageTag(47, strErr);
}
/**
 *	\fn			void lexError(const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs lexicales
 *	\note		A invoquer explicitement depuis les règles de yylex()
 *	\note		Le prototype peut être adapté à votre besoin
 */
void lexError(const char *strErr, ...)
{
	va_list pArg;
	va_start(pArg, strErr);
	prTagAndMsgFmtWithStyle(6, strErr, pArg);
	va_end(pArg);
	printLn();
	myError = 100;
	//printMessageTag(48, strErr);
}
/**
 *	\fn			void exeError (const char* strErr, ...)
 *	\brief		Fonction de gestion des erreurs d'exécution de fonctions importées,
 *	\note		comme les fonctions mathématiques prédéfinies (à base de errno), 
 *	\note		et les futurs traitements qui seront implémentés
 *	\note		Le prototype peut être adapté à votre besoin
 */
void exeError(const char *strErr, ...)
{
	va_list pArg;
	va_start(pArg, strErr);
	prTagAndMsgFmtWithStyle(7, strErr, pArg);
	va_end(pArg);
	printLn();
	myError = 300;
	//printMessageTag(49, strErr);
}

/**
 *	\part		G E S T I O N   DES  T R A C E S
 */
/**
 *	\fn			void printSymbolList(void)
 *	\brief		Afficher les symboles définis par classe et type
 */
#define PR_SYM_VAL_INTEGER(sp) printf("[% 23d] ", *(int *)(sp)->U.pValue)
#define PR_SYM_VAL_FLOAT(sp) printf("[% 12.11g] ", *(double *)(sp)->U.pValue)
#define PR_SYM_VAR_INTEGER(sp) printf("%-8.8s=[% 23d] ", \
									  (sp)->name, *(int *)(sp)->U.pValue)
#define PR_SYM_VAR_FLOAT(sp) printf("%-8.8s=[% 12.11g] ", \
									(sp)->name, *(double *)(sp)->U.pValue)
#define PR_SYM_PRG_PREDEF(sp) printf("%s() ", (sp)->name)
#define PR_SYM_OPE(sp) printf("%s ", (sp)->name)
#define PR_SYM_OTHER(sp) printf("%s --UNKNOWN TYPE--", (sp)->name)

extern pSymbol_t _symbolList;

void printSymbolList(void)
{
	for (symbol_t *mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
	{
		switch (mySp->clas)
		{
		case DAT:
			if (mySp->type == ENTIER)
				PR_SYM_VAL_INTEGER(mySp);
			else if (mySp->type == REEL)
				PR_SYM_VAL_FLOAT(mySp);
			else
				PR_SYM_OTHER(mySp);
			break;
		case CST:
			if (mySp->type == ENTIER)
				printMessage(69, mySp->name, *(int *)(mySp)->U.pValue);
			else if (mySp->type == REEL)
				PR_SYM_VAR_FLOAT(mySp);
			else if (mySp->type == UNDEF)
				printMessage(13, mySp->name);
			//else PR_SYM_OTHER(mySp);
			break;
		case VAR:
			if (mySp->type == IVAR)
				printMessage(69, mySp->name, *(int *)(mySp)->U.pValue);
			else if (mySp->type == FVAR)
				PR_SYM_VAR_FLOAT(mySp);
			else if (mySp->type == UNDEF)
				printMessage(13, mySp->name);
			//else PR_SYM_OTHER(mySp);
			break;
		case PRG:
			if (mySp->type == PREDEF)
				PR_SYM_PRG_PREDEF(mySp);
			else
				PR_SYM_OPE(mySp); /* traitement des opérateurs : ADD, SUB, MUL et DIV, ... */
			break;
		default:
			fprintf(stdout, "--UNKOWN CLASS--");
		}
		printf("\n");
	}
}
/**
 *	\fn			void printSymbolListByClass(void)
 *	\brief		Afficher les symboles définis par classe et type
 */
void printSymbolListByClass(void)
{
	symbol_t *mySp;
	int i;
	printMessage(70, "---- Nombres \t----\n");
	for (i = 0, mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == DAT)
		{
			if (mySp->type == ENTIER)
				printMessage(71, *(int *)mySp->U.pValue);
			else if (mySp->type == REEL)
				printMessage(72, *(double *)mySp->U.pValue);
			if ((++i) % 4 == 0)
				printMessage(70, "\n");
		}
	printMessage(70, "\t****\n");
	printMessage(70, "---- Variables \t----\n");
	for (i = 0, mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == CST || mySp->clas == VAR)
		{
			if (mySp->type == ENTIER || mySp->type == IVAR)
				printMessage(73, mySp->name, *(int *)mySp->U.pValue);
			else if (mySp->type == REEL || mySp->type == FVAR)
				printMessage(74, mySp->name, *(double *)mySp->U.pValue);
			if ((++i) % 2 == 0)
				printMessage(70, "\n");
		}
	printMessage(70, "\t****\n");
	printMessage(70, "---- Fonctions prédéfinies \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == PRG && mySp->type == PREDEF)
			printMessage(75, mySp->name);
	printMessage(70, "\t****\n");
	printMessage(70, "---- Opérateurs arithmétiques \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->clas == PRG && mySp->type != PREDEF)
			printMessage(76, mySp->name);
	printMessage(70, "\t****\n");
	printMessage(70, "---- Non-définis \t----\n");
	for (mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
		if (mySp->type == UNDEF)
			printMessage(76, mySp->name);
	printMessage(70, "\t****\n");
}
/** Exemple d'affichage de printSymbolList
---- Variables ----
	b       =[           4]     a       =[           1]  PHI     =[ 1.6180339887]
	DEG     =[ 57.295779513]    GAMMA   =[ 0.5772156649] E       =[ 2.7182818285]
	PI      =[ 3.1415926536] ****
---- Nombres ----
	[           4] [           2] [           1]
	[           1] ****
---- Fonctions prédéfinies ----
	abs() sqrt() pow() exp() log10() log() tg() cos()
	sin() ****
---- Mots-clés ----
	func while else if ****
---- Opérateurs arithmétiques -calcul & comparaison- et logiques ----
	<= < >= > != == ! && || ) ( # / * - + ****
---- Fonctions machine d'execution : génération de code ----
	callDefine @ ? whileCode ifCode callPredef printExpr assignVar
	evalVar pushVar pushNbr pop push negate STOP ****
---- Non-définis ----
	****
 */
/**
 *	\fn			void dbgSymbol(symbol_t * symbPtr)
 *	\brief		Afficher les attributs du symbole fourni en paramètre
 *	\note		symbPtr : pointeur sur le symbole
 */
void dbgSymbol(symbol_t *symbPtr) {}

char *strClas(int clas)
{
	switch (clas)
	{
	case DAT:
		return "VALUE";
		break;
	case PRG:
		return "PROGRAM";
		break;
	case CST:
		return "CONSTANT";
		break;
	default:
		return "UNDEF";
		break;
	}
}

char *strType(int type)
{
	switch (type)
	{
	case ENTIER:
		return "ENTIER";
		break;
	case REEL:
		return "REEL";
		break;
	case PREDEF:
		return "FONCTION";
		break;
	case ADD:
		return "ADD";
		break;
	case EQU:
		return "EQU";
		break;
	case SUB:
		return "SUB";
		break;
	case MUL:
		return "MUl";
		break;
	case DIV:
		return "DIV";
		break;
	default:
		return "UNDEF";
		break;
	}
}

/**
 *	\fn			dbgSymbolList(void)
 *	\brief		Afficher les attributs du tous les symboles
 *	\note		Les données seront affichées sous forme d'un tableau :
 *				entête/pied, 1 ligne par symbole (adresse mémoire, nom, classe,
 *				type, adresse mémoire valeur, valeur)
 */
void dbgSymbolList(void)
{
	printMessage(60);
	printMessage(81);
	printMessage(82);
	printMessage(83);

	for (symbol_t *mySp = _symbolList; mySp != SYMBOL_NULL; mySp = mySp->next)
	{
		if (mySp->clas == PRG)
		{
			printMessage(88, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, mySp->U.pFct, mySp->desc);
		}
		else if (mySp->clas == VAR)
		{
			printMessage(88, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, mySp->U.pValue, mySp->desc);
		}
		else if (mySp->clas != PRG)
		{
			switch (mySp->type)
			{
			case ENTIER:
				printMessage(88, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, *(int *)mySp->U.pValue, mySp->desc);
				break;
			case REEL:
				printMessage(89, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, *(double *)mySp->U.pValue, mySp->desc);
				break;
			default:
				printMessage(87, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, mySp->U.pValue, mySp->desc);

				break;
			}
		}
		else
		{
			printMessage(66, mySp, strClas(mySp->clas), strType(mySp->type), mySp->name, "", mySp->desc);
		}
	}

	printMessage(82);
	printMessage(84);
}
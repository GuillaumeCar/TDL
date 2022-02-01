/**
 *	\file		color.c
 *	\brief		G E S T I O N   DES  C O U L E U R S
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 */

#define _COLOR_C_
#include "hoc.h"
/**
 *	\var		_styles[]
 *	\brief		Tableau de styles prédéfinis
 */
static style_t _styles[] = {
    //  0: style par défaut (prompt, détails,...)
    "DEFAULT_OUT",
    ALL_,
    OUT,
    NORMAL,
    BLACK,
    DEFAULT,
    //  1: styple pour fournir une Information ou faire une Annonce
    "INFORMATION",
    ALL_,
    OUT,
    BOLD,
    BLACK,
    DEFAULT,
    //  2: Style pour les messages de configuration
    "CONFIGURATION",
    ALL_,
    OUT,
    ITALIC,
    RED,
    DEFAULT,
    //  3: style pour l'affichage d'un résultat entier
    "INT_RESULT",
    EXEC,
    OUT,
    REVERSE,
    BLUE,
    DEFAULT,
    //  4: style pour l'affichage d'un résultat réel
    "FLOAT_RESULT",
    EXEC,
    OUT,
    REVERSE,
    GREEN,
    DEFAULT,
    //  5: style pour l'affichage d'une erreur syntaxique
    "ERR_SYNTAXE",
    YACC,
    ERR,
    BOLD,
    RED,
    DEFAULT,
    //  6: style pour l'affichage d'une erreur lexicale
    "ERR_LEXIQUE",
    LEX_,
    ERR,
    BOLD,
    CYAN,
    DEFAULT,
    //  7: style pour l'affichage d'une erreur sémantique
    "ERR_SEMANTIQUE",
    EXEC,
    ERR,
    BOLD,
    MAGENTA,
    DEFAULT,
    //  8: style pour la traçabilité (debug) lexicale
    "DBG_LEXIQUE",
    LEX_,
    DBG,
    REVERSE,
    CYAN,
    DEFAULT,
    //  9: style pour la traçabilité (debug) syntaxique
    "DBG_SYNTAXE",
    YACC,
    DBG,
    REVERSE,
    RED,
    DEFAULT,
    // 10: style pour la traçabilité (debug) sémantique
    "DBG_SEMANTIQUE",
    EXEC,
    DBG,
    REVERSE,
    MAGENTA,
    DEFAULT,
    // 11: style pour la traçabilité (debug) des symboles
    "DBG_SYMBOLES",
    SYMB,
    DBG,
    REVERSE,
    YELLOW,
    DEFAULT,
    // 12: Style pour les messages complémentaires de la traçabilité
    "DBG_DETAIL",
    ALL_,
    DBG,
    ITALIC,
    WHITE,
    DEFAULT,
};
/**
 *	\var		_whoString[]
 *	\brief		Tableau de styles prédéfinis
 */
static char *_whoString[] = {"ALL", "AL", "AS", "EX", "TS"};
/**
 * 	\var        _typeString[]
 * 	\brief		Tableau de styles prédéfinis
 */
static char *_typeString[] = {"base", "alerte", "erreur", "debug"};
/**
 * 	\var		output
 * 	\brief		Canal de sortie courant (stdout/stderr)
 *	\note		Initialisation avant utilsation
 */
static FILE *output;
/**
 *	\var        progName
 *	\brief		Nom du programme
 */
extern char *progName;
/**
 *	\var        lineNo
 *	\brief		Ligne courante
 */
extern int lineNo;
/**
 *	\fn			void _resetStyle(void)
 *  \brief		Remise à zéro du terminal (par défaut)
 *	\note		Fonction locale
 */
void _resetStyle(void)
{
    fprintf(output, "\e[0m");
}
/**
 *	\fn			void printLn(void)
 *  \brief		Retour à ligne sur le canal de sortie courant
 *	\note 		Utilsation exceptionnelle : le RC est dans le message
 */
void printLn(void)
{
    fprintf(output, "\e[0m\n");
}
/**
 * 	\fn			void _useStyle(short iStyle)
 *  \brief		Mise en oeuvre d'un style prédéfini
 *	\param		iStyle : indice du style dans _styles[]
 * 	\note		Fonction locale
 */
void _useStyle(short iStyle)
{
    fprintf(output, "\e[0m\e[%i;%i;%im", _styles[iStyle].deco,
            _styles[iStyle].cTxt + 30, _styles[iStyle].cBck + 40);
}
/**
 *	\fn 		void prTagWithStyle(short iStyle)
 *	\brief		Affichage du TAG (who/type) d'un style prédéfini
 *	\param		iStyle : indice du style dans _styles[]
 *	\note		Tagger le début d'une ligne de message
 */
void prTagWithStyle(short iStyle)
{
    output = (_styles[iStyle].type == ERR || _styles[iStyle].type == DBG) ? stderr : stdout;
    _useStyle(iStyle);
    fprintf(output, "[%s:%d][%s]--<%s>: ", basename(progName), lineNo,
            _whoString[_styles[iStyle].who], _typeString[_styles[iStyle].type]);
    fflush(output);
    _resetStyle();
}
/**
 *	\fn 		void prMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg)
 *	\brief		Affichage d'un message formaté avec un style prédéfini
 *	\param		iStyle : indice du style dans _styles[]
 *	\param		msgFmt : message formaté
 */
void prMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg)
{
    output = (_styles[iStyle].type == ERR && _styles[iStyle].type == DBG) ? stderr : stdout;
    _useStyle(iStyle);
    vfprintf(output, msgFmt, pArg);
    fflush(output);
    _resetStyle();
}
/**
 *	\fn			void prTagAndMsgFmtWithStyle(short iStyle, const char *msgFmt, ...
 *	\brief		Affichage du TAG (who/type) d'un style prédéfini suivi d'un message
 *	\param		iStyle : indice du style dans _styles[]
 * 	\note		Tagger le début d'une ligne de message
 */
void prTagAndMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg)
{
    output = (_styles[iStyle].type == ERR && _styles[iStyle].type == DBG) ? stderr : stdout;
    _useStyle(iStyle);
    fprintf(output, "[%s:%d][%s]--<%s>: ", basename(progName), lineNo,
            _whoString[_styles[iStyle].who], _typeString[_styles[iStyle].type]);

    vfprintf(output, msgFmt, pArg);
    fflush(output);
    _resetStyle();
}
/**
 *	\fn 		void _testStyles (void)
 *	\brief		Test des styles prédéfinis
 * 	\note		Fonction locale
 */
void _testStyles(void)
{
    output = stdout; // initialisation
    for (int i = 0; i < sizeof(_styles) / sizeof(_styles[0]); i++)
    {
        //        prMsgFmtWithStyle(0,"Style[%2d]: %-14.14s ",i, _styles[i].name);
        prTagWithStyle(i);
        printLn();
    }
}
/**
 *	\fn 		void _testCouleurs256(void)
 *	\brief		Test des couleurs supportés par le terminal
 * 	\note		Fonction locale
 */
void _testCouleurs256(void)
{
    printf("\033[0m");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            printf("\033[38;5;%im%4i\033[0m", i * 16 + j, i * 16 + j);
        printf("\n");
    }
    printf("\033[0m");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            printf("\033[48;5;%im%4i\033[0m", i * 16 + j, i * 16 + j);
        printf("\n");
    }
    printf("\033[0m");
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
                printf("\033[%i;%i;%im%4i\033[0m", i, j + 30, k + 40, (i * 8 + j) * 8 + k);
            printf("\tDECO = %4i, COUL= %4i\n", i, j);
        }
}

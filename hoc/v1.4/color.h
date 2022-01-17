/**
 *	\file		color.h
 *	\brief		G E S T I O N   DES  C O U L E U R S
 *	\date		22 Janvier 2021
 *	\author		Samir El Khattabi
 */
#ifndef _COLOR_H_
#define _COLOR_H_
#if defined(_COLOR_C_)
typedef enum {INIT, BOLD, UNBOLD, ITALIC, BLINK, UNDER, NORMAL, REVERSE} decoration_t;
typedef enum {BLACK, RED, GREEN,  YELLOW, BLUE, MAGENTA, CYAN,  WHITE, SET, DEFAULT} color_t;
typedef enum {STDOUT, STDERR} outputList;
typedef enum {ALL_, LEX_, YACC, EXEC, SYMB} who_t;
typedef enum {OUT,  WAR,  ERR,  DBG} type_t;
typedef struct {
    char *name;
    who_t who;
    type_t type;
    decoration_t deco;
    color_t cTxt;
    color_t cBck;
} style_t;
#endif
#define CLEAR_SCREEN        printf("\e[H\033[2J")
#define RESET_SCREEN        printf("\e[0m")
/**
 * 	\fn         void prTagWithStyle(short iStyle)
 *	\brief 		Affichage du TAG (who/type) d'un style prédéfini
 *	\param		iStyle : indice du style dans _styles[]
 * 	\note		Tagger le début d'une ligne de message
 */
void prTagWithStyle(short iStyle);
/**
 *	\fn 		void prMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg)
 *	\brief		Affichage d'un message formaté avec un style prédéfini
 *	\param		iStyle : indice du style dans _styles[]
 *	\param		msgFmt : message formaté
 */
void prMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg);
/**
 *	\fn			void prTagAndMsgFmtWithStyle(short iStyle, const char *msgFmt, ...
 *	\brief		Affichage du TAG (who/type) d'un style prédéfini suivi d'un message
 *	\param		iStyle : indice du style dans _styles[]
 * 	\note		Tagger le début d'une ligne de message
 */
void prTagAndMsgFmtWithStyle(short iStyle, const char *msgFmt, va_list pArg) ;
/**
 *	\fn			void printLn(void)
 *  \brief		Retour à ligne sur le canal de sortie courant
 *	\note 		Utilsation exceptionnelle : le RC est dans le message
 */
void printLn(void);

#endif /* _COLOR_H_ */

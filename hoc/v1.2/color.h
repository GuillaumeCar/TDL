/**
 *	\file		color.h
 *	\brief		G E S T I O N   DES  C O U L E U R S
 *	\version	1.2
 *	\date		13 Décembre 2021
 *	\author		Samir El Khattabi
 */
#ifndef _COLOR_H_
#define _COLOR_H_
#if defined(_COLOR_C_)
typedef enum {INIT, BOLD, UNBOLD, ITALIC, BLINK, UNDER, NORMAL, REVERSE} decoration_t;
typedef enum {BLACK, RED, GREEN,  YELLOW, BLUE, MAGENTA, CYAN,  WHITE, SET, DEFAULT} color_t;
//typedef enum {STDOUT, STDERR} outputList;
typedef enum {NOR, LEX, SYN, SEM} who_t;
//typedef enum {OUT,  WAR,  ERR,  DBG} type_t;
typedef struct {
    char *name;
    who_t who;
    decoration_t deco;
    color_t cTxt;
    color_t cBck;
} style_t;
#endif
#define CLEAR_SCREEN        printf("\e[H\033[2J")
#define RESET_SCREEN        printf("\e[0m")

/**
 *	\fn			void printLn(void)
 *  \brief		Retour à ligne sur le canal de sortie courant
 *	\note 		Utilsation exceptionnelle : le RC est dans le message
 */
void printLn(void);

#endif /* _COLOR_H_ */

/**
 *	\file		code.h
 *	\brief		G E N E R A T I O N   DE   C O D E   &&
 *				M A C H I N E  D' E X E C U T I O N
 *	\date		24 Janvier 2022
 *	\author	Guillaume Carlier
 */
#ifndef _CODE_H_
#define _CODE_H_
/******************************************************************************/
/**
 *	\part		P I L E   DE LA  M A C H I N E  D' E X E C U T I O N
 */
/**
 *  \union      data
 *  \brief      l'interpréteur manipule des valeurs ou des symboles
 */
union data
{
	/**     valeur d'un donnée flottante 	: DAT/REEL,                       */
	double value;
	/**     valeur d'un donnée entière 		: DAT/ENTIER,                     */
	//	int 		iValue;
	/**     adresse d'un symbole : VAR/IVAR, VAR/IVAR, CST/ENTIER, CST/ENTIER,
	 *                             UNDEF, PREDEF,                             */
	pSymbol_t pSymb;
};
/**
 *  \typedef    data_t
 *  \brief      Définition de data_t :type de données de la pile de l'interpréteur
 */
typedef union data data_t;
/**
 *  \def        MAX_PILE
 *  \brief      Taille maximale de la pile d'exécution
 */
#define MAX_PILE 256
/**
 *  \fn         void push(data_t d);
 *  \brief      Empiler une donnée sur la pile d'exécution
 *  \note       Ce traitement est invoqué (généralement) après l'analyse
 *              syntaxique pour empiler la donnée en vue d'une opération
 *              (à venir) en phase d'interprétation
 *  \param      d   donnée à empiler
 *  \return     néant
 */
void push(data_t d);
/**
 *  \fn         data_t pop(void);
 *  \brief      Dépiler le sommet de la pile d'exécution
 *  \note       Ce traitement est invoqué (généralement) après l'analyse
 *              syntaxique pour dépiler une donnée en vue d'une opération
 *              en phase d'interprétation
 *  \return     donnée au sommet de la pile
 */
data_t pop(void);
/******************************************************************************/
/**
 *	\part		T A B L E    D' I N S T R U C T I O N S
 */
/**
 *  \def        MAX_PROG
 *  \brief      Nombre maximal d'instructions d'un programme
 */
#define MAX_PROG 2000
/**
 *  \typedef    instr_t
 *  \brief      Définition de instr_t : instruction machine
 *  \note       Une instruction machine correpond à une adresse mémoire de
 *              logement du code à éxécuter
 *
 *              ICI, POUR l'INSTANT :
 *              on ne s'intéresse qu'à des appels de fonctions sans résultat
 *              PLUS TARD :
 *              des appels de fonctions avec résultat générique (void *)
 */
typedef void (*instr_t)();
/**
 *  \def        STOP
 *  \brief      Instruction de fin d'un bloc d'instructions
 */
#define STOP (instr_t)0
/**
 *  \var        PC          Compteur d'exécution
 */
instr_t *PC;
/**
 *  \fn         instr_t *code(instr_t  frame);
 *  \brief      Installer une instruction machine dans la table d'instructions
 */
instr_t *code(instr_t frame);
/**
 *  \fn         void initCode(void);
 *  \brief      Initialise les variables globales pour la génération & exécution
 *              de code
 */
void initCode(void);
/**
 *  \fn         void execute(instr_t *p);
 *  \brief      Exécuter le programme pointé par p
 *  \note       Ce traitement est invoqué  après analyseur syntaxique &
 *              génération de code. Il s'agit d'une interprétation du programme.
 *  \param      p    adresse de début du programme à éxecuter
 */
void execute(instr_t *p);
/**
 *  \def        code2(c1, c2)
 *  \brief      factoriser 2 appels à code()
 */
#define code2(c1, c2) \
	code(c1);         \
	code(c2)
/**
*  \def        code3(c1, c2, c3)
*  \brief      factoriser 3 appels à code()
*/
#define code3(c1, c2, c3) \
	code(c1);             \
	code(c2);             \
	code(c3)

#endif /* _CODE_H_ */

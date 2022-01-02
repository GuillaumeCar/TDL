/**
 *	\file		msgFmt.c
 *	\brief		D E C L A R A T I O N   DES  M E S S A G E S
 *	\date		22 Janvier 2021
 *	\author		Samir El Khattabi
 */

static struct { short iStyle; char* msg; } _msgFmt[]  = {
/*********_********_*********_********_*********_********_***********_*********
 *	\brief		Messages d'usage génaral
 *				Annonces, informations, configuration
 */
    /* 0*/  1,  "Welcome to the High Order Calculator\nImplemented by Samir ElKhattabi & Guillaume Carlier\n",
    /* 1*/  2,  "Version 1.4\n",
    /* 2*/  1,  "\nlogout\nI hope to see you nice !!\n",
    /* 3*/  2,  "Loading: Constants ",
    /* 4*/  2,  "(done) Functions ",
    /* 5*/  2,  "(done) Operations ",
    /* 6*/  2,  "(done) ",
    /* 7*/  2,  "(done) ",
    /* 8*/  2,  "(done) ",
    /* 9*/  2,  "(done).\n",
/*********_********_*********_********_*********_********_***********_*********
 *	\brief		Messages en fonctionnement normal
 *				prompt, résultats, erreurs
 */
    /*10*/  1,  "hoc> ",
    /*11*/  3,  "= %-i\n",
    /*12*/  4,  "= %.8g\n",
    /*13*/  5,  "Undefined variable --%s--\n",
    /*14*/  5,  "Undefined function --%s()--\n",
    /*15*/  5,  "Incompatible operand for %\n",
    /*16*/  7,  "FPE***Division par zéro\n",
    /*17*/  6,  "Stack Overflow (push)\n",
    /*18*/  6,  "Stack empty (pop)\n",
    /*19*/  9,  "Bigest program (code)\n",
    /*20*/  4,  "\n",
    /*21*/  4,  "\n",
    /*22*/  4,  "\n",
    /*23*/  4,  "\n",
    /*24*/  4,  "\n",
    /*25*/  4,  "\n",
    /*26*/  4,  "\n",
    /*27*/  4,  "\n",
    /*28*/  4,  "\n",
    /*29*/  4,  "\n",
/*********_********_*********_********_*********_********_***********_*********
 *	\brief 		Messages Debug et trace
 *				AS : YACC
 */
    /*30*/  8,  "Variable assignation\n",
    /*31*/ 11,  "\t<%s> is assigned with <%-i> integer value\n",
    /*32*/ 11,  "\t<%s> is assigned with <%-.8g> float value\n",
    /*33*/  8,  "Predefined function call\n",
    /*34*/ 11,  "\t<%s> is called with <%-i> integer value\n",
    /*35*/ 11,  "\t<%s> is called with <%-.8g> float value\n",
    /*36*/  8,  "Algebric operation <Integer expression>\n",
    /*37*/ 11,  "\t<%s> of <%-i> and <%-i>\n",
    /*38*/  8,  "Algebric operation <Floatting expression>\n",
    /*39*/ 11,  "\t<%s> of <%-.8g> and <%-.8g>\n",
    /*40*/  8,  "\n",
    /*41*/ 11,  "\n",
    /*42*/  8,  "\n",
    /*43*/ 11,  "\n",
    /*44*/  8,  "\n",
    /*45*/ 11,  "\n",
    /*46*/  8,  "\n",
    /*47*/  5,  "%s\n",	/* style pour yyerror (message par défaut : syntax error) */
    /*48*/  6,  "%s\n",	/* style pour lexError */
    /*49*/  7,  "%s\n",	/* style pour exeError */
/*********_********_*********_********_*********_********_***********_*********
 * 	\brief        Messages Debug et trace
 *                AL : LEX
 */
    /*50*/ 10,  "Token detected\n",
    /*51*/ 11,  "\tclass: [%s] type: [%s]  %s\n",
    /*52*/ 11,  "\tname: <%s> value: <%-i>\n",
    /*53*/ 11,  "\tname: <%s> value: <%-.8g>\n",
    /*54*/ 11,  "\tname: <%s> at %p\n",
    /*55*/ 11,  "\tname: <%s()> at %p\n",
    /*56*/ 11,  "\t<UNKNOWN CLASS>\n",
    /*57*/ 11,  "\t<UNDEFINED VARIABLE>\n",
    /*58*/ 11,  "\t<UNKNOWN OPERATOR>\n",
    /*59*/ 11,  "\t<UNKNOWN PRG TYPE>\n",
/*********_********_*********_********_*********_********_***********_*********
 * 	\brief		Messages Debug et trace
 *              TS : Symboles
 */
    /*60*/  1,  "*[---------------------------------------------------------------------------------]*\n",
    /*61*/ 12,  "--------------\tLISTE DES SYMBOLES DEFINIS (table des symboles)  \t*************\n",
    /*62*/ 12,  "**************\tFIN DE LA LISTE DES SYMBOLES DEFINIS\t\t\t-------------\n",
    /*63*/  1,  "*[@ SYMBOLE\t|CLASS\t |TYPE\t |\t     NAME|\t   VALUE|\tDESCRIPTION]*\n",
    /*64*/  1,  "*[\t\t|\t |\t |\t\t |\t\t|\t\t   ]*",
    /*65*/ 13,  "*[%14p|%-8.8s|%-7.7s| %14.12s|%14.14s|%18.18s]*\n",
    /*66*/ 13,  "\033[3G%14p\033[1C\033[22m%-8.8s\033[1C\033[1m%-7.7s\033[1C\033[22m %14.12s\033[1C\033[1m%14.14s\033[1C\033[22;3m%18.18s\n",
    /*67*/ 14,  "\033[3G%14p\033[1C\033[22m%-8.8s\033[1C\033[1m%-7.7s\033[1C\033[22m %14.12s\033[1C\033[1m%14.14s\033[1C\033[22;3m%18.18s\n",
 
    /*  */  0, ""
};

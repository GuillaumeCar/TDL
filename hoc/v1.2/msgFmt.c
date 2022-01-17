/**
 *	\file		msgFmt.c
 *	\brief		D E C L A R A T I O N   DES  M E S S A G E S
 *	\version	1.2
 *	\date		13 Décembre 2021
 *	\author	Samir El Khattabi
 */

static struct { short iStyle; char* msg; } _msgFmt[]  = {
/*********_********_*********_********_*********_********_***********_*********
 *	\brief		Messages d'usage génaral
 *				Annonces, informations, configuration
 */
    /* 0*/  NOR,  "Welcome to the High Order Calculator\nImplemented by Samir ElKhattabi™\n",
    /* 1*/  NOR,  "Version 1.2\n",
    /* 2*/  NOR,  "\nlogout\nI hope to see you nice !!\n",
    /* 3*/  NOR,  "Loading: Constants ",
    /* 4*/  NOR,  "(done) Functions ",
    /* 5*/  NOR,  "(done) Operations ",
    /* 6*/  NOR,  "(done) ",
    /* 7*/  NOR,  "(done) ",
    /* 8*/  NOR,  "(done) ",
    /* 9*/  NOR,  "(done).\n",
/*********_********_*********_********_*********_********_***********_*********
 *	\brief		Messages en fonctionnement normal
 *				prompt, résultats, erreurs
 */
    /*10*/  NOR,  "hoc> ",
    /*11*/  NOR,  "= %-i\n",
    /*12*/  NOR,  "= %.8g\n",
	/*13*/  NOR,  "\n",
	/*14*/  NOR,  "\n",
	/*15*/  NOR,  "\n",
	/*16*/  NOR,  "\n",
	/*17*/  NOR,  "\n",
	/*18*/  NOR,  "\n",
	/*19*/  NOR,  "\n",
	
/*********_********_*********_********_*********_********_***********_*********
 *	\brief		Messages d'erreurs
 */
    /*20*/  SEM,  "Undefined variable --%s--\n",
    /*21*/  SEM,  "Undefined function --%s()--\n",
    /*22*/  SEM,  "Incompatible operand for %\n",
    /*23*/  SEM,  "FPE***Division par zéro\n",
    /*24*/  SEM,  "Stack Overflow (push)\n",
    /*25*/  SEM,  "Stack empty (pop)\n",
    /*26*/  SEM,  "Bigest program (code)\n",
    /*27*/  SEM,  "\n",
    /*28*/  SEM,  "\n",
    /*29*/  SEM,  "\n",
 
    /*  */  0, ""
};

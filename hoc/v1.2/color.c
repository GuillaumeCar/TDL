/**
 *	\file		color.c
 *	\brief		G E S T I O N   DES  C O U L E U R S
 *	\version	1.2
 *	\date		13 Décembre 2021
 * 	\author		Samir El Khattabi
 */

#define _COLOR_C_
#include "hoc.h"
#include <stdio.h>
/**
 *	\var		_whoString[]
 *	\brief		Tableau de styles prédéfinis
 */
static char *_whoString[]  = {"ALL", "AL",  "AS",   "EX"} ;
/**
 * 	\var		output
 * 	\brief		Canal de sortie courant (stdout/stderr)
 *	\note		Initialisation avant utilsation
 */
static FILE * output;
/**
 *	\var        progName
 *	\brief		Nom du programme
 */
extern char * progName;
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
void _resetStyle(void) {
    fprintf(output,"\e[0m");
}
/**
 *	\fn			void printLn(void)
 *  \brief		Retour à ligne sur le canal de sortie courant
 *	\note 		Utilsation exceptionnelle : le RC est dans le message
 */
void printLn(void) {
    fprintf(output,"\e[0m\n");
}/**
 *	\fn 		void _testCouleurs256(void)
 *	\brief		Test des couleurs supportés par le terminal
 * 	\note		Fonction locale
 */
void _testCouleurs256(void) {
    printf("\033[0m");
    for (int i=0; i<16; i++){
        for (int j=0; j<16; j++) printf("\033[38;5;%im%4i\033[0m",i*16+j,i*16+j);
        printf("\n");
    }
    printf("\033[0m");
    for (int i=0; i<16; i++){
        for (int j=0; j<16; j++) printf("\033[48;5;%im%4i\033[0m",i*16+j,i*16+j);
        printf("\n");
    }
    printf("\033[0m");
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++){
            for (int k=0; k<8; k++)
                printf("\033[%i;%i;%im%4i\033[0m",i,j+30,k+40, (i*8+j)*8+k);
            printf("\tDECO = %4i, COUL= %4i\n",i,j);
        }
}

// int main() {
// 	_testCouleurs256();
// }

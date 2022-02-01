#define _CODE_HOC_C_
#include "hoc.h"
double add(double x, double y) { return x+y; }
double sub(double x, double y) { return x-y; }
double mul(double x, double y) { return x*y; }
double myDiv(double x, double y) {
    if (y == 0.0) { exeError("FPE***Division par zéro"); }
    return x/y;
}
extern int isFloat;
void printExprCode(void) {
	data_t d; d.value = 5555; //pop();
	printExpr(isFloat, d.value);
}

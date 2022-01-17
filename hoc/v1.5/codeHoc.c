#define _CODE_HOC_
#include "hoc.h"

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double customDiv(double a, double b) {
    if (b == 0) {
        exeError("ERREUR ARITH : Div de %.8g par 0", a);
    }
    else {
        return a / b;
    }
    
    return a / b;
}

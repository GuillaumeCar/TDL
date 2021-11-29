#ifndef _HOC_H_
#define _HOC_H_
#ifdef _HOC_L_		// inclusion par hoc.l
#include "symbol.h"
#include "hoc.tab.h"
#endif
#ifdef _HOC_Y_		// inclusion par hoc.y
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#endif
#ifdef _SYMBOL_C_	// inclusion par symbol.c
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symbol.h"
#include "hoc.tab.h"
#endif
#endif /* _HOC_H_ */

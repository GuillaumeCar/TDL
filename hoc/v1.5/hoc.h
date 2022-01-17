#ifndef _HOC_H_
#define _HOC_H_
#ifdef _HOC_L_			// inclusion par hoc.l
#include "symbol.h"
#include "io.h"
#include "hoc.tab.h"
#endif
#ifdef _HOC_Y_			// inclusion par hoc.y
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "io.h"
#endif
#ifdef _SYMBOL_C_		// inclusion par symbol.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "symbol.h"
#include "hoc.tab.h"
#include "io.h"
#include "codeHoc.h"
#endif
#ifdef _COLOR_C_		// inclusion par color.c
#include <stdio.h>
#include <libgen.h>
#include <stdarg.h>
#include "color.h"
#endif
#ifdef _IO_C_			// inclusion par io.c
#include <stdarg.h>
#include <stdio.h>
#include "symbol.h"
#include "color.h"
#include "io.h"
#endif
#ifdef _CODE_HOC_ // inclusion par codeHoc.c
#include "codeHoc.h"
#include "io.h"
#endif

#endif /* _HOC_H_ */

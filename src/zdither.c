/* 
 * Highly optimised dithering 16 bits -> 8 bits. 
 * The formulas were taken in Mesa (Bob Mercier mercier@hollywood.cinenet.net).
 */

#include <stdlib.h>
#include <stdio.h>
#include "zbuffer.h"
#include <assert.h>


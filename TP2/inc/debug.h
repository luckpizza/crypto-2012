/*
 * debug.h
 *
 *  Created on: Jun 3, 2012
 *      Author: luckpizza
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
//#define DEBUG1
#define INFO 1
#define NO_ERROR 1
#ifdef DEBUG1
#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#ifdef INFO
#define info(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define info(fmt, ...)
#endif
#ifndef NO_ERROR
#define error(fmt, ...) fprintf(stderr,fmt, ##__VA_ARGS__)
#else
#define error(fmt, ...)
#endif



#endif  /* DEBUG_H_ */

/*
 * memory_utils.h
 *
 *  Created on: Jun 3, 2012
 *      Author: luckpizza
 */

#ifndef MEMORY_UTILS_H_
#define MEMORY_UTILS_H_

#ifndef RELEASE
#define my_free(x) free(x); x = NULL
#else
#define my_free(x) free(x)
#endif


void * my_malloc(unsigned long size);
void * my_calloc (unsigned long amount, unsigned long size);
void * my_realloc(void * pointer, unsigned long size);


#endif /* MEMORY_UTILS_H_ */

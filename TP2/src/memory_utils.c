/*
 * memory_utils.c
 *
 *  Created on: Jun 3, 2012
 *      Author: luckpizza
 */


#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
void memoryErrorHandler();

void memoryErrorHandler()
{
    error("MEMORY ERROR!");
    exit(-1);
}
void * my_malloc(unsigned long size)
{
    void * ret = NULL;
    int i = 0;
    debug("Using myMalloc");
    while (i++ < 4) {
        if((ret = malloc(size))){
            return ret;
        }
    }
     memoryErrorHandler();
    //ONLY TO AVOID WARNING. THIS SHOULD NEVER BEEN REACH
    return NULL;

}

void * my_realloc(void * pointer, unsigned long size)
{
    int i = 0;
    debug("Using myMalloc");
    while (i++ < 4) {
        if((pointer = realloc(pointer, size))){
            return pointer;
        }
    }
    memoryErrorHandler();
    //ONLY TO AVOID WARNING. THIS SHOULD NEVER BEEN REACH
    return NULL;

}


void * my_calloc (unsigned long amount, unsigned long size)
{
    void * ret = NULL;
    int i = 0;
    while (i++ < 4) {
        if((ret = calloc(amount, size))){
            return ret;
        }
    }
    memoryErrorHandler();
    //ONLY TO AVOID WARNING. THIS SHOULD NEVER BEEN REACH
    return NULL;

}

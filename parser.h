/*
 * parser.h
 *
 *  Created on: 28/02/2022
 *      Author: ASUS
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct parameter{
	char comando[4];
	int content1;
	int content2;
	int content3;

} parameter_t;



int ParameterFilter(char *array[],int size, parameter_t *parameter);
int HexStringToDec(char *hex,int *flagValid);
parameter_t *CreateParameter(char *array[],int size);
parameter_t *Parser_State();


#endif /* INC_PARSER_H_ */

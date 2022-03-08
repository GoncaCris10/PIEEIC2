#include "parser.h"


/* Esta funçao vai dividir os parametros num array e passar para parametros numa struct*/
/* O valor do returno da funçao da-nos o proximo estado*/

int ParameterFilter(char *array[],int size, parameter_t *parameter)
{

	// Só executa a funçao HexStringToDec dependendo do numero de parametros
	switch(size){
		case 4:parameter->content1=HexStringToDec(array[3],&flagValid);
		case 3:parameter->content2=HexStringToDec(array[2],&flagValid);
		case 2:parameter->content3=HexStringToDec(array[1],&flagValid);
		case 1:strcpy(parameter->comando, array[0]);break;
		default: flagValid = -1;
	}
	return flagValid;
}

/*Converte uma string(neste caso é cada parametro) em um numero decimal
	Se nao tiverem contidos de 0 a F a funçao vai returnar -1*/
int HexStringToDec(char *hex,int *flagValid){

	long long decimal = 0, base = 1;
    int i = 0, length;

    length = strlen(hex);

    for(i = length-1; i >= 0; i--)
    {

        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }

        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }

        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }

        else {
			*flagValid = -1;
		}
	}

    return decimal;
}


parameter_t *CreateParameter(char *array[],int size){

	parameter_t *p=(parameter_t*)malloc(sizeof(parameter_t));
	if(p==NULL){
		printf("Out of Memory\n");
	}
	return p;
}

parameter_t *Parser_State(char *input, int *a){

		int i=0,c=0;
		char *array[3];
		char delim[] = " ";
		parameter_t *p;

		int size = strlen(input);
		input[size-1] = '\0';

		char *ptr= strtok(input,delim);

		while(ptr != NULL)
		{

			array[i] = ptr;
			ptr = strtok(NULL, delim);
			i++;

		}
		p = CreateParameter(array,i);
	     ParameterFilter(array,i,p);


		return p;
}

/*
 * parser.c
 *
 *  Created on: 28/02/2022
 *      Author: ASUS
 */



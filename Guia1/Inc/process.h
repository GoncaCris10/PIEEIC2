
#include "parser.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


uint8_t array_store[128];

void Memory_Read(parameter_t *p);
void Memory_Write(parameter_t *p);
void Make_Port_Pin_Input(parameter_t *p);
void Make_Port_Pin_Output(parameter_t *p);
void Read_Digital_Input(parameter_t *p);
void Write_Digital_Output(parameter_t *p);
void Analog_Read(parameter_t *p);
void Last_Command(parameter_t *p);
void Help(void);

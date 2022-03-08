
#include "process.h"

#define isbitset(x,n) ((x>>n) &0x1)

uint8_t command_index = 0;
uint8_t adcFlag = 0;
uint16_t adcValue = 0;

GPIO_TypeDef* gpios[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

uint16_t pins[16] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
                                         GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
                                         GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11,
                                         GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

typedef struct st_adc_channel{
    uint32_t adc_channel;
    GPIO_TypeDef* gpio_adc_channel;
    uint16_t pin_channel;
} ST_ADC_CHANNEL;

ST_ADC_CHANNEL adc_config[] = {{ADC_CHANNEL_0, GPIOA, GPIO_PIN_0},
                                {ADC_CHANNEL_1, GPIOA, GPIO_PIN_1},
                                {ADC_CHANNEL_2, GPIOA, GPIO_PIN_2},
                                {ADC_CHANNEL_3, GPIOA, GPIO_PIN_3},
                                {ADC_CHANNEL_4, GPIOA, GPIO_PIN_4},
                                {ADC_CHANNEL_5, GPIOA, GPIO_PIN_5},
                                {ADC_CHANNEL_6, GPIOA, GPIO_PIN_6},
                                {ADC_CHANNEL_7, GPIOA, GPIO_PIN_7},
                                {ADC_CHANNEL_8, GPIOB, GPIO_PIN_0},
                                {ADC_CHANNEL_9, GPIOB, GPIO_PIN_1},
                                {ADC_CHANNEL_10, GPIOC, GPIO_PIN_0},
                                {ADC_CHANNEL_11, GPIOC, GPIO_PIN_1},
                                {ADC_CHANNEL_12, GPIOC, GPIO_PIN_2},
                                {ADC_CHANNEL_13, GPIOC, GPIO_PIN_3},
                                {ADC_CHANNEL_14, GPIOC, GPIO_PIN_4},
                                {ADC_CHANNEL_15, GPIOC, GPIO_PIN_5}
                            };

void Memory_Read(parameter_t *p)
{
	uint16_t addr = p->content1;
	uint8_t length = p->content2;
	printf("addr = 0x%X | length = 0x%X", addr, length);

	if((addr + length) <= 0x4000)
	{
		uint8_t *position;
		position = (uint8_t*)((uint32_t)addr);

		for(int i = 0; i < length; i++)
		{
			printf("\r0x%X", *position);
			position++;
		}
	}
	else
		printf("\r\rMemória reservada/proibida!");

	printf("\r\rOperação Memory Read concluída com sucesso!\r\n");
}

void Memory_Write(parameter_t *p)
{
	uint16_t addr = p->content1;
	uint8_t length =p->content2;
	uint8_t byte = p->content3;
	printf("addr = 0x%X | length = 0x%X | byte = 0x%X", addr, length, byte);

	if((addr + length) <= 0x4000)
	{
		uint8_t *position;
		position = (uint8_t*)((uint32_t)addr);

		for(int i = 0; i < length; i++)
		{
			*position = byte;
			position++;
		}
	}
	else
		printf("\r\rMemória reservada/proibida!");

	printf("\r\rOperação Memory Write concluida com sucesso!");
}

void Make_Port_Pin_Input(parameter_t *p)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	uint8_t port_addr = p->content1;
	uint16_t pin_setting = p->content2;

	printf("port_addr = 0x%X | pin_setting = 0x%X", port_addr, pin_setting);

	if(1<= port_addr && port_addr <= 8)
	{
		GPIO_InitStruct.Pin = pin_setting;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(gpios[port_addr - 1], &GPIO_InitStruct);
	}

	else
		printf("\r\rPorto inválido!");

	printf("\r\rOperação Make Pin Input concluída com sucesso!");
}

void Make_Port_Pin_Output(parameter_t *p)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	uint8_t port_addr = p->content1;
	uint16_t pin_setting = p->content2;

	printf("port_addr = 0x%X | pin_setting = 0x%X", port_addr, pin_setting);

	if(1<= port_addr && port_addr <= 8)
	{
		GPIO_InitStruct.Pin = pin_setting;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(gpios[port_addr - 1], &GPIO_InitStruct);
	}

	else
		printf("\r\rPorto inválido!");

	printf("\r\rOperação Make Pin Output concluída com sucesso!");
}

void Read_Digital_Input(parameter_t *p)
{
	uint8_t port_addr = p->content1;
	uint16_t pin_setting = p->content2;

	printf("port_addr = 0x%X | pin_setting = 0x%X\r", port_addr, pin_setting);

	if(1<= port_addr && port_addr <= 8)
	{
		for(int i=15; i>=0; i--)
		{
			if(isbitset(pin_setting, i))
			{
				printf("'");

				if(HAL_GPIO_ReadPin(gpios[port_addr - 1], pins[i]))
					printf("1' ");

				else
					printf("0' ");
			}

			else
				printf("0 ");
		}
	}

	else
		printf("\r\rPorto inválido!");

	printf("\r\rOperação Read Digital concluída com sucesso!");
}

void Write_Digital_Output(parameter_t *p)
{
	uint8_t port_addr = p->content1;
	uint16_t pin_setting = p->content2;
	uint16_t pin_values = p->content3;

	printf("port_addr = 0x%X | pin_setting = 0x%X | pin_values = 0x%X", port_addr, pin_setting, pin_values);

	if(1<= port_addr && port_addr <= 8)
	{
		for(int i=15; i>=0; i--)
		{
			if(isbitset(pin_setting, i))
			{
				if(isbitset(pin_values, i))
					HAL_GPIO_WritePin(gpios[port_addr - 1], pins[i], GPIO_PIN_SET);

				else
					HAL_GPIO_WritePin(gpios[port_addr - 1], pins[i], GPIO_PIN_RESET);
			}
		}
	}

	else
		printf("\r\rPorto invalido!");

	printf("\r\rOperação Write Digital concluída com sucesso!");
}

void Analog_Read(parameter_t *p)
{
  double vref;
	uint8_t addr3 = p->content1;

	printf("addr3 = 0x%X", addr3);

	GPIO_InitTypeDef GPIO_InitStruct = {0};			//Configura-se o pino do canal que o utilizador pretende.
	GPIO_InitStruct.Pin = adc_config[addr3].pin_channel;		//Ativo o pino correspondente do array pins_channels.
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(adc_config[addr3].gpio_adc_channel, &GPIO_InitStruct);	//Ativo o GPIO correspondente ao pino que configuramos a partir do array gpios_channels.

	ADC_ChannelConfTypeDef sConfig = {0};				//Configura-se o canal que o utilizador pretende.
	sConfig.Channel = adc_config[addr3].adc_channel;	//Ativo o channel correspondente ao pino de entrada ADC, que configuramos anteriormente, através do array_channels.
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
		Error_Handler();

	if(HAL_ADC_Start(&hadc3) == HAL_OK)
  {
		if(HAL_ADC_PollForConversion(&hadc3,1000) == HAL_OK)
			adcValue = HAL_ADC_GetValue(&hadc3);

		HAL_ADC_Stop(&hadc3);
	}

	vref = ((double) adcValue * (3300) / (4095 * 1000));
	HAL_Delay(50);

	printf("\r\radcValue: %u", adcValue);
  printf("\rHex: %X ", adcValue);
  printf("\rTensao medida: %0.2f", vref);

	printf("\r\rOperação Analog Read concluída com sucesso!");
}

void Last_Command(parameter_t *p)
{
	if(array_store[0] == '\0')
		printf("Nenhum comando executado antes!\r"
					 "Por favor coloque um comando válido!");

	else
	{
		strcpy((char*)Main_Buffer, (char*)array_store);
		printf("Comando: \"%s\"", Main_Buffer);
		printf("\r\rA processar último comando válido!");
		HAL_Delay(500);
		command_index = 0xfd;
	}
}

void Help(void)
{
	printf("Memory Read - \"MR <addr> <length>\"\r"
				 "Memory Write - \"MW <addr> <length> <byte>\"\r"
				 "Make Pin Input - \"MI <port addr> <pin setting>\"\r"
				 "Make Pin Output - \"MO <port addr> <pin setting>\"\r"
				 "Read Dig Input - \"RD <port addr> <pin setting>\"\r"
				 "Write Dig Output - \"WD <port addr> <pin setting> <pin values>\"\r"
				 "Analog Read - \"RA <addr3>\"\r"
				 "\"$\" - (Last Command)\r"
				 "Help - \"?\"\r"
				 "Version - \"VER\"\r"
				 "\r"
				 "Backspace - \"<BS>\"\r"
				 "Delete - \"<ESC>\"\r"
				 "\r"
				 "<addr>, <pin setting>, <pin values> = {\"0000\", ..., \"FFFF\"}\r"
				 "<length>, <byte>, <port addr> = {\"00\", ..., \"FF\"}\r"
				 "<addr3> = {\"00\", ..., \"10\"}");
}


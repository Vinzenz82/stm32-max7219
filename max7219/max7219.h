// vim: set ai et ts=4 sw=4:
#ifndef MAX7219_H_
#define MAX7219_H_

#include "stdbool.h"
#include "stdint.h"

// #define TM1638_PLATFORM_STM32        // HAL Functions
#define TM1638_PLATFORM_STM32_LL        // LL Functions

#define NUMBER_OF_DIGITS      8

#if defined( TM1638_PLATFORM_STM32 )
#define MAX7219_CS_Pin        GPIO_PIN_6
#define MAX7219_CS_GPIO_Port  GPIOA
extern SPI_HandleTypeDef      SPI_PORT;
#define SPI_PORT              hspi1
#elif defined( TM1638_PLATFORM_STM32_LL )
#define MAX7219_CS_Pin  LL_GPIO_PIN_1
#define MAX7219_CS_GPIO_Port GPIOB
#define SPI_PORT              SPI2
#endif


typedef enum {
    MAX7219_SEG_G = (1<<0),
    MAX7219_SEG_F = (1<<1),
    MAX7219_SEG_E = (1<<2),
    MAX7219_SEG_D = (1<<3),
    MAX7219_SEG_C = (1<<4),
    MAX7219_SEG_B = (1<<5),
    MAX7219_SEG_A = (1<<6),
    MAX7219_SEG_DP = (1<<7),
} MAX7219_SEGMENTS;

typedef enum {
    MAX7219_SYM_0 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_1 = MAX7219_SEG_B | MAX7219_SEG_C,
    MAX7219_SYM_2 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_G,
    MAX7219_SYM_3 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_G,
    MAX7219_SYM_4 = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_5 = MAX7219_SEG_A | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_6 = MAX7219_SEG_A | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_7 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C,
    MAX7219_SYM_8 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_9 = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_A = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_B = MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_C = MAX7219_SEG_A | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_D = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_G,
    MAX7219_SYM_E = MAX7219_SEG_A | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_F = MAX7219_SEG_A | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_G = MAX7219_SEG_A | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_H = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_I = MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_J = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E,
    MAX7219_SYM_L = MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_N = MAX7219_SEG_C | MAX7219_SEG_E | MAX7219_SEG_G,
    MAX7219_SYM_O = MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_G,
    MAX7219_SYM_P = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_Q = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_R = MAX7219_SEG_E | MAX7219_SEG_G,
    MAX7219_SYM_S = MAX7219_SYM_5,
    MAX7219_SYM_T = MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_U = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_E | MAX7219_SEG_F,
    MAX7219_SYM_Y = MAX7219_SEG_B | MAX7219_SEG_C | MAX7219_SEG_D | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_MINUS = MAX7219_SEG_G,
    MAX7219_SYM_DEGREE = MAX7219_SEG_A | MAX7219_SEG_B | MAX7219_SEG_F | MAX7219_SEG_G,
    MAX7219_SYM_DOT = MAX7219_SEG_DP,
    MAX7219_SYM_BLANK = 0x00,
} MAX7219_SYMBOLS;

typedef struct MAX7219_MODULE_ROW_t
{
    union{
        struct{
            uint8_t Led1:1;
            uint8_t Led2:1;
            uint8_t Led3:1;
            uint8_t Led4:1;
            uint8_t Led5:1;
            uint8_t Led6:1;
            uint8_t Led7:1;
            uint8_t Led8:1;
        };
        uint8_t raw;
    };
} MAX7219_MODULE_ROW_st;

typedef struct MAX7219_MODULE_t
{
    union{
        struct{
            MAX7219_MODULE_ROW_st Row1;
            MAX7219_MODULE_ROW_st Row2;
            MAX7219_MODULE_ROW_st Row3;
            MAX7219_MODULE_ROW_st Row4;
            MAX7219_MODULE_ROW_st Row5;
            MAX7219_MODULE_ROW_st Row6;
            MAX7219_MODULE_ROW_st Row7;
            MAX7219_MODULE_ROW_st Row8;
        };
        MAX7219_MODULE_ROW_st raw[8];
    };    
} MAX7219_MODULE_st;

typedef struct MAX7219_ARRAY_t
{
    MAX7219_MODULE_st Unit[4];
} MAX7219_ARRAY_st;

void max7219_Init();
void max7219_SetIntensivity(uint8_t intensivity);
void max7219_Clean(void);
void max7219_SendData(uint8_t addr, uint8_t data);

void max7219_SetBuffer(MAX7219_ARRAY_st newBuffer);
void max7219_DisplayBuffer(void);

void max7219_TurnOn(void);
void max7219_TurnOff(void);

#endif /* MAX7219_H_ */

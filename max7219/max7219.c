// vim: set ai et ts=4 sw=4:

#include <max7219.h>
#include <max7219_font.h>

// change for your MCU
#if defined( TM1638_PLATFORM_STM32 )
#include "stm32f1xx_hal.h"
#elif defined( TM1638_PLATFORM_STM32_LL )
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_spi.h"
#include "stm32f3xx_ll_utils.h"
#endif

typedef enum {
    REG_NO_OP           = 0x00,
    REG_DIGIT_0         = 0x01,
    REG_DIGIT_1         = 0x02,
    REG_DIGIT_2         = 0x03,
    REG_DIGIT_3         = 0x04,
    REG_DIGIT_4         = 0x05,
    REG_DIGIT_5         = 0x06,
    REG_DIGIT_6         = 0x07,
    REG_DIGIT_7         = 0x08,
    REG_DECODE_MODE     = 0x09,
    REG_INTENSITY       = 0x0A,
    REG_SCAN_LIMIT      = 0x0B,
    REG_SHUTDOWN        = 0x0C,
    REG_DISPLAY_TEST    = 0x0F,
} MAX7219_REGISTERS;

MAX7219_ARRAY_st buffer = {0};

void max7219_Init() {
    uint8_t j = 0;

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_DECODE_MODE, 0x00); // decode off
    }

    max7219_SetIntensivity(0);

    //max7219_TurnOff();

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_SCAN_LIMIT, NUMBER_OF_DIGITS - 1);
    }

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_DISPLAY_TEST, 0x00);
    }
    
    max7219_Clean();
}

void max7219_SetIntensivity(uint8_t intensivity) {
    if (intensivity > 0x0F)
        return;

    uint8_t j = 0;

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_INTENSITY, intensivity);
    }
}

void max7219_Clean() {
	uint8_t i = 0, col = 1;

    for(col = 1; col < 9; col++) {
        for(i = 0; i<4; i++) {
            max7219_SendData(col, 0u ); 
        }
    }
}

void max7219_SendData(uint8_t addr, uint8_t data) {
    
#if defined(TM1638_PLATFORM_STM32)
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET);
#elif defined(TM1638_PLATFORM_STM32_LL)
    LL_SPI_Enable(SPI_PORT);
    LL_GPIO_ResetOutputPin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin);
#endif

#if defined(TM1638_PLATFORM_STM32)
    HAL_SPI_Transmit(&hspi1, &addr, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
#elif defined(TM1638_PLATFORM_STM32_LL)
    // Send bytes over the SPI
    LL_SPI_TransmitData16(SPI_PORT,(data<<8) + addr);
    // Wait until the transmission is complete
    while( LL_SPI_IsActiveFlag_BSY(SPI_PORT) ){__NOP();/*LL_mDelay(1);*/};
#endif

#if defined(TM1638_PLATFORM_STM32)
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET);
#elif defined(TM1638_PLATFORM_STM32_LL)
    LL_GPIO_SetOutputPin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin);
    LL_SPI_Disable(SPI_PORT);
#endif
}

void max7219_SendDataNoCs(uint8_t addr, uint8_t data) {
    

#if defined(TM1638_PLATFORM_STM32)
    HAL_SPI_Transmit(&hspi1, &addr, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
#elif defined(TM1638_PLATFORM_STM32_LL)
    // Send bytes over the SPI
    LL_SPI_TransmitData16(SPI_PORT,(data<<8) + addr);
    // Wait until the transmission is complete
    while( LL_SPI_IsActiveFlag_BSY(SPI_PORT) ){__NOP();/*LL_mDelay(1);*/};
#endif
}

void max7219_SetBuffer(MAX7219_ARRAY_st newBuffer)
{
    buffer = newBuffer;
}

void max7219_DisplayBuffer(void)
{
    uint8_t i = 0, col = 1;
    LL_SPI_Enable(SPI_PORT);

    for(col = 1; col < 9; col++) {
        LL_GPIO_ResetOutputPin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin);
        for(i = 3; i<7; i++) { //0-4
            
            max7219_SendDataNoCs(col, buffer.Unit[i].raw[col-1].raw); 
            
        }
        LL_GPIO_SetOutputPin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin);
    }
    LL_SPI_Disable(SPI_PORT);
}

void max7219_TurnOn(void) {    
    uint8_t j = 0;

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_SHUTDOWN, 0x01);
    }

}

void max7219_TurnOff(void) {
    uint8_t j = 0;

    for(j = 0; j<4; j++) {
        max7219_SendData(REG_SHUTDOWN, 0x00);
    }
}

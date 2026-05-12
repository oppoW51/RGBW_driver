#include "I2C_API.h"
#include <stdio.h>


I2C_Error_t I2C_Init(const I2C_Ch_t i2c_ch, const I2C_Freq_t i2c_freq)
{
    printf("[I2C] Init: ch=%d, freq=%d\n", i2c_ch, i2c_freq);
    return I2C_ERR_SUCCESS;
}


I2C_Error_t I2C_Start(const I2C_Ch_t i2c_ch, const uint8_t i2c_addr, const I2C_Dir_t direction)
{
    printf("[I2C] Start: ch=%d, addr=0x%02X, dir=%d\n", i2c_ch, i2c_addr, direction);
    return I2C_ERR_SUCCESS;
}


I2C_Error_t I2C_Stop(const I2C_Ch_t i2c_ch)
{
    printf("[I2C] Stop: ch=%d\n", i2c_ch);
    return I2C_ERR_SUCCESS;
}


I2C_Error_t I2C_Read(const I2C_Ch_t i2c_ch, uint8_t* data_bytes, const uint16_t length)
{
    (void)data_bytes;
    printf("[I2C] Read: ch=%d, len=%d\n", i2c_ch, length);
    return I2C_ERR_SUCCESS;
}


I2C_Error_t I2C_Write(const I2C_Ch_t i2c_ch, const uint8_t* data_bytes, const uint16_t length)
{
    printf("[I2C] Write: ch=%d, len=%d, data=[", i2c_ch, length);
    for (uint16_t i = 0; i < length; i++) 
        printf(" 0x%02X", data_bytes[i]);
    printf(" ]\n");
    return I2C_ERR_SUCCESS;
}

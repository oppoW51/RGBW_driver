#include "RGBW_driver.h"

int main(void)
{
    RGBW_Dev_t led =
    {
        .i2c_ch   = I2C_CH0,
        .i2c_freq = I2C_FREQ_400_KHZ,
        .i2c_addr = RGBW_I2C_ADDR_AD_GND
    };

    if (RGBW_Init(&led) != RGBW_ERR_SUCCESS)
        return 1;
    
    if (RGBW_SetChannel(&led, RGBW_CH_D1, RGBW_LED_ON) != RGBW_ERR_SUCCESS)
        return 1;
    
    if (RGBW_SetBrightness(&led, RGBW_CH_D1, 255) != RGBW_ERR_SUCCESS)
        return 1;
    
    if (RGBW_SetRGB(&led, 50, 0, 7) != RGBW_ERR_SUCCESS)
        return 1;
    
    if (RGBW_SetAllChannels(&led, RGBW_LED_ON) != RGBW_ERR_SUCCESS)
        return 1;
    
    if (RGBW_SetAllChannels(&led, RGBW_LED_OFF) != RGBW_ERR_SUCCESS)
        return 1;

    return 0;
}

#include "RGBW_driver.h"
#include "I2C_API.h"


/** @brief Writes 8-bit value to RGBW controller register via I2C. */
static RGBW_Error_t RGBW_WriteReg(const RGBW_Dev_t* dev, uint8_t reg, uint8_t value)
{
    if (!dev)
        return RGBW_ERR_INPUT;
    
    const uint8_t buf[] = {reg, value};
    if (I2C_Start(dev->i2c_ch, dev->i2c_addr, I2C_DIR_WRITE) != I2C_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (I2C_Write(dev->i2c_ch, buf, (uint16_t)sizeof(buf)) != I2C_ERR_SUCCESS)
    {
        I2C_Stop(dev->i2c_ch);
        return RGBW_ERR_I2C;
    }

    if (I2C_Stop(dev->i2c_ch) != I2C_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}


RGBW_Error_t RGBW_Init(const RGBW_Dev_t* dev)
{
    if (!dev)
        return RGBW_ERR_INPUT;

    if (I2C_Init(dev->i2c_ch, dev->i2c_freq) != I2C_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev ,RGBW_REG_RESET, RGBW_RESET) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;
    
    if (RGBW_WriteReg(dev, RGBW_REG_SHUTDOWN, RGBW_SHUTDOWN_NORMAL) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev, RGBW_REG_GLOBAL_CTRL, RGBW_GLOBAL_CTRL_NORMAL) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_SetAllChannels(dev, RGBW_LED_OFF) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev, RGBW_REG_UPDATE, RGBW_UPDATE) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}


RGBW_Error_t RGBW_SetBrightness(const RGBW_Dev_t* dev, RGBW_Channel_t channel, uint8_t value)
{
    if (!dev)
        return RGBW_ERR_INPUT;    

    switch (channel)
    {
        case RGBW_CH_D1:
            if (RGBW_WriteReg(dev, RGBW_REG_PWM1, value) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D2:
            if (RGBW_WriteReg(dev, RGBW_REG_PWM2, value) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D3:
            if (RGBW_WriteReg(dev, RGBW_REG_PWM3, value) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D4:
            if (RGBW_WriteReg(dev, RGBW_REG_PWM4, value) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        default:
            return RGBW_ERR_INPUT;
    }

    if (RGBW_WriteReg(dev, RGBW_REG_UPDATE, RGBW_UPDATE) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}


RGBW_Error_t RGBW_SetChannel(const RGBW_Dev_t* dev, RGBW_Channel_t channel, uint8_t state)
{
    if (!dev || state > RGBW_LED_CTRL_ALLOWED)
        return RGBW_ERR_INPUT;

    switch (channel)
    {
        case RGBW_CH_D1:
            if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL1, state) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D2:
            if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL2, state) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D3:
            if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL3, state) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        case RGBW_CH_D4:
            if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL4, state) != RGBW_ERR_SUCCESS)
                return RGBW_ERR_I2C;
            break;
        default:
            return RGBW_ERR_INPUT;
    }

    if (RGBW_WriteReg(dev, RGBW_REG_UPDATE, RGBW_UPDATE) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}


RGBW_Error_t RGBW_SetAllChannels(const RGBW_Dev_t* dev, uint8_t state)
{
    if (!dev || state > RGBW_LED_CTRL_ALLOWED)
        return RGBW_ERR_INPUT;

    if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL1, state) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL2, state) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;
    
    if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL3, state) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;
    
    if (RGBW_WriteReg(dev, RGBW_REG_LED_CTRL4, state) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;
   
    if (RGBW_WriteReg(dev, RGBW_REG_UPDATE, RGBW_UPDATE) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}


RGBW_Error_t RGBW_SetRGB(const RGBW_Dev_t* dev, uint8_t r, uint8_t g, uint8_t b)
{
    if (!dev)
        return RGBW_ERR_INPUT;

    if (RGBW_WriteReg(dev, RGBW_REG_PWM1, r) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev, RGBW_REG_PWM2, g) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;
    
    if (RGBW_WriteReg(dev, RGBW_REG_PWM3, b) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    if (RGBW_WriteReg(dev, RGBW_REG_UPDATE, RGBW_UPDATE) != RGBW_ERR_SUCCESS)
        return RGBW_ERR_I2C;

    return RGBW_ERR_SUCCESS;
}

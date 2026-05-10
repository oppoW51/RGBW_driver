#ifndef RGBW_DRIVER_H
#define RGBW_DRIVER_H

#include <stdint.h>


/** @brief Slave register map */
#define RGBW_REG_SHUTDOWN       (0x00U)  /**< Software shutdown mode */
#define RGBW_REG_PWM1           (0x05U)  /**< 1 Channel PWM data */ 
#define RGBW_REG_PWM2           (0x06U)  /**< 2 Channel PWM data */
#define RGBW_REG_PWM3           (0x07U)  /**< 3 Channel PWM data */
#define RGBW_REG_PWM4           (0x08U)  /**< 4 Channel PWM data */
#define RGBW_REG_UPDATE         (0x25U)  /**< Update registers */
#define RGBW_REG_LED_CTRL1      (0x2AU)  /**< Control of 1 channel */
#define RGBW_REG_LED_CTRL2      (0x2BU)  /**< Control of 2 channel */
#define RGBW_REG_LED_CTRL3      (0x2CU)  /**< Control of 3 channel */
#define RGBW_REG_LED_CTRL4      (0x2DU)  /**< Control of 4 channel */
#define RGBW_REG_GLOBAL_CTRL    (0x4AU)  /**< Control of all channels */
#define RGBW_REG_FREQ           (0x4BU)  /**< Output frequency */
#define RGBW_REG_RESET          (0x4FU)  /**< Reset all registers */


/** @brief Slave addreses */ 
#define RGBW_I2C_ADDR_AD_GND    (0x3CU)  /**< AD connected to GND */
#define RGBW_I2C_ADDR_AD_VCC    (0x3FU)  /**< AD connected to VCC */
#define RGBW_I2C_ADDR_AD_SCL    (0x3DU)  /**< AD connected to SCL */
#define RGBW_I2C_ADDR_AD_SDA    (0x3EU)  /**< AD connected to SDA */


/** @brief Slave bitmasks */
#define RGBW_SHUTDOWN_NORMAL    (0x01U)  /**< Normal operation */
#define RGBW_SHUTDOWN_ENABLE    (0x00U)  /**< Software shutdown */
#define RGBW_UPDATE             (0x00U)  /**< Update registers */
#define RGBW_LED_ON             (0x01U)  /**< LED channel on */
#define RGBW_LED_OFF            (0x00U)  /**< LED channel off */
#define RGBW_LED_IMAX           (0x00U)  /**< Current IMAX */
#define RGBW_LED_IMAX_DIV2      (0x02U)  /**< Current IMAX/2 */
#define RGBW_LED_IMAX_DIV3      (0x04U)  /**< Current IMAX/3 */
#define RGBW_LED_IMAX_DIV4      (0x06U)  /**< Current IMAX/4 */
#define RGBW_GLOBAL_CTRL_NORMAL (0x00U)  /**< Normal operation */
#define RGBW_GLOBAL_CTRL_OFF    (0x01U)  /**< LEDs shutdown */
#define RGBW_FREQ_3KHZ          (0x00U)  /**< 3kHz PWM frequency */
#define RGBW_FREQ_22KHZ         (0x01U)  /**< 22kHz PWM frequency */
#define RGBW_RESET              (0x00U)  /**< Reset all registers */


/** @brief Enumeration defining the error of RGBW_driver */
typedef enum
{
    RGBW_ERR_SUCCESS   = (0U),
    RGBW_ERR_I2C       = (1U),
    RGBW_ERR_INPUT     = (2U)
} RGBW_Error_t;


/**
* @brief Initialize RGBW LED controller.
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_Init(void);


/**
* @brief Switch off all LEDs.
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_LedsOff(void);


/**
* @brief Set brightness for a single channel.
* @param channel Channel number (1-4).
* @param value Brightness value (0-255).
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_SetBrightness(uint8_t channel, uint8_t value);


/**
* @brief Set mode of channel.
* @param channel Channel number (1-4).
* @param state 2:0 bits mode (0b000-0b111).
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_SetChannel(uint8_t channel, uint8_t state);


/**
* @brief Set mode of all channels.
* @param state 2:0 bits mode (0b000-0b111).
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_SetAllChannels(uint8_t state);


/**
* @brief Set color by RGB code.
* @param r Brightness value of red color (0-255).
* @param g Brightness value of green color (0-255).
* @param b Brightness value of blue color (0-255).
* @return RGBW_Error_t Status of the operation.
*/
RGBW_Error_t RGBW_SetRGB(uint8_t r, uint8_t g, uint8_t b);

#endif

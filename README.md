# RGBW LED Driver

C99 driver for a multichannel PWM LED controller over I2C.  
Built on top of the provided abstract I2C API. Does not access MCU registers directly.

## Project Structure

- `Inc/I2C_API.h` - provided I2C API
- `Inc/RGBW_driver.h` - public API, register map, constants
- `Src/RGBW_driver.c` - driver logic
- `Src/I2C_stub.c` - mock I2C transport for host testing
- `Src/main.c` - usage example
- `Makefile` - build script

## Features

- Device initialization
- Individual PWM brightness control
- Per-channel on/off control
- All channels on/off control
- RGB color setup (D1=R, D2=G, D3=B)
- Error checking after every operation

## Build

Compile:

```bash
make
```

Run:

```bash
./rgbw_driver
```

Clean build files:

```bash
make clean
```

ARM compile check:

```bash
arm-none-eabi-gcc -c Src/RGBW_driver.c -IInc -Wall -Wextra -Werror -std=c99 -o rgbw_driver.o
```

**Note:** for real MCU integration, replace `Src/I2C_stub.c` with the target-specific implementation of `I2C_API.h`.

## API

| Function | Description |
|---|---|
| `RGBW_Init()` | Reset device, exit shutdown mode, disable all channels at startup |
| `RGBW_SetBrightness()` | Set PWM brightness for one channel |
| `RGBW_SetChannel()` | Set on/off state and current for one channel |
| `RGBW_SetAllChannels()` | Set on/off state and current for all channels |
| `RGBW_SetRGB()` | Set RGB color using D1, D2, D3 as R, G, B |

## Usage

Create device descriptor:

```c
RGBW_Dev_t led =
{
    .i2c_ch   = I2C_CH0,
    .i2c_freq = I2C_FREQ_400_KHZ,
    .i2c_addr = RGBW_I2C_ADDR_AD_GND
};
```

Initialize device:

```c
if (RGBW_Init(&led) != RGBW_ERR_SUCCESS)
    return 1;
```

Set brightness and channel state:

```c
RGBW_SetBrightness(&led, RGBW_CH_D1, 255U);
RGBW_SetChannel(&led, RGBW_CH_D1, RGBW_LED_ON);
```

Set RGB color:

```c
RGBW_SetRGB(&led, 50U, 0U, 7U);
```

Control all channels:

```c
RGBW_SetAllChannels(&led, RGBW_LED_ON);
RGBW_SetAllChannels(&led, RGBW_LED_OFF);
```

## Usage Notes

- `RGBW_Dev_t` stores I2C channel, bus frequency and 7-bit slave address.
- I2C slave address depends on AD pin connection:
  - `RGBW_I2C_ADDR_AD_GND`
  - `RGBW_I2C_ADDR_AD_SCL`
  - `RGBW_I2C_ADDR_AD_SDA`
  - `RGBW_I2C_ADDR_AD_VCC`
- LED control value uses only bits `[2:0]`:
  - bit `0` - channel on/off
  - bits `2:1` - output current setting
- PWM brightness value range is `0..255`.
- `RGBW_SetRGB()` maps channels as D1=R, D2=G, D3=B.
- PWM and LED control changes are applied through the Update Register.
- All public functions return `RGBW_Error_t`.
- `Src/main.c` contains a simple demonstration of the driver API.

### Repository on github and codeberg

Codeberg - `https://codeberg.org/oppoW51/RGBW_driver`

Github - `https://github.com/oppoW51/RGBW_driver`

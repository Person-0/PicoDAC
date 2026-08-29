# PicoDAC Firmware

This directory contains the firmware for PicoDAC.

> Note that the board selected is `Pico 2` (non risc-v) but the actual board is XIAORP2350, which has an extra onboard Neopixel RGB LED that we are using to show the DAC state (checkout [src/dac.c](./src/dac.c)).


## Current State

Firmware is WIP and needs real-world testing, hence the current state is very basic.

Currently only these two things have been tested to work:

- Windows11 recognizes it as a USB Audio Class 2 Device
- Streaming audio makes the onboard LED as set in the Blink pattern enum in [PicoDAC.c](./PicoDAC.c)

The following stuff is untested and will be tested, fixed if required once I get my hands on the necessary components or/and the built PCB:
- Onboard Neopixel RGB LED
- DAC Initialization process

The following stuff will be implemented after the stuff mentioned above is done:
- DAC audio playback (ring buffer implementation?)
- 9x RGB LED strip (music level visualizer): Since it requires me to process the music data, i've decided to do it after the DAC accepts the USB audio data

## Current Startup sequence
1. Power On (everything is powered up, uses USB-C VBUS)
2. MCU's Onboard LED indicator blinks and shows USB status live accodingly
3. MCU's Onboard Neopixel indicator shows DAC init status **(untested)**
    - Blue = init
    - Green = DAC OK
    - Red = DAC init failed / error

## Special Notes

- Use the official Raspberry Pi Pico VS Code extension to build or flash the firmware as it will save you lots of time and config messes.
- (VERY IMPORTANT) If the device freezes on audio playback, downgrade the **TinyUSB** version from `0.18.0` (which comes bundled with `Pico SDK 2.3.0`) to `0.17.0`. Debugging this took me hours and this was the only fix I found that worked for me. See [this github issue](https://github.com/hathach/tinyusb/discussions/3215).

## Pin Reference
- GP00 - DAC_MCLK
- GP01 - DAC_SCLK1
- GP02 - DAC_LCRK1
- GP03 - DAC_SDIN1
- GP04 - DAC_RESET
- GP05 - MCU_LS_OE (level shifter output-enable)
- GP06 - DAC_SDA
- GP07 - DAC_SCL
<br>...
- GP22 - ONBOARD_NEOPIXEL
- GP23 - ONBOARD_NEOPIXEL_PWR
- GP25 - ONBOARD_LED
- GP26 - LED_CONTROL (9x SK6812 Row)
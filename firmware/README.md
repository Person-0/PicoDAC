# PicoDAC Firmware

This directory contains the firmware for PicoDAC.

> Note that currently the board specified is `Pico` (for testing purposes) however the final build will be for `Pico-2`.

It is WIP and needs real-world testing, hence the current state is very basic.
- Windows11 recognizes it as a USB Audio Class 2 Device
- Streaming audio makes the onboard LED as set in the Blink pattern enum in [PicoDAC.c](./PicoDAC.c)

## Special Notes:

- Use the official Raspberry Pi Pico VS Code extension to build or flash the firmware as it will save you lots of time and config messes
- (VERY IMPORTANT) If the deviec freezes on audio playback, downgrade the TinyUSB version from `0.18.0` (which comes bundled with Pico SDK 2.3.0) to `0.17.0`. Debugging this took me hours and this was the only fix I found that worked for me. See [this github issue](https://github.com/hathach/tinyusb/discussions/3215).
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "neopixel.pio.h"

#include "pindefs.h"

static PIO pio = pio1;
static uint sm = 0;

void neopixel_init(void) {
  gpio_init(PIN_ONBOARD_NEOPIXEL_PWR);
  gpio_set_dir(PIN_ONBOARD_NEOPIXEL_PWR, GPIO_OUT);
  gpio_put(PIN_ONBOARD_NEOPIXEL_PWR, 1);

  uint offset = pio_add_program(pio, &neopixel_program);

	pio_sm_config c = neopixel_program_get_default_config(offset);

  sm_config_set_sideset_pins(&c, PIN_ONBOARD_NEOPIXEL);
  sm_config_set_out_shift(&c, false, true, 24);

  pio_gpio_init(pio, PIN_ONBOARD_NEOPIXEL);

  pio_sm_init(pio, sm, offset, &c);
  pio_sm_set_enabled(pio, sm, true);
}

void neopixel_set(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t pixel = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;  // grb
  pio_sm_put_blocking(pio, sm, pixel << 8);
}

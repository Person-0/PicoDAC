#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "tusb.h"

#include "neopixel.h"
#include "./pindefs.h"

#include "./dac.h"

// -------------- REGISTER METHODS --------------
// cs43131 register map uses a 20bit address
// ----------------------------------------------

static bool cs43131_write_reg(uint32_t reg, uint8_t value) {
    uint8_t buf[5];
    buf[0] = (reg >> 16) & 0xFF;
    buf[1] = (reg >> 8)  & 0xFF;
    buf[2] = reg & 0xFF;
    buf[3] = 0x00; // 8 bit register access
    buf[4] = value;
    int ret = i2c_write_blocking(
        i2c1,
        CS43131_I2C_ADDR,
        buf,
        sizeof(buf),
        false
    );
    return ret == sizeof(buf);
}

static bool cs43131_read_reg(uint32_t reg, uint8_t *value) {
    uint8_t buf[4];
    buf[0] = (reg >> 16) & 0xFF;
    buf[1] = (reg >> 8)  & 0xFF;
    buf[2] = reg & 0xFF;
    buf[3] = 0x00; // 8 bit register access
    int ret = i2c_write_blocking(
        i2c1,
        CS43131_I2C_ADDR,
        buf,
        sizeof(buf),
        true
    );
    if (ret != sizeof(buf)) return false;
    ret = i2c_read_blocking(
        i2c1,
        CS43131_I2C_ADDR,
        value,
        1,
        false
    );
    return ret == 1;
}

static bool cs43131_test(void) {
    uint8_t id_a;
    if (!cs43131_read_reg(0x10000, &id_a)) {
        TU_LOG1("CS43131: I2C read failed\n");
        return false;
    }
    TU_LOG1("CS43131 ID A/B = 0x%02X\n", id_a);
    return true;
}

// ----------------------------------------------


//----------------------------------
// Util Functions
//----------------------------------

static void dac_reset(void) {
    TU_LOG1("DAC reset called\r\n");

    gpio_init(PIN_DAC_RESET);
    gpio_set_dir(PIN_DAC_RESET, GPIO_OUT);

    gpio_put(PIN_DAC_RESET, 0);
    sleep_ms(2);

    gpio_put(PIN_DAC_RESET, 1);
    sleep_ms(2);
}

static void dac_i2c_init(void) {
    i2c_init(i2c1, 400 * 1000); // 400 kHz, will change later

    gpio_set_function(PIN_DAC_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_DAC_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(PIN_DAC_SDA);
    gpio_pull_up(PIN_DAC_SCL);
}

static void level_shifters_init(void) {
    gpio_init(PIN_MCU_LS_OE);
    gpio_set_dir(PIN_MCU_LS_OE, GPIO_OUT);
    gpio_put(PIN_MCU_LS_OE, 1);
    sleep_ms(2);
}

// onboard neopixel represents the state
static void dac_init(void) {
    TU_LOG1("DAC init\r\n");

    neopixel_set(0, 0, 255);        // blue = init
    level_shifters_init();
    dac_i2c_init();
    dac_reset();
    sleep_ms(10);

    if (cs43131_test()) {
        neopixel_set(0, 255, 0);    // green = ok
        TU_LOG1("DAC OK\r\n");
    } else {
        neopixel_set(255, 0, 0);    // red = error
        TU_LOG1("DAC ERR\r\n");
    }
}
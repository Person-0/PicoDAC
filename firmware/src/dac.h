//----------------------------------
// Global definitions
//----------------------------------

#define CS43131_I2C_ADDR 0x30

//----------------------------------
// Util Functions
//----------------------------------

static void dac_reset(void);
static void dac_i2c_init(void);
static void dac_init(void);
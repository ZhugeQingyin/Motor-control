#include "common.h"
#include "KEA128_port_cfg.h"
#include "stdio.h"
#include "math.h"
#include "SKEAZ1284.h"
//--------函数库--------
#include "KEA128_ftm.h"
#include "KEA128_pit.h"
#include "KEA128_gpio.h"
#include "KEA128_port.h"
#include "KEA128_adc.h"
#include "KEA128_irq.h"
#include "KEA128_uart.h"
#include "KEA128_kbi.h"
#include "KEA128_flash.h"
#include "KEA128_systick.h"
#include "KEA128_i2c.h"
#include "KEA128_spi.h"
#include "isr.h"

//--------外设库-----------
#include "Peripheral_IIC.h"
#include "Peripheral_MPU6050.h"
#include "Peripheral_OLED.h"


//--------USER-------------
#include "LED.h"
#include "Interaction.h"
#include "Speed.h"
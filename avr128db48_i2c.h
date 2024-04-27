#define F_CPU 4000000     // 4MHz default clock
#define CLK_PER 4000000   // 4MHz default clock

#include <avr/io.h>
#include <util/delay.h>

/* AVR128DB48 I2C Driver Functions */
static void wait_for_WIF(void);
static void wait_for_RIF(void);

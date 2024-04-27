#include "avr128db48_i2c.h"

/* AVR128DB48 I2C Driver Functions */
void wait_for_WIF(void)
{
	// Write interrupt flag, wait until transmit address or byte write operation is completed
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
}

void wait_for_RIF(void)
{
	// Read interrupt flag, wait until read operation is successfully completed
	while(!(TWI0.MSTATUS & TWI_RIF_bm));
}

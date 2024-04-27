#include "avr128db48_i2c.h"

/* AVR128DB48 I2C Driver Functions */
void wait_for_WIF(void)
{
	// Write interrupt flag (WIF), wait until transmit address or byte write operation is completed
	while(!(TWI0.MSTATUS & TWI_WIF_bm));
}

void wait_for_RIF(void)
{
	// Read interrupt flag (RIF), wait until read operation is successfully completed
	while(!(TWI0.MSTATUS & TWI_RIF_bm));
}

void wait_for_idle(void)
{
	// Wait until bus state is idle
	while((TWI0.MSTATUS & TWI_BUSSTATE_BUSY_gc) != TWI_BUSSTATE_IDLE_gc) ;	
}

void issue_stop_condition(void)
{
	// Issue stop condition
	TWI0.MCTRLB |= TWI_MCMD_STOP_gc;	
}

void issue_ack(void)
{
	// MCMD - Issue ACK followed by read operation
	TWI0.MCTRLB = 0x02;
}

void issue_nack(void)
{
	// MCMD - Issue NACK followed by stop condition
	TWI0.MCTRLB = 0x07;
}

void i2c0_transmit_address_packet(uint8_t address, uint8_t direction_bit)
{
	// Write -> direction_bit = 0; Read -> direction_bit = 1
	TWI0.MADDR = ((address << 1) | (direction_bit & 0x01));
	
	if ((direction_bit & 0x01) == 0x00)
		wait_for_WIF();	// Wait for write interrupt flag (WIF)
	else
		wait_for_RIF();	// Wait for read interrupt flag (RIF)
}

void i2c0_send_data_packet(uint8_t data)
{
	/* Stop bit should be issued after data is sent */
	TWI0.MDATA = data;
	wait_for_WIF();
}

uint8_t i2c0_receive_data_packet(void)
{
	/* ACK or NACK should be issued after this function */
	wait_for_RIF();
	return TWI0.MDATA;	// Reading MDATA register clears RIF flag
}

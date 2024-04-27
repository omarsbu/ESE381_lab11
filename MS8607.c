/*
 * MS8607.c
 *
 * Created: 4/27/2024 3:44:27 PM
 *  Author: omtm2
 */ 
#include "MS8607.h"

/* MS8607 Initialization  Function */
void MS8607_init(void)
{
	// Set I2C Baud Rate to 400kHz
	TWI0.MBAUD = (uint8_t)TWI0_BAUD(MS8607_SCL_FREQ, 0.282);
	
	// Enable TWI0
	TWI0.MCTRLA = TWI_ENABLE_bm;
	
	// Initialize the address register
	TWI0.MADDR = 0x00;
	
	// Initialize the data register
	TWI0.MDATA = 0x00;
	
	// Set bus state idle
	TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

/* MS8607 Read and Write Functions  */
void MS8607_Write_command(uint8_t slave_address, uint8_t command)
{
	wait_for_idle();
	i2c0_transmit_address_packet(slave_address, 0x00);
	i2c0_send_data_packet(command);
	issue_stop_condition();
}

uint8_t MS8607_Read(uint8_t slave_address, volatile uint8_t* data, uint8_t length)
{
	uint8_t i = 0;	// initialize counter variable

	wait_for_idle();
	i2c0_transmit_address_packet(slave_address, 0x01);
	
	// Store n bytes of data in data array, issue ack after reading each byte
	while (i < (length - 1))
	{
		data[i] = i2c0_receive_data_packet();
		issue_ack();		
		i++;
	}
	
	// Issue nack after reading last byte of data
	data[i] = i2c0_receive_data_packet();
	issue_nack();	
	
	return &(data[0]);	// return base address of data array
}

void MS8607_reset_PT(void)
{
	MS8607_Write_command(MS8607_PT_ADDRESS, PSENSOR_RESET_COMMAND);
}

void MS8607_reset_RH(void)
{
	MS8607_Write_command(MS8607_RH_ADDRESS, HSENSOR_RESET_COMMAND);
}

void MS8607_PROM_read_PT(uint8_t PT_PROM*)
{
	// Send reset sequence for PT
	MS8607_reset_PT();	
	
	// Read all 7 16-bit words into an array with 14 8-bit bytes
	// Each 16-bit word consists of a high byte and a low byte
	// The high byte is stored in the index before the low byte in the array
	for (uint8_t i = 0; i < 14; i += 0x02)
	{
		// Write the command to read the PROM data, starting from address 0
		// Increment the address by 2, each PROM word is 2 bytes
		MS8607_Write_command(MS8607_PT_ADDRESS, PROM_ADDRESS_READ_ADDRESS_0 + i);
		MS8607_Read(MS8607_PT_ADDRESS, &PT_PROM[i], 2);	// Read 2 bytes (1 word) from the PROM into PT_PROM array
	}	
}

void MS8607_PROM_read_RH(uint8_t *RH_PROM)
{
	// Send reset sequence for RH 
	MS8607_reset_RH();
	
	// Read all 7 16-bit words into an array with 14 8-bit bytes
	// Each 16-bit word consists of a high byte and a low byte
	// The high byte is stored in the index before the low byte in the array
	for (uint8_t i = 0; i < 14; i += 0x02)
	{
		// Write the command to read the PROM data, starting from address 0
		// Increment the address by 2, each PROM word is 2 bytes
		MS8607_Write_command(MS8607_RH_ADDRESS, PROM_ADDRESS_READ_ADDRESS_0 + i);
		MS8607_Read(MS8607_RH_ADDRESS, &RH_PROM[i], 2);	// Read 2 bytes (1 word) from the PROM into RH_PROM array
	}	
}

void MS8607_convert_pressure(uint8_t D1_OSR)
{
	MS8607_Write_command(MS8607_PT_ADDRESS, D1_OSR);	// start conversion
	_delay_ms(16);	// delay maximum conversion time
}
void MS8607_convert_temperature(uint8_t D2_OSR)
{
	MS8607_Write_command(MS8607_PT_ADDRESS, D2_OSR);	// start conversion
	_delay_ms(16);	// delay maximum conversion time	
}

void MS8607_Read_pressure(uint8_t D1_OSR, uint8_t* ADC_pressure)
{
	MS8607_convert_pressure(D1_OSR);	// Initiate pressure conversion
	MS8607_Write_command(MS8607_PT_ADDRESS, PSENSOR_READ_ADC);	// ADC read sequence
	
	// The pressure is sent as a 24 bit value
	// The result is store in an array containing 3 8-bit elements
	// The high bytes are stored in the indexes before the low bytes in the array
	MS8607_Read(MS8607_PT_ADDRESS, &ADC_pressure, 3);
}
void MS8607_Read_temperature(uint8_t D2_OSR, uint8_t* ADC_temperature)
{
	MS8607_convert_temperature(D2_OSR)
	MS8607_Write_command(MS8607_PT_ADDRESS, PSENSOR_READ_ADC);
	
	// The temperature is sent as a 24 bit value
	// The result is store in an array containing 3 8-bit elements
	// The high bytes are stored in the indexes before the low bytes in the array
	MS8607_Read(MS8607_PT_ADDRESS, &ADC_temperature, 3);
}


uint8_t MS8607_read_user_register(void)
{
	
}

void MS8607_write_user_register(uint8_t value)
{

}

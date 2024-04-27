/*
 * MS8607.h
 *
 * Created: 4/27/2024 3:44:16 PM
 *  Author: omtm2
 */ 

#ifndef MS8607_H_
#define MS8607_H_

#define F_CPU 4000000     // 4MHz default clock
#define CLK_PER 4000000   // 4MHz default clock

#include <avr/io.h>
#include <util/delay.h>
#include "avr128db48_i2c.h"

#define TWI0_BAUD(F_SCL, T_RISE) ((((((float)CLK_PER / (float)F_SCL)) - 10 - ((float)CLK_PER * T_RISE))) / 2)
#define MS8607_SCL_FREQ			 400000		// 400kHz I2C clock

#define MS8607_PT_ADDRESS		 0x76		// Pressure and Temperature (PT) I2C address
#define MS8607_RH_ADDRESS		 0x40		// Relative Humidity (RH) I2C address

/* Relative humidity sensing commands */
#define HSENSOR_RESET_COMMAND							0xFE	// 0b11111110
#define HSENSOR_WRITE_USER_REG_COMMAND					0xE6	// 0b11100110
#define HSENSOR_READ_USER_REG_COMMAND					0xE7	// 0b11100111
#define HSENSOR_READ_HUMIDITY_W_HOLD_COMMAND			0xE5	// 0b11100101
#define HSENSOR_READ_HUMIDITY_WO_HOLD_COMMAND			0xF5	// 0b11110101
#define HSENSOR_READ_SERIAL_FIRST_8BYTES_COMMAND		0xFA0F  // 0b1111101000001111
#define HSENSOR_READ_SERIAL_LAST_6BYTES_COMMAND			0xFCC9  // 0b1111110011001001

/* Pressure and temperature device commands */
#define PSENSOR_RESET_COMMAND							0x1E	// 0b00011110
#define PSENSOR_START_PRESSURE_ADC_CONVERSION			0x40	// 0b01000000
#define PSENSOR_START_TEMPERATURE_ADC_CONVERSION		0x50	// 0b01010000
#define PSENSOR_READ_ADC								0x00	// 0b00000000

/* PROM Read Addresses*/
#define PROM_ADDRESS_READ_ADDRESS_0						0xA0	// 0b10100000
#define PROM_ADDRESS_READ_ADDRESS_1						0xA2	// 0b10100010
#define PROM_ADDRESS_READ_ADDRESS_2						0xA4	// 0b10100100
#define PROM_ADDRESS_READ_ADDRESS_3						0xA6	// 0b10100110
#define PROM_ADDRESS_READ_ADDRESS_4						0xA8	// 0b10101000
#define PROM_ADDRESS_READ_ADDRESS_5						0xAA	// 0b10101010
#define PROM_ADDRESS_READ_ADDRESS_6						0xAC	// 0b10101100
#define PROM_ADDRESS_READ_ADDRESS_7						0xAE	// 0b10101110

#define I2C_SLAVE_RESPONSE_ACKED                        (!(TWI_RXACK_bm & TWI0.MSTATUS))
#define I2C_DATA_RECEIVED                               (TWI_RIF_bm & TWI0.MSTATUS)

static volatile uint8_t buffer [32];

/* MS8607 Initialization  Function */
static void MS8607_init(void);

/* MS8607 Read and Write Functions  */
static void MS8607_Write_command(uint8_t slave_address, uint8_t command);
static uint8_t MS8607_Read(uint8_t slave_address, volatile uint8_t* data, uint8_t length);

/* User register Read and Write Functions*/
static void MS8607_Write_user_register(uint8_t value);
static uint8_t MS8607_Read_user_register(void);

/* PROM Read Functions*/
static void MS8607_PROM_read_PT(volatile uint8_t * PR_PROM);
static void MS8607_PROM_read_RH(volatile uint8_t *RH_PROM);

/* ADC Conversion Functions*/
static void MS8607_convert_pressure(uint8_t D1_OSR);
static void MS8607_convert_temperature(uint8_t D2_OSR);
static void MS8607_Read_pressure(uint8_t D1_OSR, uint8_t* ADC_pressure);
static void MS8607_Read_temperature(uint8_t D2_OSR, uint8_t* ADC_temperature);

/* Reset Functions*/
static void MS8607_reset_PT(void);
static void MS8607_reset_RH(void);

#endif /* MS8607_H_ */

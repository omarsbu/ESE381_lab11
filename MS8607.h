#ifndef AVR128DB48_MS8607_DRIVER_H_
#define AVR128DB48_MS8607_DRIVER_H_

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
#define HSENSOR_RESET_COMMAND								0xFE
#define HSENSOR_WRITE_USER_REG_COMMAND						0xE6
#define HSENSOR_READ_USER_REG_COMMAND						0xE7
#define HSENSOR_READ_HUMIDITY_W_HOLD_COMMAND				0xE5
#define HSENSOR_READ_HUMIDITY_WO_HOLD_COMMAND				0xF5
#define HSENSOR_READ_SERIAL_FIRST_8BYTES_COMMAND			0xFA0F
#define HSENSOR_READ_SERIAL_LAST_6BYTES_COMMAND				0xFCC9

/* Pressure and temperature device commands */
#define PSENSOR_RESET_COMMAND								0x1E
#define PSENSOR_START_PRESSURE_ADC_CONVERSION				0x40
#define PSENSOR_START_TEMPERATURE_ADC_CONVERSION			0x50
#define PSENSOR_READ_ADC									0x00
#define PROM_ADDRESS_READ_ADDRESS_0							0xA0
#define PROM_ADDRESS_READ_ADDRESS_1							0xA2
#define PROM_ADDRESS_READ_ADDRESS_2							0xA4
#define PROM_ADDRESS_READ_ADDRESS_3							0xA6
#define PROM_ADDRESS_READ_ADDRESS_4							0xA8
#define PROM_ADDRESS_READ_ADDRESS_5							0xAA
#define PROM_ADDRESS_READ_ADDRESS_6							0xAC
#define PROM_ADDRESS_READ_ADDRESS_7							0xAE

#define I2C_SLAVE_RESPONSE_ACKED                        (!(TWI_RXACK_bm & TWI0.MSTATUS))
#define I2C_DATA_RECEIVED                               (TWI_RIF_bm & TWI0.MSTATUS)

static volatile uint8_t buffer [32];

/* MS8607 Initialization  Function */
static void MS8607_init(void);

/* MS8607 Read and Write Functions  */
static void MS8607_Write(uint8_t slave_address, uint8_t command);
static void MS8607_Read(uint8_t slave_address, uint8_t* array);
static void MS8607_write_user_register(uint8_t value);
static uint8_t MS8607_read_user_register(void);

/* PROM Read Functions*/
static void MS8607_PROM_read_PT(uint8_t * PR_PROM_data);
static void MS8607_PROM_read_RH(uint8_t *RH_PROM_data);

/* Reset Functions*/
static void MS8607_reset_PT(void);
static void MS8607_reset_RH(void);

/* MS8607 Block Read and Block Write Functions  */
static void MS8607_Block_Write(uint8_t slave_address,  volatile uint8_t *array_ptr,  uint8_t start_addr , uint8_t count);
static uint16_t MS8607_Block_Read(uint8_t slave_address, volatile uint8_t *array_ptr,  uint8_t start_addr , uint8_t count);

/* AVR128DB48 I2C Driver Functions */
static void wait_for_WIF(void);
static void wait_for_RIF(void);

#endif /* AVR128DB48_MS8607_DRIVER_H_ */
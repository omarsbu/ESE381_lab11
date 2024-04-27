#ifndef AVR128DB48_I2C_H_
#define AVR128DB48_I2C_H_

#define F_CPU 4000000     // 4MHz default clock
#define CLK_PER 4000000   // 4MHz default clock

#include <avr/io.h>
#include <util/delay.h>

/* AVR128DB48 I2C Driver Functions */
static void wait_for_WIF(void);
static void wait_for_RIF(void);
static void wait_for_idle(void);
static void issue_stop_condition(void);
static void issue_ack(void);
static void issue_nack(void);
static void i2c0_transmit_address_packet(uint8_t address, uint8_t direction_bit);
static void i2c0_send_data_packet(uint8_t data);
static uint8_t i2c0_receive_data_packet(void);

#endif /* AVR128DB48_I2C_H_ */

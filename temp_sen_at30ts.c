/*
 * at30.c
 *
 *  Created on: Oct 19, 2021
 *      Author: Computer
 */
#include "temp_sen_at30ts.h"
#include "main.h"
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_it.h"
extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef huart2;
uint8_t pointer[1];
uint8_t txBuf[256];
/*1. declaring the elements of array
  2. Transmit it via I2C protocol to the slave
  3. create delay for 10ms*/
void config()
{
	pointer[0] = 0x01;
	HAL_I2C_Master_Transmit(&hi2c3, ADDR, pointer, 1, 100);
	HAL_Delay(10);

	arr[0]=CONFIG_REG_ADDR;
	arr[1]=0x60;
	arr[2]=0x00;
	HAL_I2C_Master_Transmit(&hi2c3, ADDR, arr, 3, 100);
//	HAL_I2C_Mem_Write(&hi2c3, ADDR, CONFIG_REG_ADDR, 1, arr, 2, 100);
	HAL_Delay(10);
}
/* 1. Creating an array to point towards data register
 * 2. Receiving the temperature in the data array*/
void read()
{
	uint8_t ar[1];
	ar[0]=DATA_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c3, ADDR, ar, 1, 1000);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(&hi2c3, ADDR, data,2, 100);
	HAL_Delay(10);
}
/* 1. setting temperature low limit*/
void tl_limit()
{
	uint8_t tl[3];
	tl[0]=TL_REG_ADDR;
	tl[1]=0x00;
    tl[2]=0x00;
	HAL_I2C_Master_Transmit(&hi2c3, ADDR, tl, 3,1000);
	HAL_Delay(10);
}
/* 1. setting temperature high limit*/
void th_limit()
{
	uint8_t th[3];
	th[0]=TH_REG_ADDR;
	th[1]=0x64;
	th[2]=0x00;
	HAL_I2C_Master_Transmit(&hi2c3, ADDR, th, 3,1000);
	HAL_Delay(10);
}
/* receiving data through uart
 * msb is shifted 8bits or'ed with lsb to make it 16 bit data which is stored in temp_raw
 * temp_raw is multiplied with const
 * sent using char type txbuf variable through uart transmit
 */
void display()
{
	uint8_t data_temp[2];
//	HAL_UART_Receive(&huart2, data, 2, 1000);
	HAL_Delay(10);
	msb=data[0];
	lsb=data[1];
	temp_raw = msb<<8 | lsb;
	temp_raw = temp_raw>>4;
	temp = (temp_raw * CONST);
	int len = sprintf((char*)txBuf, "Temperature: %d\n", temp);
	HAL_UART_Transmit(&huart2, txBuf, len, 10000);
}

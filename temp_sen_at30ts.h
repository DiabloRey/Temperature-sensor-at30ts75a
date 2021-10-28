/*
 * at30.h
 *
 *  Created on: Oct 19, 2021
 *      Author: Computer
 */

#ifndef INC_AT30_H_
#define INC_AT30_H_

#include "main.h"
#define CONST 0.0625f
#define ADDR (0x48<<1)
#define CONFIG_REG_ADDR	0x01
#define TL_REG_ADDR		0x02
#define TH_REG_ADDR		0x03
#define DATA_REG_ADDR	0x00


uint8_t arr[3];

void tl_limit();
void th_limit();
void config();
void read();
void display();

#endif /* INC_AT30_H_ */

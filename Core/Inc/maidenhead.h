/*
 *@filename: maidenhead.h
 *@Description: Convert latitude and longitude information to Maidenhead grid
 *@version: 1.0
 *@Author: BH8PHG W_Linus
 *@Date: 2022/04/25
 */
#ifndef __MAIDENHEAD_H_
#define __MAIDENHEAD_H_

#include <stm32g0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>

void gnss_getMaidenhead(float longitude,float latitude,uint8_t* destString);

#endif

#ifndef __DISP_H_
#define __DISP_H_

#include <stm32g0xx_hal.h>
#include <st7735.h>
#include <air551g.h>
#include <Lcd_Driver.h>

void disp_Frame(void);
void disp_InvalidGNSSInfo(GNSS_info gnss);
void disp_ValidGNSSInfo(GNSS_info gnss);

#endif

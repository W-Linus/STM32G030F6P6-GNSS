#ifndef __DISP_H_
#define __DISP_H_

#include <stm32g0xx_hal.h>
#include <st7735.h>
#include <Air530Z.h>
#include <Lcd_Driver.h>

extern volatile uint32_t KeyR_PB0_Flag;

void disp_Frame(void);
void disp_InvalidGNSSInfo(GNSS_info gnss);
void disp_ValidGNSSInfo(GNSS_info gnss);

void show_basicStatus(GNSS_info gnss,float BattVolt,float Temperature);
void show_detailGNSS(GNSS_info gnss);
void show_bigTime(GNSS_info gnss);
void show_speed(GNSS_info gnss);
void show_bigLoaction(GNSS_info gnss);
void show_sysInfo(uint8_t* sysTemp,uint8_t* sysVolt,uint8_t* batVolt,uint8_t* softVer);
void show_originalData(uint8_t* originalPack,GNSS_info gnss);

#endif

/*
 *@filename: air551g.h
 *@Description: Air551G GNSS Module operation file
 *@version: 1.0
 *@Author: BH8PHG W_Linus
 *@Date: 2022/04/25
 */
#ifndef __AIR551G_H_
#define __AIR551G_H_

#define AIR551G_uart &huart2
#define PC_uart 		 &huart1

#include <stm32g0xx_hal.h>
#include <string.h>
#include <stdio.h>
#include <maidenhead.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

typedef struct {
	/*Data validity*/
	uint8_t data_validity;
	/*Position*/
	uint8_t lat_dir; 	//N S 
	float latitude_ddmm;		//ddmm.mmmm
	float latitude; //dd.dddddd
	uint8_t long_dir;	//E W
	float longitude_dddmm;	//dddmm.mmmm
	float longitude; //ddd.dddddd
	uint8_t maidenhead[7];
	char lat_str[10];
	char long_str[11];
	/*Time*/
	int year_utc;
	int year_cst;
	int month_utc;
	int month_cst;
	int day_utc;
	int day_cst;
	
	int hour_utc;
	int hour_cst;
	int minute;
	int second;
	
	char date_utc_str[11];
	char date_cst_str[11];
	char time_utc_str[9];
	char time_cst_str[9];
	/*motion*/
	float speed_mps; //meter per second
	float speed_kph; //kilometer per hour
	float speed_knot;//n mile per hour
	
	char speed_mps_str[8];
	char speed_kph_str[8];
	char speed_knot_str[8];
	/*data check*/
	int BCC_Checksum;
} GNSS_info;


void air551g_init(void);
void air551g_prepareRptBuffer(void);
void air551g_rpt(void);

GNSS_info air551g_dataGet(void);
GNSS_info gnss_getTimeDate(GNSS_info gnssdata);
GNSS_info gnss_getLocation(GNSS_info gnssdata);
GNSS_info gnss_getSpeed(GNSS_info gnssdata);




#endif

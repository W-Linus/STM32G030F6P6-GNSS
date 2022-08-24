#include <disp.h>

volatile uint8_t lastStatus='A';
volatile uint8_t lastStrLen=0;

void disp_Frame(void){
	ST7735_FillRectangle(0,0,10,10,RED);
	ST7735_WriteString(12,1,"GNSS FAIL",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	//ST7735_WriteString(0,15,"JJ00aa",Font_11x18,ST7735_GREEN,ST7735_BLACK);
	
	ST7735_FillEmptyRectangle(70,18,46,15,ST7735_WHITE);
	ST7735_FillEmptyRectangle(115,18,32,15,ST7735_WHITE);
	//ST7735_WriteString(72,21,"114.51",Font_7x10,WHITE,ST7735_BLACK);
	ST7735_WriteString(117,21,"km/h",Font_7x10,WHITE,ST7735_BLACK);
	
	ST7735_FillEmptyRectangle(0,50,160,30,ST7735_WHITE);
	ST7735_FillEmptyRectangle(0,50,80,30,ST7735_WHITE);
	ST7735_FillEmptyRectangle(0,38,160,13,ST7735_WHITE);
	ST7735_FillEmptyRectangle(0,38,80,13,ST7735_WHITE);
	
	ST7735_WriteString(12,40,"CST Time",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	//ST7735_WriteString(5,55,"2022/04/30",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	//ST7735_WriteString(13,67,"17:58:30",Font_7x10,ST7735_WHITE,ST7735_BLACK);	
	ST7735_WriteString(92,40,"Position",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	//ST7735_WriteString(85,55,"118.920265",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	//ST7735_WriteString(85,67,"32.858742",Font_7x10,ST7735_WHITE,ST7735_BLACK);
}



void disp_ValidGNSSInfo(GNSS_info gnss){
			/*ST7735_FillRectangle(0,0,10,10,ST7735_GREEN);
			ST7735_WriteString(12,1,"GNSS OK  ",Font_7x10,ST7735_WHITE,ST7735_BLACK);*/
			ST7735_WriteString(0,15,(char*)gnss.maidenhead,Font_11x18,ST7735_GREEN,ST7735_BLACK);
			
			if(gnss.speed_kph>=10.0&&gnss.speed_kph<100.0){
				ST7735_FillRectangle(92,21,22,11,ST7735_BLACK);
			}
			
			if(gnss.speed_kph<10.0){
				ST7735_FillRectangle(85,21,22,11,ST7735_BLACK);
			}
			ST7735_WriteString(72,21,(char*)gnss.speed_kph_str,Font_7x10,WHITE,ST7735_BLACK);
			ST7735_WriteString(117,21,"km/h",Font_7x10,WHITE,ST7735_BLACK);
			ST7735_WriteString(5,55,(char*)gnss.date_cst_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			ST7735_WriteString(13,67,(char*)gnss.time_cst_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);	
			ST7735_WriteString(85,55,(char*)gnss.long_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);	
			ST7735_WriteString(85,67,(char*)gnss.lat_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			ST7735_WriteString(151,11,&gnss.lat_dir,Font_7x10,ST7735_BLUE,ST7735_BLACK);
			ST7735_WriteString(151,26,&gnss.long_dir,Font_7x10,ST7735_MAGENTA,ST7735_BLACK);
}





void disp_InvalidGNSSInfo(GNSS_info gnss){
			/*ST7735_FillRectangle(0,0,10,10,ST7735_YELLOW);  
			ST7735_WriteString(12,1,"GNSS WAIT",Font_7x10,ST7735_WHITE,ST7735_BLACK);*/
			ST7735_WriteString(0,15,(char*)gnss.maidenhead,Font_11x18,ST7735_GREEN,ST7735_BLACK);
			
		if(gnss.speed_kph>=10.0&&gnss.speed_kph<100.0){
				ST7735_FillRectangle(92,21,22,11,ST7735_BLACK);
			}
			
			if(gnss.speed_kph<10.0){
				ST7735_FillRectangle(85,21,22,11,ST7735_BLACK);
			}
			ST7735_WriteString(72,21,(char*)gnss.speed_kph_str,Font_7x10,WHITE,ST7735_BLACK);
			ST7735_WriteString(117,21,"km/h",Font_7x10,WHITE,ST7735_BLACK);
			ST7735_WriteString(5,55,(char*)gnss.date_cst_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			ST7735_WriteString(13,67,(char*)gnss.time_cst_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);	
			ST7735_WriteString(85,55,(char*)gnss.long_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);	
			ST7735_WriteString(85,67,(char*)gnss.lat_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			ST7735_WriteString(151,11,&gnss.lat_dir,Font_7x10,ST7735_BLUE,ST7735_BLACK);
			ST7735_WriteString(151,26,&gnss.long_dir,Font_7x10,ST7735_MAGENTA,ST7735_BLACK);
}


void show_basicStatus(GNSS_info gnss,float BattVolt,float Temperature){
			if(gnss.data_validity=='A'){
				ST7735_FillRectangle(0,0,10,10,ST7735_GREEN);
				ST7735_WriteString(12,1,"GNSS OK  ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
		}
			if(gnss.data_validity!='A'){
				ST7735_FillRectangle(0,0,10,10,ST7735_YELLOW);  
				ST7735_WriteString(12,1,"GNSS WAIT",Font_7x10,ST7735_WHITE,ST7735_BLACK);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
		}
			
		char temperature_Str[4];
		sprintf(temperature_Str,"%.1lf",Temperature);
		ST7735_WriteString(85,1,temperature_Str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			
		if(BattVolt>=3.93){
			ST7735_FillRectangle(155,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(148,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(141,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(134,0,5,10,ST7735_GREEN);
		}
		
		if(BattVolt>=3.79&&BattVolt<3.93){
			ST7735_FillRectangle(155,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(148,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(141,0,5,10,ST7735_GREEN);
			ST7735_FillRectangle(134,0,5,10,ST7735_BLACK);
		}
		
		if(BattVolt>=3.72&&BattVolt<3.79){
			ST7735_FillRectangle(155,0,5,10,ST7735_YELLOW);
			ST7735_FillRectangle(148,0,5,10,ST7735_YELLOW);
			ST7735_FillRectangle(141,0,5,10,ST7735_BLACK);
			ST7735_FillRectangle(134,0,5,10,ST7735_BLACK);
		}
		
		if(BattVolt<3.72){
			ST7735_FillRectangle(155,0,5,10,ST7735_RED);
			ST7735_FillRectangle(148,0,5,10,ST7735_BLACK);
			ST7735_FillRectangle(141,0,5,10,ST7735_BLACK);
			ST7735_FillRectangle(134,0,5,10,ST7735_BLACK);
		}
		
			
}




void show_detailGNSS(GNSS_info gnss){
	ST7735_WriteString(13,67,(char*)gnss.time_cst_str,Font_7x10,ST7735_WHITE,ST7735_BLACK);
			if(gnss.data_validity=='A'&&gnss.latitude!=0&&gnss.longitude!=0){
				disp_ValidGNSSInfo(gnss);
				//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
		}
		
			if(gnss.data_validity!='A'){
				disp_InvalidGNSSInfo(gnss);
				//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
		}
}



void show_bigTime(GNSS_info gnss){
	if(KeyR_PB0_Flag%2!=0){
		ST7735_WriteString(25,20,(char*)gnss.date_cst_str,Font_11x18,ST7735_WHITE,ST7735_BLACK);
		ST7735_WriteString(35,45,(char*)gnss.time_cst_str,Font_11x18,ST7735_WHITE,ST7735_BLACK);
		ST7735_WriteString(0,69,(char*)"CST",Font_7x10,ST7735_BLUE,ST7735_BLACK);
		ST7735_WriteString(124,69,(char*)"UTC+8",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	}else{
		ST7735_WriteString(25,20,(char*)gnss.date_utc_str,Font_11x18,ST7735_WHITE,ST7735_BLACK);
		ST7735_WriteString(35,45,(char*)gnss.time_utc_str,Font_11x18,ST7735_WHITE,ST7735_BLACK);
		ST7735_WriteString(0,69,(char*)"GMT",Font_7x10,ST7735_MAGENTA,ST7735_BLACK);
		ST7735_WriteString(124,69,(char*)"UTC+0",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	}
}


void show_speed(GNSS_info gnss){
	/*Show Kilometer per Hour*/
			if(gnss.speed_kph>=100.0&&gnss.speed_kph<1000.0){
				ST7735_FillRectangle(83,15,22,18,ST7735_BLACK);
			}
			if(gnss.speed_kph>=10.0&&gnss.speed_kph<100.0){
				ST7735_FillRectangle(72,15,33,18,ST7735_BLACK);
			}
			if(gnss.speed_kph<10.0){
				ST7735_FillRectangle(61,15,40,18,ST7735_BLACK);
			}
			ST7735_WriteString(17,15,(char*)gnss.speed_kph_str,Font_11x18,WHITE,ST7735_BLACK);
			ST7735_WriteString(104,15,"km/h",Font_11x18,ST7735_CYAN,ST7735_BLACK);
	/*Show meter per Second*/
			if(gnss.speed_mps>=100.0&&gnss.speed_mps<1000.0){
				ST7735_FillRectangle(83,38,22,18,ST7735_BLACK);
			}
			if(gnss.speed_mps>=10.0&&gnss.speed_mps<100.0){
				ST7735_FillRectangle(72,38,33,18,ST7735_BLACK);
			}
			if(gnss.speed_mps<10.0){
				ST7735_FillRectangle(61,38,40,18,ST7735_BLACK);
			}
			ST7735_WriteString(17,38,(char*)gnss.speed_mps_str,Font_11x18,WHITE,ST7735_BLACK);
			ST7735_WriteString(104,38,"m/s",Font_11x18,ST7735_CYAN,ST7735_BLACK);
	/*Show Knots*/
			if(gnss.speed_knot>=100.0&&gnss.speed_knot<1000.0){
				ST7735_FillRectangle(83,60,22,18,ST7735_BLACK);
			}
			if(gnss.speed_knot>=10.0&&gnss.speed_knot<100.0){
				ST7735_FillRectangle(72,60,33,18,ST7735_BLACK);
			}
			if(gnss.speed_knot<10.0){
				ST7735_FillRectangle(61,60,40,18,ST7735_BLACK);
			}
			ST7735_WriteString(17,60,(char*)gnss.speed_knot_str,Font_11x18,WHITE,ST7735_BLACK);
			ST7735_WriteString(104,60,"Kt",Font_11x18,ST7735_CYAN,ST7735_BLACK);
}


void show_sysInfo(uint8_t* sysTemp,uint8_t* sysVolt,uint8_t* batVolt,uint8_t* softVer){
	ST7735_WriteString(18,15,"System Info",Font_11x18,ST7735_WHITE,ST7735_BLACK);
	
	ST7735_WriteString(10,35,"Sys_Temp:",Font_7x10,ST7735_YELLOW,ST7735_BLACK);
	ST7735_WriteString(75,35,(char*)sysTemp,Font_7x10,ST7735_WHITE,ST7735_BLACK);
	
	ST7735_WriteString(10,47,"Sys_Volt:",Font_7x10,ST7735_YELLOW,ST7735_BLACK);
	ST7735_WriteString(75,47,(char*)sysVolt,Font_7x10,ST7735_WHITE,ST7735_BLACK);
	
	ST7735_WriteString(10,59,"Bat_Volt:",Font_7x10,ST7735_YELLOW,ST7735_BLACK);
	ST7735_WriteString(75,59,(char*)batVolt,Font_7x10,ST7735_WHITE,ST7735_BLACK);
	
	ST7735_WriteString(10,70,"Soft_Ver:",Font_7x10,ST7735_YELLOW,ST7735_BLACK);
	ST7735_WriteString(75,70,(char*)softVer,Font_7x10,ST7735_WHITE,ST7735_BLACK);

}


void show_originalData(uint8_t* originalPack,GNSS_info gnss){
	ST7735_FillRectangle(0,69,10,10,ST7735_BLUE);
	ST7735_WriteString(15,69,"BCC Check Passed!",Font_7x10,ST7735_WHITE,ST7735_BLACK);
	
	if((lastStatus!=gnss.data_validity)/*||(lastStrLen!=strlen((char*)originalPack))*/){
		ST7735_FillRectangle(0,12,160,68,ST7735_BLACK);
		lastStatus=gnss.data_validity;
		//lastStrLen=strlen((char*)originalPack);
		ST7735_FillRectangle(0,12,160,68,ST7735_BLACK);
		memset((uint8_t*)originalPack,0,sizeof(originalPack));
	}
	ST7735_WriteString(0,20,(char*)originalPack,Font_7x10,ST7735_WHITE,ST7735_BLACK);
}

#include <disp.h>

void disp_Frame(void){
	ST7735_FillRectangle(0,0,10,10,RED);
	ST7735_WriteString(12,0,"GNSS FAIL",Font_7x10,ST7735_WHITE,ST7735_BLACK);
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
			ST7735_FillRectangle(0,0,10,10,ST7735_GREEN);
			ST7735_WriteString(12,0,"GNSS OK  ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
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
			ST7735_WriteString(151,2,&gnss.lat_dir,Font_7x10,ST7735_BLUE,ST7735_BLACK);
			ST7735_WriteString(151,17,&gnss.long_dir,Font_7x10,ST7735_MAGENTA,ST7735_BLACK);
}





void disp_InvalidGNSSInfo(GNSS_info gnss){
			ST7735_FillRectangle(0,0,10,10,ST7735_YELLOW);  
			ST7735_WriteString(12,0,"GNSS WAIT",Font_7x10,ST7735_WHITE,ST7735_BLACK);
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
			ST7735_WriteString(151,2,&gnss.lat_dir,Font_7x10,ST7735_BLUE,ST7735_BLACK);
			ST7735_WriteString(151,171,&gnss.long_dir,Font_7x10,ST7735_MAGENTA,ST7735_BLACK);
}

/*
 *@filename: air551g.c 
 *@Description: Air551G GNSS Module operation file
 *@version: 1.0
 *@Author: BH8PHG W_Linus
 *@Date: 2022/04/25
 */
 
#include <air551g.h>

uint8_t Init_SetRprtRate[]="$PGKC101,100*32\r\n"; 		//Set NMEA Report rate to 10Hz(100ms)
uint8_t Init_ColdStartup[]="$PGKC030,4,2*2A\r\n"; 		//Set GNSS Cold Startup
uint8_t Init_WarmStartup[]="$PGKC030,2,2*2C\r\n"; 		//Set GNSS Warm Startup
uint8_t Init_HotStartup[]="$PGKC030,1,2*2F\r\n"; 		//Set GNSS Hot Startup
uint8_t Init_Use_L1andL5[]="$PGKC121,5,F,7*2B\r\n";		//Dual band GNSS L1+L5 enable
uint8_t Init_GKC242[]="$PGKC242,0,1,0,0,0,0,0*36\r\n";//Only get GNRMC package

uint8_t rxBuffer[300];	//GNSS raw data receiving cache
uint8_t rptBuffer[120];	//Forwarding to the upper computer and caching for data parsing

uint8_t commaPos[12];	//position index of comma

volatile uint16_t packSize;  //size of GNRMC data
volatile uint8_t bcc_Checksum;



/*
 *@name: air551g_init
 *@brief: initialize the Air551G GNSS module
 *@param: none
 *@return: none
 */
void air551g_init(){
	HAL_Delay(5000);
	HAL_UART_Transmit(AIR551G_uart,Init_WarmStartup,sizeof(Init_WarmStartup),0xFFFF);
	HAL_Delay(500);
	HAL_UART_Transmit(AIR551G_uart,Init_Use_L1andL5,sizeof(Init_Use_L1andL5),0xFFFF);
	HAL_Delay(500);
	HAL_UART_Transmit(AIR551G_uart,Init_GKC242,sizeof(Init_GKC242),0xFFFF);
	HAL_Delay(500);
	HAL_UART_Transmit(AIR551G_uart,Init_SetRprtRate,sizeof(Init_SetRprtRate),0xFFFF);
	HAL_Delay(500);
	HAL_UART_Receive_DMA(AIR551G_uart,rxBuffer,200); //Receive 2 Packs of NMEA data, Then abstract 1 pack to avoid data error.
}



/*
 *@name: air551g_dataGet
 *@brief: Get the GNSS info from module
 *@param: none
 *@return: GNSS_info
 */
GNSS_info air551g_dataGet(void){
	GNSS_info gnssdata={0};
	uint8_t bcc_temp=0;
	
	//Calculate the BCC checksum
	for(int i=1;i<packSize-5;i++){
		bcc_temp^=rptBuffer[i];
	}
	bcc_Checksum=bcc_temp;
	
	sscanf((char*)rptBuffer+commaPos[11]+5,"%x",&gnssdata.BCC_Checksum);//Get the incoming BCC checksum
	
	//Compare the calculated checksum with the incoming checksum
	if(bcc_Checksum==gnssdata.BCC_Checksum){
		//After the verification is passed, the data acquisition operation is performed.
		
		//Get location validity indication 
		sscanf((char*)rptBuffer+commaPos[1]+1,"%c",&gnssdata.data_validity);//A-Positioning valid | V-Positioning invalid
		gnssdata=gnss_getTimeDate(gnssdata);
		gnssdata=gnss_getLocation(gnssdata);
		gnssdata=gnss_getSpeed(gnssdata);
		gnss_getMaidenhead(gnssdata.latitude,gnssdata.longitude,gnssdata.maidenhead);
	}
	return gnssdata;

}




/*
 *@name: air551g_prepareRptBuffer
 *@brief: Prepare packets for forwarding to PC
 *@param: none
 *@return: none
 */
void air551g_prepareRptBuffer(){
	uint8_t data_begin,data_end;
	uint8_t commaTemp=0;
	//In 2 packs buffer to find where the 1 pack start and where to end
	for(int i=0;i<150;i++){
		if(rxBuffer[i]=='$'){
			data_begin=i;
			break;
		}
	}
	
	for(int j=data_begin;j<300;j++){
		if(rxBuffer[j]=='*'){
			data_end=j;
			break;
		}
	}
	
	packSize=(data_end-data_begin)+5;
	memcpy(rptBuffer,rxBuffer+data_begin,packSize);

	for(int a=0;a<packSize;a++){ //GNRMC data uses commas for data splitting, so you need to find all comma indices
		if(rptBuffer[a]==','){
			commaPos[commaTemp]=a;
			commaTemp+=1;
		}
	}
}



/*
 *@name: air551g_rpt
 *@brief: send packets for forwarding to PC
 *@param: none
 *@return: none
 */
void air551g_rpt(void){
	air551g_prepareRptBuffer();
	HAL_UART_Transmit(PC_uart,rptBuffer,packSize,0xFFFF);
}



/*
 *@name: gnss_getTimeDate
 *@brief: Extract time information from GNRMC information
 *@param: gnssdata
 *@return: GNSS_info
 */
GNSS_info gnss_getTimeDate(GNSS_info gnssdata){
	//get hour(utc)
	sscanf((char*)rptBuffer+commaPos[0]+1,"%2d",&gnssdata.hour_utc);
	//convert to CST(UTC+8)
	gnssdata.hour_cst=gnssdata.hour_utc+8;
	if(gnssdata.hour_cst>=24){
		gnssdata.hour_cst-=24;
	}
	//get minute and second
	sscanf((char*)rptBuffer+commaPos[0]+3,"%2d",&gnssdata.minute);
	sscanf((char*)rptBuffer+commaPos[0]+5,"%2d",&gnssdata.second);
	//get day(utc)
	sscanf((char*)rptBuffer+commaPos[8]+1,"%2d",&gnssdata.day_utc);
	//convert to CST(UTC+8)
	if(gnssdata.hour_cst<gnssdata.hour_utc){gnssdata.day_cst=gnssdata.day_utc+1;}
		else{ gnssdata.day_cst=gnssdata.day_utc;}
		
	sscanf((char*)rptBuffer+commaPos[8]+5,"%2d",&gnssdata.year_utc);
	gnssdata.year_utc+=2000;//convert YY to YYYY
		
	sscanf((char*)rptBuffer+commaPos[8]+3,"%2d",&gnssdata.month_utc);
		
	if(gnssdata.day_cst!=gnssdata.day_utc){ //if day(UTC+0) != day(UTC+8),then we need to judge is it end of month or not
		switch(gnssdata.month_utc){
			case 1:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=2;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;
				
			case 2:
				if(gnssdata.year_utc%4==0){ //Leap year judgment
					if(gnssdata.day_utc==29){
						gnssdata.day_cst=1;
						gnssdata.month_cst=3;
					}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;				
				}
				if(gnssdata.day_utc==28){
					gnssdata.day_cst=1;
					gnssdata.month_cst=3;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
			}
				break;
				
			case 3:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=4;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;
				
			case 4:
				if(gnssdata.day_utc==30){
					gnssdata.day_cst=1;
					gnssdata.month_cst=5;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;
				
			case 5:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=6;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;				
				
			case 6:
				if(gnssdata.day_utc==30){
					gnssdata.day_cst=1;
					gnssdata.month_cst=7;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;		

			case 7:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=8;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;		

			case 8:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=9;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;				
				
			case 9:
				if(gnssdata.day_utc==30){
					gnssdata.day_cst=1;
					gnssdata.month_cst=10;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;						

			case 10:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=11;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;

			case 11:
				if(gnssdata.day_utc==30){
					gnssdata.day_cst=1;
					gnssdata.month_cst=12;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;							

			case 12:
				if(gnssdata.day_utc==31){
					gnssdata.day_cst=1;
					gnssdata.month_cst=1;
					gnssdata.year_cst=gnssdata.year_utc+1;
				}else{
						gnssdata.year_cst=gnssdata.year_utc;
						gnssdata.month_cst=gnssdata.month_utc;					
				}
				break;								
		}
	}else{
		gnssdata.year_cst=gnssdata.year_utc;
		gnssdata.month_cst=gnssdata.month_utc;
	}
	sprintf((char*)gnssdata.date_utc_str,"%04d/%02d/%02d",gnssdata.year_utc,gnssdata.month_utc,gnssdata.day_utc);
	sprintf((char*)gnssdata.date_cst_str,"%04d/%02d/%02d",gnssdata.year_cst,gnssdata.month_cst,gnssdata.day_cst);
	sprintf((char*)gnssdata.time_utc_str,"%02d:%02d:%02d",gnssdata.hour_utc,gnssdata.minute,gnssdata.second);
	sprintf((char*)gnssdata.time_cst_str,"%02d:%02d:%02d",gnssdata.hour_cst,gnssdata.minute,gnssdata.second);
	return gnssdata;
}




/*
 *@name: gnss_getLocation
 *@brief: Extract location information from GNRMC information
 *@param: gnssdata
 *@return: GNSS_info
 */
GNSS_info gnss_getLocation(GNSS_info gnssdata){
	sscanf((char*)rptBuffer+commaPos[2]+1,"%08f",&gnssdata.latitude_ddmm);
	sscanf((char*)rptBuffer+commaPos[3]+1,"%c",&gnssdata.lat_dir);
	sscanf((char*)rptBuffer+commaPos[4]+1,"%09f",&gnssdata.longitude_dddmm);
	sscanf((char*)rptBuffer+commaPos[5]+1,"%c",&gnssdata.long_dir);
	gnssdata.latitude_ddmm=gnssdata.latitude_ddmm/100.0;
	gnssdata.longitude_dddmm=gnssdata.longitude_dddmm/100.0;
	
	/*convert ddmm.mmmm format data to dd.dddddd format*/
	gnssdata.latitude=(int)gnssdata.latitude_ddmm + (100.0*(gnssdata.latitude_ddmm-(int)gnssdata.latitude_ddmm))/60.0;
	gnssdata.longitude=(int)gnssdata.longitude_dddmm + (100.0*(gnssdata.longitude_dddmm-(int)gnssdata.longitude_dddmm))/60.0;
	sprintf((char*)gnssdata.lat_str,"%06f",gnssdata.latitude);
	sprintf((char*)gnssdata.long_str,"%06f",gnssdata.longitude);
	return gnssdata;
}




/*
 *@name: gnss_getSpeed
 *@brief: Extract speed information from GNRMC information
 *@param: gnssdata
 *@return: GNSS_info
 */
GNSS_info gnss_getSpeed(GNSS_info gnssdata){
	sscanf((char*)rptBuffer+commaPos[6]+1,"%3f",&gnssdata.speed_knot);
	gnssdata.speed_kph=gnssdata.speed_knot*1.852;
	gnssdata.speed_mps=gnssdata.speed_kph/3.6;
	sprintf((char*)gnssdata.speed_kph_str,"%.0002f",gnssdata.speed_kph);
	sprintf((char*)gnssdata.speed_mps_str,"%.02f",gnssdata.speed_mps);
	sprintf((char*)gnssdata.speed_knot_str,"%.02f",gnssdata.speed_knot);
	return gnssdata;
}



#include "stm32g0xx_hal.h"
#include "Lcd_Driver.h"

//Һ��IO��ʼ������

//��SPI���ߴ���һ��8λ����
void  SPI_WriteData(uint8_t Data)
{
	HAL_SPI_Transmit(&ST7735_SPI,&Data,sizeof(Data),0xffff);
}

//��Һ����дһ��8λָ��
void Lcd_WriteIndex(uint8_t Index)
{
   //SPI д����ʱ��ʼ
   LCD_RS_CLR;
	 SPI_WriteData(Index);
}

//��Һ����дһ��8λ����
void Lcd_WriteData(uint8_t Data)
{
   LCD_RS_SET;
   SPI_WriteData(Data); 
}
//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(uint16_t Data)
{

   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//д���8λ����
	 SPI_WriteData(Data); 			//д���8λ����

}

void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{	
	Lcd_Reset(); //Reset before LCD Init.
	 Lcd_WriteIndex(0xfe);     //Inter register enable 1
    Lcd_WriteIndex(0xfe);     
    Lcd_WriteIndex(0xfe);
    Lcd_WriteIndex(0xef);     //Inter register enable 2

    Lcd_WriteIndex(0xb3);     //????????
    Lcd_WriteData(0x03);
        
    Lcd_WriteIndex(0x36);     //Memory Access Ctrl
    Lcd_WriteData(0x68);        //MY MX MV ML BGR MH 0 0  ??D8 
        
    Lcd_WriteIndex(0x3a);             //Pixel Format Set
    Lcd_WriteData(0x05);            //16BIT  565??

    Lcd_WriteIndex(0xb6);           //????
    Lcd_WriteData(0x11);
    Lcd_WriteIndex(0xac);  
    Lcd_WriteData(0x0b);

    Lcd_WriteIndex(0xb4);             //Display Inversion Control
    Lcd_WriteData(0x21);

    Lcd_WriteIndex(0xb1);             //????
    Lcd_WriteData(0xc0);

    Lcd_WriteIndex(0xe6);              //VREG1_CTL   
    Lcd_WriteData(0x50);
    Lcd_WriteData(0x43);          //???
    Lcd_WriteIndex(0xe7);             //VREG2_CTL
    Lcd_WriteData(0x56);            //-3V
    Lcd_WriteData(0x43);          //

    Lcd_WriteIndex(0xF0);             //SET_GAMMA1
    Lcd_WriteData(0x1f);
    Lcd_WriteData(0x41);
    Lcd_WriteData(0x1B);
    Lcd_WriteData(0x55);
    Lcd_WriteData(0x36);
    Lcd_WriteData(0x3d);
    Lcd_WriteData(0x3e);
    Lcd_WriteData(0x0); 
    Lcd_WriteData(0x16);
    Lcd_WriteData(0x08);
    Lcd_WriteData(0x09);
    Lcd_WriteData(0x15);
    Lcd_WriteData(0x14);
    Lcd_WriteData(0xf); 

    Lcd_WriteIndex(0xF1);             //SET_GAMMA2
        
    Lcd_WriteData(0x1f);
    Lcd_WriteData(0x41);
    Lcd_WriteData(0x1B);
    Lcd_WriteData(0x55);
    Lcd_WriteData(0x36);
    Lcd_WriteData(0x3d);
    Lcd_WriteData(0x3e);
    Lcd_WriteData(0x0); 
    Lcd_WriteData(0x16);
    Lcd_WriteData(0x08);
    Lcd_WriteData(0x09);
    Lcd_WriteData(0x15);
    Lcd_WriteData(0x14);
    Lcd_WriteData(0xf); 

    Lcd_WriteIndex(0xfe);         //??Inter register enable
    Lcd_WriteIndex(0xff);

    Lcd_WriteIndex(0x35);         //Tearing Effect Line ON
    Lcd_WriteData(0x00);
    Lcd_WriteIndex(0x44);         //Scan line set
    Lcd_WriteData(0x00);
    Lcd_WriteIndex(0x11);         //Sleep Out
    HAL_Delay(120);          //DELAY120ms
    Lcd_WriteIndex(0x29);         //???

    Lcd_WriteIndex(0x2A); //Set Column Address 
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00); 
    Lcd_WriteData(0x00); 
    Lcd_WriteData(0x9f); 
    
    Lcd_WriteIndex(0x2B); //Set Page Address 
    Lcd_WriteData(0x00); 
    Lcd_WriteData(0x18); 
    Lcd_WriteData(0x00); 
    Lcd_WriteData(0x67); 

		Lcd_WriteIndex(0x2c);
	//LCD Init For 1.44Inch LCD Panel with ST7735R.
/*	Lcd_WriteIndex(0x11);//Sleep exit 
	HAL_Delay(120);
	Lcd_WriteIndex(0x21); 
Lcd_WriteIndex(0x21); 

Lcd_WriteIndex(0xB1); 
Lcd_WriteData(0x05);
Lcd_WriteData(0x3A);
Lcd_WriteData(0x3A);

Lcd_WriteIndex(0xB2);
Lcd_WriteData(0x05);
Lcd_WriteData(0x3A);
Lcd_WriteData(0x3A);

Lcd_WriteIndex(0xB3); 
Lcd_WriteData(0x05);  
Lcd_WriteData(0x3A);
Lcd_WriteData(0x3A);
Lcd_WriteData(0x05);
Lcd_WriteData(0x3A);
Lcd_WriteData(0x3A);

Lcd_WriteIndex(0xB4);
Lcd_WriteData(0x03);

Lcd_WriteIndex(0xC0);
Lcd_WriteData(0x62);
Lcd_WriteData(0x02);
Lcd_WriteData(0x04);

Lcd_WriteIndex(0xC1);
Lcd_WriteData(0xC0);

Lcd_WriteIndex(0xC2);
Lcd_WriteData(0x0D);
Lcd_WriteData(0x00);

Lcd_WriteIndex(0xC3);
Lcd_WriteData(0x8D);
Lcd_WriteData(0x6A);   

Lcd_WriteIndex(0xC4);
Lcd_WriteData(0x8D); 
Lcd_WriteData(0xEE); 

Lcd_WriteIndex(0xC5);*/  /*VCOM*/
/*Lcd_WriteData(0x0E);    

Lcd_WriteIndex(0xE0);
Lcd_WriteData(0x10);
Lcd_WriteData(0x0E);
Lcd_WriteData(0x02);
Lcd_WriteData(0x03);
Lcd_WriteData(0x0E);
Lcd_WriteData(0x07);
Lcd_WriteData(0x02);
Lcd_WriteData(0x07);
Lcd_WriteData(0x0A);
Lcd_WriteData(0x12);
Lcd_WriteData(0x27);
Lcd_WriteData(0x37);
Lcd_WriteData(0x00);
Lcd_WriteData(0x0D);
Lcd_WriteData(0x0E);
Lcd_WriteData(0x10);

Lcd_WriteIndex(0xE1);
Lcd_WriteData(0x10);
Lcd_WriteData(0x0E);
Lcd_WriteData(0x03);
Lcd_WriteData(0x03);
Lcd_WriteData(0x0F);
Lcd_WriteData(0x06);
Lcd_WriteData(0x02);
Lcd_WriteData(0x08);
Lcd_WriteData(0x0A);
Lcd_WriteData(0x13);
Lcd_WriteData(0x26);
Lcd_WriteData(0x36);
Lcd_WriteData(0x00);
Lcd_WriteData(0x0D);
Lcd_WriteData(0x0E);
Lcd_WriteData(0x10);

Lcd_WriteIndex(0x3A); 
Lcd_WriteData(0x05);

Lcd_WriteIndex(0x36);
Lcd_WriteData(0xA8);//

Lcd_WriteIndex(0x29); 
*/
	 LCD_BL_SET;
}


/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+0x18);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+0x18);	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 �������ܣ���TFTĳһ�����ɫ                          
 ���ڲ�����color  ����ɫֵ                                 
******************************************/
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);

  //Lcd_ReadData();//���������ֽ�
  //Data=Lcd_ReadData();
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}


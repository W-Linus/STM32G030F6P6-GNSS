
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  生成日期   : 2018-1111
//  最近修改   : 
//  功能描述   : 0.96寸ISP LCD 4接口演示例程(STM32系列)
/******************************************************************************
//本程序适用与STM32F103C8
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）
//              RES   接PB0
//              DC    接PB1
//              CS    接PA4//可以直接接地
//              BLK    接P10 BLK可以悬空不接；在需要关闭背光的时候将BLK置低电平
*******************************************************************************/
// 修改历史   :
// 日    期   : 
// 修改内容   : 
//******************************************************************************/

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

#define ST7735_SPI hspi1
extern SPI_HandleTypeDef ST7735_SPI;

#define X_MAX_PIXEL	        160
#define Y_MAX_PIXEL	        80


#define LCD_RES_Pin       GPIO_PIN_4
#define LCD_RES_GPIO_Port GPIOA
#define LCD_CS_Pin        GPIO_PIN_11
#define LCD_CS_GPIO_Port  GPIOA
#define LCD_DC_Pin        GPIO_PIN_5
#define LCD_DC_GPIO_Port  GPIOA
#define LCD_BackLight_GPIO_Port GPIOA
#define LCD_BackLight_Pin GPIO_PIN_12


#define	LCD_CS_SET  	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)
#define	LCD_RS_SET  	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)
#define	LCD_BL_SET  	HAL_GPIO_WritePin(LCD_BackLight_GPIO_Port,LCD_BackLight_Pin,GPIO_PIN_SET)
#define	LCD_RST_SET  	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_SET)
//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET) 
    
#define	LCD_RST_CLR  	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_RESET)
#define	LCD_RS_CLR  	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define	LCD_BL_CLR  	HAL_GPIO_WritePin(LCD_BackLight_GPIO_Port,LCD_BackLight_Pin,GPIO_PIN_RESET)

#define LCD_DATAOUT(x) HAL_SPI_Transmit(&ST7735_SPI, x, 1, HAL_MAX_DELAY)

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);


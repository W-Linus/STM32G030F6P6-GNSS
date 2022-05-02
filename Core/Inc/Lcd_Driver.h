
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��������   : 2018-1111
//  ����޸�   : 
//  ��������   : 0.96��ISP LCD 4�ӿ���ʾ����(STM32ϵ��)
/******************************************************************************
//������������STM32F103C8
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB0
//              DC    ��PB1
//              CS    ��PA4//����ֱ�ӽӵ�
//              BLK    ��P10 BLK�������ղ��ӣ�����Ҫ�رձ����ʱ��BLK�õ͵�ƽ
*******************************************************************************/
// �޸���ʷ   :
// ��    ��   : 
// �޸�����   : 
//******************************************************************************/

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

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
//Һ�����ƿ���0�������궨��
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


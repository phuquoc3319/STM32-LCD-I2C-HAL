
/** Put this in the src folder **/

#include "i2c-lcd.h"
#include "stdarg.h"
#include "stdio.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD (0x7E) // change this according to ur setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	while (HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100) != HAL_OK)
	{
		if (HAL_I2C_GetError (&hi2c1) != HAL_I2C_ERROR_AF)
		{
			Error_Handler ();
		}
	}
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	
	while (HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100) != HAL_OK)
	{
		if (HAL_I2C_GetError (&hi2c1) != HAL_I2C_ERROR_AF)
		{
			Error_Handler ();
		}
	}
}

void lcd_init (void)
{
	lcd_send_cmd (0x33); 
	lcd_send_cmd (0x32); 
	lcd_send_cmd (0x28); //Function Set 4-bit mode 
	lcd_send_cmd (0x0c); //Display On/Off Control 
	lcd_send_cmd (0x06); //Entry mode set 
	lcd_send_cmd (0x02); //Clear Display 
//	lcd_send_cmd (0x01);
	//Minimum delay to wait before driving LCD module 
	HAL_Delay (1000);
	
}
void lcd_print_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

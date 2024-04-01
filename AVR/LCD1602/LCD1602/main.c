#include <avr/io.h>
#include "liquid_crystal_i2c.h"

int main(void)
{
	
	
	
	
	LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_2LINE); // intialize 4-lines display

	lq_turnOnBacklight(&device); // simply turning on the backlight

	lq_print(&device, "Hello world!");
	lq_setCursor(&device, 1, 0); // moving cursor to the next line
	lq_print(&device, "How are you?");
	
}
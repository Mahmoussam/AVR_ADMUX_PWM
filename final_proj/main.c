


#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LCD/ALCD.h"

void init_ADC();
uint16_t ADC_read(uint8_t channel);
/*
adc*5/2^10 = v_in

*/
int main(void)
{
    lcd_init(16);
	init_ADC();
	DDRD |=(1<<6);//for OC0A,PD6
	TCCR0A =(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |=(1<<CS00)|(1<<CS02);//1024 as prescaler to obtain cycle with 16 ms width
    uint32_t adc_val;
	char lcd_line1[16]="ADC val:       ",lcd_line2[16]="Duty cycle:    ";
	
	
	while (1)
    {	
		//calculate and prepare necessary data
		adc_val=ADC_read(0);
		uint8_t duty_cycle=(adc_val*100/1023);
		//calculate value for OCR0A
		uint8_t timer_val=duty_cycle*255/100;
		if(timer_val>0)timer_val--;
		OCR0A=timer_val;
		//build the output strings
		for(int i=8;i<16;i++)lcd_line1[i]=' ';
		for(int i=11;i<13;i++)lcd_line2[i]=' ';
		itoa(adc_val,lcd_line1+8,10);
		itoa(duty_cycle,lcd_line2+11,10);
		//lcd_line2[14]='%';
		//print to screen
		lcd_gotoxy(0,0);
		lcd_puts(lcd_line1);
		lcd_gotoxy(0,1);
		lcd_puts(lcd_line2);
		lcd_putchar('%');
		_delay_ms(600);
		lcd_clear();
	}
}
void init_ADC(void){
	ADMUX =0x40;// use chip's vcc as ref,channel 0 
	ADCSRA =0x87;// 1000 0111 ===>enable adc with prescalar 128
	ADCSRB=0x00;// best practice
}
uint16_t ADC_read(uint8_t channel){
	ADMUX |=channel;
	ADCSRA |= (1 << ADSC); // Start ADC conversion
	while(!(ADCSRA & (1<<ADIF)));//wait till end of conversion
	ADCSRA |=(1<<ADIF);//reset the flag
	uint16_t result=ADCL|(ADCH<<8);//ADC;
	return result;
}
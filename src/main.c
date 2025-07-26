#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stc12.h>
#include "main.h"
#include "uart.h"

//FCPU = 11.0592 MHz

#define RES0 0
#define RES1 1

#define ILIMIT 3
//#define ILIMIT2 4

#define MOTOUT P1_2
#define LED P3_6

void main(void)
{

	/*----------------------------------------------------------------*/
    /*----------------------		ADC		--------------------------*/
	ADC_CONTR |= (1<<7);	//enable
    CLK_DIV |= (1<<5);		//right justify ADC
    P1ASF |= (1<<RES0)|(1<<RES1)|(1<<ILIMIT);
    //P1M1 |=  (1<<RES0)|(1<<RES1)|(1<<ILIMIT1);
	P1 |= (1<<RES0)|(1<<RES1);
    
    
    /*----------------------------------------------------------------*/
    /*---------------------		PINS	------------------------------*/
    P1M0 |= (1<<2); 
    P3M0 |= (1<<7); 
    
    
    /*----------------------------------------------------------------*/
    /*------------------		PCA			--------------------------*/
    
    CCAPM2 |= (1<<6)|(1<<1); 	//ECOM2, PWM2
    CMOD |= 1<<1;
    CCON |= (1<<6);				//run
    CCAP2L = 0xFF;				//off
    CCAP2H = 0xFF;				//off
    
    /*----------------------------------------------------------------*/
    /*------------------		TIMER0		--------------------------*/
	AUXR |= 0x80;			//imer clock is 1T mode
	TMOD &= 0xF0;			//Set timer work mode
	TL0 = 0xCD;				//Initial timer value
	TH0 = 0xD4;				//Initial timer value
    /*----------------------------------------------------------------*/
    
    EA = 1;
    int16_t res0, res1;
    int16_t current, counts = 0;
    int16_t current_lim = 0;
    uint8_t psc = 0;
    
    
	delay_msp(300);
    LED = 0;
    MOTOUT = 1;
    delay_msp(100);
    
    while(1) {
		
		res0 = adc_read(RES0);
		res1 = adc_read(RES1);
		current_lim = adc_read(ILIMIT) >> 1;
		
		if(res0 == 0) res1 += 32;
		if(res1 == 0) res0 += 32;
				

		if(res0 > res1){
			current = res0 - res1;
		}else{
			current = res1 - res0;
		}
		
		
		if(current > current_lim){
			CCAP2L = 0xFF;
			CCAP2H = 0xFF;
			CCON = 0;
			MOTOUT = 0;
			P3_7 = 0;
			LED = 1; 
			
			while(1);
		}
		
		if((CCAP2L > 0 && psc++ > 10)){
			CCAP2L -= 1;
			CCAP2H -= 1;
			psc = 0;
		}
		
		delay_msp(10);
    }
}

void delay_msp(__data uint16_t ms)
{
    //load 57536 into T0
    TF0 = 0;
    TH0 = 0xCD;
    TL0 = 0xD4;
    TR0 = 1;
    while(ms--) {
        while(TF0 == 0);
        TH0 = 0xCD;
		TL0 = 0xD4;
        TF0 = 0;
    }
    TR0 = 0;
}

uint16_t adc_read(uint8_t channel)
{
	channel;
	__asm
	mov	a, dpl
	orl a, #0x88
	mov _ADC_CONTR, a
	nop
	nop
	nop
	nop
	nop
adcloop:
	mov a, _ADC_CONTR
	jnb acc.4, adcloop
	mov _ADC_CONTR, #0x00
	
	mov dpl, _ADC_RESL
	mov dph, _ADC_RES
	__endasm;
	return;
}

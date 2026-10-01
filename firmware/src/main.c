#include <ch32fun.h>
#include <stdio.h>

int main(){
    SystemInit();
    RCC->APB2PCENR = RCC_APB2Periph_GPIOD;

    GPIOD->CFGLR &= ~(0xf<<(4*0));
	GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP)<<(4*0);

    while(1){
        GPIOD->BSHR = 1;	 // Turn on GPIOD0
		Delay_Ms( 50 );
		GPIOD->BSHR = 1<<16; // Turn off GPIOD0
		Delay_Ms( 50 );
        printf("Test");
        Delay_Ms(2000);
    }
}

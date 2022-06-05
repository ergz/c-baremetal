// the user led is connected to port A pin 5 (PA5)

// definition of addresses on STM32
#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x00003800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)
#define AHB1_ENBL_R_OFFSET		(0x30UL)
#define RCC_AHB1_ENBL_R			(*(volatile unsigned int*)(RCC_BASE + AHB1_ENBL_R_OFFSET))

#define MODE_R_OFFSET 			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int*)(GPIOA_BASE + MODE_R_OFFSET))

//#define GPIOA_MODE 				(1U<<10) // make mode reg be output
#define GPIOA_ENBL				(1U<<0) // turn on bit 0

#define ODR_OFFSET 				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int*)(GPIOA_BASE + ODR_OFFSET))

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

// 0x4002 0000 - 0x4002 03FF

int main(void)
{
	// enable clock access to GPIOA
	RCC_AHB1_ENBL_R |= GPIOA_ENBL; // the bit OR is basically adding these two registers

	// set PA5 as output pin
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &= ~(1U<<11);


	for (;;) {
		// toggle the led
		GPIOA_OD_R |= LED_PIN;
	}
}

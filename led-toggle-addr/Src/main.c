#include <stdint.h>


#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET				(0x00003800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)
#define AHB1_ENBL_R_OFFSET		(0x30UL)
#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_ENBL				(1U<<0) // turn on bit 0
#define ODR_OFFSET				(0x14UL)

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_TypeDef;

typedef struct {
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
} RCC_TypeDef;

#define RCC					((RCC_TypeDef*)RCC_BASE)
#define GPIOA				((GPIO_TypeDef*)GPIOA_BASE)

int main(void)
{
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_ENBL;

	// set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	for (;;) {
		// toggle the led
		for (int i = 0; i < 1000000; i++);
		GPIOA->ODR ^= LED_PIN;
	}
}










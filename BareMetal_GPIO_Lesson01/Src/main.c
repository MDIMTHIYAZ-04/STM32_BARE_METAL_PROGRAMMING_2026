#include <stdint.h>
#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018U)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004U)
#define GPIOC_BSRR (*(volatile uint32_t *)0x40011010U)

void delay(void)
{
    for (volatile uint32_t i = 0; i < 1000000U; i++)
    {

    }
}

int main(void)
{
	//clock config
	RCC_APB2ENR |= (1U << 4);
	// gpioc config
	GPIOC_CRH &= ~(0xFU << 20);
	GPIOC_CRH |=  (0x2U << 20);
	GPIOC_CRH |=  (0x4U << 20);
	// gpio13 to high
	while (1)
	{
	    GPIOC_BSRR = (1U << 29);  // LED ON
	    delay();

	    GPIOC_BSRR = (1U << 13);  // LED OFF
	    delay();
	}
}

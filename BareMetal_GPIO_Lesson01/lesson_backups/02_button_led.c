
#include <stdint.h>

/* ================= RCC REGISTERS ================= */

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018UL)

/* ================= GPIOA REGISTERS ================ */

#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800UL)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808UL)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080CUL)

/* ================= GPIOC REGISTERS ================ */

#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004UL)
#define GPIOC_ODR   (*(volatile uint32_t *)0x4001100CUL)

/* ================= PIN DEFINITIONS ================ */

#define BUTTON_PIN  0U      /* PA0 */
#define LED_PIN     13U     /* PC13 */

/* ================= MAIN PROGRAM =================== */

int main(void)
{
    /* STEP 1: Enable GPIOA and GPIOC clocks */
    RCC_APB2ENR |= (1U << 2);   /* IOPAEN */
    RCC_APB2ENR |= (1U << 4);   /* IOPCEN */

    /* Read back after enabling peripheral clocks */
    (void)RCC_APB2ENR;

    /* STEP 2: Configure PA0 as input with pull-up/pull-down */
    GPIOA_CRL &= ~(0xFU << (BUTTON_PIN * 4U));
    GPIOA_CRL |=  (0x8U << (BUTTON_PIN * 4U));

    /* Select pull-down for PA0 */
    GPIOA_ODR &= ~(1U << BUTTON_PIN);

    /* STEP 3: Configure PC13 as general-purpose push-pull output */
    GPIOC_CRH &= ~(0xFU << ((LED_PIN - 8U) * 4U));
    GPIOC_CRH |=  (0x2U << ((LED_PIN - 8U) * 4U));

    /* STEP 4: Initially turn the active-low LED OFF */
    GPIOC_ODR |= (1U << LED_PIN);

    /* STEP 5: Continuously read the button and control the LED */
    while (1)
    {
        if (GPIOA_IDR & (1U << BUTTON_PIN))
        {
            /* Button pressed: PA0 is HIGH */
            GPIOC_ODR &= ~(1U << LED_PIN);  /* LED ON */
        }
        else
        {
            /* Button released: PA0 is LOW */
            GPIOC_ODR |= (1U << LED_PIN);   /* LED OFF */
        }
    }
}

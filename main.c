// base addresses
#define RCC_BASE    0x40023800U
#define GPIOA_BASE  0x40020000U
#define GPIOB_BASE  0x40020400U
#define GPIOC_BASE  0x40020800U
#define GPIOD_BASE  0x40020C00U
#define GPIOE_BASE  0x40021000U

#define RCC_CR_OFFSET 0x00U // clock control register
#define RCC_CFGR_OFFSET   0x08U // clock configuration register
#define RCC_AHB1ENR_OFFSET 0x30U // AHB1 peripheral clock enable register

#define GPIOx_ODR_OFFSET 0x14U // output data register
#define GPIOx_IDR_OFFSET 0x10U // input data register
#define GPIOx_PUPDR_OFFSET 0x0CU // pull-up / pull-down register

/*
 * The purpose of the GPIOx_BSRR register is to allow atomic read/modify 
 * accesses to any of the GPIO registers.
 */
#define GPIOx_BSRR_OFFSET 0x18U // port bit set/reset register
#define GPIOx_MODER_OFFSET 0x00U // port mode register

#define RCC_CR          (RCC_BASE + RCC_CR_OFFSET)
#define RCC_CFGR        (RCC_BASE + RCC_CFGR_OFFSET)
#define RCC_AHB1_ENR    (RCC_BASE + RCC_AHB1ENR_OFFSET)

// GPIO A complete addresses
#define GPIOA_ODR       (GPIOA_BASE + GPIOx_ODR_OFFSET)
#define GPIOA_IDR       (GPIOA_BASE + GPIOx_IDR_OFFSET)
#define GPIOA_PUPDR     (GPIOA_BASE + GPIOx_PUPDR_OFFSET)
#define GPIOA_BSRR      (GPIOA_BASE + GPIOx_BSRR_OFFSET)
#define GPIOA_MODER     (GPIOA_BASE + GPIOx_MODER_OFFSET)

// GPIO C complete addresses
#define GPIOC_ODR       (GPIOC_BASE + GPIOx_ODR_OFFSET)
#define GPIOC_IDR       (GPIOC_BASE + GPIOx_IDR_OFFSET)
#define GPIOC_PUPDR     (GPIOC_BASE + GPIOx_PUPDR_OFFSET)
#define GPIOC_BSRR      (GPIOC_BASE + GPIOx_BSRR_OFFSET)
#define GPIOC_MODER     (GPIOC_BASE + GPIOx_MODER_OFFSET)

#define REG(x) (*(unsigned int *)x)

void sleep(unsigned volatile int amount){
    for(unsigned volatile int i = 0; i < amount; ++i) ;
}

int main(){
    // enable external clock
    REG(RCC_CR) |= (1 << 16);

    // check if HSE is good to go
    if(REG(RCC_CR) & (1 << 17)){
        // set clock source to HSE
        REG(RCC_CFGR) |= (1 << 0);
    }

    // enable clock for IO port A
    REG(RCC_AHB1_ENR) |= (1 << 0);
    // enable clock for IO port C
    REG(RCC_AHB1_ENR) |= (1 << 2);

    // set pin 5 of port A to general purpose output mode
    REG(GPIOA_MODER) |= (1 << 10);
    REG(GPIOA_MODER) |= (0 << 11);

    // set pin 13 of port C to input
    // REG(GPIOC_MODER) |= (0 << 4);
    // REG(GPIOC_MODER) |= (0 << 5);

    while(1){
        // toggle register
        REG(GPIOA_ODR) ^= (1 << 5);

        int pressed = !(REG(GPIOC_IDR) & (1 << 13));

        // if button is pressed, blink faster
        sleep(pressed ? 100000U : 1000000U);
    }
}

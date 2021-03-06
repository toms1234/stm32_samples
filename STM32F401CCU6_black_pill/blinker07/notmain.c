
//------------------------------------------------------------------------
//------------------------------------------------------------------------

void PUT16 ( unsigned int, unsigned int );
void PUT32 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define RCCBASE 0x40023800
#define RCC_CR          (RCCBASE+0x00)
#define RCC_CFGR        (RCCBASE+0x08)
#define RCC_AHB1ENR     (RCCBASE+0x30)
#define RCC_APB1ENR     (RCCBASE+0x40)
#define RCC_BDCR        (RCCBASE+0x70)

#define GPIOCBASE 0x40020800
#define GPIOC_MODER     (GPIOCBASE+0x00)
#define GPIOC_OTYPER    (GPIOCBASE+0x04)
#define GPIOC_BSRR      (GPIOCBASE+0x18)

#define TIM5BASE  0x40000C00
#define TIM5_CR1        (TIM5BASE+0x00)
#define TIM5_DIER       (TIM5BASE+0x0C)
#define TIM5_SR         (TIM5BASE+0x10)
#define TIM5_CNT        (TIM5BASE+0x24)
#define TIM5_PSC        (TIM5BASE+0x24)
#define TIM5_ARR        (TIM5BASE+0x2C)

#define PWRBASE         0x40007000
#define PWR_CR          (PWRBASE+0x00)
#define PWR_CSR         (PWRBASE+0x04)

#define RTCBASE         0x40002800
#define RTC_TR          (RTCBASE+0x00)
#define RTC_DR          (RTCBASE+0x04)
#define RTC_CR          (RTCBASE+0x08)
#define RTC_ISR         (RTCBASE+0x0C)
#define RTC_PRER        (RTCBASE+0x10)
#define RTC_ALRMAR      (RTCBASE+0x1C)
#define RTC_WPR         (RTCBASE+0x24)
#define RTC_SSR         (RTCBASE+0x28)
#define RTC_SHIFTR      (RTCBASE+0x2C)
#define RTC_TSTR        (RTCBASE+0x30)
#define RTC_TSDR        (RTCBASE+0x34)
#define RTC_TSSSR       (RTCBASE+0x38)

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018

#define NVIC_ISER0 0xE000E100

//------------------------------------------------------------------------
static void led_init ( void )
{
    unsigned int ra;

    ra=GET32(RCC_AHB1ENR);
    ra|=1<<2; //enable GPIOC
    PUT32(RCC_AHB1ENR,ra);

    ra=GET32(GPIOC_MODER);
    ra&=~(3<<(13<<1)); //PC13
    ra|= (1<<(13<<1)); //PC13
    PUT32(GPIOC_MODER,ra);

    ra=GET32(GPIOC_OTYPER);
    ra&=~(1<<13); //PC13
    PUT32(GPIOC_OTYPER,ra);
}
//------------------------------------------------------------------------
static void led_on ( void )
{
    PUT32(GPIOC_BSRR,((1<<13)<<16));
}
//------------------------------------------------------------------------
static void led_off ( void )
{
    PUT32(GPIOC_BSRR,((1<<13)<< 0));
}
//------------------------------------------------------------------------
static int clock_init ( void )
{
    unsigned int ra;

    //switch to external clock.
    ra=GET32(RCC_CR);
    ra|=1<<16;
    PUT32(RCC_CR,ra);
    while(1) if(GET32(RCC_CR)&(1<<17)) break;
    ra=GET32(RCC_CFGR);
    ra&=~3;
    ra|=1;
    PUT32(RCC_CFGR,ra);
    while(1) if(((GET32(RCC_CFGR)>>2)&3)==1) break;

    return(0);
}
//------------------------------------------------------------------------
volatile unsigned int tick;
void systick_handler ( void )
{
    GET32(STK_CSR);
    if((tick++)&1) led_on();
    else     led_off();
}
//------------------------------------------------------------------------
int notmain ( void )
{

    led_init();
    clock_init();
    tick=0;
    PUT32(STK_CSR,0x00000004);
    PUT32(STK_RVR,8000000-1);
    PUT32(STK_CVR,8000000-1);
    PUT32(STK_CSR,0x00000007);

    return(0);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

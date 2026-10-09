#include "stm32f10x.h"
#include "gpio.h"

void LED_Init(void)
{
    //1.开GPIOC时钟
RCC->APB2ENR|=(1U<<4);
GPIOC->BSRR=(1U<<13);

GPIOC->CRH&=(0xfU<<20);
GPIOC->CRH|=(0X2U<<20);


}

void KEY_Init(void)

{
    
     // 开启GPIOB外设时钟，用于PB6启动按键。
RCC->APB2ENR|=(1U<<3);
// 开启GPIOA外设时钟，用于PA2故障复位按键。
RCC->APB2ENR|=(1U<<2);
// 清除PB6原来的GPIO配置。（启动按键）
GPIOB->CRL&=(0xfU<<24);
    // 将PB6配置为上拉/下拉输入模式。
    GPIOB->CRL|=(0x8U<<24);
        // 将PB6对应ODR位置1，从而选择内部上拉。
        GPIOB->ODR|=(0x1U<<6);
          // 清除PA2原来的GPIO配置。（故障复位按键）
    GPIOA->CRL &= ~(0xFU << 8);
   // 将PA2配置为上拉/下拉输入模式。
    GPIOA->CRL |= (0x8U << 8);
    // 将PA2对应ODR位置1，从而选择内部上拉。
    GPIOA->ODR |= (1U << 2);
}

// 读取指定按键是否按下。
uint8_t KEY_Read(uint8_t key_id)
{

    if(key_id==KEY_START)
    {
        if(GPIOB->IDR&(1U<<6)==0)
        {
 // 返回1表示启动按键已经按下。
            return 1;
        }

        // 返回0表示启动按键没有按下。
        return 0;
    }

    if(key_id==KEY_FAULT_RESET)
    {
        if(GPIOA->IDR&(1U<<2)==0)
        {
              
 // 返回1表示启动按键已经按下。
            return 1;
        
        }
        // 返回0表示启动按键没有按下。
        return 0;
        
    }

    // 非法按键编号统一返回未按下。
    return 0;

}
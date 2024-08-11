/*
 * project.h
 *
 *  Created on: Jul 28, 2024
 *      Author: ASUS
 */


#include "project.h"

void pc2_adc_init()
{
    RCC->AHB1ENR |= (1<<2);    // Enable GPIOC clock
    GPIOC->MODER |= (3<<4);    // Set PC2 to analog mode

    RCC->APB2ENR |= (1<<8);    // Enable ADC1 clock

    ADC1->SQR1 &= ~(0xF<<20);  // Number of Conversion Sequence Length (0000) for 1 Conversion
    ADC1->SQR3 |= (0xC<<0);    // First sequence with channel number 12

    ADC1->CR1 |= (1<<8);       // Enable scan mode

    ADC1->CR2 &= ~(1<<1);      // Non-continuous conversion mode
    ADC1->CR2 |= (1<<0);       // Turn on the ADC
}

void start_conversion()
{
    ADC1->CR2 |= (1<<30);      // Start the conversion
}

uint32_t adc_read()
{
    while (!(ADC1->SR & (1<<1)));  // Wait for conversion to complete
    return (ADC1->DR);             // Return the ADC value
}

void GPIO_init()
{
    // Enable clocks for GPIOA and GPIOC
    RCC->AHB1ENR |= (1<<0) | (1<<2);

    // Set PA5 as output for LED
    GPIOA->MODER |= (1<<10);
    GPIOA->MODER &= ~(1<<11);

    // Set PC13 as input for the switch
    GPIOC->MODER &= ~(3<<26);

    GPIOA->MODER |=(2<<18)|(2<<20);
    GPIOA->AFR[1] |=(0x77<<4);

    GPIOC->MODER |=(2<<20)|(2<<22);
    GPIOC->AFR[1] |=(0X77<<8);


}

void uart1_tx_config()
{
    RCC->APB2ENR |= (1<<4);  // Enable USART1 clock
    USART1->BRR = 0x683;   // Set baud rate to 9600
    USART1->CR1 |= (1<<3); // Enable transmitter
    USART1->CR1 |= (1<<13);  // Enable USART1
}

void uart3_rx_config()
{
    RCC->APB1ENR |= (1<<18);// Enable USART3 clock
    USART3->BRR = 0x683;  // Set baud rate to 9600
    USART3->CR1 |= (1<<2); // Enable receiver
    USART3->CR1 |= (1<<13); // Enable USART3

}

void EXTI_Cnfg()
{
    // Configure SYSCFG for EXTI on PC13
    RCC->APB2ENR |= (1<<14);   // Enable SYSCFG clock
    SYSCFG->EXTICR[3] &= ~(0xF<<4);
    SYSCFG->EXTICR[3] |= (1<<5);  // Select PC13 for EXTI13

    EXTI->FTSR |= (1<<13); // Falling edge trigger for EXTI13
    EXTI->IMR |= (1<<13);   // Unmask EXTI13
}


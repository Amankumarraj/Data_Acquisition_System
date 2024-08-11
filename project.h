/*
 * project.h
 *
 *  Created on: Jul 28, 2024
 *      Author: ASUS
 */

#include <stm32f4xx.h>
#ifndef PROJECT_H_
#define PROJECT_H_




#include <stm32f4xx.h>

void pc2_adc_init();
void start_conversion();
uint32_t adc_read();

void GPIO_init();
void uart1_tx_config();
void uart3_rx_config();
void EXTI_Cnfg();



#endif /* PROJECT_H_ */

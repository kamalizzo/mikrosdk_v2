/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
* @file  mcu_definitions.h
* @brief MCU specific pin and module definitions.
*/

#ifndef _MCU_DEFINITIONS_H_
#define _MCU_DEFINITIONS_H_

#include "mcu_reg_addresses.h"

// ADC
#define ADC0_PC0_CH0
#define ADC0_PC1_CH1
#define ADC0_PC2_CH2
#define ADC0_PC3_CH3
#define ADC0_PC4_CH4
#define ADC0_PC5_CH5
#define ADC0_PE2_CH6
#define ADC0_PE3_CH7

#define ADC_MODULE_0 (1)

#define HAL_LL_AN_COUNT (8)
#define ADC_MODULE_COUNT (1)

// ADC Register addresses and offsets
#define HAL_LL_ADC0_ADCL_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_ADCH_REG_ADDRESS (0x79)
#define HAL_LL_ADC0_ADC_REG_ADDRESS (0x78)
#define HAL_LL_ADC0_BASE_ADDRESS (HAL_LL_ADC0_ADC_REG_ADDRESS)
#define HAL_LL_ADC0_ADCSRA_REG_ADDRESS (0x7A)
#define HAL_LL_ADC0_ADCSRB_REG_ADDRESS (0x7B)
#define HAL_LL_ADC0_ADMUX_REG_ADDRESS (0x7C)
#define HAL_LL_ADC0_DIDR1_REG_ADDRESS (0x7F)
// EOF ADC Register addresses and offsets
// EOF ADC

// I2C
#define TWI0_SCL_PC5
#define TWI0_SDA_PC4
#define TWI1_SCL_PE1
#define TWI1_SDA_PE0

#define TWI_MODULE_0 (1)
#define I2C_MODULE_0 (TWI_MODULE_0)
#define TWI_MODULE_1 (2)
#define I2C_MODULE_1 (TWI_MODULE_1)
#define TWI_MODULE_COUNT (2)
#define I2C_MODULE_COUNT (TWI_MODULE_COUNT)

// I2C Register addresses and offsets
#define HAL_LL_TWI0_TWBR0_REG_ADDRESS (0xB8)
#define HAL_LL_I2C0_BASE_ADDRESS (HAL_LL_TWI0_TWBR0_REG_ADDRESS)
#define HAL_LL_TWI0_TWSR0_REG_ADDRESS (0xB9)
#define HAL_LL_TWI0_TWAR0_REG_ADDRESS (0xBA)
#define HAL_LL_TWI0_TWDR0_REG_ADDRESS (0xBB)
#define HAL_LL_TWI0_TWCR0_REG_ADDRESS (0xBC)
#define HAL_LL_TWI0_TWAMR0_REG_ADDRESS (0xBD)
#define HAL_LL_TWI1_TWBR1_REG_ADDRESS (0xD8)
#define HAL_LL_I2C1_BASE_ADDRESS (HAL_LL_TWI1_TWBR1_REG_ADDRESS)
#define HAL_LL_TWI1_TWSR1_REG_ADDRESS (0xD9)
#define HAL_LL_TWI1_TWAR1_REG_ADDRESS (0xDA)
#define HAL_LL_TWI1_TWDR1_REG_ADDRESS (0xDB)
#define HAL_LL_TWI1_TWCR1_REG_ADDRESS (0xDC)
#define HAL_LL_TWI1_TWAMR1_REG_ADDRESS (0xDD)
// EOF I2C Register addresses and offsets
// EOF I2C

// U(S)ART
#define USART0_RXD_PD0
#define USART0_TXD_PD1
#define USART1_RXD_PB4
#define USART1_TXD_PB3

#define UART_MODULE_0 (1)
#define UART_MODULE_1 (2)
#define UART_MODULE_COUNT (2)

// U(S)ART Register addresses and offsets
#define HAL_LL_USART0_UCSR0A_REG_ADDRESS (0xC0)
#define HAL_LL_USART0_UCSR0B_REG_ADDRESS (0xC1)
#define HAL_LL_USART0_UCSR0C_REG_ADDRESS (0xC2)
#define HAL_LL_USART0_UCSR0D_REG_ADDRESS (0xC3)
#define HAL_LL_USART0_UBRR0L_REG_ADDRESS (0xC4)
#define HAL_LL_USART0_UBRR0H_REG_ADDRESS (0xC5)
#define HAL_LL_USART0_UBRR0_REG_ADDRESS (0xC4)
#define HAL_LL_USART0_UDR0_REG_ADDRESS (0xC6)
#define HAL_LL_USART1_UCSR1A_REG_ADDRESS (0xC8)
#define HAL_LL_USART1_UCSR1B_REG_ADDRESS (0xC9)
#define HAL_LL_USART1_UCSR1C_REG_ADDRESS (0xCA)
#define HAL_LL_USART1_UCSR1D_REG_ADDRESS (0xCB)
#define HAL_LL_USART1_UBRR1L_REG_ADDRESS (0xCC)
#define HAL_LL_USART1_UBRR1H_REG_ADDRESS (0xCD)
#define HAL_LL_USART1_UBRR1_REG_ADDRESS (0xCC)
#define HAL_LL_USART1_UDR1_REG_ADDRESS (0xCE)
// EOF U(S)ART Register addresses and offsets
// EOF U(S)ART

// SPI
#define SPI0_MISO_PB4
#define SPI0_MOSI_PB3
#define SPI0_SCK_PB5
#define SPI0_SS_PB2
#define SPI1_MISO_PC0
#define SPI1_MOSI_PE3
#define SPI1_SCK_PC1
#define SPI1_SS_PE2

#define SPI_MODULE_0 (1)
#define SPI_MODULE_1 (2)
#define SPI_MODULE_COUNT (2)

// SPI Register addresses and offsets
#define HAL_LL_SPI0_SPCR_REG_ADDRESS (0x4C)
#define HAL_LL_SPI0_SPSR_REG_ADDRESS (0x4D)
#define HAL_LL_SPI0_SPDR_REG_ADDRESS (0x4E)
#define HAL_LL_SPI1_SPCR_REG_ADDRESS (0xAC)
#define HAL_LL_SPI1_SPSR_REG_ADDRESS (0xAD)
#define HAL_LL_SPI1_SPDR_REG_ADDRESS (0xAE)
// EOF SPI Register addresses and offsets
// EOF SPI

// TIM
#define TIM0_PD5_CH_B
#define TIM0_PD6_CH_A
#define TIM1_PB1_CH_A
#define TIM1_PB2_CH_B
#define TIM2_PB3_CH_A
#define TIM2_PD3_CH_B
#define TIM3_PD0_CH_A
#define TIM3_PD2_CH_B
#define TIM4_PD1_CH_A
#define TIM4_PD2_CH_B

#define TIM_MODULE_0 (1)
#define TIM_MODULE_1 (2)
#define TIM_MODULE_2 (3)
#define TIM_MODULE_3 (4)
#define TIM_MODULE_4 (5)
#define TIM_MODULE_COUNT (5)

// TIM Register addresses and offsets
#define HAL_LL_TIM0_TIFR0_REG_ADDRESS (0x35)
#define HAL_LL_TIM1_TIFR1_REG_ADDRESS (0x36)
#define HAL_LL_TIM2_TIFR2_REG_ADDRESS (0x37)
#define HAL_LL_TIM3_TIFR3_REG_ADDRESS (0x38)
#define HAL_LL_TIM4_TIFR4_REG_ADDRESS (0x39)
#define HAL_LL_TIM0_TCCR0A_REG_ADDRESS (0x44)
#define HAL_LL_TIM0_TCCR0B_REG_ADDRESS (0x45)
#define HAL_LL_TIM0_TCNT0_REG_ADDRESS (0x46)
#define HAL_LL_TIM0_OCR0A_REG_ADDRESS (0x47)
#define HAL_LL_TIM0_OCR0B_REG_ADDRESS (0x48)
#define HAL_LL_TIM0_TIMSK0_REG_ADDRESS (0x6E)
#define HAL_LL_TIM1_TIMSK1_REG_ADDRESS (0x6F)
#define HAL_LL_TIM2_TIMSK2_REG_ADDRESS (0x70)
#define HAL_LL_TIM3_TIMSK3_REG_ADDRESS (0x71)
#define HAL_LL_TIM4_TIMSK4_REG_ADDRESS (0x72)
#define HAL_LL_TIM1_TCCR1A_REG_ADDRESS (0x80)
#define HAL_LL_TIM1_TCCR1B_REG_ADDRESS (0x81)
#define HAL_LL_TIM1_TCCR1C_REG_ADDRESS (0x82)
#define HAL_LL_TIM1_TCNT1H_REG_ADDRESS (0x85)
#define HAL_LL_TIM1_TCNT1L_REG_ADDRESS (0x84)
#define HAL_LL_TIM1_ICR1_REG_ADDRESS (0x86)
#define HAL_LL_TIM1_OCR1AH_REG_ADDRESS (0x89)
#define HAL_LL_TIM1_OCR1AL_REG_ADDRESS (0x88)
#define HAL_LL_TIM1_OCR1BH_REG_ADDRESS (0x8b)
#define HAL_LL_TIM1_OCR1BL_REG_ADDRESS (0x8A)
#define HAL_LL_TIM3_TCCR3A_REG_ADDRESS (0x90)
#define HAL_LL_TIM3_TCCR3B_REG_ADDRESS (0x91)
#define HAL_LL_TIM3_TCCR3C_REG_ADDRESS (0x92)
#define HAL_LL_TIM3_TCNT3H_REG_ADDRESS (0x95)
#define HAL_LL_TIM3_TCNT3L_REG_ADDRESS (0x94)
#define HAL_LL_TIM3_ICR3_REG_ADDRESS (0x96)
#define HAL_LL_TIM3_OCR3AH_REG_ADDRESS (0x99)
#define HAL_LL_TIM3_OCR3AL_REG_ADDRESS (0x98)
#define HAL_LL_TIM3_OCR3BH_REG_ADDRESS (0x9b)
#define HAL_LL_TIM3_OCR3BL_REG_ADDRESS (0x9A)
#define HAL_LL_TIM4_TCCR4A_REG_ADDRESS (0xA0)
#define HAL_LL_TIM4_TCCR4B_REG_ADDRESS (0xA1)
#define HAL_LL_TIM4_TCCR4C_REG_ADDRESS (0xA2)
#define HAL_LL_TIM4_TCNT4H_REG_ADDRESS (0xa5)
#define HAL_LL_TIM4_TCNT4L_REG_ADDRESS (0xA4)
#define HAL_LL_TIM4_ICR4_REG_ADDRESS (0xA6)
#define HAL_LL_TIM4_OCR4AH_REG_ADDRESS (0xa9)
#define HAL_LL_TIM4_OCR4AL_REG_ADDRESS (0xA8)
#define HAL_LL_TIM4_OCR4BH_REG_ADDRESS (0xab)
#define HAL_LL_TIM4_OCR4BL_REG_ADDRESS (0xAA)
#define HAL_LL_TIM2_TCCR2A_REG_ADDRESS (0xB0)
#define HAL_LL_TIM2_TCCR2B_REG_ADDRESS (0xB1)
#define HAL_LL_TIM2_TCNT2_REG_ADDRESS (0xB2)
#define HAL_LL_TIM2_OCR2A_REG_ADDRESS (0xB3)
#define HAL_LL_TIM2_OCR2B_REG_ADDRESS (0xB4)
#define HAL_LL_TIM2_ASSR_REG_ADDRESS (0xB6)
// EOF TIM Register addresses and offsets
// EOF TIM

// GPIO
#define __PB0_CN
#define __PB1_CN
#define __PB2_CN
#define __PB3_CN
#define __PB4_CN
#define __PB5_CN
#define __PB6_CN
#define __PB7_CN
#define __PC0_CN
#define __PC1_CN
#define __PC2_CN
#define __PC3_CN
#define __PC4_CN
#define __PC5_CN
#define __PC6_CN
#define __PD0_CN
#define __PD1_CN
#define __PD2_CN
#define __PD3_CN
#define __PD4_CN
#define __PD5_CN
#define __PD6_CN
#define __PD7_CN
#define __PE0_CN
#define __PE1_CN
#define __PE2_CN
#define __PE3_CN

#define __PORT_B_CN
#define __PORT_C_CN
#define __PORT_D_CN
#define __PORT_E_CN

#define PORT_SIZE  (8)
#define PORT_COUNT (4)

// GPIO Register addresses and offsets
#define PINB_REG_ADDRESS (0x23)
#define DDRB_REG_ADDRESS (0x24)
#define PORTB_REG_ADDRESS (0x25)
#define PINC_REG_ADDRESS (0x26)
#define DDRC_REG_ADDRESS (0x27)
#define PORTC_REG_ADDRESS (0x28)
#define PIND_REG_ADDRESS (0x29)
#define DDRD_REG_ADDRESS (0x2A)
#define PORTD_REG_ADDRESS (0x2B)
#define PINE_REG_ADDRESS (0x2C)
#define DDRE_REG_ADDRESS (0x2D)
#define PORTE_REG_ADDRESS (0x2E)
// REMAP Register addresses
#define HAL_LL_MODULE_REMAP (false)
// EOF GPIO Register addresses and offsets
// EOF GPIO

// POWER REDUCTION REGISTER
#define HAL_LL_PRR0_REG_ADDRESS (0x64)
#define HAL_LL_PRR1_REG_ADDRESS (0x65)
#define HAL_LL_POWER_REDUCTION (true)
// EOF POWER REDUCTION REGISTER

// IVT
#define HAL_LL_USART0_RX_IVT (18)
#define HAL_LL_USART0_UDRE_IVT (19)
#define HAL_LL_USART0_TX_IVT (20)
#define HAL_LL_USART0_START_IVT (26)
#define HAL_LL_USART1_RX_IVT (28)
#define HAL_LL_USART1_UDRE_IVT (29)
#define HAL_LL_USART1_TX_IVT (30)
#define HAL_LL_USART1_START_IVT (31)
// IVT ADDRESSES
#define HAL_LL_USART0_RX_IVT_ADDRESS (0x24)
#define HAL_LL_USART0_UDRE_IVT_ADDRESS (0x26)
#define HAL_LL_USART0_TX_IVT_ADDRESS (0x28)
#define HAL_LL_USART0_START_IVT_ADDRESS (0x34)
#define HAL_LL_USART1_RX_IVT_ADDRESS (0x38)
#define HAL_LL_USART1_UDRE_IVT_ADDRESS (0x3A)
#define HAL_LL_USART1_TX_IVT_ADDRESS (0x3C)
#define HAL_LL_USART1_START_IVT_ADDRESS (0x3E)
// EOF IVT

#endif // _MCU_DEFINITIONS_H_
// ------------------------------------------------------------------------- END

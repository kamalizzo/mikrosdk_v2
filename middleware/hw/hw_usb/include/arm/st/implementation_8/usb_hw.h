/****************************************************************************
**
** Copyright (C) 2025 MikroElektronika d.o.o.
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
 * @file  usb_hw.h
 * @brief Initializes USB HW module.
 * @details Sets clock, pins, etc.
 */

#ifndef _USB_HW_H_
#define _USB_HW_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu.h"
#include "interrupts.h"
// Note: Added for MikroE implementation.
// MikroE interrupt source uses NVIC -> (IRQx + 16).
#define NVIC_EnableIRQ(_x)  interrupt_enable(_x + 16)
#define NVIC_DisableIRQ(_x) interrupt_disable(_x + 16)

/*!
 * @addtogroup middleware Middleware
 * @{
 */

/*!
 * @addtogroup usb MikroE USB HW implementation.
 * @brief MikroE USB HW init library.
 *
 * @details This library initializes HW specific
 * USB pins/clock etc.
 * @{
 */

// Clock value in Hz provided externally.
extern volatile uint32_t SystemCoreClock;

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock for GPIO_PORT_A.
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;

    // SysTick_Config(SystemCoreClock / 1000);

    RCC->CCIPR &= ~RCC_CCIPR_CLK48SEL;
    // USB Clock enable.
    RCC->APB1ENR1 |= RCC_APB1ENR1_USBEN;

    // Set PA11 and PA12 to input mode (00)
    GPIOA->MODER &= ~((3U << (11 * 2)) | (3U << (12 * 2)));  // Clear bits

    // Set PA11 and PA12 to pull-down (10)
    GPIOA->PUPDR &= ~((3U << (11 * 2)) | (3U << (12 * 2)));      // Clear
    GPIOA->PUPDR |=  ((2U << (11 * 2)) | (2U << (12 * 2)));      // Set to 10 (pull-down)

    // Speed register: set high speed (11)
    GPIOA->OSPEEDR |= ((3U << (11 * 2)) | (3U << (12 * 2)));

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
    RCC->APB1ENR2 |= RCC_APB1ENR2_UCPD1EN;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END

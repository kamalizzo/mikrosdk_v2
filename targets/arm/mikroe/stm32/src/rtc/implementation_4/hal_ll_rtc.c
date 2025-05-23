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
 * @file  hal_ll_rtc.c
 * @brief RTC HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_rtc.h"
#include "delays.h"

/**
 *  Return values
 */
typedef enum
{
    HAL_LL_RTC_SUCCESS = 0,
    HAL_LL_RTC_ERROR = (-1)
} hal_ll_rtc_err_t;

// ---------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief Writes specified value to
 *        specified register.
 *
 * @param[in] reg  - register address.
 * @param[in] _val - Value to be written.
 */
#define write_reg(reg,_val) (selected_reg(reg) = (_val))

/**
 * @brief Returns value stored
 *        in a register.
 *
 * @param[in] reg  - register address.
 *
 * @return Register(reg) value.
 */
#define read_reg(reg) (selected_reg(reg))

/**
 * @brief Returns value of specified bit
 *        mask from a register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 *
 * @return Register(reg) bits value.
 */
#define read_reg_bits(reg,bit_mask) (selected_reg(reg) & (bit_mask))

/* !< @brief MACROS for the code */
#define FIRST_KEY                  0x000000ca
#define SECOND_KEY                 0x00000053
#define FIRST_KEY_WDG              0x000000ca
#define SECOND_KEY_WDG             0x00000053
#define DEFAULT_TIME               0x00400000
#define ENABLE_INIT                0x00000080
#define DEFAULT_PRESC              0x007F00FF
#define ENABLE_CLOCK_CHANGE        0x00010000
#define CHANGE_CLOCK               0x00008101
#define IWDG_REGISTER_ACCESS       0x00005555
#define IWDG_PRESCALER             0x00000000
#define CLEAR                      0x000000ff

#define EXIT                       0
#define OFF                        0
#define ON                         1
#define SET_WDG_RELOADER           1
#define FMT_24H                    6
#define RTC_ACCESS                 8
#define ENABLE_CLK_PWR             28

#define RCC_BDCR_LSEON_BIT          0
#define RCC_BDCR_LSERDY_BIT         1
#define RCC_BDCR_RTCSEL_BIT_1       8
#define RCC_BDCR_RTCSEL_BIT_2       9
#define RCC_BDCR_RTCEN_BIT          15
#define RCC_APB1ENR_PWREN_BIT       28
#define RCC_BDCR_BDRST_BIT          16
#define PWR_CR_DBP_BIT              8

#define INIT_OFF                   check_reg_bit(registers.rtc_isr, 6)>>6!=1
#define LSE_NOT_READY              check_reg_bit(registers.rcc_bdcr, 1)
#define RTC_ABP_NOT_READY          check_reg_bit(registers.rtc_isr, 5)>>5!=1
#define WAIT_UPDATE                read_reg( registers.iwdg_sr )!=0
#define RTC_OFF                    !check_reg_bit( registers.rcc_bdcr, RCC_BDCR_RTCEN_BIT )
#define MODIFIED_REGISTER          (read_reg(registers.rtc_tr) == NEW_TIME)
#define DEFAULT_REGISTER           (read_reg(registers.rtc_tr) == DEFAULT_TIME)

/*!< @brief SYSTEM RESET MACROS */
#define WATCHDOG_START              0x0000CCCC
#define WATCHDOG_ENABLE_ACCESS      0x00005555
#define WATCHDOG_PR_256             111
#define WATCHDOG_RLR_1              1
#define WATCHDOG_KEY_VALUE          0x0000AAAA
#define CHECK_BKP_REGISTER         if(read_reg(registers.rtc_bkp0r)!=0){\
                                   temp_1 = read_reg(registers.rtc_bkp0r) ;\
                                   write_reg(registers.rtc_bkp0r,0);}

#define BKP_TO_RTC_REG             write_reg(registers.rtc_tr,temp_1+1);\
                                   temp_1 = 0;

/* !< @brief RTC_TR REGISTER MASKS */
#define RTCTIME_MASK_HR10          0x00300000
#define RTCTIME_MASK_HR01          0x000f0000
#define RTCTIME_MASK_MIN10         0x00007000
#define RTCTIME_MASK_MIN01         0x00000f00
#define RTCTIME_MASK_SEC10         0x00000070
#define RTCTIME_MASK_SEC01         0x0000000f
#define RTCTIME_MASK_PMAM          0x00400000

/* !< @brief REGISTER CONVERTER MACROS */
#define HOUR10_TO_HOUR             ((read_reg(registers.rtc_tr) & RTCTIME_MASK_HR10) >> 20) *10
#define HOUR01_TO_HOUR             (read_reg(registers.rtc_tr) & RTCTIME_MASK_HR01) >> 16
#define MINUTE10_TO_MINUTE         ((read_reg(registers.rtc_tr) & RTCTIME_MASK_MIN10) >> 12) *10
#define MINUTE01_TO_MINUTE         (read_reg(registers.rtc_tr) & RTCTIME_MASK_MIN01) >> 8
#define SECOND10_TO_SECOND         ((read_reg(registers.rtc_tr) & RTCTIME_MASK_SEC10) >> 4) *10
#define SECOND01_TO_SECOND         (read_reg(registers.rtc_tr) & RTCTIME_MASK_SEC01)

#define SECOND_TO_SECOND01         time->second % 10
#define SECOND_TO_SECOND10         (time->second - seconds_01) / 10
#define MINUTE_TO_MINUTE01         time->minute % 10
#define MINUTE_TO_MINUTE10         (time->minute - minutes_01) / 10
#define HOUR_TO_HOUR01             time->hour % 10
#define HOUR_TO_HOUR10             (time->hour - hours_01) / 10
#define SECOND_TO_REGISTER         ((uint32_t)seconds_01) | ((uint32_t)seconds_10 << 4)
#define MINUTE_TO_REGISTER         ((uint32_t)minutes_01 << 8 ) | ((uint32_t)minutes_10 << 12)
#define HOUR_TO_REGISTER           ((uint32_t)hours_01 << 16 ) | ((uint32_t)hours_10 << 20)

// ----------------------------------------------------------------- PRIVATE TYPES

/*!< @brief RTC register structure. */
typedef struct
{
    hal_ll_base_addr_t* rtc_wpr;
    hal_ll_base_addr_t* rtc_isr;
    hal_ll_base_addr_t* rtc_prer;
    hal_ll_base_addr_t* rtc_tr;
    hal_ll_base_addr_t* rtc_dr;
    hal_ll_base_addr_t* rtc_cr;
    hal_ll_base_addr_t* rcc_apb1enr;
    hal_ll_base_addr_t* pwr_cr1;
    hal_ll_base_addr_t* rcc_bdcr;
    hal_ll_base_addr_t* iwdg_kr;
    hal_ll_base_addr_t* iwdg_pr;
    hal_ll_base_addr_t* iwdg_rlr;
    hal_ll_base_addr_t* iwdg_sr;
    hal_ll_base_addr_t* rtc_bkp0r;
    hal_ll_base_addr_t* rtc_bkp1r;
} reg_t;

// -------------------------------------------------------------------- VARIABLES

/*!< @brief RTC registers info  */
 reg_t registers = { RTC_WPR_REG_ADDRESS, RTC_ISR_REG_ADDRESS, RTC_PRER_REG_ADDRESS, RTC_TR_REG_ADDRESS, RTC_DR_REG_ADDRESS, RTC_CR_REG_ADDRESS, RCC_APB1ENR1_REG_ADDRESS, PWR_CR1_REG_ADDRESS, RCC_BDCR_REG_ADDRESS, IWDG_KR_REG_ADDRESS, IWDG_PR_REG_ADDRESS, IWDG_RLR_REG_ADDRESS, IWDG_SR_REG_ADDRESS, RTC_BKP0R_REG_ADDRESS, RTC_BKP1R_REG_ADDRESS };

#ifdef __GNUC__
/**
 * @brief Initialize the RTC counter.
 * @details Set the date to 01/01/2000 at 00:00:00.
 * @b Example
 * @code
 * // Initialize RTC.
 * hal_ll_rtc_init();
 * @endcode
 */
void __attribute__ ((weak)) hal_ll_rtc_init();

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the counter register.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_start();

/**
 * @brief Stop the RTC module.
 * @details Stop the RTC module count.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values of 0h:0m:0s.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Configure time registers with the values from hal_ll_rtc_time_t structure.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_set_time( hal_ll_rtc_time_t *time );

/**
 * @brief Get time and date.
 * @details Configure hal_ll_rtc_time_t structure with the values from time registers.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__((weak)) hal_ll_rtc_get_time( hal_ll_rtc_time_t *rtc );

/**
 * @brief Preforms system reset.
 * @details Resets the core and all on-chip peripherals except the Debug
 * interface.
 * @param None.
 * @warning System reset affects core and periferals,
 * depending on the architecture you will need to reconfigure opened modules.
 */
void __attribute__ ((weak)) hal_ll_rtc_system_reset();

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS
/**
 * @brief create an uint32_t variable that can be used to change the time register.
 * @param[in] time : RTC hal_ll_rtc_time_t structure.
 * @return uint32_t variable that suits the RTC time register requirement.
 * @details use the different values of the RTC time structure to create a variable that can be used to change the time register.
 */
static uint32_t set_time_register( hal_ll_rtc_time_t *time );
#endif

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS
/**
 * @brief create an uint32_t variable that can be used to change the time register.
 * @param[in] time : RTC hal_ll_rtc_time_t structure.
 * @return uint32_t variable that suits the RTC time register requirement.
 * @details use the different values of the RTC time structure to create a variable that can be used to change the time register.
 */
static uint32_t set_time_register( hal_ll_rtc_time_t *time );

//------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
void hal_ll_rtc_init() {

    uint32_t temp_1;
    uint32_t temp_2;

    set_reg_bit( registers.rcc_apb1enr, RCC_APB1ENR_PWREN_BIT );
    set_reg_bit( registers.pwr_cr1, PWR_CR_DBP_BIT );
    write_reg( registers.rtc_wpr, FIRST_KEY );
    write_reg( registers.rtc_wpr, SECOND_KEY );
    set_reg_bit( registers.rcc_bdcr, RCC_BDCR_RTCSEL_BIT_1 );
    clear_reg_bit( registers.rcc_bdcr, RCC_BDCR_RTCSEL_BIT_2 );
    set_reg_bit( registers.rcc_bdcr, RCC_BDCR_LSEON_BIT );

    CHECK_BKP_REGISTER

    if( temp_1 ){
        hal_ll_rtc_start();
        write_reg( registers.rtc_wpr, CLEAR );
        write_reg( registers.rtc_wpr, FIRST_KEY );
        write_reg( registers.rtc_wpr, SECOND_KEY );
        write_reg( registers.rtc_isr, ENABLE_INIT );

        while( INIT_OFF );

        BKP_TO_RTC_REG;

        write_reg( registers.rtc_isr, EXIT );

        Delay_100ms();
        hal_ll_rtc_stop();
        write_reg( registers.rtc_wpr, CLEAR );

    }

}

err_t hal_ll_rtc_start() {

    set_reg_bit( registers.rcc_bdcr, RCC_BDCR_RTCEN_BIT );

    if ( !RTC_OFF ) {
        return HAL_LL_RTC_SUCCESS;
    }
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_stop() {

    clear_reg_bit( registers.rcc_bdcr, RCC_BDCR_RTCEN_BIT );

    if ( RTC_OFF ) {
        return HAL_LL_RTC_SUCCESS;
    }
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_reset() {
    uint8_t rtc_state = ON;
    if( RTC_OFF ){
        hal_ll_rtc_start();
        rtc_state = OFF ;
    }
    write_reg( registers.rtc_wpr, CLEAR );
    write_reg( registers.rtc_wpr, FIRST_KEY );
    write_reg( registers.rtc_wpr, SECOND_KEY );
    write_reg( registers.rtc_isr, ENABLE_INIT );

    while( INIT_OFF );
    write_reg( registers.rtc_tr, DEFAULT_TIME );
    write_reg( registers.rtc_isr, EXIT );

    Delay_1ms();
    if( rtc_state==OFF ){
        hal_ll_rtc_stop();
    }

    if ( DEFAULT_REGISTER ) {
        return HAL_LL_RTC_SUCCESS;
    }
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {

    uint8_t rtc_state = ON;
    if( RTC_OFF ){
        hal_ll_rtc_start();
        rtc_state = OFF ;
    }
    write_reg( registers.rtc_wpr, CLEAR );
    write_reg( registers.rtc_wpr, FIRST_KEY );
    write_reg( registers.rtc_wpr, SECOND_KEY );
    write_reg( registers.rtc_isr, ENABLE_INIT );

    while( INIT_OFF );

    uint32_t NEW_TIME = set_time_register( time );
    write_reg( registers.rtc_tr, NEW_TIME );
    clear_reg_bit( registers.rtc_cr, FMT_24H );
    write_reg( registers.rtc_isr, EXIT );

    Delay_1ms();
    if( rtc_state==OFF ){
        hal_ll_rtc_stop();
    }

    if ( MODIFIED_REGISTER ) {
        return HAL_LL_RTC_SUCCESS;
    }
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *rtc ) {

    write_reg( registers.rtc_bkp0r, read_reg( registers.rtc_tr ) );

    rtc->hour  = HOUR10_TO_HOUR;
    rtc->hour += HOUR01_TO_HOUR;

    rtc->minute  = MINUTE10_TO_MINUTE;
    rtc->minute += MINUTE01_TO_MINUTE;

    rtc->second  = SECOND10_TO_SECOND;
    rtc->second += SECOND01_TO_SECOND;

    return HAL_LL_RTC_SUCCESS;
}


void hal_ll_rtc_system_reset() {

    uint8_t rtc_state = ON;
    if( RTC_OFF ){
        hal_ll_rtc_start();
        rtc_state = OFF ;
    }
    // Unlock write protection
    write_reg( registers.rtc_wpr, CLEAR );
    write_reg( registers.rtc_wpr, FIRST_KEY );
    write_reg( registers.rtc_wpr, SECOND_KEY );
    write_reg( registers.rtc_isr, ENABLE_INIT );

    while( INIT_OFF );

    write_reg( registers.rtc_bkp0r, read_reg( registers.rtc_tr ) );
    write_reg( registers.rtc_isr, EXIT );

    Delay_100ms();
    if( rtc_state==OFF ){
        hal_ll_rtc_stop();
    }
    write_reg( registers.iwdg_kr, WATCHDOG_START );
    write_reg( registers.iwdg_kr, WATCHDOG_ENABLE_ACCESS );
    write_reg( registers.iwdg_pr, WATCHDOG_PR_256 );
    write_reg( registers.iwdg_rlr, WATCHDOG_RLR_1 );
    write_reg( registers.iwdg_kr, WATCHDOG_KEY_VALUE );

}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

static uint32_t set_time_register( hal_ll_rtc_time_t *time ) {

    uint8_t seconds_01 = SECOND_TO_SECOND01;
    uint8_t seconds_10 = SECOND_TO_SECOND10;

    uint8_t minutes_01 = MINUTE_TO_MINUTE01;
    uint8_t minutes_10 = MINUTE_TO_MINUTE10;

    uint8_t hours_01 = HOUR_TO_HOUR01;
    uint8_t hours_10 = HOUR_TO_HOUR10;

    uint32_t NEW_TIME = SECOND_TO_REGISTER;
    NEW_TIME |= MINUTE_TO_REGISTER;
    NEW_TIME |= HOUR_TO_REGISTER;

    return NEW_TIME;

}

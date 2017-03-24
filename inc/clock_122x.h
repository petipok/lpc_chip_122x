/*
 * @brief LPC122X Clock control functions
 *
 * @note
 * WARNING: THIS LIBRARY HAS BEEN PORTED TO LPC122x devices from the lpc_chip_11u14 LPCOPEN chip library. Please consider this when using it.
 * This library is provided as is, and the authors DO NOT GUARANTEE that it is working.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CLOCK_122X_H_
#define __CLOCK_122X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CLOCK_122X CHIP: LPC11xx Clock Control block driver
 * @ingroup CHIP_122X_Drivers
 * @{
 */

/** Internal oscillator frequency */
#define SYSCTL_IRC_FREQ (12000000)

/**
 * @brief	Set System PLL divider values
 * @param	msel    : PLL feedback divider value. M = msel + 1.
 * @param	psel    : PLL post divider value. P =  (1<<psel).
 * @return	Nothing
 * @note	See the user manual for how to setup the PLL.
 */
STATIC INLINE void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel)
{
	LPC_SYSCTL->SYSPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}

/**
 * @brief	Read System PLL lock status
 * @return	true of the PLL is locked. false if not locked
 */
STATIC INLINE bool Chip_Clock_IsSystemPLLLocked(void)
{
	return (bool) ((LPC_SYSCTL->SYSPLLSTAT & 1) != 0);
}

/**
 * Clock sources for system and USB PLLs
 */
typedef enum CHIP_SYSCTL_PLLCLKSRC {
	SYSCTL_PLLCLKSRC_IRC = 0,		/*!< Internal oscillator in */
	SYSCTL_PLLCLKSRC_MAINOSC,		/*!< Crystal (main) oscillator in */
	SYSCTL_PLLCLKSRC_RESERVED1,	/*!< Reserved */
	SYSCTL_PLLCLKSRC_RESERVED2,	/*!< Reserved */
} CHIP_SYSCTL_PLLCLKSRC_T;

/**
 * @brief	Set System PLL clock source
 * @param	src	: Clock source for system PLL
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source.
 */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src);



/**
 * @brief	Bypass System Oscillator and set oscillator frequency range
 * @param	bypass	: Flag to bypass oscillator
 * @param	highfr	: Flag to set oscillator range from 15-25 MHz
 * @return	Nothing
 * @note	Sets the PLL input to bypass the oscillator. This would be
 * used if an external clock that is not an oscillator is attached
 * to the XTALIN pin.
 */
void Chip_Clock_SetPLLBypass(bool bypass, bool highfr);

/**
 * Watchdog and low frequency oscillator frequencies plus or minus 40%
 */
typedef enum CHIP_WDTLFO_OSC {
	WDTLFO_OSC_ILLEGAL,
	WDTLFO_OSC_0_50,	/*!< 0.5 MHz watchdog/LFO rate */
	WDTLFO_OSC_0_80,	/*!< 0.8 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_10,	/*!< 1.1 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_40,	/*!< 1.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_60,	/*!< 1.6 MHz watchdog/LFO rate */
	WDTLFO_OSC_1_80,	/*!< 1.8 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_00,	/*!< 2.0 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_20,	/*!< 2.2 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_40,	/*!< 2.4 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_60,	/*!< 2.6 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_70,	/*!< 2.7 MHz watchdog/LFO rate */
	WDTLFO_OSC_2_90,	/*!< 2.9 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_10,	/*!< 3.1 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_20,	/*!< 3.2 MHz watchdog/LFO rate */
	WDTLFO_OSC_3_40		/*!< 3.4 MHz watchdog/LFO rate */
} CHIP_WDTLFO_OSC_T;

/**
 * @brief	Setup Watchdog oscillator rate and divider
 * @param	wdtclk	: Selected watchdog clock rate
 * @param	div		: Watchdog divider value, even value between 2 and 64
 * @return	Nothing
 * @note	Watchdog rate = selected rate divided by divider rate
 */
STATIC INLINE void Chip_Clock_SetWDTOSC(CHIP_WDTLFO_OSC_T wdtclk, uint8_t div)
{
	LPC_SYSCTL->WDTOSCCTRL  = (((uint32_t) wdtclk) << 5) | ((div >> 1) - 1);
}

/**
 * Clock sources for main system clock
 */
typedef enum CHIP_SYSCTL_MAINCLKSRC {
	SYSCTL_MAINCLKSRC_IRC = 0,		/*!< Internal oscillator */
	SYSCTL_MAINCLKSRC_PLLIN,		/*!< System PLL input */
	SYSCTL_MAINCLKSRC_WDTOSC,	/*!< Watchdog oscillator rate */
	SYSCTL_MAINCLKSRC_PLLOUT,		/*!< System PLL output */
} CHIP_SYSCTL_MAINCLKSRC_T;

/**
 * @brief	Set main system clock source
 * @param	src	: Clock source for main system
 * @return	Nothing
 * @note	This function will also toggle the clock source update register
 * to update the clock source.
 */
void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src);

/**
 * @brief   Returns the main clock source
 * @return	Which clock is used for the core clock source?
 */
STATIC INLINE CHIP_SYSCTL_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void)
{
	return (CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCTL->MAINCLKSEL);
}

/**
 * @brief	Set system clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSysClockDiv(uint32_t div)
{
	LPC_SYSCTL->SYSAHBCLKDIV  = div;
}

/**
 * System and peripheral clocks
 */
typedef enum CHIP_SYSCTL_CLOCK {
	SYSCTL_CLOCK_SYS = 0,				/*!< 0: System clock */
	SYSCTL_CLOCK_ROM,					/*!<1:  ROM clock */
	SYSCTL_CLOCK_RAM,					/*!< 2: RAM clock */
	SYSCTL_CLOCK_FLASHREG,				/*!< 3: FLASH register interface clock */
	SYSCTL_CLOCK_FLASHARRAY,			/*!< 4: FLASH array access clock */
	SYSCTL_CLOCK_I2C,					/*!< 5: I2C clock, not on LPC110x */
	SYSCTL_CLOCK_CRC,					/*!< 6: CRC clock */
	SYSCTL_CLOCK_CT16B0,				/*!< 7: 16-bit Counter/timer 0 clock */
	SYSCTL_CLOCK_CT16B1,				/*!< 8: 16-bit Counter/timer 1 clock */
	SYSCTL_CLOCK_CT32B0,				/*!< 9: 32-bit Counter/timer 0 clock */
	SYSCTL_CLOCK_CT32B1,				/*!< 10: 32-bit Counter/timer 1 clock */
	SYSCTL_CLOCK_SSP0,					/*!< 11: SSP0 clock */
	SYSCTL_CLOCK_UART0,					/*!< 12: UART0 clock */
	SYSCTL_CLOCK_UART1,					/*!< 13: UART1 clock */
	SYSCTL_CLOCK_ADC,					/*!< 14: ADC clock */

	SYSCTL_CLOCK_WDT,					/*!< 15: Watchdog timer clock */
	SYSCTL_CLOCK_IOCON,					/*!< 16: IOCON block clock */

	SYSCTL_CLOCK_DMA,					/*!< 17: DMA clock */
	SYSCTL_CLOCK_RESERVED18,
	SYSCTL_CLOCK_RTC,					/*!< 19: RTC clock */
	SYSCTL_CLOCK_CMP,					/*!< 20: Comparator clock */
	SYSCTL_CLOCK_RESERVED21,			/*!< 21: Reserved */
	SYSCTL_CLOCK_RESERVED22,			/*!< 22: Reserved */
	SYSCTL_CLOCK_RESERVED23,			/*!< 23: Reserved */
	SYSCTL_CLOCK_RESERVED24,			/*!< 24: Reserved */
	SYSCTL_CLOCK_RESERVED25,			/*!< 25: Reserved */
	SYSCTL_CLOCK_RESERVED26,			/*!< 26: Reserved */
	SYSCTL_CLOCK_RESERVED27,			/*!< 27: Reserved */
	SYSCTL_CLOCK_RESERVED28,			/*!< 28: Reserved */
	SYSCTL_CLOCK_GPIO2,					/*!< 29: GPIO 2 clock*/
	SYSCTL_CLOCK_GPIO1,					/*!< 30: GPIO 2 clock*/
	SYSCTL_CLOCK_GPIO0,					/*!< 31: GPIO 2 clock*/
} CHIP_SYSCTL_CLOCK_T;

/**
 * @brief	Enable a system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_EnablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCTL->SYSAHBCLKCTRL |= (1 << clk);
}

/**
 * @brief	Disable a system or peripheral clock
 * @param	clk	: Clock to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_Clock_DisablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCTL->SYSAHBCLKCTRL &= ~(1 << clk);
}

/**
 * @brief	Set SSP0 divider
 * @param	div	: divider for SSP0 clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The SSP0 clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetSSP0ClockDiv(uint32_t div)
{
	LPC_SYSCTL->SSP0CLKDIV  = div;
}

/**
 * @brief	Return SSP0 divider
 * @return	divider for SSP0 clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetSSP0ClockDiv(void)
{
	return LPC_SYSCTL->SSP0CLKDIV;
}

/**
 * @brief	Set UART 0 divider clock
 * @param	div	: divider for UART clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The UART clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetUART0ClockDiv(uint32_t div)
{
	LPC_SYSCTL->UART0CLKDIV  = div;
}

/**
 * @brief	Return UART 0 divider
 * @return	divider for UART clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetUART0ClockDiv(void)
{
	return LPC_SYSCTL->UART0CLKDIV;
}

/**
 * @brief	Set UART 1 divider clock
 * @param	div	: divider for UART clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The UART clock
 * rate is the main system clock divided by this value.
 */
STATIC INLINE void Chip_Clock_SetUART1ClockDiv(uint32_t div)
{
	LPC_SYSCTL->UART1CLKDIV  = div;
}

/**
 * @brief	Return UART 1 divider
 * @return	divider for UART clock
 * @note	A value of 0 means the clock is disabled.
 */
STATIC INLINE uint32_t Chip_Clock_GetUART1ClockDiv(void)
{
	return LPC_SYSCTL->UART1CLKDIV;
}

/**
 * Clock sources for CLKOUT
 */
typedef enum CHIP_SYSCTL_CLKOUTSRC {
	SYSCTL_CLKOUTSRC_IRC = 0,		/*!< Internal oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_MAINOSC,		/*!< Main oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_WDTOSC,		/*!< Watchdog oscillator for CLKOUT */
	SYSCTL_CLKOUTSRC_MAINSYSCLK,	/*!< Main system clock for CLKOUT */
} CHIP_SYSCTL_CLKOUTSRC_T;

/**
 * @brief	Set CLKOUT clock source and divider
 * @param	src	: Clock source for CLKOUT
 * @param	div	: divider for CLKOUT clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The CLKOUT clock
 * rate is the clock source divided by the divider. This function will
 * also toggle the clock source update register to update the clock
 * source.
 */
void Chip_Clock_SetCLKOUTSource(CHIP_SYSCTL_CLKOUTSRC_T src, uint32_t div);


/**
 * @brief	Returns the main oscillator clock rate
 * @return	main oscillator clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetMainOscRate(void)
{
	return OscRateIn;
}

/**
 * @brief	Returns the internal oscillator (IRC) clock rate
 * @return	internal oscillator (IRC) clock rate
 */
STATIC INLINE uint32_t Chip_Clock_GetIntOscRate(void)
{
	return SYSCTL_IRC_FREQ;
}

/**
 * @brief	Return estimated watchdog oscillator rate
 * @return	Estimated watchdog oscillator rate
 * @note	This rate is accurate to plus or minus 40%.
 */
uint32_t Chip_Clock_GetWDTOSCRate(void);


/**
 * @brief	Return System PLL input clock rate
 * @return	System PLL input clock rate
 */
uint32_t Chip_Clock_GetSystemPLLInClockRate(void);

/**
 * @brief	Return System PLL output clock rate
 * @return	System PLL output clock rate
 */
uint32_t Chip_Clock_GetSystemPLLOutClockRate(void);

/**
 * @brief	Return main clock rate
 * @return	main clock rate
 */
uint32_t Chip_Clock_GetMainClockRate(void);

/**
 * @brief	Return system clock rate
 * @return	system clock rate
 */
uint32_t Chip_Clock_GetSystemClockRate(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_11XX_H_ */

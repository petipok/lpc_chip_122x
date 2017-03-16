/*
 * @brief LPC122x Pin Interrupt and Pattern Match Registers and driver
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

#ifndef __PININT_122X_H_
#define __PININT_122X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PININT_122X CHIP: LPC122x Pin Interrupt and Pattern Match driver
 * @ingroup CHIP_122X_Drivers
 * For device familes identified with CHIP definitions CHIP_LPC122X,
 * @{
 */

#if defined(CHIP_LPC122X)
#include "gpio_122x.h"

/**
 * @brief LPC122x Pin Interrupt can be configured via the GPIO control registers
 */

#define LPC_PIN_INT_T	LPC_GPIO_T

/**
 * LPC11xx Pin Interrupt channel values
 */
#define PININTCH0         (1 << 0)
#define PININTCH1         (1 << 1)
#define PININTCH2         (1 << 2)
#define PININTCH3         (1 << 3)
#define PININTCH4         (1 << 4)
#define PININTCH5         (1 << 5)
#define PININTCH6         (1 << 6)
#define PININTCH7         (1 << 7)
#define PININTCH(ch)      (1 << (ch))

/**
 * @brief	Initialize Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block
 * @return	Nothing
 * @note	This function should be used after the Chip_GPIO_Init() function.
 */
STATIC INLINE void Chip_PININT_Init(LPC_PIN_INT_T *pPININT) {}

/**
 * @brief	De-Initialize Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DeInit(LPC_PIN_INT_T *pPININT) {}

/**
 * @brief	Configure the pins as edge sensitive in Pin interrupt block 
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_SetPinModeEdge(LPC_PIN_INT_T *pPININT,  uint32_t port, uint32_t pins)
{
    pPININT[port].IS &= ~pins;
    pPININT[port].IBE &= ~pins;
}

/**
 * @brief	Configure the pins as level sensitive in Pin interrupt block 
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_SetPinModeLevel(LPC_PIN_INT_T *pPININT,  uint32_t port, uint32_t pins)
{
	pPININT[port].IS |= pins;
	pPININT[port].IBE &= ~pins;
}

/**
 * @brief	Configure the pins as level sensitive in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block
 * @param	pins	: Pins (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_SetPinModeBothEdge(LPC_PIN_INT_T *pPININT,  uint32_t port, uint32_t pins)
{
	pPININT[port].IS &= ~pins;
	pPININT[port].IBE |= pins;
}

/**
 * @brief	Return current PININT rising edge or high level interrupt enable state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	A bifield containing the high edge/level interrupt enables for each
 * interrupt. Bit 0 = PININT0, 1 = PININT1, etc.
 * For each bit, a 0 means the high edge/level interrupt is disabled, while a 1
 * means it's enabled.
 */
STATIC INLINE uint32_t Chip_PININT_GetEnabled(LPC_PIN_INT_T *pPININT, uint32_t port)
{
    return pPININT[port].IEV;
}

/**
 * @brief	Enable high edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to enable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_EnableInt(LPC_PIN_INT_T *pPININT,  uint32_t port, uint32_t pins)
{
	pPININT[port].IEV |= pins;
}

/**
 * @brief	Disable high edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to disable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DisableInt(LPC_PIN_INT_T *pPININT,  uint32_t port, uint32_t pins)
{
	pPININT[port].IEV &= ~pins;
}


/**
 * @brief	Get interrupt status from Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Interrupt status (bit n for PININTn = high means interrupt ie pending)
 */
STATIC INLINE uint32_t Chip_PININT_GetIntStatus(LPC_PIN_INT_T *pPININT, uint32_t port)
{
    return pPININT[port].RIS;
}

/**
 * @brief	Clear interrupt status in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pin interrupts to clear (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_ClearIntStatus(LPC_PIN_INT_T *pPININT, uint32_t port, uint32_t pins)
{
	pPININT[port].CLR |= pins;
}

#endif /* defined(CHIP_LPC11AXX) || defined(CHIP_LPC11EXX) || defined(CHIP_LPC11UXX) */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __PININT_11XX_H_ */

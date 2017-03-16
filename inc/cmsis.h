/*
 * @brief LPC122x selective CMSIS inclusion file
 *
 * @note
 * WARNING: THIS LIBRARY HAS BEEN PORTED TO LPC122x devices from the lpc_chip_11u14 LPCOPEN chip library. Please consider this when using it.
 * This library is provided as is, and the authors DO NOT GUARANTEE that it is working.
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CMSIS_H_
#define __CMSIS_H_

#include "lpc_types.h"
#include "sys_config.h"

#if defined(CHIP_LPC122x)
#include "cmsis_122x.h"
typedef LPC122X_IRQn_Type IRQn_Type;
#else
#error "No CHIP_* definition is defined"
#endif

/* Cortex-M0 processor and core peripherals */
#include "core_cm0.h"

#endif /* __CMSIS_H_ */

/**
 * @file rtc_122x.h
 *
 * @date 22 Mar 2017
 * @author ppok
 */

#ifndef LPC_CHIP_122X_INC_RTC_122X_H_
#define LPC_CHIP_122X_INC_RTC_122X_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Real Time Clock register block structure
 */
typedef struct {							/*!< RTC Structure          */
	__I  uint32_t  DR;						/*!< Data Register */
	__IO uint32_t  MR;						/*!< Match Register */
	__IO uint32_t  LR;						/*!< Load Register */
	__IO uint32_t  CR;					    /*!< Control Register */
	__IO uint32_t  ICSC;					/*!< Interrupt control set/clear register    */
	__I  uint32_t  RIS;						/*!< Raw interrupt status register */
	__I uint32_t   MIS;						/*!< Masked interrupt status register */
	__O uint32_t   ICR;						/*!< Interrupt Clear Register */
} LPC_RTC_T;

#define RTC_CR_RTCSTART			(1<<0)

#define RTC_ICSC_RTCIC			(1<<0)

#define RTC_RIS_RTCRIS			(1<<0)

#define RTC_MIS_RTCMIS			(1<<0)

#define RTC_ICR_RTCICR			(1<<0)

#ifdef __cplusplus
}
#endif

#endif /* LPC_CHIP_122X_INC_RTC_122X_H_ */

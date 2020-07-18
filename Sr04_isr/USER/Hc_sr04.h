/*
 * Hc_sr04.h
 *
 *  Created on: 2020Äê7ÔÂ17ÈÕ
 *      Author: 1004
 */

#ifndef USER_HC_SR04_H_
#define USER_HC_SR04_H_
#include "zf_spi.h"
#include "common.h"
#include "zf_gpio.h"
#include "zf_assert.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_PRINTF.h"



#define TRIG_PIN        P33_12
#define ECHO_PIN        P33_13
void Sr04_init (void);
uint32 get_distance(STMN_enum stmn);
#endif /* USER_HC_SR04_H_ */

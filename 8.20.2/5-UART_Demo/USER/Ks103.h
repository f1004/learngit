/*
 * Ks103.h
 *
 *  Created on: 2020Äê7ÔÂ18ÈÕ
 *      Author: 1004
 */

#ifndef USER_KS103_H_
#define USER_KS103_H_
#include "common.h"
#include "Vadc/Adc/IfxVadc_Adc.h"
#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"

void Ks103_init(void);
int32 Ks103_getdistance(void);


#endif /* USER_KS103_H_ */

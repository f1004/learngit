/*
 * img.h
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: 1004
 */

#ifndef USER_IMG_H_
#define USER_IMG_H_

#include "Cpu/Std/Ifx_Types.h"

#ifndef img_height
#define img_height 120
#endif
#ifndef img_width
#define img_width 188
#endif

extern int pixel_total;

int *Histo(uint8 *img) ;
uint8 PixelAverage(int *histogram, uint8 threshold);
uint8 IterationThreshold(int *histogram);
int Binarize(uint8 *img, uint8 threshold);
uint8 OtsuThreshold(int *histogram);

#endif /* USER_IMG_H_ */

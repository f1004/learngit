//
// Created by plectranthus_fg on 2020/07/13.
//

#ifndef IMG_BASE_IMG_H
#define IMG_BASE_IMG_H

#ifndef img_width
#define img_width 188
#endif
#ifndef img_height
#define img_height 120
#endif
#include "Cpu/Std/Ifx_Types.h"
#include <cstdint>

#include <bitset>
#include <vector>
#include <cstring>

extern int pixel_total;

int *Histo(uint8 *img);
uint8 OtsuThreshold(int *histogram);
int Binarize(uint8_t *img, uint8 threshold);
uint8 IterationThreshold(int *histogram);
int GaussianConvolution(uint8 *img);
int ImageFilter(uint8 *img);

class Point{
     public:
     int x_,y_;
   };


    std::vector<std::bitset<img_width>> PerspectiveTransform(uint8_t *img, int bottom_width);

#endif //IMG_BASE_IMG_H

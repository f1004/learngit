#include "img.h"
#include <stdlib.h>
#include <string.h>

int pixel_total = img_height * img_width;
/*
function: Histo
last edited: 2020/07/13 1:56
last edit by: Plectranthus_fg
description: Calculate frequency distribution histogram
!!!WARNING: use delete []histogram to free the memory to avoid memory leak !!!
!!!WARNING: use *p = nullptr to reset the pointer to avoid dangling pointer !!!
*/
int* Histo(uint8 *img) {
	int *histogram = malloc(256*sizeof(int));
	memset(histogram,0,256*sizeof(int));
	for (int i = 0; i < pixel_total; i++) {
		histogram[img[i]] += 1;
	}
	return histogram;
}

/*
    function: OtsuThreshold
    last edited: 2020/07/13 3:43
    last edit by: Plectranthus_fg
    description: use Otsu method to get the threshold
*/
uint8 OtsuThreshold(int *histogram) {
    int sumB = 0;
    int sum1 = 0;
    float wB = 0.0f;
    float wF = 0.0f;
    float mF = 0.0f;
    float max_var = 0.0f;
    float inter_var = 0.0f;
    uint8 threshold = 0;
    int index_histo = 0;

    for (index_histo = 0; index_histo < 256; index_histo++) {
        sum1 += index_histo * histogram[index_histo];
    }

    for (index_histo = 0; index_histo < 256; index_histo++) {
        wB = wB + histogram[index_histo];
        wF = pixel_total - wB;
        if (wB == 0 || wF == 0) {
            continue;
        }
        sumB = sumB + index_histo * histogram[index_histo];
        mF = (sum1 - sumB) / wF;
        inter_var = wB * wF * ((sumB / wB) - mF) * ((sumB / wB) - mF);
        if (inter_var >= max_var) {
            threshold = index_histo;
            max_var = inter_var;
        }
    }

    return threshold;
}

/*
function: PixelAverage
last edited: 2020/07/13 4:29
last edit by: Plectranthus_fg
description: Calculate the gray scale average of foreground and background.(Only used by IterationThreshold())
*/
uint8 PixelAverage(int *histogram, uint8 threshold) {
	int foreground_average, background_average;
	int foreground_total, background_total;
	foreground_average = 0;
	background_average = 0;
	foreground_total = 0;
	background_total = 0;
	for (int i = 0; i < threshold; ++i) {
		background_total += histogram[i];
		background_average += histogram[i] * i;
	}
	background_average = background_average / background_total;
	for (int i = threshold; i < 256; ++i) {
		foreground_total += histogram[i];
		foreground_average += histogram[i] * i;
	}
	foreground_average = foreground_average / foreground_total;
	int average = (background_average + foreground_average) / 2;
	return (uint8)average;
}

/*
function: IterationThreshold
last edited: 2020/07/13 4:26
last edit by: Plectranthus_fg
description: use Iteration method to get the threshold,
which runs slower but may get better data Under complex lighting.
*/
uint8 IterationThreshold(int *histogram) {
	int p_min, p_max;
	for (p_min = 0; p_min < 256; ++p_min) {
		if (histogram[p_min] != 0) {
			break;
		}
	}
	for (p_max = 255; p_max >= 0; --p_max) {
		if (histogram[p_max] != 0) {
			break;
		}
	}
	uint8 threshold = (p_min + p_max) / 2;
	uint8 threshold_cache = PixelAverage(histogram, threshold);
	while (threshold != threshold_cache) {
		threshold = threshold_cache;
		threshold_cache = PixelAverage(histogram, threshold);
	}
	return threshold;
}

/*
    function: Binarize
    last edited: 2020/07/13 4:29
    last edit by: Plectranthus_fg
    description: Convert origin image to binary images with provided threshold
*/
int Binarize(uint8 *img, uint8 threshold) {
    for (int i = 0; i < pixel_total; ++i) {
        if (img[i] < threshold) {
            img[i] = 0;
        } else {
            img[i] = 255;
        }
    }
    return 0;
}

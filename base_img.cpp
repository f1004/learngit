//
// Created by plectranthus_fg on 2020/07/13.
//
#include "base_img.h"
#include <cmath>
using namespace std;

int pixel_total = img_height * img_width;
namespace img {
    /*
    function: Histo
    last edited: 2020/07/13 1:56
    last edit by: Plectranthus_fg
    description: Calculate frequency distribution histogram
    !!!WARNING: use delete []histogram to free the memory to avoid memory leak !!!
    !!!WARNING: use *p = nullptr to reset the pointer to avoid dangling pointer !!!
    */
    int *Histo(uint8_t *img) {
        int *histogram = new int[256]{};
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
    uint8_t OtsuThreshold(int *histogram) {
        int sumB = 0;
        int sum1 = 0;
        float wB = 0.0f;
        float wF = 0.0f;
        float mF = 0.0f;
        float max_var = 0.0f;
        float inter_var = 0.0f;
        uint8_t threshold = 0;
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
        return average;
    }

    /*
    function: IterationThreshold
    last edited: 2020/07/13 4:26
    last edit by: Plectranthus_fg
    description: use Iteration method to get the threshold,
    which runs slower but may get better data Under complex lighting.
    */
    uint8_t IterationThreshold(int *histogram) {
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
    int Binarize(uint8_t *img, uint8_t threshold) {
        for (int i = 0; i < pixel_total; ++i) {
            (img[i] < threshold) ? img[i] = 0 : img[i] = 255;
        }
        return 0;
    }

    /*
        function: GaussianConvolution
        last edited: 2020/07/17 13:07
        last edit by: Plectranthus_fg
        description: Use Gaussian Convolutional kernel to convolute image with same padding
        Convolutional kernel = [1/16    2/16    1/16]
                               [2/16    4/16    2/16]
                               [1/16    2/16    1/16]
    */
    int GaussianConvolution(uint8_t *img) {
        uint8_t image[img_height][img_width];
        std::memcpy(image, img, sizeof(image));
        img[0] =
                (image[0][0] / 16) + (image[0][0] / 8) + (image[0][1] / 16) +
                (image[0][0] / 8) + (image[0][0] / 4) + (image[0][1] / 8) +
                (image[1][0] / 16) + (image[1][0] / 8) + (image[1][1] / 16);
        for (int i = 1; i < img_width - 1; ++i) {
            img[i] =
                    (image[0][i - 1] / 16) + (image[0][i] / 8) + (image[0][i + 1] / 16) +
                    (image[0][i - 1] / 8) + (image[0][i] / 4) + (image[0][i + 1] / 8) +
                    (image[1][i - 1] / 16) + (image[1][i] / 8) + (image[1][i + 1] / 16);
        }
        img[img_width - 1] =
                (image[0][img_width - 2] / 16) + (image[0][img_width - 1] / 8) + (image[0][img_width - 1] / 16) +
                (image[0][img_width - 2] / 8) + (image[0][img_width - 1] / 4) + (image[0][img_width - 1] / 8) +
                (image[1][img_width - 2] / 16) + (image[1][img_width - 1] / 8) + (image[1][img_width - 1] / 16);
        for (int j = img_width; j < (img_height - 1) * img_width - 1; ++j) {
            if (j % img_width == 0) {
                img[j] =
                        (image[j / img_width - 1][0] / 16) + (image[j / img_width - 1][0] / 8) +
                        (image[j / img_width - 1][1] / 16) +
                        (image[j / img_width][0] / 8) + (image[j / img_width][0] / 4) + (image[j / img_width][1] / 8) +
                        (image[j / img_width + 1][0] / 16) + (image[j / img_width + 1][0] / 8) +
                        (image[j / img_width + 1][1] / 16);
            } else if (j % img_width == img_width - 1) {
                img[j] =
                        (image[j / img_width - 1][img_width - 2] / 16) + (image[j / img_width - 1][img_width - 1] / 8) +
                        (image[j / img_width - 1][img_width - 1] / 16) +
                        (image[j / img_width][img_width - 2] / 8) + (image[j / img_width][img_width - 1] / 4) +
                        (image[j / img_width][img_width - 1] / 8) +
                        (image[j / img_width + 1][img_width - 2] / 16) + (image[j / img_width + 1][img_width - 1] / 8) +
                        (image[j / img_width + 1][img_width - 1] / 16);
            } else {
                img[j] =
                        (image[j / img_width - 1][j % img_width - 1] / 16) +
                        (image[j / img_width - 1][j % img_width] / 8) +
                        (image[j / img_width - 1][j % img_width + 1] / 16) +
                        (image[j / img_width][j % img_width - 1] / 8) +
                        (image[j / img_width][j % img_width] / 4) +
                        (image[j / img_width][j % img_width + 1] / 8) +
                        (image[j / img_width + 1][j % img_width - 1] / 16) +
                        (image[j / img_width + 1][j % img_width] / 8) +
                        (image[j / img_width + 1][j % img_width + 1] / 16);
            }
        }
        img[pixel_total - img_width] =
                (image[img_height - 1][0] / 16) + (image[0][0] / 8) + (image[0][1] / 16) +
                (image[0][0] / 8) + (image[0][0] / 4) + (image[0][1] / 8) +
                (image[1][0] / 16) + (image[1][0] / 8) + (image[1][1] / 16);
        img[pixel_total - 1] =
                (image[img_height - 2][img_width - 2] / 16) +
                (image[img_height - 2][img_width - 1] / 8) +
                (image[img_height - 2][img_width - 1] / 16) +
                (image[img_height - 1][img_width - 2] / 8) +
                (image[img_height - 1][img_width - 1] / 4) +
                (image[img_height - 1][img_width - 1] / 8) +
                (image[img_height - 1][img_width - 2] / 16) +
                (image[img_height - 1][img_width - 1] / 8) +
                (image[img_height - 1][img_width - 1] / 16);;
        return 0;
    }

    /*
    function: ImageFilter
    last edited: 2020/07/21 0:21
    last edit by: Plectranthus_fg
    description: Find the edge of the binary image
    */
    int ImageFilter(uint8_t *img) {
        for (int i = 0; i < pixel_total; ++i) {
            (img[i] == 0x00 || img[i] == 0xF7) ? img[i] = 0xFF : img[i] = 0x00;
        }
        return 0;
    }

    /*
    function: ImageFilter
    last edited: 2020/07/23 20:54
    last edit by: Plectranthus_fg
    description: Find the edge of the binary image
    */
    std::vector<std::bitset<img_width>> PerspectiveTransform(uint8_t *img, int bottom_width) {
        std::vector<std::bitset<img_width>> top_down_perspective;
        std::bitset<img_width> cache = {0};
        for (int i = 0; i < img_height; ++i) {
            auto line_width = (img_height - i) / (double) img_height *
                              (img_width - bottom_width) + bottom_width;
            for (int j = 0; j < img_width; ++j) {
                if (img[i*img_width + j] == 0x00) {
                    int a = (int) round((long double)line_width / img_width * j + (img_width - line_width) / 2);
                    cache[img_width - a] = true;
                }
            }
            top_down_perspective.push_back(cache);
            cache = {0};
        }
        return top_down_perspective;
    }
}

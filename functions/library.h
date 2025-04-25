#include "../libs/stb_image.h"
#include "../libs/stb_image_write.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

unsigned char* Interpolation(unsigned char* img,int width, int height,int channels, int size_of_kernel,int dop_pix,int new_width,int new_height);
unsigned char* Gaussian_filter(unsigned char*img, int width,int height,int channels,int size_of_kernel,int square_of_devatiion);
unsigned char* Median_filter(unsigned char*img, int width,int height,int channels,int size_of_kernel);
unsigned char* Canny_Edge_Detector(unsigned char*img, int width, int height, int channels, int size_of_kernel,int square_of_devation);
unsigned char* bord_on_img(unsigned char*img, int width, int height, int channels,int size_of_kernel,int square_of_devation);
unsigned char* Sharpening_Kernels(unsigned char*img, int width, int height, int channels);
unsigned char* image_rotation(unsigned char*img,int width,int height,int channels,char* side);
unsigned char* Scaling(unsigned char*img,int width,int height,int channels,float magnification_size);
unsigned char* Morphing(unsigned char*img,unsigned char*img2,int width,int height,int channels,int width2,int height2,int channels2);
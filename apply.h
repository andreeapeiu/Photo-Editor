// Peiu Andreea 324 CA - refacere PCLP1
#ifndef APPLY_H
#define APPLY_H

#include "image_utils.h"

void gaussian_blur(image * img);

void blur(image *img);

void sharpen(image *img);

void edge(image *img);

void apply(image *img, char s[]);

#endif

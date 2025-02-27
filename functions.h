// Peiu Andreea 324 CA - refacere PCLP1
#ifndef FUNCTION_H
#define FUNCTION_H

#include "image_utils.h"

void do2(image * img, FILE *file);

void do3(image *img, FILE *file);

void do5(image *img, FILE *file);

void cast(image *img, unsigned char r, unsigned char g, unsigned char b,
		  int i, int j);

void do6(image *img, FILE *file);

void loading(image *img, char namefile[]);

void crop2(image *img, int l, int c, image *new_image);

void crop3(image *img, int l, int c, image *new_image);

void crop(image *img);

void sel(int x1, int y1, int x2, int y2, image *img);

int verify_number(char *p);

void parse_assign_coord(char *s, int *x1, int *y1, int *x2,
						int *y2, image *img);

void select_all(image *img);

void save_ascii(const char *name_file, image *img);

void save_binary(const char *name_file, image *img);

void verify_power(int y);

double *frequency(image img, int y);

void histogram(image *img, char s[]);

void equalize(image *img);

void clamp(int *x);

void gaussian_blur(image *img);

void blur(image *img);

void sharpen(image *img);

void edge(image *img);

void apply(image *img, char s[]);

#endif

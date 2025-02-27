// Peiu Andreea 324 CA - refacere PCLP1
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 100

typedef struct {
	int x1, x2, y1, y2;
} selection;

typedef struct {
	int r, g, b;
} color_rgb;

typedef struct {
	char magic_word[3];
	int type; // 1 2 3 4 5 sau 6
	int width; // latime
	int height; // inaltime
	int max_val; // max pt greyscale
	int loaded; // 0 sau 1
	int selected_with_function; // 0 sau 1
	int saved;
	int **greyscale; // 0-255
	color_rgb **colors;
	selection selected;
} image;

void free_colors_memory(image *img);

void free_rgb_matrix(color_rgb **matrix, int m);

void free_matrix(int **matrix, int m);

void free_image(image *img);

void dealloc_matrix(int **v, int n);

void dealloc_color(color_rgb **v, int n);

double double_clamp(double x, int low, int upp);

void exit_program(image *img);

void verify_comments(FILE *file);

int **alloc_matrix(int l, int c, image *img);

color_rgb **alloc_color(int l, int c, image *img);

void swap(int *a, int *b);

int verify_p_number(char *p);

double rounding(double val);

#endif // IMAGE_UTILS_H

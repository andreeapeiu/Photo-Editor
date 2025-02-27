// Peiu Andreea 324 CA
#ifndef ROTATE_H
#define ROTATE_H

#include "image_utils.h"

void rotate_non_square_90_grey(image * img);

void rotate_non_square_90_color(image *img);

void rotate_90_grey(image *img);

void rotate_90_color(image *img);

char *parse_rotation_command(char s[]);

void handle_rotation_minus_90(image *img, int is_square);

void handle_rotation_180(image *img, int is_square);

void handle_rotation_90(image *img, int is_square);

void rotate(image *img, char s[]);

#endif

// Peiu Andreea 324 CA - refacere PCLP1

#include "image_utils.h"

void free_colors_memory(image *img)
{
	for (int i = 0; i < img->height; i++)
		free(img->colors[i]);
	free(img->colors);
}

void free_rgb_matrix(color_rgb **matrix, int m)
{
	for (int i = 0; i < m; i++)
		free(matrix[i]);
	free(matrix);
}

void free_matrix(int **matrix, int m)
{
	for (int i = 0; i < m; i++)
		free(matrix[i]);
	free(matrix);
}

void free_image(image *img)
{
	if (img->type == 2 || img->type == 5)
		free_matrix(img->greyscale, img->height);
	else if (img->type == 3 || img->type == 6)
		free_colors_memory(img);
}

void dealloc_matrix(int **v, int n)
{
	for (int i = 0; i < n; i++)
		free(v[i]);
	free(v);
}

void dealloc_color(color_rgb **v, int n)
{
	int i;
	for (i = 0; i < n; i++)
		free(v[i]);
	free(v);
}

double double_clamp(double x, int low, int upp)
{
	if (x < low)
		return 1. * low;
	else if (x > upp)
		return 1. * upp;
	return x;
}

void exit_program(image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}
	if (img->loaded == 1) {
		if (img->type == 2 || img->type == 5)
			dealloc_matrix(img->greyscale, img->height);
		else
			dealloc_color(img->colors, img->height);

		img->loaded = 0;
		img->height = 0;
		img->width = 0;
		img->selected.x1 = 0;
		img->selected.x2 = 0;
		img->selected.y1 = 0;
		img->selected.y2 = 0;
	}
}

void verify_comments(FILE *file)
{
	char c;
	char line[NMAX];
	fscanf(file, "%c", &c);
	while (c == '#') {
		fgets(line, sizeof(line), file);
		if (feof(file))
			return;
		fscanf(file, "%c", &c);
	}
	fseek(file, -1, SEEK_CUR);
}

int **alloc_matrix(int l, int c, image *img)
{
	// n este nr de linii si m nr de coloane
	int **v = (int **)calloc(l, sizeof(int *));
	if (!v) {
		printf("Failed to allocate memory\n");
		exit_program(img);
	}
	for (int i = 0; i < l; i++) {
		v[i] = (int *)calloc(c, sizeof(int));
		if (!v[i]) {
			printf("Failed to allocate memory\n");
			exit_program(img);
		}
	}
	return v;
}

color_rgb **alloc_color(int l, int c, image *img)
{
	// n este nr de linii si m nr de coloane
	color_rgb **v = (color_rgb **)calloc(l, sizeof(color_rgb *));
	if (!v) {
		printf("Failed to allocate memory\n");
		exit_program(img);
	}
	for (int i = 0; i < l; i++) {
		v[i] = (color_rgb *)calloc(c, sizeof(color_rgb));
		if (!v[i]) {
			printf("Failed to allocate memory\n");
			exit_program(img);
		}
	}
	return v;
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int verify_p_number(char *p)
{
	int size = (int)strlen(p);
	for (int i = 0; i < size; i++)
		if (!isdigit(p[i]))
			printf("Invalid command\n");
	return 1;
}

double rounding(double val)
{
	int x = (int)val;
	if (val - x >= 0.5)
		return x + 1;
	return x;
}

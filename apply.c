// Peiu Andreea 324 CA - refacere PCLP1

#include "apply.h"
#include "image_utils.h"
#include "functions.h"

void gaussian_blur(image *img)
{
	double kernel[3][3] = { { 1, 2, 1 }, { 2, 4, 2 }, { 1, 2, 1 } };
	double ker_copy[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ker_copy[i][j] = (double)kernel[i][j] / 16;

	int x1 = img->selected.x1, x2 = img->selected.x2;
	int y1 = img->selected.y1, y2 = img->selected.y2;
	if (x1 == 0)
		x1++;
	if (x2 == img->width)
		x2--;
	if (y1 == 0)
		y1++;
	if (y2 == img->height)
		y2--;

	image copie;
	copie.height = y2 - y1;
	copie.width = x2 - x1;
	copie.colors = alloc_color(copie.height, copie.width, &copie);

	double sum1, sum2, sum3;
	double s1, s2, s3;

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
			sum1 = sum1 + img->colors[i - 1][j - 1].r * ker_copy[0][0];
			sum1 = sum1 + img->colors[i - 1][j].r * ker_copy[0][1];
			sum1 = sum1 + img->colors[i - 1][j + 1].r * ker_copy[0][2];
			sum1 = sum1 + img->colors[i][j - 1].r * ker_copy[1][0];
			sum1 = sum1 + img->colors[i][j].r * ker_copy[1][1];
			sum1 = sum1 + img->colors[i][j + 1].r * ker_copy[1][2];
			sum1 = sum1 + img->colors[i + 1][j - 1].r * ker_copy[2][0];
			sum1 = sum1 + img->colors[i + 1][j].r * ker_copy[2][1];
			sum1 = sum1 + img->colors[i + 1][j + 1].r * ker_copy[2][2];
			sum2 = sum2 + img->colors[i - 1][j - 1].g * ker_copy[0][0];
			sum2 = sum2 + img->colors[i - 1][j].g * ker_copy[0][1];
			sum2 = sum2 + img->colors[i - 1][j + 1].g * ker_copy[0][2];
			sum2 = sum2 + img->colors[i][j - 1].g * ker_copy[1][0];
			sum2 = sum2 + img->colors[i][j].g * ker_copy[1][1];
			sum2 = sum2 + img->colors[i][j + 1].g * ker_copy[1][2];
			sum2 = sum2 + img->colors[i + 1][j - 1].g * ker_copy[2][0];
			sum2 = sum2 + img->colors[i + 1][j].g * ker_copy[2][1];
			sum2 = sum2 + img->colors[i + 1][j + 1].g * ker_copy[2][2];
			sum3 = sum3 + img->colors[i - 1][j - 1].b * ker_copy[0][0];
			sum3 = sum3 + img->colors[i - 1][j].b * ker_copy[0][1];
			sum3 = sum3 + img->colors[i - 1][j + 1].b * ker_copy[0][2];
			sum3 = sum3 + img->colors[i][j - 1].b * ker_copy[1][0];
			sum3 = sum3 + img->colors[i][j].b * ker_copy[1][1];
			sum3 = sum3 + img->colors[i][j + 1].b * ker_copy[1][2];
			sum3 = sum3 + img->colors[i + 1][j - 1].b * ker_copy[2][0];
			sum3 = sum3 + img->colors[i + 1][j].b * ker_copy[2][1];
			sum3 = sum3 + img->colors[i + 1][j + 1].b * ker_copy[2][2];
			s1 = rounding(double_clamp(sum1, 0, 255));
			s2 = rounding(double_clamp(sum2, 0, 255));
			s3 = rounding(double_clamp(sum3, 0, 255));
			copie.colors[i - y1][j - x1].r = s1;
			copie.colors[i - y1][j - x1].g = s2;
			copie.colors[i - y1][j - x1].b = s3;
		}
	}

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			img->colors[i][j].r = copie.colors[i - y1][j - x1].r;
			img->colors[i][j].g = copie.colors[i - y1][j - x1].g;
			img->colors[i][j].b = copie.colors[i - y1][j - x1].b;
		}
	}

	printf("APPLY GAUSSIAN_BLUR done\n");

	free_colors_memory(&copie);
}

void blur(image *img)
{
	double kernel[3][3] = { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };
	double ker_copy[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ker_copy[i][j] = (double)kernel[i][j] / 9;

	int x1 = img->selected.x1, x2 = img->selected.x2;
	int y1 = img->selected.y1, y2 = img->selected.y2;
	if (x1 == 0)
		x1++;
	if (x2 == img->width)
		x2--;
	if (y1 == 0)
		y1++;
	if (y2 == img->height)
		y2--;

	image copie;
	copie.height = y2 - y1;
	copie.width = x2 - x1;
	copie.colors = alloc_color(copie.height, copie.width, &copie);

	double sum1, sum2, sum3;
	double s1, s2, s3;
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
			sum1 = sum1 + img->colors[i - 1][j - 1].r * ker_copy[0][0];
			sum1 = sum1 + img->colors[i - 1][j].r * ker_copy[0][1];
			sum1 = sum1 + img->colors[i - 1][j + 1].r * ker_copy[0][2];
			sum1 = sum1 + img->colors[i][j - 1].r * ker_copy[1][0];
			sum1 = sum1 + img->colors[i][j].r * ker_copy[1][1];
			sum1 = sum1 + img->colors[i][j + 1].r * ker_copy[1][2];
			sum1 = sum1 + img->colors[i + 1][j - 1].r * ker_copy[2][0];
			sum1 = sum1 + img->colors[i + 1][j].r * ker_copy[2][1];
			sum1 = sum1 + img->colors[i + 1][j + 1].r * ker_copy[2][2];
			sum2 = sum2 + img->colors[i - 1][j - 1].g * ker_copy[0][0];
			sum2 = sum2 + img->colors[i - 1][j].g * ker_copy[0][1];
			sum2 = sum2 + img->colors[i - 1][j + 1].g * ker_copy[0][2];
			sum2 = sum2 + img->colors[i][j - 1].g * ker_copy[1][0];
			sum2 = sum2 + img->colors[i][j].g * ker_copy[1][1];
			sum2 = sum2 + img->colors[i][j + 1].g * ker_copy[1][2];
			sum2 = sum2 + img->colors[i + 1][j - 1].g * ker_copy[2][0];
			sum2 = sum2 + img->colors[i + 1][j].g * ker_copy[2][1];
			sum2 = sum2 + img->colors[i + 1][j + 1].g * ker_copy[2][2];
			sum3 = sum3 + img->colors[i - 1][j - 1].b * ker_copy[0][0];
			sum3 = sum3 + img->colors[i - 1][j].b * ker_copy[0][1];
			sum3 = sum3 + img->colors[i - 1][j + 1].b * ker_copy[0][2];
			sum3 = sum3 + img->colors[i][j - 1].b * ker_copy[1][0];
			sum3 = sum3 + img->colors[i][j].b * ker_copy[1][1];
			sum3 = sum3 + img->colors[i][j + 1].b * ker_copy[1][2];
			sum3 = sum3 + img->colors[i + 1][j - 1].b * ker_copy[2][0];
			sum3 = sum3 + img->colors[i + 1][j].b * ker_copy[2][1];
			sum3 = sum3 + img->colors[i + 1][j + 1].b * ker_copy[2][2];

			s1 = rounding(double_clamp(sum1, 0, 255));
			s2 = rounding(double_clamp(sum2, 0, 255));
			s3 = rounding(double_clamp(sum3, 0, 255));
			copie.colors[i - y1][j - x1].r = s1;
			copie.colors[i - y1][j - x1].g = s2;
			copie.colors[i - y1][j - x1].b = s3;
		}
	}

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			img->colors[i][j].r = copie.colors[i - y1][j - x1].r;
			img->colors[i][j].g = copie.colors[i - y1][j - x1].g;
			img->colors[i][j].b = copie.colors[i - y1][j - x1].b;
		}
	}

	printf("APPLY BLUR done\n");

	free_colors_memory(&copie);
}

void sharpen(image *img)
{
	int kernel[3][3] = { { 0, -1, 0 },
		{ -1, 5, -1 },
		{ 0, -1, 0 } };

	int x1 = img->selected.x1, x2 = img->selected.x2;
	int y1 = img->selected.y1, y2 = img->selected.y2;
	if (x1 == 0)
		x1++;
	if (x2 == img->width)
		x2--;
	if (y1 == 0)
		y1++;
	if (y2 == img->height)
		y2--;

	image copie;
	copie.height = y2 - y1;
	copie.width = x2 - x1;
	copie.colors = alloc_color(copie.height, copie.width, &copie);

	int sum1, sum2, sum3;

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
			sum1 = sum1 + img->colors[i - 1][j - 1].r * kernel[0][0];
			sum1 = sum1 + img->colors[i - 1][j].r * kernel[0][1];
			sum1 = sum1 + img->colors[i - 1][j + 1].r * kernel[0][2];
			sum1 = sum1 + img->colors[i][j - 1].r * kernel[1][0];
			sum1 = sum1 + img->colors[i][j].r * kernel[1][1];
			sum1 = sum1 + img->colors[i][j + 1].r * kernel[1][2];
			sum1 = sum1 + img->colors[i + 1][j - 1].r * kernel[2][0];
			sum1 = sum1 + img->colors[i + 1][j].r * kernel[2][1];
			sum1 = sum1 + img->colors[i + 1][j + 1].r * kernel[2][2];
			sum2 = sum2 + img->colors[i - 1][j - 1].g * kernel[0][0];
			sum2 = sum2 + img->colors[i - 1][j].g * kernel[0][1];
			sum2 = sum2 + img->colors[i - 1][j + 1].g * kernel[0][2];
			sum2 = sum2 + img->colors[i][j - 1].g * kernel[1][0];
			sum2 = sum2 + img->colors[i][j].g * kernel[1][1];
			sum2 = sum2 + img->colors[i][j + 1].g * kernel[1][2];
			sum2 = sum2 + img->colors[i + 1][j - 1].g * kernel[2][0];
			sum2 = sum2 + img->colors[i + 1][j].g * kernel[2][1];
			sum2 = sum2 + img->colors[i + 1][j + 1].g * kernel[2][2];
			sum3 = sum3 + img->colors[i - 1][j - 1].b * kernel[0][0];
			sum3 = sum3 + img->colors[i - 1][j].b * kernel[0][1];
			sum3 = sum3 + img->colors[i - 1][j + 1].b * kernel[0][2];
			sum3 = sum3 + img->colors[i][j - 1].b * kernel[1][0];
			sum3 = sum3 + img->colors[i][j].b * kernel[1][1];
			sum3 = sum3 + img->colors[i][j + 1].b * kernel[1][2];
			sum3 = sum3 + img->colors[i + 1][j - 1].b * kernel[2][0];
			sum3 = sum3 + img->colors[i + 1][j].b * kernel[2][1];
			sum3 = sum3 + img->colors[i + 1][j + 1].b * kernel[2][2];
			clamp(&sum1);
			clamp(&sum2);
			clamp(&sum3);
			copie.colors[i - y1][j - x1].r = sum1;
			copie.colors[i - y1][j - x1].g = sum2;
			copie.colors[i - y1][j - x1].b = sum3;
		}
	}

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			img->colors[i][j].r = copie.colors[i - y1][j - x1].r;
			img->colors[i][j].g = copie.colors[i - y1][j - x1].g;
			img->colors[i][j].b = copie.colors[i - y1][j - x1].b;
		}
	}

	printf("APPLY SHARPEN done\n");
	free_colors_memory(&copie);
}

void edge(image *img)
{
	int kernel[3][3] = { { -1, -1, -1 },
						 { -1, 8, -1 },
						 { -1, -1, -1 } };

	int x1 = img->selected.x1, x2 = img->selected.x2;
	int y1 = img->selected.y1, y2 = img->selected.y2;
	if (x1 == 0)
		x1++;
	if (x2 == img->width)
		x2--;
	if (y1 == 0)
		y1++;
	if (y2 == img->height)
		y2--;

	image copie;
	copie.height = y2 - y1;
	copie.width = x2 - x1;
	copie.colors = alloc_color(copie.height, copie.width, &copie);

	int sum1, sum2, sum3;

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
			sum1 = sum1 + img->colors[i - 1][j - 1].r * kernel[0][0];
			sum1 = sum1 + img->colors[i - 1][j].r * kernel[0][1];
			sum1 = sum1 + img->colors[i - 1][j + 1].r * kernel[0][2];
			sum1 = sum1 + img->colors[i][j - 1].r * kernel[1][0];
			sum1 = sum1 + img->colors[i][j].r * kernel[1][1];
			sum1 = sum1 + img->colors[i][j + 1].r * kernel[1][2];
			sum1 = sum1 + img->colors[i + 1][j - 1].r * kernel[2][0];
			sum1 = sum1 + img->colors[i + 1][j].r * kernel[2][1];
			sum1 = sum1 + img->colors[i + 1][j + 1].r * kernel[2][2];
			sum2 = sum2 + img->colors[i - 1][j - 1].g * kernel[0][0];
			sum2 = sum2 + img->colors[i - 1][j].g * kernel[0][1];
			sum2 = sum2 + img->colors[i - 1][j + 1].g * kernel[0][2];
			sum2 = sum2 + img->colors[i][j - 1].g * kernel[1][0];
			sum2 = sum2 + img->colors[i][j].g * kernel[1][1];
			sum2 = sum2 + img->colors[i][j + 1].g * kernel[1][2];
			sum2 = sum2 + img->colors[i + 1][j - 1].g * kernel[2][0];
			sum2 = sum2 + img->colors[i + 1][j].g * kernel[2][1];
			sum2 = sum2 + img->colors[i + 1][j + 1].g * kernel[2][2];
			sum3 = sum3 + img->colors[i - 1][j - 1].b * kernel[0][0];
			sum3 = sum3 + img->colors[i - 1][j].b * kernel[0][1];
			sum3 = sum3 + img->colors[i - 1][j + 1].b * kernel[0][2];
			sum3 = sum3 + img->colors[i][j - 1].b * kernel[1][0];
			sum3 = sum3 + img->colors[i][j].b * kernel[1][1];
			sum3 = sum3 + img->colors[i][j + 1].b * kernel[1][2];
			sum3 = sum3 + img->colors[i + 1][j - 1].b * kernel[2][0];
			sum3 = sum3 + img->colors[i + 1][j].b * kernel[2][1];
			sum3 = sum3 + img->colors[i + 1][j + 1].b * kernel[2][2];
			clamp(&sum1);
			clamp(&sum2);
			clamp(&sum3);
			copie.colors[i - y1][j - x1].r = sum1;
			copie.colors[i - y1][j - x1].g = sum2;
			copie.colors[i - y1][j - x1].b = sum3;
		}
	}

	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			img->colors[i][j].r = copie.colors[i - y1][j - x1].r;
			img->colors[i][j].g = copie.colors[i - y1][j - x1].g;
			img->colors[i][j].b = copie.colors[i - y1][j - x1].b;
		}
	}

	printf("APPLY EDGE done\n");

	free_colors_memory(&copie);
}

void apply(image *img, char s[])
{
	if (img->loaded == 0) {
		printf("No image loaded\n");
		return;
	}
	char *p, apply_type[NMAX];
	p = strtok(s, "\n ");

	p = strtok(NULL, "\n ");

	if (!p) {
		printf("Invalid command\n");
		return;
	}
	strcpy(apply_type, p);

	if (img->type == 2 || img->type == 5) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	// aleg filtrul dupa input
	if (strcmp(apply_type, "EDGE") == 0)
		edge(img);
	else if (strcmp(apply_type, "BLUR") == 0)
		blur(img);
	else if (strcmp(apply_type, "SHARPEN") == 0)
		sharpen(img);
	else if (strcmp(apply_type, "GAUSSIAN_BLUR") == 0)
		gaussian_blur(img);
	else
		printf("APPLY parameter invalid\n");
}

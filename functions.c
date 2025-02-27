// Peiu Andreea 324 CA - refacere PCLP1

#include "functions.h"

void do2(image *img, FILE *file)
{
	img->type = 2;
	img->greyscale = alloc_matrix(img->height, img->width, img);
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			fscanf(file, "%d", &img->greyscale[i][j]);
}

void do3(image *img, FILE *file)
{
	img->type = 3;
	img->colors = alloc_color(img->height, img->width, img);
	int r, g, b;
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++) {
			fscanf(file, "%d", &r);
			fscanf(file, "%d", &g);
			fscanf(file, "%d", &b);
			img->colors[i][j].r = r;
			img->colors[i][j].g = g;
			img->colors[i][j].b = b;
		}
}

void do5(image *img, FILE *file)
{
	img->type = 5;
	img->greyscale = alloc_matrix(img->height, img->width, img);
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			fread(&img->greyscale[i][j], sizeof(unsigned char), 1, file);
}

void cast(image *img, unsigned char r, unsigned char g, unsigned char b,
		  int i, int j)
{
	img->colors[i][j].r = (int)r;
	img->colors[i][j].g = (int)g;
	img->colors[i][j].b = (int)b;
}

void do6(image *img, FILE *file)
{
	img->type = 6;
	img->colors = alloc_color(img->height, img->width, img);
	unsigned char r, g, b;
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++) {
			fread(&r, sizeof(unsigned char), 1, file);
			fread(&g, sizeof(unsigned char), 1, file);
			fread(&b, sizeof(unsigned char), 1, file);
			cast(img, r, g, b, i, j);
		}
}

// citesc din fisier si verific daca sunt comentarii
void loading(image *img, char namefile[])
{
	if (img->loaded == 1)
		free_image(img);

	FILE *file = fopen(namefile, "r");
	if (!file) {
		printf("Failed to load %s\n", namefile);
		img->loaded = 0;
		return;
	}

	verify_comments(file);

	if (fscanf(file, "%s", img->magic_word) != 1) {
		printf("Error reading magic word\n");
		fclose(file);
		return;
	}

	verify_comments(file);

	if (fscanf(file, "%d %d", &img->width, &img->height) != 2) {
		printf("Error reading width and height\n");
		fclose(file);
		return;
	}

	verify_comments(file);

	if (fscanf(file, "%d", &img->max_val) != 1) {
		printf("Error reading max value\n");
		fclose(file);
		return;
	}

	verify_comments(file);

	if (strcmp(img->magic_word, "P2") == 0) {
		do2(img, file);
	} else if (strcmp(img->magic_word, "P3") == 0) {
		do3(img, file);
	} else {
		int aux = ftell(file);
		fclose(file);
		file = fopen(namefile, "rb");
		fseek(file, aux + 1, SEEK_SET);

		if (strcmp(img->magic_word, "P5") == 0)
			do5(img, file);
		else if (strcmp(img->magic_word, "P6") == 0)
			do6(img, file);
	}

	img->loaded = 1;
	img->selected_with_function = 0;
	img->selected.x1 = 0;
	img->selected.x2 = img->width;
	img->selected.y1 = 0;
	img->selected.y2 = img->height;

	fclose(file);
	printf("Loaded %s\n", namefile);
}

void crop2(image *img, int l, int c, image *new_image)
{
	// greyscale
	new_image->greyscale = alloc_matrix(l, c, img);
	for (int i = img->selected.y1; i < img->selected.y2; i++)
		for (int j = img->selected.x1; j < img->selected.x2; j++)
			new_image->greyscale[i - img->selected.y1][j - img->selected.x1] =
			img->greyscale[i][j];

	new_image->selected = img->selected;
	free_image(img);
}

void crop3(image *img, int l, int c, image *new_image)
{
	// rgb
	new_image->colors = alloc_color(l, c, img);
	for (int i = img->selected.y1; i < img->selected.y2; i++)
		for (int j = img->selected.x1; j < img->selected.x2; j++) {
			new_image->colors[i - img->selected.y1][j - img->selected.x1].r =
			img->colors[i][j].r;
			new_image->colors[i - img->selected.y1][j - img->selected.x1].g =
			img->colors[i][j].g;
			new_image->colors[i - img->selected.y1][j - img->selected.x1].b =
			img->colors[i][j].b;
		}

	new_image->selected_with_function = img->selected_with_function;
	new_image->selected = img->selected;
	free_image(img);
}

void crop(image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}

	if (img->selected_with_function == 0) {
		printf("Image cropped\n");
		return;
	}

	if (img->width != img->selected.x2 - img->selected.x1 ||
		img->height != img->selected.y2 - img->selected.y1) {

		image *new = (image *)calloc(1, sizeof(image));
		if (!new) {
			printf("Memory allocation failed for new image.\n");
			return;
		}

		strcpy(new->magic_word, img->magic_word);
		new->type = img->type;
		new->max_val = img->max_val;

		int l = img->selected.y2 - img->selected.y1;
		int c = img->selected.x2 - img->selected.x1;

		// dau crop in functie de tipul imaginii
		if (img->type == 2 || img->type == 5)
			crop2(img, l, c, new);
		else if (img->type == 3 || img->type == 6)
			crop3(img, l, c, new);

		new->height = l;
		new->width = c;
		new->loaded = 1;
		*img = *new;

		free(new);
	}

	printf("Image cropped\n");
}

void sel(int x1, int y1, int x2, int y2, image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}

	if (x1 < 0 || x1 > img->width || x2 < 0 || x2 > img->width ||
		y1 < 0 || y1 > img->height || y2 < 0 || y2 > img->height) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (x1 > x2)
		swap(&x1, &x2);
	if (y1 > y2)
		swap(&y1, &y2);

	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
	img->selected.x1 = x1;
	img->selected.y1 = y1;
	img->selected.x2 = x2;
	img->selected.y2 = y2;
	img->selected_with_function = 1;
}

int verify_number(char *p)
{
	int i = 0;
	if (p[i] == '-')
		i++;
	for (; p[i] != '\0'; i++) {
		if (!isdigit(p[i]))
			return 0; // No
	}
	if (p[0] == '\0')
		return 0;
	return 1; // yes
}

// fiecare coordonata este transformata in numar
void parse_assign_coord(char *s, int *x1, int *y1, int *x2,
						int *y2, image *img)
{
	char *p;
	p = strtok(s, "\n "); // select
	p = strtok(NULL, "\n ");
	if (p) {
		if (verify_number(p)) {
			*x1 = atoi(p);
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, "\n ");
	if (p) {
		if (verify_number(p)) {
			*y1 = atoi(p);
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("Invalid command\n");
		return;
	}

	p = strtok(NULL, "\n ");
	if (p) {
		if (verify_number(p)) {
			*x2 = atoi(p);
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("Invalid command\n");
		return;
	}

	p = strtok(NULL, "\n ");
	if (p) {
		if (verify_number(p)) {
			*y2 = atoi(p);
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("Invalid command\n");
		return;
	}
	sel(*x1, *y1, *x2, *y2, img);
}

void select_all(image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}
	img->selected.x1 = 0;
	img->selected.y1 = 0;
	img->selected.x2 = img->width;
	img->selected.y2 = img->height;
	printf("Selected ALL\n");
	img->selected_with_function = 0;
}

// scriu in fisierul ascii
void save_ascii(const char *name_file, image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}
	FILE *file = fopen(name_file, "w");
	if (!file) {
		printf("FAILED %s\n", name_file);
		return;
	}
	img->saved = 0;
	if (img->type == 2 || img->type == 5) {
		fprintf(file, "P2\n");
		fprintf(file, "%d %d\n", img->width, img->height);
		fprintf(file, "%d\n", img->max_val);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++)
				fprintf(file, "%d ", img->greyscale[i][j]);
			fprintf(file, "\n");
		}
		printf("Saved %s\n", name_file);
		img->saved = 1;
		fclose(file);
		return;
	} else if (img->type == 3 || img->type == 6) {
		fprintf(file, "P3\n");
		fprintf(file, "%d %d\n", img->width, img->height);
		fprintf(file, "%d\n", img->max_val);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				fprintf(file, "%d ", img->colors[i][j].r);
				fprintf(file, "%d ", img->colors[i][j].g);
				fprintf(file, "%d ", img->colors[i][j].b);
			}
			fprintf(file, "\n");
		}
		printf("Saved %s\n", name_file);
		img->saved = 1;
		fclose(file);
		return;
	}
	fclose(file);
	if (img->saved == 0) {
		printf("Failed to save %s\n", name_file);
		return;
	}
}

// scriu in fisierul binar
void save_binary(const char *name_file, image *img)
{
	if (img->loaded != 1) {
		printf("No image loaded\n");
		return;
	}
	FILE *file = fopen(name_file, "wb");
	if (!file) {
		printf("FAILED %s\n", name_file);
		return;
	}

	img->saved = 0;
	if (img->type == 5 || img->type == 2) {
		fprintf(file, "P5\n");
		fprintf(file, "%d %d\n", img->width, img->height);
		fprintf(file, "%d\n", img->max_val);
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++) {
				unsigned char a = (unsigned char)img->greyscale[i][j];
				fwrite(&a, sizeof(unsigned char), 1, file);
			}
		printf("Saved %s\n", name_file);
		img->saved = 1;
		fclose(file);
		return;
	} else if (img->type == 6 || img->type == 3) {
		fprintf(file, "P6\n");
		fprintf(file, "%d %d\n", img->width, img->height);
		fprintf(file, "%d\n", img->max_val);
		unsigned char r, g, b;
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++) {
				r = (unsigned char)img->colors[i][j].r;
				g = (unsigned char)img->colors[i][j].g;
				b = (unsigned char)img->colors[i][j].b;
				fwrite(&r, sizeof(unsigned char), 1, file);
				fwrite(&g, sizeof(unsigned char), 1, file);
				fwrite(&b, sizeof(unsigned char), 1, file);
			}
		printf("Saved %s\n", name_file);
		img->saved = 1;
		fclose(file);
		return;
	}
	fclose(file);
	if (img->saved == 0) {
		printf("Failed to save %s\n", name_file);
		return;
	}
}

void verify_power(int y)
{
	int nr = 1, copie_y = y;
	while (y != 1) {
		nr = nr * 2;
		y = y / 2;
	}
	if (nr != copie_y)
		printf("Invalid number of bins\n");
}

double *frequency(image img, int y)
{
	double *freq = (double *)malloc(y * sizeof(double));
	if (!freq)
		return NULL;

	int len = 256 / y;
	for (int i = 0; i < y; i++)
		freq[i] = 0;

	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			for (int k = 0; k < y; k++) {
				// incadrez valoarea intr-un interval
				if (len * k <= img.greyscale[i][j] && img.greyscale[i][j]
					< len * (k + 1))
					freq[k]++;
			}
		}
	}

	return freq;
}

void histogram(image *img, char s[])
{
	int x = 0, y = 0;

	if (img->loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	char *p;
	p = strtok(s, "\n ");

	p = strtok(NULL, "\n ");

	if (!p) {
		printf("Invalid command\n");
		return;
	}

	if (img->type == 3 || img->type == 6) {
		printf("Black and white image needed\n");
		return;
	}

	if (p) {
		x = atoi(p); // number of stars
	} else {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, "\n ");
	if (p) {
		y = atoi(p); // number of bins
	} else {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, "\n ");
	if (p) {
		printf("Invalid command\n");
		return;
	}

	verify_power(y);
	double *frecv = frequency(*img, y);

	int max = frecv[0];

	for (int i = 0; i < 256; i++)
		if (frecv[i] > max)
			max = frecv[i];

	int stele;
	for (int i = 0; i < y; i++) {
		stele = (int)(((double)frecv[i] / max) * x);
		printf("%d\t|\t", stele);
		for (int j = 0; j < stele; j++)
			printf("*");
		printf("\n");
	}

	free(frecv);
}

void equalize(image *img)
{
	if (img->loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	if (img->type == 3 || img->type == 6) {
		printf("Black and white image needed\n");
		return;
	}
	int *frecv = (int *)calloc(256, sizeof(int));
	if (!frecv)
		return;

	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			frecv[img->greyscale[i][j]]++;

	int *sum = (int *)calloc(256, sizeof(int));
	if (!sum)
		return;
	sum[0] = frecv[0];
	for (int i = 1; i < 256; i++)
		sum[i] = sum[i - 1] + frecv[i];
	int area = img->height * img->width;
	int index;
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++) {
			index = img->greyscale[i][j];
			img->greyscale[i][j] = floor(sum[index] * 255 / area);
		}
	printf("Equalize done\n");
	free(frecv);
	free(sum);
}

void clamp(int *x)
{
	if (*x < 0)
		*x = 0;
	if (*x > 255)
		*x = 255;
}

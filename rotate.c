// Peiu Andreea 324 CA
#include "rotate.h"

void rotate_non_square_90_grey(image *img)
{
	if (!img || !img->greyscale) {
		printf("Invalid image or greyscale matrix is NULL.\n");
		return;
	}

	if (img->width <= 0 || img->height <= 0) {
		printf("Invalid image dimensions.\n");
		return;
	}

	// matrice temporara pentru transpunere
	int **tmp = alloc_matrix(img->width, img->height, img);
	if (!tmp) {
		printf("Memory allocation failed for temporary matrix.\n");
		return;
	}

	// transpun matricea
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			tmp[j][i] = img->greyscale[i][j];
		}
	}

	// inversez elementele pentru fiecare coloana a matricei transpuse
	for (int j = 0; j < img->width; j++) {
		for (int i = 0; i < img->height / 2; i++) {
			int aux = tmp[j][i];
			tmp[j][i] = tmp[j][img->height - i - 1];
			tmp[j][img->height - i - 1] = aux;
		}
	}

	free_matrix(img->greyscale, img->height);

	img->greyscale = tmp;

	// actualizez dimensiunile
	int old_width = img->width;
	img->width = img->height;
	img->height = old_width;

	img->selected.x1 = 0;
	img->selected.y1 = 0;
	img->selected.x2 = img->width;
	img->selected.y2 = img->height;
	img->selected_with_function = 0;

}

void rotate_non_square_90_color(image *img)
{
	if (!img || !img->colors) {
		printf("Invalid image.\n");
		return;
	}

	if (img->width <= 0 || img->height <= 0) {
		printf("Invalid image dimensions.\n");
		return;
	}

	// matrice temporara pentru transpunere
	color_rgb * *tmp = alloc_color(img->width, img->height, img);
	if (!tmp) {
		printf("Memory allocation failed for temporary matrix.\n");
		return;
	}

	// transpun matricea
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			tmp[j][i] = img->colors[i][j];
		}
	}

	// inversez elementele pentru fiecare coloana a matricei transpuse
	for (int j = 0; j < img->width; j++) {
		for (int i = 0; i < img->height / 2; i++) {
			color_rgb aux = tmp[j][i];
			tmp[j][i] = tmp[j][img->height - i - 1];
			tmp[j][img->height - i - 1] = aux;
		}
	}
	free_colors_memory(img);

	img->colors = tmp;

	// actualizez dimensiunile si select all
	int old_width = img->width;
	img->width = img->height;
	img->height = old_width;

	img->selected.x1 = 0;
	img->selected.y1 = 0;
	img->selected.x2 = img->width;
	img->selected.y2 = img->height;
	img->selected_with_function = 0;

}

void rotate_90_grey(image *img)
{
	if (!img || !img->greyscale) {
		printf("Invalid image or greyscale matrix is NULL.\n");
		return;
	}

	int x1 = img->selected.x1;
	int y1 = img->selected.y1;
	int x2 = img->selected.x2;
	int y2 = img->selected.y2;

	if (x1 < 0 || y1 < 0 || x2 > img->width || y2 > img->height) {
		return;
	}

	int sel_width = x2 - x1;

	// dimensiunea selectiei
	int size = sel_width;

	// matrice temporara pentru selectie
	int **tmp = alloc_matrix(size, size, img);
	if (!tmp) {
		printf("Memory allocation failed for temporary matrix.\n");
		return;
	}

	// copiez selectia transpusa in matricea temporara
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp[j][i] = img->greyscale[y1 + i][x1 + j];
		}
	}

	// inversez elementele pentru fiecare coloana a matricei transpuse
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size / 2; j++) {
			int aux = tmp[i][j];
			tmp[i][j] = tmp[i][size - j - 1];
			tmp[i][size - j - 1] = aux;
		}
	}

	// copiez matricea rotita inapoi in cea originala
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			img->greyscale[y1 + i][x1 + j] = tmp[i][j];
		}
	}

	free_matrix(tmp, size);
}

void rotate_90_color(image *img)
{
	if (!img || !img->colors) {
		printf("Invalid image.\n");
		return;
	}

	int x1 = img->selected.x1;
	int y1 = img->selected.y1;
	int x2 = img->selected.x2;
	int y2 = img->selected.y2;

	if (x1 < 0 || y1 < 0 || x2 > img->width || y2 > img->height)
		return;

	int sel_width = x2 - x1;

	// dimensiunea selectiei
	int size = sel_width;

	// matrice temporara pentru selectie
	color_rgb **tmp = alloc_color(size, size, img);
	if (!tmp) {
		printf("Memory allocation failed for temporary matrix.\n");
		return;
	}

	// copiez selectia transpusa in matricea temporara
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp[j][i] = img->colors[y1 + i][x1 + j];
		}
	}

	// inversez elementele pentru fiecare coloana a matricei transpuse
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size / 2; j++) {
			color_rgb aux = tmp[i][j];
			tmp[i][j] = tmp[i][size - j - 1];
			tmp[i][size - j - 1] = aux;
		}
	}

	// copiez matricea rotita inapoi in cea originala
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			img->colors[y1 + i][x1 + j] = tmp[i][j];
		}
	}

	free_rgb_matrix(tmp, size);

}

// helper pentru a extrage unghiul de rotatie
char *parse_rotation_command(char s[])
{
	char *p = strtok(s, "\n ");
	p = strtok(NULL, "\n ");
	return p;
}

// helper pentru rotirea la "-90" si "270"
void handle_rotation_minus_90(image *img, int is_square)
{
	if (img->type == 2 || img->type == 5) {
		if (is_square) {
			rotate_90_grey(img);
			rotate_90_grey(img);
			rotate_90_grey(img);
		} else {
			rotate_non_square_90_grey(img);
			rotate_non_square_90_grey(img);
			rotate_non_square_90_grey(img);
		}
	} else {
		if (is_square) {
			rotate_90_color(img);
			rotate_90_color(img);
			rotate_90_color(img);
		} else {
			rotate_non_square_90_color(img);
			rotate_non_square_90_color(img);
			rotate_non_square_90_color(img);
		}
	}
}

// helper pentru rotirea la "180" si "-180"
void handle_rotation_180(image *img, int is_square)
{
	if (img->type == 2 || img->type == 5) {
		if (is_square) {
			rotate_90_grey(img);
			rotate_90_grey(img);
		} else {
			rotate_non_square_90_grey(img);
			rotate_non_square_90_grey(img);
		}
	} else {
		if (is_square) {
			rotate_90_color(img);
			rotate_90_color(img);
		} else {
			rotate_non_square_90_color(img);
			rotate_non_square_90_color(img);
		}
	}
}

// helper pentru rotirea la "90" si "-270"
void handle_rotation_90(image *img, int is_square)
{
	if (img->type == 2 || img->type == 5) {
		if (is_square) {
			rotate_90_grey(img);
		} else {
			rotate_non_square_90_grey(img);
		}
	} else {
		if (is_square) {
			rotate_90_color(img);
		} else {
			rotate_non_square_90_color(img);
		}
	}
}

// functia principala de rotire
void rotate(image *img, char s[])
{
	if (img->loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	int x1 = img->selected.x1, x2 = img->selected.x2;
	int y1 = img->selected.y1, y2 = img->selected.y2;
	int c = x2 - x1;
	int l = y2 - y1;

	int is_square = (l == c || (x1 == 0 && y1 == 0 &&
					 x2 == img->width && y2 == img->height));
	if (!is_square) {
		printf("The selection must be square\n");
		return;
	}

	char *p = parse_rotation_command(s);
	if (!p) {
		printf("Invalid command\n");
		return;
	}

	if (strcmp(p, "0") == 0 || strcmp(p, "360") == 0 ||
		strcmp(p, "-360") == 0) {
		printf("Rotated %s\n", p);
		return;
	}

	if (strcmp(p, "-90") == 0 || strcmp(p, "270") == 0) {
		handle_rotation_minus_90(img, l == c);
		printf("Rotated %s\n", p);
		return;
	}

	if (strcmp(p, "180") == 0 || strcmp(p, "-180") == 0) {
		handle_rotation_180(img, l == c);
		printf("Rotated %s\n", p);
		return;
	}

	if (strcmp(p, "90") == 0 || strcmp(p, "-270") == 0) {
		handle_rotation_90(img, l == c);
		printf("Rotated %s\n", p);
		return;
	}

	printf("Unsupported rotation angle\n");
}

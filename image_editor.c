// Peiu Andreea 324 CA - refacere PCLP1

#include "image_utils.h"
#include "rotate.h"
#include "functions.h"

int main(void)
{
	char comanda[NMAX], name_file[NMAX], copy_command[NMAX];
	int ok = 1, check_function, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	image *img = (image *)calloc(1, sizeof(image));
	if (!img)
		return 1;

	img->loaded = 0; img->selected_with_function = 0;
	while (ok) {
		fgets(comanda, NMAX, stdin);
		strcpy(copy_command, comanda);
		check_function = 0;
		char *p = strtok(comanda, "\n ");

		if (strcmp(p, "LOAD") == 0) {
			p = strtok(NULL, "\n ");
			strcpy(name_file, p);
			loading(img, name_file);
			check_function = 1;
		}

		if (strcmp(p, "SELECT") == 0) {
			p = strtok(NULL, "\n ");
			if (strcmp(p, "ALL") == 0) {
				select_all(img);
				check_function = 1;
			} else {
				parse_assign_coord(copy_command, &x1, &y1, &x2, &y2, img);
				check_function = 1;
			}
		}
		if (strstr(comanda, "CROP")) {
			crop(img);
			check_function = 1;
		}

		if (strstr(copy_command, "ascii")) {
			p = strtok(NULL, "\n ");
			strcpy(name_file, p);
			save_ascii(name_file, img);
			check_function = 1;
		} else if (strstr(comanda, "SAVE")) {
			p = strtok(NULL, "\n ");
			strcpy(name_file, p);
			save_binary(name_file, img);
			check_function = 1;
		}

		if (strstr(comanda, "HISTOGRAM")) {
			histogram(img, copy_command);
			check_function = 1;
		}

		if (strstr(comanda, "EQUALIZE")) {
			equalize(img);
			check_function = 1;
		}

		if (strstr(comanda, "ROTATE")) {
			rotate(img, copy_command);
			check_function = 1;
		}

		if (strstr(copy_command, "APPLY")) {
			apply(img, copy_command);
			check_function = 1;
		}

		if (strcmp(p, "EXIT") == 0) {
			exit_program(img);
			ok = 0;
			check_function = 1;
		}

		if (check_function == 0)
			printf("Invalid command\n");
	}

	free(img);
	return 0;
}

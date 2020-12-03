/*
 * uwu -- uwunator extension for cat
 * Copyright (C) 2020  Jacob Koziej <jacobkoziej@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAT_PATH "cat"


int main(int argc, char **argv)
{
	// obtain cat command
	int cat_bufsiz = strlen(CAT_PATH) + 1;

	for (int i = 1; i < argc; i++)
		cat_bufsiz += strlen(argv[i]) + 1;

	char *cat_cmd = malloc(sizeof(char) * cat_bufsiz);

	if (cat_cmd == NULL) {
		fprintf(stderr, "Memory allocation for cat command failed.\n");
		exit(EXIT_FAILURE);
	}

	strncpy(cat_cmd, CAT_PATH, sizeof(char) * cat_bufsiz - 1);

	for (int i = 1; i < argc; i++) {
		strcat(cat_cmd, " ");
		strcat(cat_cmd, argv[i]);
	}

	free(cat_cmd);


	exit(EXIT_SUCCESS);
}

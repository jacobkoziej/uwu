/*
 * uwuconf.c -- uwu config parsing
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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uwuconf.h"


/* generate cat command to run */
char **gen_cat_cmd(int argc, char *cat_path, char **argv)
{
	char **cat_cmd = malloc(sizeof(char*) * argc + 1);
	if (cat_cmd == NULL) {
		fprintf(stderr, "Error: Memory allocation for cat command failed\n");
		exit(EXIT_FAILURE);
	}

	cat_cmd[0] = strdup(CAT_PATH);
	for (int i = 1; i < argc; i++)
		cat_cmd[i] = strdup(argv[i]);
	cat_cmd[argc] = NULL;

	for (int i = 0; i < argc; i++) {
		if (cat_cmd[i] == NULL) {
			fprintf(stderr, "Error: Memory allocation for cat arguments failed\n");
			exit(EXIT_FAILURE);
		}
	}

	return cat_cmd;
}

/* load arguments */
void load_args(int argc, char **argv, struct config *conf)
{
	struct option long_options[] = {
		{"config-file", required_argument, NULL, 'c'},
		{       "help",       no_argument, NULL, 'h'},
		{    "version",       no_argument, NULL, 'i'},
		{"buffer-size", required_argument, NULL, 'B'},
		{0, 0, 0, 0}
	};

	int opt = 0;
	int siz = -1;

	while ((opt = getopt_long(argc, argv, PROG_ARGS,
		long_options, NULL)) != -1) {

		switch (opt) {
			// config path override
			case 'c':
				exit(EXIT_SUCCESS);

			// help
			case 'h':
				exit(EXIT_SUCCESS);

			// version info
			case 'i':
				exit(EXIT_SUCCESS);

			// buffer size
			case 'B':
				// only set buffer size if not unbuffered
				if (siz) siz = atoi(optarg);

				if (0 > siz) {
					fprintf(stderr, "Invalid buffer size: %d\n", siz);
					exit (EXIT_FAILURE);
				}

				conf->bufsiz = siz;
				break;
		}
	}
}

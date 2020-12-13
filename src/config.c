/*
 * config.c -- configuration of the uwu program
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

#include "config.h"
#include "error.h"


/* append cat arguments, return new argument count or -1 on failure */
int add_cat_arg(char ***cat_cmd, char *arg)
{
	// check if input is NULL
	if (!cat_cmd) return -1;

	// allocate memory if *cat_cmd is NULL
	if (!*cat_cmd) {
		*cat_cmd = malloc(sizeof(char**));
		if (!*cat_cmd) return -1;
	}

	char **temp = *cat_cmd;


	// get size of input array
	int cnt = 0;
	while (temp[cnt])
		++cnt;
	++cnt;

	temp = reallocarray(temp, sizeof(char**), cnt + 1);
	if (!temp) return -1;

	// set previous end to arg
	temp[cnt - 1] = strdup(arg);

	// manage failures
	if(!temp[cnt - 1]) {
		char **failed = temp;

		do {
			temp = failed;
			temp = reallocarray(temp, sizeof(char**), cnt);
		} while (!temp);

		*cat_cmd = temp;

		return -1;
	}

	// set new end to NULL
	temp[cnt] = NULL;
	*cat_cmd = temp;


	return cnt + 1;
}

/* load arguments */
void load_args(int argc, char **argv, struct config *conf)
{
	struct option long_options[] = {
		/* cat-specific */
		{"number-nonblank",  no_argument, NULL, 'b'},
		{"number",           no_argument, NULL, 'n'},
		{"squeeze-blank",    no_argument, NULL, 's'},
		{"show-nonprinting", no_argument, NULL, 'v'},
		{"show-ends",        no_argument, NULL, 'E'},
		{"show-tabs",        no_argument, NULL, 'T'},
		{"show-all",         no_argument, NULL, 'A'},
		/* cat-specific */

		{"config-file", required_argument, NULL, 'c'},
		{       "help",       no_argument, NULL, 'h'},
		{    "version",       no_argument, NULL, 'i'},
		{   "uwu-list", required_argument, NULL, 'l'},
		{"buffer-size", required_argument, NULL, 'B'},
		{0, 0, 0, 0}
	};

	int cnt = 0;
	int opt = 0;
	int siz = -1;

	cnt = add_cat_arg(&conf->cat_cmd, CAT_PATH);

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

			// uwu list override
			case 'l':
				break;

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

			// exit on invalid option
			case '?':
				exit(EXIT_FAILURE);

			// get cat arguments (flags)
			default:
				cnt = add_cat_arg(&conf->cat_cmd,
					argv[optind - 1]);

				if (cnt == -1)
					die("Failed to generate cat arguments");

				break;
		}
	}

	// get remaining cat arguments (files)
	while (optind < argc)
		cnt = add_cat_arg(&conf->cat_cmd, argv[optind++]);
}

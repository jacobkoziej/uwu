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
#include <stdlib.h>

#include "uwuconf.h"


/* load arguments */
void load_args(int argc, char **argv)
{
	struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};

	int opt = 0;

	while ((opt = getopt_long(argc, argv, PROG_ARGS,
		long_options, NULL)) != -1) {

		switch (opt) {
			// help
			case 'h':
				exit(EXIT_SUCCESS);
		}
	}
}

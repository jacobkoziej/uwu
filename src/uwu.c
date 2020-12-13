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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "uwu.h"
#include "config.h"


int main(int argc, char **argv)
{
	struct config conf = {
		BUFSIZ,
		NULL,
		NULL
	};

	load_args(argc, argv, &conf);


	/* open pipes to cat */
	int cat[NUM_CAT_PIPES][2];

	for (int i = 0; i < NUM_CAT_PIPES; i++)
		if (pipe(cat[i]) == -1) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}


	/* create pipes between cat & uwu */
	int cat_pid = fork();

	switch (cat_pid) {
		// error
		case -1:
			fprintf(stderr, "Error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);

		// child
		case 0:
			// redirect stdin/stdout/sdterr to cat pipes
			dup2(cat[CAT_STDIN_FD][PIPE_R], STDIN_FILENO);
			dup2(cat[CAT_STDOUT_FD][PIPE_W], STDOUT_FILENO);
			dup2(cat[CAT_STDERR_FD][PIPE_W], STDERR_FILENO);

			// close unused ends of pipes
			for (int i = 0; i < NUM_CAT_PIPES; i++) {
				close(cat[i][PIPE_R]);
				close(cat[i][PIPE_W]);
			}

			execvp(conf.cat_cmd[0], conf.cat_cmd);

			fprintf(stderr, "Error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);

		// parent
		default:
			// close unused ends of pipes
			close(cat[CAT_STDIN_FD][PIPE_R]);
			close(cat[CAT_STDOUT_FD][PIPE_W]);
			close(cat[CAT_STDERR_FD][PIPE_W]);

			break;
	}


	exit(EXIT_SUCCESS);
}

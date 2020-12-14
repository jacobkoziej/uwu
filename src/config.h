/*
 * config.h -- common header for config.h
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

#ifndef CONFIG_H
#define CONFIG_H

#include "uwunate.h"


#define CAT_PATH "cat"

#define PROG_ARGS "bc:ehil:nstuvAB:ET"


// runtime configuration
struct config {
	int bufsiz;
	char *file;
	char *uwu_list_path;
	char **cat_cmd;
};

/* prototype */
int add_cat_arg(char***, char*);
void load_args(int, char**, struct config*);
int parse_uwu_list(char*, uwus_t*);


#endif  /* CONFIG_H */

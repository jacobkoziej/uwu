/*
 * uwuconf.h -- common header for uwuconf.c
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

#ifndef UWUCONF_H
#define UWUCONF_H

#define CAT_PATH "cat"

#define PROG_ARGS "behnstuvAET"


// runtime configuration
struct config {
	int bufsiz;
	char *file;
};

/* prototype */
char **gen_cat_cmd(int, char*, char**);
void load_args(int, char**);


#endif  /* UWUCONF_H */

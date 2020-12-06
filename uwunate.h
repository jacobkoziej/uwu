/*
 * uwunate.h -- definition of uwunation structures and supporting types
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

#ifndef UWUNATE_H
#define UWUNATE_H

// node for uwu strings
typedef struct uwus_t {
	char *org;
	char *uwu;
	struct uwus_t *n;
} uwus_t;


/* prototype */
int cnt_uwus(uwus_t*);
void del_uwu(uwus_t*);
char ***gen_uwus_arr(uwus_t*);
void insrt_uwu(uwus_t**, uwus_t*);
uwus_t *new_uwu(char*, char*);
void purge_uwus(uwus_t**);


#endif  /* UWUNATE_H */

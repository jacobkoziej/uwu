/*
 * uwunate.c -- uwunation support
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

#include <stdlib.h>
#include <string.h>

#include "uwunate.h"


// create a new uwus_t node, on failure return NULL
uwus_t *new_uwu(char *org, char *uwu)
{
	uwus_t *new = malloc(sizeof(uwus_t));
	if (new == NULL) return NULL;

	new->org = strdup(org);
	new->uwu = strdup(uwu);
	new->n   = NULL;

	if (new->org == NULL || new->uwu == NULL) goto error;

	return new;

error:
	if (new->uwu != NULL) free(new->uwu);
	if (new->org != NULL) free(new->org);
	free(new);

	return NULL;
}

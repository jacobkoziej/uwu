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

/* return number of uwus_t nodes from entry */
int cnt_uwus(uwus_t *head)
{
	int cnt = 0;

	while (head) {
		++cnt;
		head = head->n;
	}

	return cnt;
}

/* delete an uwus_t node */
void del_uwu(uwus_t *del)
{
	free(del->uwu);
	free(del->org);
	free(del);
}

/* insert an uwus_t node in the correct alphabetical position */
void insrt_uwu(uwus_t **head, uwus_t *new)
{
	uwus_t **tracer = head;

	while((*tracer) && strcmp((*tracer)->org, new->org) < 1)
		tracer = &(*tracer)->n;

	new->n = *tracer;
	*tracer = new;
}

/* create a new uwus_t node, on failure return NULL */
uwus_t *new_uwu(char *org, char *uwu)
{
	uwus_t *new = malloc(sizeof(uwus_t));
	if (new == NULL) return NULL;

	new->org = strdup(org);
	new->uwu = strdup(uwu);
	new->n   = NULL;

	if (new->org == NULL || new->uwu == NULL) {
		del_uwu(new);
		return NULL;
	}

	return new;
}

/* purge all uwus_t nodes */
void purge_uwus(uwus_t **head)
{
	while (*head) {
		uwus_t *curr = *head;
		*head = (*head)->n;
		del_uwu(curr);
	}
}

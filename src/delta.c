/*
 * Blame - An RCS file annotator
 * Copyright (C) 2004  Michael Chapman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <system.h>

#include <delta.h>
#include <hash.h>

/*
 * Returns a deep duplicate of <delta>.
 */
delta_t *
delta_dup(const delta_t *delta) {
	delta_t *result;
	
	assert(delta);
	
	result = MALLOC(1, delta_t);
	result->template = delta->template;
	result->revision = delta->revision;
	
	if (!delta->template) {
		result->date = delta->date;
		result->author = delta->author;
		result->state = delta->state;
		
		result->branches = (delta->branches ? hash_dup(delta->branches) : NULL);
		
		result->log = delta->log;
		result->text = (delta->text ? lines_dup(delta->text, delta->text->capacity) : NULL);

		result->next = (delta->next ? delta_ref_dup(delta->next) : NULL);
	}
	
	return result;
}

/*
 * Deeply free <delta>.
 */
void
delta_free(delta_t *delta) {
	assert(delta);
	assert(delta->revision);

	if (!delta->template) {
		if (delta->branches) hash_free(delta->branches);
		if (delta->text) lines_free(delta->text);
		if (delta->next) delta_ref_free(delta->next);
	}
	
	FREE(delta);
}

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "unarchive.h"
#include "libbb.h"

extern void seek_sub_file(const int src_fd, const unsigned int amount)
{
	if ((lseek(src_fd, amount, SEEK_CUR) == -1) && (errno == ESPIPE)) {
		unsigned int i;
		for (i = 0; i < amount; i++) {
			xread_char(src_fd);
		}
	}
}

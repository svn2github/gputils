/* Symbol table support

   Copyright (C) 2016 Molnar Karoly

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef __GPHASH_H__
#define __GPHASH_H__

extern void gp_hash_init(hash128_t *Hash);

extern void gp_hash_mem(hash128_t *Hash, const void *Array, size_t Length);

extern void gp_hash_str_len(hash128_t *Hash, const char *String, size_t Length, gp_boolean Case_insensitive);

extern void gp_hash_str(hash128_t *Hash, const char *String, gp_boolean Case_insensitive);

#endif /* __GPHASH_H__ */

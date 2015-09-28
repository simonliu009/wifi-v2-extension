/* bricklib
 * Copyright (C) 2010 Olaf Lüke <olaf@tinkerforge.com>
 *
 * pearson_hash.h: Implementation of fast Pearson Hash
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef PEARSON_HASH_H
#define PEARSON_HASH_H

#include <stdint.h>

#define PEARSON_PERMUTATION_SIZE 256

extern const uint8_t pearson_permutation[PEARSON_PERMUTATION_SIZE];

#define PEARSON(cur, next) do{ cur = pearson_permutation[(cur) ^ (next)]; }while(0)

#endif

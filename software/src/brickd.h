/* master-brick
 * Copyright (C) 2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * wifi_brickd.h: Simplistic reimplementation of brickd for WIFI Extension
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

#ifndef BRICKD_H
#define BRICKD_H

#include <stdint.h>
#include <stdbool.h>

#include "espmissingincludes.h"

#define BRICKD_ROUTING_TABLE_SIZE 10

typedef struct BrickdRouting BrickdRouting;

typedef enum {
	BRICKD_AUTHENTICATION_STATE_DISABLED = 0,
	BRICKD_AUTHENTICATION_STATE_ENABLED,
	BRICKD_AUTHENTICATION_STATE_NONCE_SEND,
	BRICKD_AUTHENTICATION_STATE_DONE
} BrickdAuthenticationState;

struct BrickdRouting {
	uint32_t uid;
	uint32_t counter;
	uint8_t func_id;
	uint8_t sequence_number;
	int8_t cid;
	uint8_t tmp;
};

#define BRICKD_FID_GET_AUTHENTICATION_NONCE 1
#define BRICKD_FID_AUTHENTICATE 2

#define MESSAGE_HEADER_LENGTH_POSITION 4

typedef struct {
	uint32_t uid;
	uint8_t length;
	uint8_t fid;
	uint8_t other_options:2,
	        authentication:1,
	        return_expected:1,
			sequence_num:4;
	uint8_t future_use:6,
	        error:2;
} __attribute__((__packed__)) MessageHeader;

typedef struct {
	MessageHeader header;
} __attribute__((packed)) GetAuthenticationNonce;

typedef struct {
	MessageHeader header;
	uint8_t server_nonce[4];
} __attribute__((packed)) GetAuthenticationNonceReturn;

typedef struct {
	MessageHeader header;
	uint8_t client_nonce[4];
	uint8_t digest[20];
} __attribute__((packed)) Authenticate;

/*void brickd_get_authentication_nonce(const ComType com, const GetAuthenticationNonce *data);
void brickd_authenticate(const ComType com, const Authenticate *data);
void brickd_set_authentication_seed(const uint32_t seed);
void brickd_enable_authentication(void);
void brickd_disable_authentication(void);
bool brickd_check_auth(const MessageHeader *header, const int8_t cid);*/

void ICACHE_FLASH_ATTR brickd_init(void);
uint32_t ICACHE_FLASH_ATTR brickd_counter_diff(const uint32_t new, const uint32_t old);
void ICACHE_FLASH_ATTR brickd_route_from(const void *data, const uint8_t cid);
int8_t ICACHE_FLASH_ATTR brickd_route_to_peak(const void *data, BrickdRouting **match);
int8_t ICACHE_FLASH_ATTR brickd_route_to(const void *data);
void ICACHE_FLASH_ATTR brickd_disconnect(const uint8_t cid);
void ICACHE_FLASH_ATTR brickd_print_routing_table(void);

#endif

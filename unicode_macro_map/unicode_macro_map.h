// Copyright 2025 Stephen Ostermiller
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include "progmem.h"

extern const char* unicode_macro_map[];

/**
 * \brief Send the unicode string for the given index in the `unicode_macro_map` array.
 *
 * \param index The index into the `unicode_macro_map` array.
 */
void unicode_macro_map_send_string(uint8_t index);

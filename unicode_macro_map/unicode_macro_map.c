/* Copyright 2025 Stephen Ostermiller <https://ostermiller.org/contact.pl?regarding=qmk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "unicode.h"
#include "unicode_macro_map.h"
#include "unicodemap.h"
#include "send_mixed_string.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

// This is built on top of unicode map which requires
// this array to be defined. Declare it here, but
// it will never be used.
const uint32_t PROGMEM unicode_map[] = {};

void unicode_macro_map_send_string(uint8_t index) {
    send_mixed_string_P((const char*)pgm_read_word(&unicode_macro_map[index]));
}

bool process_record_unicode_macro_map(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= QK_UNICODEMAP && keycode <= QK_UNICODEMAP_PAIR_MAX) {
        if (record->event.pressed) {
            unicode_macro_map_send_string(unicodemap_index(keycode));
        }
        return false;
    }

    return true;
}

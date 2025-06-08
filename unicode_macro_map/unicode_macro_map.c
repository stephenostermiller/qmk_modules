// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "unicode.h"
#include "unicode_macro_map.h"
#include "unicodemap.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

const uint32_t PROGMEM unicode_map[] = {};

void unicode_macro_map_send_string(uint8_t index) {
    clear_mods();
    clear_weak_mods();
    send_keyboard_report();
    send_unicode_string(unicode_macro_map[index]);
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

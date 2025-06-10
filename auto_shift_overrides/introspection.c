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

// Walk though the key overrides to see if the shift key has
// been overridden for this key.  If so, return the override.
uint16_t get_shift_replacement(uint16_t keycode) {
    for(int i=0; i<sizeof(key_overrides)/sizeof(key_overrides[0]); i++){
        if(key_overrides[i]->trigger == keycode && key_overrides[i]->suppressed_mods == MOD_MASK_SHIFT) {
            return key_overrides[i]->replacement;
        }
    }
    return 0;
}

// handle auto shift presses
void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    if (shifted) {
        uint16_t replacement = get_shift_replacement(keycode);
        if (replacement){
            // found a key override, use the replacement for auto shift
            process_keycode_any(replacement, true);
            return;
        }
        // for regular keys, shift modifier needs to be active to get shifted behavior
        add_weak_mods(MOD_BIT(KC_LSFT));
    }
    // no override found or shift not held, use normal key code
    register_code16(keycode);
}

// handle auto shift releases
void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    if (shifted) {
        uint16_t replacement = get_shift_replacement(keycode);
        if (replacement){
            // found a key override, use the replacement for auto shift
            process_keycode_any(replacement, false);
            return;
        }
    }
    // no override found or shift not held, use normal key code
    unregister_code16(keycode);
}


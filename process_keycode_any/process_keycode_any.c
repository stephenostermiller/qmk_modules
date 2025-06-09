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

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

#include "process_keycode_any.h"

#ifdef BACKLIGHT_ENABLE
#    include "process_backlight.h"
#endif

#ifdef CONNECTION_ENABLE
#    include "process_connection.h"
#endif

#ifdef GRAVE_ESC_ENABLE
#    include "process_grave_esc.h"
#endif

#ifdef HAPTIC_ENABLE
#    include "process_haptic.h"
#endif

#ifdef JOYSTICK_ENABLE
#    include "process_joystick.h"
#endif

#ifdef LEADER_ENABLE
#    include "process_leader.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    include "process_led_matrix.h"
#endif

#ifdef MAGIC_ENABLE
#    include "process_magic.h"
#endif

#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif

#if !defined(NO_ACTION_LAYER)
#    include "process_default_layer.h"
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
#    include "process_programmable_button.h"
#endif

#if defined(RGB_MATRIX_ENABLE)
#    include "process_rgb_matrix.h"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "process_underglow.h"
#endif

#ifdef SECURE_ENABLE
#    include "process_secure.h"
#endif

#ifdef TRI_LAYER_ENABLE
#    include "process_tri_layer.h"
#endif

#ifdef UNICODE_COMMON_ENABLE
#    include "process_unicode_common.h"
#endif

#ifdef LAYER_LOCK_ENABLE
#    include "process_layer_lock.h"
#endif

#ifndef NO_ACTION_ONESHOT
#    include "process_oneshot.h"
#endif

bool process_record_modules(uint16_t keycode, keyrecord_t *record);

bool process_quantum_all(uint16_t keycode, keyrecord_t *record) {
    return (
#       if defined(KEY_LOCK_ENABLE)
            // Must run first to be able to mask key_up events.
            process_key_lock(&keycode, record) &&
#       endif
#       if defined(DYNAMIC_MACRO_ENABLE) && !defined(DYNAMIC_MACRO_USER_CALL)
            // Must run asap to ensure all keypresses are recorded.
            process_dynamic_macro(keycode, record) &&
#       endif
#       ifdef REPEAT_KEY_ENABLE
            process_last_key(keycode, record) && process_repeat_key(keycode, record) &&
#       endif
#       if defined(AUDIO_ENABLE) && defined(AUDIO_CLICKY)
            process_clicky(keycode, record) &&
#       endif
#       ifdef HAPTIC_ENABLE
            process_haptic(keycode, record) &&
#       endif
#       if defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
            process_auto_mouse(keycode, record) &&
#       endif
        process_record_modules(keycode, record) && // modules must run before kb
        process_record_kb(keycode, record) &&
#       if defined(VIA_ENABLE)
            process_record_via(keycode, record) &&
#       endif
#       if defined(SECURE_ENABLE)
            process_secure(keycode, record) &&
#       endif
#       if defined(SEQUENCER_ENABLE)
            process_sequencer(keycode, record) &&
#       endif
#       if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
            process_midi(keycode, record) &&
#       endif
#       ifdef AUDIO_ENABLE
            process_audio(keycode, record) &&
#       endif
#       if defined(BACKLIGHT_ENABLE)
            process_backlight(keycode, record) &&
#       endif
#       if defined(LED_MATRIX_ENABLE)
            process_led_matrix(keycode, record) &&
#       endif
#       ifdef STENO_ENABLE
            process_steno(keycode, record) &&
#       endif
#       if (defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))) && !defined(NO_MUSIC_MODE)
            process_music(keycode, record) &&
#       endif
#       ifdef CAPS_WORD_ENABLE
            process_caps_word(keycode, record) &&
#       endif
#       ifdef KEY_OVERRIDE_ENABLE
            process_key_override(keycode, record) &&
#       endif
#       ifdef TAP_DANCE_ENABLE
            process_tap_dance(keycode, record) &&
#       endif
#       if defined(UNICODE_COMMON_ENABLE)
            process_unicode_common(keycode, record) &&
#       endif
#       ifdef LEADER_ENABLE
            process_leader(keycode, record) &&
#       endif
#       ifdef AUTO_SHIFT_ENABLE
            process_auto_shift(keycode, record) &&
#       endif
#       ifdef DYNAMIC_TAPPING_TERM_ENABLE
            process_dynamic_tapping_term(keycode, record) &&
#       endif
#       ifdef SPACE_CADET_ENABLE
            process_space_cadet(keycode, record) &&
#       endif
#       ifdef MAGIC_ENABLE
            process_magic(keycode, record) &&
#       endif
#       ifdef GRAVE_ESC_ENABLE
            process_grave_esc(keycode, record) &&
#       endif
#       if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            process_underglow(keycode, record) &&
#       endif
#       if defined(RGB_MATRIX_ENABLE)
            process_rgb_matrix(keycode, record) &&
#       endif
#       ifdef JOYSTICK_ENABLE
            process_joystick(keycode, record) &&
#       endif
#       ifdef PROGRAMMABLE_BUTTON_ENABLE
            process_programmable_button(keycode, record) &&
#       endif
#       ifdef AUTOCORRECT_ENABLE
            process_autocorrect(keycode, record) &&
#       endif
#       ifdef TRI_LAYER_ENABLE
            process_tri_layer(keycode, record) &&
#       endif
#       if !defined(NO_ACTION_LAYER)
            process_default_layer(keycode, record) &&
#       endif
#       ifdef LAYER_LOCK_ENABLE
            process_layer_lock(keycode, record) &&
#       endif
#       ifdef CONNECTION_ENABLE
            process_connection(keycode, record) &&
#       endif
#       ifndef NO_ACTION_ONESHOT
            process_oneshot(keycode, record) &&
#       endif
        true
    );
}

bool process_keycode_any(uint16_t keycode, const bool pressed) {

    keyrecord_t record = (keyrecord_t){.event = MAKE_KEYEVENT(0, 0, pressed)};
    action_t action = action_for_keycode(keycode);

    if (action.code != ACTION_NO) {
        process_action(&record, action);
        return false;
    }

    return process_quantum_all(keycode, &record);
}

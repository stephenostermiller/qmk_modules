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
#include QMK_KEYBOARD_H
#include "eztd.h"
#include "process_keycode_any.h"

enum {
    EZTD_UNPRESSED, // initial state and state after reset
    EZTD_SINGLE_TAP, // key tapped once
    EZTD_SINGLE_HOLD, // key pressed once and held
    EZTD_DOUBLE_TAP, // key tapped twice
    EZTD_DOUBLE_HOLD, // key held on second press
    EZTD_TRIPLE_TAP, // key tapped thrice
    EZTD_TRIPLE_HOLD, // key held on third press
    EZTD_OVERTAP, // Key has been tapped additional times or interrupted
};

// mutable state
typedef struct {
    // The number of over taps that have already been sent.
    uint8_t overtaps_sent;
    // The key down event that has been sent without a corresponding key up event.
    uint16_t pressed_key;
} eztd_state_t;

// Mutable state array
static eztd_state_t eztd_states[TAP_DANCE_MAX_SIMULTANEOUS];

void eztd_key_event(tap_dance_state_t *state, uint16_t keycode, uint16_t single_tap, uint8_t single_count) {
    uint8_t i;
    uint8_t presses = 1;

    // If configured to send multiple single taps
    if (keycode == EZTD_MULTI_SINGLE) {
        keycode = single_tap;
        presses = single_count;
    }

    switch(keycode) {
        case KC_TRANSPARENT:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            // These features are not compatible with
            // tap dancing, ignore the key codes.
            return;
    }

    // If a key-down was already sent, send the corresponding key-up.
    if (eztd_states[state->state_idx].pressed_key){
        process_keycode_any(eztd_states[state->state_idx].pressed_key, false);
#       if TAP_CODE_DELAY > 0
            wait_ms(TAP_CODE_DELAY);
#       endif
    }

    // Send key events for the latest key
    for (i=0; i<presses; i++) {
        // Always send key-down
        process_keycode_any(keycode, true);
        // Send key-up events except the last one.
        // There is always something held, even if
        // momentarily, after calling this method.
        if (i<presses-1) {
#           if TAP_CODE_DELAY > 0
                wait_ms(TAP_CODE_DELAY);
#           endif
            process_keycode_any(keycode, false);
#           if TAP_CODE_DELAY > 0
                wait_ms(TAP_CODE_DELAY);
#           endif
        }
    }

    // Save which key is being held into mutable state.
    // The corresponding key up event will be sent in the reset callback.
    eztd_states[state->state_idx].pressed_key = keycode;
}

uint8_t eztd_step(tap_dance_state_t *state, eztd_data_t *data) {
    if (data->interrupted_is_tap && state->interrupted) {
        // When interrupted and configured for flow
        // treat all taps as over taps.
        return EZTD_OVERTAP;
    }
    // Expect that single tap and single hold are always configured.
    // No check here for when they aren't.
    if (state->count == 1) {
        if (state->interrupted || state->pressed) {
            // interrupted after the first press when not configured for flow
            // or the key is actually held on the first press
            return EZTD_SINGLE_HOLD;
        }
        return EZTD_SINGLE_TAP;
    }
    // One tap cases have already been handled,
    // so extra taps when the second tap isn't
    // configured are over taps
    if (!data->double_tap) {
        return EZTD_OVERTAP;
    }
    if (state->count == 2) {
        if (state->interrupted || state->pressed) {
            // interrupted after the second press when not configured for flow
            // or the key is actually held on the second press
            return EZTD_DOUBLE_HOLD;
        }
        return EZTD_DOUBLE_TAP;
    }
    // One and two tap cases have already been handled,
    // so extra taps when the third tap isn't
    // configured are over taps
    if (!data->triple_tap) {
        return EZTD_OVERTAP;
    }
    if (state->count == 3) {
        if (state->interrupted || state->pressed) {
            // interrupted after the third press when not configured for flow
            // or the key is actually held on the third press
            return EZTD_TRIPLE_HOLD;
        }
        return EZTD_TRIPLE_TAP;
    }
    // One two and three tap cases have already been handled,
    // all additional taps are over taps.
    return EZTD_OVERTAP;
}

void eztd_send_unsent_overtaps(tap_dance_state_t *state, eztd_data_t* data) {
    // Send all the over taps that haven't already been sent
    eztd_key_event(state, EZTD_MULTI_SINGLE, data->tap, state->count - eztd_states[state->state_idx].overtaps_sent);
    // Record that all taps have been sent in mutable state.
    eztd_states[state->state_idx].overtaps_sent = state->count;
}

void eztd_each(tap_dance_state_t *state, void *user_data) {
    eztd_data_t data;
    memcpy_P(&data, user_data, sizeof(eztd_data_t));
    // Over taps get sent before the end of the tap dance.
    // If the user is tapping the key 100 times, the keystrokes
    // should begin to appear on the fourth tap instead of
    // waiting until the timeout after the 100th tap.
    if (eztd_step(state, &data) == EZTD_OVERTAP) {
        eztd_send_unsent_overtaps(state, &data);
    }
}

void eztd_finished(tap_dance_state_t *state, void *user_data) {
    eztd_data_t data;
    memcpy_P(&data, user_data, sizeof(eztd_data_t));
    // send key down when tap dance is finished.
    switch (eztd_step(state, &data)) {
        case EZTD_SINGLE_TAP: eztd_key_event(state, data.tap, XXXXXXX, 1); break;
        case EZTD_SINGLE_HOLD: eztd_key_event(state, data.hold, data.tap, 1); break;
        case EZTD_DOUBLE_TAP: eztd_key_event(state, data.double_tap, data.tap, 2); break;
        case EZTD_DOUBLE_HOLD: eztd_key_event(state, data.double_hold, data.tap, 2); break;
        case EZTD_TRIPLE_TAP: eztd_key_event(state, data.triple_tap, data.tap, 3); break;
        case EZTD_TRIPLE_HOLD: eztd_key_event(state, data.triple_hold, data.tap, 3); break;
        case EZTD_OVERTAP: eztd_send_unsent_overtaps(state, &data); break;
    }
}

void eztd_reset(tap_dance_state_t *state, void *user_data) {
    // Send key up when tap dance is reset.
    process_keycode_any(eztd_states[state->state_idx].pressed_key, false);
    // Reset mutable state so it can be reused
    eztd_states[state->state_idx].pressed_key = 0;
    eztd_states[state->state_idx].overtaps_sent = 0;
}

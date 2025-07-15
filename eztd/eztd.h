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

#pragma once

#include "process_tap_dance.h"

typedef struct {
    // when the dance is interrupted by another key getting pressed,
    // should it use the single tap action?
    // This should usually be set to true when the tap dance
    // key is a number or letter.
    // This should usually be set to false when a hold action
    // is a modifier key.
    bool interrupted_is_tap: 1;
    // When a key is held, send a single tap rather
    // than letting the key repeat
    bool held_keys_tap: 1;
    //  specify the keycode for actions
    uint16_t tap; // code to send when key tapped once
    uint16_t hold; // code to send when key pressed once and held
    uint16_t double_tap; // code to send when key tapped twice
    uint16_t double_hold; // code to send when key held on second press
    uint16_t triple_tap; // code to send when key tapped thrice
    uint16_t triple_hold; // code to send when key held on third press
} eztd_data_t;

void eztd_each(tap_dance_state_t *state, void *user_data);
void eztd_finished(tap_dance_state_t *state, void *user_data);
void eztd_reset(tap_dance_state_t *state, void *user_data);
void eztd_keyevent(uint16_t keycode, bool pressed);

#define EZTD_ACTION(config) {{eztd_each, eztd_finished, eztd_reset}, (void*)&(config)}

#define EZTD_TAP_DTAP(single_tap_keycode, double_tap_keycode) \
    {false, false, (single_tap_keycode), (single_tap_keycode), (double_tap_keycode), (double_tap_keycode), XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_DTAP(single_tap_keycode, double_tap_keycode) \
    {true, false, (single_tap_keycode), (single_tap_keycode), (double_tap_keycode), (double_tap_keycode), XXXXXXX, XXXXXXX}

#define EZTD_TAP_HOLD(single_tap_keycode, single_hold_keycode) \
    {false, false, (single_tap_keycode), (single_hold_keycode), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_HOLD(single_tap_keycode, single_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}

#define EZTD_ALLTAP_HOLD(single_tap_keycode, single_hold_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_TTAP(single_tap_keycode, triple_tap_keycode) \
    {true, false, (single_tap_keycode), (single_tap_keycode), EZTD_MULTI_SINGLE, EZTD_MULTI_SINGLE, (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_TAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode) \
    {false, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_tap_keycode), XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_tap_keycode), XXXXXXX, XXXXXXX}

#define EZTD_ALLTAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_tap_keycode), XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_HOLD_TTAP(single_tap_keycode, single_hold_keycode, triple_tap_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, EZTD_MULTI_SINGLE, (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_ALLTAP_HOLD_TTAP(single_tap_keycode, single_hold_keycode, triple_tap_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, EZTD_MULTI_SINGLE, (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_TAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode) \
    {false, false, (single_tap_keycode), (single_tap_keycode), (double_tap_keycode), (double_tap_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_FLOWTAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode) \
    {true, false, (single_tap_keycode), (single_tap_keycode), (double_tap_keycode), (double_tap_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_FLOWTAP_HOLD_DHOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), XXXXXXX, XXXXXXX}

#define EZTD_ALLTAP_HOLD_DHOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), XXXXXXX, XXXXXXX}

#define EZTD_TAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode) \
    {false, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_HOLD_DTAP_TTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode, triple_tap_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_tap_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_ALLTAP_HOLD_DTAP_TTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode, triple_tap_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_tap_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_FLOWTAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), XXXXXXX, XXXXXXX}

#define EZTD_ALLTAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), XXXXXXX, XXXXXXX}

#define EZTD_FLOWTAP_HOLD_DHOLD_THOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode, triple_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), EZTD_MULTI_SINGLE, (triple_hold_keycode)}

#define EZTD_FLOWTAP_HOLD_DHOLD_THOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode, triple_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), EZTD_MULTI_SINGLE, (triple_hold_keycode)}

#define EZTD_ALLTAP_HOLD_DHOLD_TTAP(single_tap_keycode, single_hold_keycode, double_hold_keycode, triple_tap_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_TAP_HOLD_DTAP_DHOLD_TTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode) \
    {false, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_ALLTAP_HOLD_DTAP_DHOLD_TTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_tap_keycode)}

#define EZTD_FLOWTAP_HOLD_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)}

#define EZTD_ALLTAP_HOLD_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), EZTD_MULTI_SINGLE, (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)}

#define EZTD_TAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {false, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)}

#define EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {true, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)}

#define EZTD_ALLTAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {true, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)}

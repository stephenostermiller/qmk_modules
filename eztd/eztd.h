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

enum {
    EZTD_UNPRESSED, // initial state and state after reset
    EZTD_SINGLE_TAP, // key tapped once
    EZTD_SINGLE_HOLD, // key pressed once and held
    EZTD_DOUBLE_TAP, // key tapped twice
    EZTD_DOUBLE_HOLD, // key held on second press
    EZTD_TRIPLE_TAP, // key tapped thrice
    EZTD_TRIPLE_HOLD, // key held on third press
    EZTD_FIRST_OVERTAP, // key was tapped exactly one more time than it has configuration to handle
    EZTD_NTH_OVERTAP, // key was tapped additional extra times
};

typedef struct {
    // mutable, holds the computed dance_step between function calls
    // must be initialized to EZTD_UNPRESSED
    uint8_t step;
    // all others are immutable

    // when the dance is interrupted by another key getting pressed,
    // should it use the single tap action?
    // This should usually be set to true when the tap dance
    // key is a number or letter.
    // This should usually be set to false when a hold action
    // is a modifier key.
    bool interrupted_is_tap;
    //  specify the keycode for actions
    uint16_t tap; // code to send when key tapped once
    uint16_t hold; // code to send when key pressed once and held
    uint16_t double_tap; // code to send when key tapped twice
    uint16_t double_hold; // code to send when key held on second press
    uint16_t triple_tap; // code to send when key tapped thrice
    uint16_t triple_hold; // code to send when key held on third press
} eztd_data;

void eztd_each(tap_dance_state_t *state, void *user_data);
void eztd_finished(tap_dance_state_t *state, void *user_data);
void eztd_reset(tap_dance_state_t *state, void *user_data);
void eztd_keyevent(uint16_t keycode, bool pressed);

// non-flow tap should be used when the tap dance key includes holding a modifier
#define EZTD_TAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)})}
#define EZTD_TAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), XXXXXXX, XXXXXXX})}
#define EZTD_TAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_hold_keycode), double_tap_keycode, (double_tap_keycode), XXXXXXX, XXXXXXX})}
#define EZTD_TAP_HOLD(single_tap_keycode, single_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_hold_keycode), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX})}
#define EZTD_TAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_tap_keycode), double_tap_keycode, (double_tap_keycode), (triple_tap_keycode), triple_tap_keycode})}
#define EZTD_TAP_DTAP(single_tap_keycode, double_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, false, (single_tap_keycode), (single_tap_keycode), double_tap_keycode, (double_tap_keycode), XXXXXXX, XXXXXXX})}

// flow tap should be used when the tap dance key is a letter or number.
#define EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), (triple_tap_keycode), (triple_hold_keycode)})}
#define EZTD_FLOWTAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_hold_keycode), (double_tap_keycode), (double_hold_keycode), XXXXXXX, XXXXXXX})}
#define EZTD_FLOWTAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_hold_keycode), double_tap_keycode, (double_tap_keycode), XXXXXXX, XXXXXXX})}
#define EZTD_FLOWTAP_HOLD(single_tap_keycode, single_hold_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_hold_keycode), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX})}
#define EZTD_FLOWTAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_tap_keycode), double_tap_keycode, (double_tap_keycode), (triple_tap_keycode), triple_tap_keycode})}
#define EZTD_FLOWTAP_DTAP(single_tap_keycode, double_tap_keycode) \
    {.fn = {eztd_each, eztd_finished, eztd_reset}, .user_data = (void *)&((eztd_data){EZTD_UNPRESSED, true, (single_tap_keycode), (single_tap_keycode), double_tap_keycode, (double_tap_keycode), XXXXXXX, XXXXXXX})}

# Easy Tap Dance — QMK Module

This module provides advanced tap dance functionality with very little code.

- It supports 6 different types of presses:
   - Single tap
   - Single hold
   - Double tap
   - Double hold
   - Triple tap
   - Triple hold
- It provides functions with different combinations of key presses:
   - `EZTD_TAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode)`
   - `EZTD_TAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode)`
   - `EZTD_TAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode)`
   - `EZTD_TAP_HOLD(single_tap_keycode, single_hold_keycode)`
   - `EZTD_TAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode)`
   - `EZTD_TAP_DTAP(single_tap_keycode, double_tap_keycode)`
   - `EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP_THOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode, triple_tap_keycode, triple_hold_keycode)`
   - `EZTD_FLOWTAP_HOLD_DTAP_DHOLD(single_tap_keycode, single_hold_keycode, double_tap_keycode, double_hold_keycode)`
   - `EZTD_FLOWTAP_HOLD_DTAP(single_tap_keycode, single_hold_keycode, double_tap_keycode)`
   - `EZTD_FLOWTAP_HOLD(single_tap_keycode, single_hold_keycode)`
   - `EZTD_FLOWTAP_DTAP_TTAP(single_tap_keycode, double_tap_keycode, triple_tap_keycode)`
   - `EZTD_FLOWTAP_DTAP(single_tap_keycode, double_tap_keycode)`
- It supports advanced keycodes
- It supports "flow" mode.

Should you use flow or not? Flow controls what happens when the tap dance is interrupted by another keypress. In flow mode, the tap dance ends and all of the tap dance key presses are treated as single clicks. This is good when tap dance is used on letters and numbers keys. It prevents accidental tap danced (like double clicks) during normal typing. Non-flow mode treats interruptions as held. It is best for tap dancing on modifier keys.


An example of how it is used:

```c
enum tap_dance_keycodes {
    LCDT_SHFT, LCDT_CRTL, LCDT_META, LCDT_ALT, RCDT_ALT, RCDT_META, RCDT_CRTL, RCDT_SHFT
};

tap_dance_action_t tap_dance_actions[] = {
    // Space cadet left: TAP (, HOLD shift, DOUBLE TAP caps word
    [LCDT_SHFT] = EZTD_TAP_HOLD_DTAP(KC_LEFT_PAREN, KC_LEFT_SHIFT, QK_CAPS_WORD_TOGGLE),
    // Space cadet left: TAP <, HOLD control (qwerty layout)
    [LCDT_CRTL] = EZTD_TAP_HOLD(KC_LEFT_ANGLE_BRACKET,  LM(LAY_QWERTY_CONTROL, MOD_MASK_CTRL)),
    // Space cadet left: TAP [, HOLD meta (qwerty layout), DOUBLE TAP toggle auto shift on/off
    [LCDT_META] = EZTD_TAP_HOLD_DTAP(KC_LEFT_BRACKET, LM(LAY_QWERTY_META, MOD_MASK_GUI), QK_AUTO_SHIFT_TOGGLE),
    // Space cadet left: TAP {, HOLD alt (qwerty layout), DOUBLE TAP toggle insert/overtype
    [LCDT_ALT] = EZTD_TAP_HOLD_DTAP(KC_LEFT_CURLY_BRACE, LM(LAY_QWERTY_ALT, MOD_MASK_ALT), KC_INS),
    // Space cadet right: TAP }, HOLD alt (qwerty layout), DOUBLE TAP lock screen (meta-l)
    [RCDT_ALT] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_CURLY_BRACE, LM(LAY_QWERTY_ALT, MOD_MASK_ALT), G(KC_L)),
    // Space cadet right: TAP ], HOLD meta (qwerty layout), DOUBLE TAP full screen (f11)
    [RCDT_META] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_BRACKET, LM(LAY_QWERTY_META, MOD_MASK_GUI), KC_F11),
    // Space cadet right: TAP >, HOLD control (qwerty layout), DOUBLE TAP close window (alt-f4)
    [RCDT_CRTL] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_ANGLE_BRACKET, LM(LAY_QWERTY_CONTROL, MOD_MASK_CTRL), A(KC_F4)),
    // Space cadet right: TAP ), HOLD shift, DOUBLE TAP caps lock
    [RCDT_SHFT] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_PAREN, KC_RIGHT_SHIFT, KC_CAPS),
```

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/eztd",
        "stephen_ostermiller/process_keycode_any"
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

# Easy Tap Dance — QMK Module

This module provides advanced tap dance functionality with very little code.

### Supports 6 different types of presses

- Single tap
- Single hold
- Double tap
- Double hold
- Triple tap
- Triple hold

### Supports advanced keycodes

Unlike basic tap dance functionality included with QMK, you can use use modifier keys, layer switches, and other advanced functionality just by specifying their keycodes.

### Supports "flow" mode.

"Flow" controls what happens when the tap dance is interrupted by another keypress. In flow-mode, the tap dance ends and all of the tap dance key presses are treated as single clicks. This is good when tap dance is used on letter and number keys. Non-flow-mode treats interruptions as held. It is best for tap dancing on modifier keys.

### Provides functions with different combinations of key presses

| Function | When interrupted by another key | When held | Single tap | Single hold | Double tap | Double hold | Triple tap | Triple hold | Four or more taps |
|----|----|----|----|----|----|----|----|----|----|
| `EZTD_TAP_DTAP()` | Sends hold | Holds / repeats |**Argument 1** | Same as single tap | **Argument 2** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_DTAP()` | Sends single taps | Holds / repeats |**Argument 1** | Same as single tap | **Argument 2** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_TAP_HOLD()` | Sends hold | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | Single tap 2 times | Single tap 3 times | Single tap 3 times |  Single tap N times |
| `EZTD_FLOWTAP_HOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | Single tap 2 times | Single tap 3 times | Single tap 3 times |  Single tap N times |
| `EZTD_ALLTAP_HOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | Single tap 2 times | Single tap 2 times | Single tap 3 times | Single tap 3 times |  Single tap N times |
| `EZTD_FLOWTAP_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | Same as single tap | Single tap 2 times | Single tap 2 times | **Argument 2** | Same as triple tap | Single tap N times |
| `EZTD_TAP_HOLD_DTAP()` | Sends hold | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_HOLD_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | Single tap 2 times | **Argument 3** | Same as triple tap | Single tap N times |
| `EZTD_ALLTAP_HOLD_TTAP()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | Single tap 2 times | Single tap 2 times | **Argument 3** | Same as triple tap | Single tap N times |
| `EZTD_TAP_DTAP_TTAP()` | Sends hold | Holds / repeats |**Argument 1** | Same as single tap | **Argument 2** | Same as double tap | **Argument 3** | Same as triple tap | Single tap N times |
| `EZTD_FLOWTAP_DTAP_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | Same as single tap | **Argument 2** | Same as double tap | **Argument 3** | Same as triple tap | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DHOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_ALLTAP_HOLD_DHOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_TAP_HOLD_DTAP_DHOLD()` | Sends hold | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP_DHOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP_DHOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | Single tap 3 times | Single tap 3 times | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | **Argument 4** | Same as triple tap | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP_TTAP()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | Same as double tap | **Argument 4** | Same as triple tap | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DHOLD_THOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | Single tap 3 times | **Argument 4** | Single tap N times |
| `EZTD_ALLTAP_HOLD_DHOLD_THOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | Single tap 3 times | **Argument 4** | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DHOLD_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | **Argument 4** | Same as triple tap | Single tap N times |
| `EZTD_TAP_HOLD_DTAP_DHOLD_TTAP()` | Sends hold | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | Same as triple tap | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | Same as triple tap | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP_DHOLD_TTAP()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | Same as triple tap | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DHOLD_TTAP_THOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | **Argument 4** | **Argument 5** | Single tap N times |
| `EZTD_ALLTAP_HOLD_DHOLD_TTAP_THOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | Single tap 2 times | **Argument 3** | **Argument 4** | **Argument 5** | Single tap N times |
| `EZTD_TAP_HOLD_DTAP_DHOLD_TTAP_THOLD()` | Sends hold | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | **Argument 6** | Single tap N times |
| `EZTD_FLOWTAP_HOLD_DTAP_DHOLD_TTAP_THOLD()` | Sends single taps | Holds / repeats |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | **Argument 6** | Single tap N times |
| `EZTD_ALLTAP_HOLD_DTAP_DHOLD_TTAP_THOLD()` | Sends single taps | Taps |**Argument 1** | **Argument 2** | **Argument 3** | **Argument 4** | **Argument 5** | **Argument 6** | Single tap N times |

## Example

```c
enum eztd_enum {
    EZTD_LCDT_SHFT, EZTD_LCDT_CRTL, EZTD_LCDT_META, EZTD_LCDT_ALT, EZTD_RCDT_ALT, EZTD_RCDT_META, EZTD_RCDT_CRTL, EZTD_RCDT_SHFT, EZTD_T
};


const eztd_data_t eztd_data[] PROGMEM = {
    // Space cadet left: TAP (, HOLD shift, DOUBLE TAP caps word
    [EZTD_LCDT_SHFT] = EZTD_TAP_HOLD_DTAP(KC_LEFT_PAREN, KC_LEFT_SHIFT, QK_CAPS_WORD_TOGGLE),
    // Space cadet left: TAP <, HOLD control (qwerty layout)
    [EZTD_LCDT_CRTL] = EZTD_TAP_HOLD(KC_LEFT_ANGLE_BRACKET,  LM(LAY_QWERTY_CONTROL, MOD_MASK_CTRL)),
    // Space cadet left: TAP [, HOLD meta (qwerty layout), DOUBLE TAP toggle auto shift on/off
    [EZTD_LCDT_META] = EZTD_TAP_HOLD_DTAP(KC_LEFT_BRACKET, LM(LAY_QWERTY_META, MOD_MASK_GUI), QK_AUTO_SHIFT_TOGGLE),
    // Space cadet left: TAP {, HOLD alt (qwerty layout), DOUBLE TAP toggle insert/overtype
    [EZTD_LCDT_ALT] = EZTD_TAP_HOLD_DTAP(KC_LEFT_CURLY_BRACE, LM(LAY_QWERTY_ALT, MOD_MASK_ALT), KC_INS),
    // Space cadet right: TAP }, HOLD alt (qwerty layout), DOUBLE TAP lock screen (meta-l)
    [EZTD_RCDT_ALT] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_CURLY_BRACE, LM(LAY_QWERTY_ALT, MOD_MASK_ALT), G(KC_L)),
    // Space cadet right: TAP ], HOLD meta (qwerty layout), DOUBLE TAP full screen (f11)
    [EZTD_RCDT_META] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_BRACKET, LM(LAY_QWERTY_META, MOD_MASK_GUI), KC_F11),
    // Space cadet right: TAP >, HOLD control (qwerty layout), DOUBLE TAP close window (alt-f4)
    [EZTD_RCDT_CRTL] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_ANGLE_BRACKET, LM(LAY_QWERTY_CONTROL, MOD_MASK_CTRL), A(KC_F4)),
    // Space cadet right: TAP ), HOLD shift, DOUBLE TAP caps lock
    [EZTD_RCDT_SHFT] = EZTD_TAP_HOLD_DTAP(KC_RIGHT_PAREN, KC_RIGHT_SHIFT, KC_CAPS),
    // TAP t, DOUBLE TAP tt, TRIPLE TAP print screen
    [EZTD_T] = EZTD_FLOWTAP_TTAP(KC_T, KC_PSCR),
};

enum tap_dance_enum {
    LCDT_SHFT, LCDT_CRTL, LCDT_META, LCDT_ALT, RCDT_ALT, RCDT_META, RCDT_CRTL, RCDT_SHFT, TD_T
};

const tap_dance_action_t tap_dance_actions[] PROGMEM = {
    [LCDT_SHFT] = EZTD_ACTION(eztd_data[EZTD_LCDT_SHFT]),
    [LCDT_CRTL] = EZTD_ACTION(eztd_data[EZTD_LCDT_CRTL]),
    [LCDT_META] = EZTD_ACTION(eztd_data[EZTD_LCDT_META]),
    [LCDT_ALT] = EZTD_ACTION(eztd_data[EZTD_LCDT_ALT]),
    [RCDT_ALT] = EZTD_ACTION(eztd_data[EZTD_RCDT_ALT]),
    [RCDT_META] = EZTD_ACTION(eztd_data[EZTD_RCDT_META]),
    [RCDT_CRTL] = EZTD_ACTION(eztd_data[EZTD_RCDT_CRTL]),
    [RCDT_SHFT] = EZTD_ACTION(eztd_data[EZTD_RCDT_SHFT]),
    [TD_T] = EZTD_ACTION(eztd_data[EZTD_T]),
};
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

# Process Any Key — QMK Module

This module adds a method that can be called from your `keymap.c` that will process any possible keycode. For example:

```c
// Send that the A key was pressed
process_keycode_any(KC_A, true);
// Add a delay between press and release
wait_ms(10);
// Send that the A key was released
process_keycode_any(KC_A, false);
```

> [!WARNING]
> Care must be taken when calling this method to prevent recursion.

For example, when calling this method from a tap dance handler, make sure it can't
re-trigger the same tap dance. One way of ensuring this is to wrap the method call
in another method that ignores keycodes that could be problematic:

```c
void my_tap_dance_key_processor(uint16_t keycode, const bool pressed) {
    switch(keycode) {
        case KC_TRANSPARENT:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            // These features are not compatible with
            // tap dancing, ignore them.
            return;
    }

    process_keycode_any(keycode, pressed);
}
```

Using `process_keycode_any` recursively will cause your keyboard to become unresponsive until rebooted.

The QMK developers do **not** provide a similar method in QMK core because of the recursion risk.

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/process_keycode_any",
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

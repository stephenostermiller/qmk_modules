# Auto Shift Override Compatibility — QMK Module

When using this module, keycodes in `keymap.c`,s `key_overrides[]` that override a keycode with `MOD_MASK_SHIFT` will automatically work with auto shift.

> [!IMPORTANT]
> This module monopolizes the `autoshift_press_user()` and `autoshift_release_user()` functions.
> When you use this module you won't be able to use these functions yourself, nor use other
> modules that use these functions.

This module (ab)uses introspection to take over the two auto shift callbacks that are normally reserved for use only in `keymap.c`. Versions of these methods for modules are not available, at least not at the time this module was authored.

Using this module will turn on auto shift functionality as if `AUTO_SHIFT_ENABLE = yes` were specified in your `rules.mk`.

This module depends on the [Process Any Keycode](../process_keycode_any/) module, so you must pull in both this module and `process_keycode_any`.

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/auto_shift_overrides",
        "stephen_ostermiller/process_keycode_any"
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

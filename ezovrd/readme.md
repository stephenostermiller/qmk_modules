# Easy Override — QMK Module

This module provides key overrides that work with all keycodes. Here is an example of using it to toggle caps word on and off using shift-period.

```c
const key_override_t *key_overrides[] = {
	&ezovrd_make_basic(MOD_MASK_SHIFT, KC_DOT, QK_CAPS_WORD_TOGGLE),
};
```

## Features

This module provides functions with similar method signatures to the built in qmk overrides but with upgrades

### Support for advanced keycodes

Unlike built in overrides, you can use advanced keycodes for the key replacement such as:

- Unicode characters
- Layer switching
- Caps word toggle

### Automatic mod suppression

Trigger mods are suppressed mods unless they are replacement key code mods. For example if you want to make shift-1 type `'` and shift-2 type `"`, you can use:

```c
const key_override_t *key_overrides[] = {
    &ezovrd_make_basic(MOD_MASK_SHIFT, KC_1, KC_QUOTE),
    &ezovrd_make_basic(MOD_MASK_SHIFT, KC_2, S(KC_QUOTE)),
}
```

This will do the right thing with mod suppression in both cases.
For shift-1, the shift key is suppressed and an (un-shifted) apostrophe is typed.
For the shift-2, the shift key is NOT suppressed, so that the double quote (which requires the shift) gets typed.

## Available functions

```c
ezovrd_make_basic(mod_mask, trigger_key, replacement_key);
```

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/ezovrd",
        "stephen_ostermiller/process_keycode_any"
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

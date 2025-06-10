# Easy Override — QMK Module

This module provides key overrides that work with all keycodes. Here is an example of using it to toggle caps word on and off using shift-period.

```c
const key_override_t *key_overrides[] = {
	&ezovrd_make_basic(MOD_MASK_SHIFT, KC_DOT, QK_CAPS_WORD_TOGGLE),
};
```

This module provides upgraded functions with similar method signatures to the built in qmk overrides, but which support advanced keycodes.

```c
ezovrd_make_basic(trigger_mods, trigger_key, replacement_key);

ezovrd_make_with_layers(trigger_mods, trigger_key, replacement_key, layers);

ezovrd_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, layers, negative_mask);

ezovrd_make_with_layers_negmods_and_options(trigger_mods_, trigger_key, replacement_key, layer_mask, negative_mask, options_);
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

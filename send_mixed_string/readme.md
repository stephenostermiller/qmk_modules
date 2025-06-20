# Send Mixed Unicode/ASCII String — QMK Module

This module adds a method will send the keystrokes for a string containing Unicode mixed with normal numbers and letters.

```c
send_mixed_string("All my ❤️");
```

Unlike `unicode_send_string()` which is built into QMK, this method will send simple one character keycodes when possible instead of sending the entire string with Unicode escape sequences. This makes the method much more efficient.

This module also comes with a corresponding function that can send a string from where it is compiled into flash memory. Regular strings are copied out of flash memory to RAM. If you create your strings with `PROGMEM` you can use fewer memory resources.

```c
const char love_note[] PROGMEM = "All my ❤️";
send_mixed_string_P(love_note);
```

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/send_mixed_string"
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

# Unicode Macro Map — QMK Module

This module takes over the unicode keycode space just like the unicode map functionality but with some added advantages:

- No more hex codes needed to specify unicode charaters in your keymap.
- Supports emojis that consist of multiple code points.
- Each unicode keycode can be a string of many characters, ie. a macro.

```c

const char u_em_dash[] PROGMEM  = "—";
const char u_heart[] PROGMEM  = "❤️";
const char u_tblflp[] PROGMEM = "(╯°□°）╯︵ ┻━┻";
const char u_low_ae[] PROGMEM = "æ";
const char u_upp_ae[] PROGMEM = "Æ";
const char u_to[] PROGMEM = "To Whom It May Concern:";
const char u_sig[] PROGMEM = "Sincerely,\nA Concerned Citizen";

enum unicode_names {
    U_EM_DASH, U_HEART, U_TBLFLP, U_LOW_AE, U_UPP_AE, U_TO, U_SIG
};

const char* const unicode_macro_map[] PROGMEM = {
    [U_EM_DASH] = u_em_dash,
    [U_HEART] = u_heart,
    [U_TBLFLP]= u_tblflp,
    [U_LOW_AE]= u_low_ae,
    [U_UPP_AE]= u_upp_ae,
    [U_TO]= u_to,
    [U_SIG]= u_sig,
};
```

Then you can use these keycodes in your keymap:

- `UM(U_EM_DASH)`
- `UM(U_HEART)`
- `UM(U_TBLFLP)`
- `UP(U_LOW_AE, U_UPP_AE)`
- `UM(U_TO)`
- `UM(U_SIG)`

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/send_mixed_string",
        "stephen_ostermiller/unicode_macro_map"
    ]
}
```

## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

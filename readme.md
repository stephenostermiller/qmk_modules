# Stephen Ostermiller's QMK keyboard community modules

Here are community modules for the [Quantum Mechanical Keyboard
(QMK)](https://docs.qmk.fm) firmware, used on many brands of programmable keyboard.
These modules were developed for use in [Stephen's QMK
keymap](https://github.com/stephenostermiller/qmk_userspace/tree/main/keyboards/ergodox_ez/base/keymaps/dvorak_qwerty).

| Module                                        | Description                                              |
|-----------------------------------------------|----------------------------------------------------------|
| [Auto Unicode OS](./auto_unicode_os/)         | Uses operating system detection to set the unicode mode. |
| [Easy Override](./ezovrd/)                    | Key overrides that supports every keycode.               |
| [Easy Tap Dance](./eztd/)                     | Tap dancing without writing handler methods.             |
| [Process Any Keycode](./process_keycode_any/) | A single method that handles every keycode.              |
| [Send Mixed String](./send_mixed_string/)     | Sends strings containing unicode and ASCII efficiently.  |
| [Unicode Macro Map](./unicode_macro_map/)     | Emoji and macro unicode keycodes,                        |

## How to install

**Step 1. Download modules.** Run these shell commands substituting in your qmk directory.

```sh
cd </path/to/qmk_firmware OR /path/to/qmk_userspace>
mkdir -p modules
git submodule add https://github.com/stephenostermiller/qmk_modules.git modules/stephen_ostermiller
git submodule update --init --recursive
```

**Step 2. Add modules to keymap.json.** Add a module to your keymap by writing a
file `keymap.json` in your keymap folder with a list of the modules you want to use.

```json
{
    "modules": [
        "stephen_ostermiller/auto_unicode_os",
        "stephen_ostermiller/ezovrd",
        "stephen_ostermiller/eztd",
        "stephen_ostermiller/process_keycode_any",
        "stephen_ostermiller/send_mixed_string",
        "stephen_ostermiller/unicode_macro_map"
    ]
}

```

**Step 3. Update the firmware.** Compile and flash the firmware as usual. If
there are build errors, try running `qmk clean` and compiling again for a clean
build.

## How to uninstall

Remove the modules from `keymap.json` and delete the `modules/stephen_ostermiller` directory.

## License

 GNU General Public License Version 2. See the [LICENSE file](LICENSE.txt) for details.

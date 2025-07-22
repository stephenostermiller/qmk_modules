# Unicode Fancy Alphabet — QMK Module

This module adds the ability for your keyboard to type alternate unicode alphabet symbols in place of your layout's existing numbers and letters.

## Usage

This module defines a keycode that enables fancy alphabet mode: `UFA_CYC`. Assign this keycode in your keymap to use the functionality of this module.

- Pressing `UFA_CYC` while fancy alphabet mode is off turns the mode on.
- Pressing it again while fancy alphabet mode is on cycles to the next fancy alphabet.
- Pressing the escape key while fancy alphabet mode is on turns off the mode.
- Pressing `UFA_CYC` after fancy alphabet mode has been turned off turns it back on using the same alphabet used last time it was on.

Another keycode enables fancy alphabet mode just while the key is held down: `UFA_MO`. The `UFA_OFF` keycode will turn off fancy unicode typing. There are also keycodes that set a specific fancy text (in parenthesis below).

Alternately you can programmatically turn the mode on and set which alphabet you want to use. See the functions available in [unicode_fancy_alphabet.h](unicode_fancy_alphabet.h).

## Supported alphabets

### `UNICODE_FANCY_ALPHABET_DOUBLE_STRUCK` (UFA_DS)

𝕒 𝕓 𝕔 𝕕 𝕖 𝕗 𝕘 𝕙 𝕚 𝕛 𝕜 𝕝 𝕞 𝕟 𝕠 𝕡 𝕢 𝕣 𝕤 𝕥 𝕦 𝕧 𝕨 𝕩 𝕪 𝕫 𝔸 𝔹 ℂ 𝔻 𝔼 𝔽 𝔾 ℍ 𝕀 𝕁 𝕂 𝕃 𝕄 ℕ 𝕆 ℙ ℚ ℝ 𝕊 𝕋 𝕌 𝕍 𝕎 𝕏 𝕐 ℤ 𝟘 𝟙 𝟚 𝟛 𝟜 𝟝 𝟞 𝟟 𝟠 𝟡

### `UNICODE_FANCY_ALPHABET_CIRCLED` (UFA_CIR)

ⓐ ⓑ ⓒ ⓓ ⓔ ⓕ ⓖ ⓗ ⓘ ⓙ ⓚ ⓛ ⓜ ⓝ ⓞ ⓟ ⓠ ⓡ ⓢ ⓣ ⓤ ⓥ ⓦ ⓧ ⓨ ⓩ Ⓐ Ⓑ Ⓒ Ⓓ Ⓔ Ⓕ Ⓖ Ⓗ Ⓘ Ⓙ Ⓚ Ⓛ Ⓜ Ⓝ Ⓞ Ⓟ Ⓠ Ⓡ Ⓢ Ⓣ Ⓤ Ⓥ Ⓦ Ⓧ Ⓨ Ⓩ ⓪ ① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨

### `UNICODE_FANCY_ALPHABET_NEGATIVE_CIRCLED` (UFA_NC)

🅐 🅑 🅒 🅓 🅔 🅕 🅖 🅗 🅘 🅙 🅚 🅛 🅜 🅝 🅞 🅟 🅠 🅡 🅢 🅣 🅤 🅥 🅦 🅧 🅨 🅩 ⓿ ❶ ❷ ❸ ❹ ❺ ❻ ❼ ❽ ❾

### `UNICODE_FANCY_ALPHABET_SQUARED` (UFA_SQ)

🄰 🄱 🄲 🄳 🄴 🄵 🄶 🄷 🄸 🄹 🄺 🄻 🄼 🄽 🄾 🄿 🅀 🅁 🅂 🅃 🅄 🅅 🅆 🅈 🅉

### `UNICODE_FANCY_ALPHABET_NEGATIVE_SQUARED` (UFA_NSQ)

🅰 🅱 🅲 🅳 🅴 🅵 🅶 🅷 🅸 🅹 🅺 🅻 🅼 🅽 🅾 🅿 🆀 🆁 🆂 🆃 🆄 🆅 🆆 🆇 🆈 🆉

### `UNICODE_FANCY_ALPHABET_SCRIPT` (UFA_SCR)

𝒶 𝒷 𝒸 𝒹 ℯ 𝒻 ℊ 𝒽 𝒾 𝒿 𝓀 𝓁 𝓂 𝓃 ℴ 𝓅 𝓆 𝓇 𝓈 𝓉 𝓊 𝓋 𝓌 𝓍 𝓎 𝓏 𝒜 ℬ 𝒞 𝒟 ℰ ℱ 𝒢 ℋ ℐ 𝒥 𝒦 ℒ ℳ 𝒩 𝒪 𝒫 𝒬 ℛ 𝒮 𝒯 𝒰 𝒱 𝒲 𝒳 𝒴 𝒵

### `UNICODE_FANCY_ALPHABET_SCRIPT_BOLD` (UFA_SB)

𝓪 𝓫 𝓬 𝓭 𝓮 𝓯 𝓰 𝓱 𝓲 𝓳 𝓴 𝓵 𝓶 𝓷 𝓸 𝓹 𝓺 𝓻 𝓼 𝓽 𝓾 𝓿 𝔀 𝔁 𝔂 𝔃 𝓐 𝓑 𝓒 𝓓 𝓔 𝓕 𝓖 𝓗 𝓘 𝓙 𝓚 𝓛 𝓜 𝓝 𝓞 𝓟 𝓠 𝓡 𝓢 𝓣 𝓤 𝓥 𝓦 𝓧 𝓨 𝓩

### `UNICODE_FANCY_ALPHABET_FRAKTUR` (UFA_FRK)

𝔞 𝔟 𝔠 𝔡 𝔢 𝔣 𝔤 𝔥 𝔦 𝔧 𝔨 𝔩 𝔪 𝔫 𝔬 𝔭 𝔮 𝔯 𝔰 𝔱 𝔲 𝔳 𝔴 𝔵 𝔶 𝔷 𝔄 𝔅 ℭ 𝔇 𝔈 𝔉 𝔊 ℌ ℑ 𝔍 𝔎 𝔏 𝔐 𝔑 𝔒 𝔓 𝔔 ℜ 𝔖 𝔗 𝔘 𝔙 𝔚 𝔛 𝔜 ℨ

### `UNICODE_FANCY_ALPHABET_FRAKTUR_BOLD` (UFA_FB)

𝖆 𝖇 𝖈 𝖉 𝖊 𝖋 𝖌 𝖍 𝖎 𝖏 𝖐 𝖑 𝖒 𝖓 𝖔 𝖕 𝖖 𝖗 𝖘 𝖙 𝖚 𝖛 𝖜 𝖝 𝖞 𝖟 𝕬 𝕭 𝕮 𝕯 𝕰 𝕱 𝕲 𝕳 𝕴 𝕵 𝕶 𝕷 𝕸 𝕹 𝕺 𝕻 𝕼 𝕽 𝕾 𝕿 𝖀 𝖁 𝖂 𝖃 𝖄 𝖅

### `UNICODE_FANCY_ALPHABET_REGIONAL` (UFA_REG)

🇦 🇧 🇨 🇩 🇪 🇫 🇬 🇭 🇮 🇯 🇰 🇱 🇲 🇳 🇴 🇵 🇶 🇷 🇸 🇹 🇺 🇻 🇼 🇽 🇾 🇿

Typing country codes with this alphabet creates emoji flags. For example typing "US" with it results in 🇺🇸.

### `UNICODE_FANCY_ALPHABET_MONOSPACED` (UFA_MON)

𝚊 𝚋 𝚌 𝚍 𝚎 𝚏 𝚐 𝚑 𝚒 𝚓 𝚔 𝚕 𝚖 𝚗 𝚘 𝚙 𝚚 𝚛 𝚜 𝚝 𝚞 𝚟 𝚠 𝚡 𝚢 𝚣 𝙰 𝙱 𝙲 𝙳 𝙴 𝙵 𝙶 𝙷 𝙸 𝙹 𝙺 𝙻 𝙼 𝙽 𝙾 𝙿 𝚀 𝚁 𝚂 𝚃 𝚄 𝚅 𝚆 𝚇 𝚈 𝚉 𝟶 𝟷 𝟸 𝟹 𝟺 𝟻 𝟼 𝟽 𝟾 𝟿

### `UNICODE_FANCY_ALPHABET_ITALIC` (UFA_ITC)

𝑎 𝑏 𝑐 𝑑 𝑒 𝑓 𝑔 ℎ 𝑖 𝑗 𝑘 𝑙 𝑚 𝑛 𝑜 𝑝 𝑞 𝑟 𝑠 𝑡 𝑢 𝑣 𝑤 𝑥 𝑦 𝑧 𝐴 𝐵 𝐶 𝐷 𝐸 𝐹 𝐺 𝐻 𝐼 𝐽 𝐾 𝐿 𝑀 𝑂 𝑃 𝑄 𝑅 𝑆 𝑇 𝑈 𝑊 𝑋 𝑌 𝑍

### `UNICODE_FANCY_ALPHABET_BOLD_ITALIC` (UFA_BI)

𝒂 𝒃 𝒄 𝒅 𝒆 𝒇 𝒈 𝒉 𝒊 𝒋 𝒌 𝒍 𝒎 𝒏 𝒐 𝒑 𝒒 𝒓 𝒔 𝒕 𝒖 𝒗 𝒘 𝒙 𝒚 𝒛 𝑨 𝑩 𝑪 𝑫 𝑭 𝑮 𝑯 𝑰 𝑱 𝑲 𝑳 𝑴 𝑵 𝑶 𝑸 𝑹 𝑺 𝑻 𝑼 𝑽 𝑾 𝑿 𝒀 𝒁

### `UNICODE_FANCY_ALPHABET_BOLD` (UFA_BLD)

𝐚 𝐛 𝐜 𝐝 𝐞 𝐟 𝐠 𝐡 𝐢 𝐣 𝐤 𝐥 𝐦 𝐧 𝐨 𝐩 𝐪 𝐫 𝐬 𝐭 𝐮 𝐯 𝐰 𝐱 𝐲 𝐳 𝐀 𝐁 𝐂 𝐃 𝐄 𝐅 𝐆 𝐇 𝐈 𝐉 𝐊 𝐋 𝐌 𝐍 𝐎 𝐐 𝐑 𝐒 𝐓 𝐔 𝐕 𝐖 𝐗 𝐘 𝐙

### `UNICODE_FANCY_ALPHABET_WIDE` (UFA_WDE)

ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ ｊ ｋ ｌ ｍ ｎ ｏ ｐ ｑ ｒ ｓ ｔ ｕ ｖ ｗ ｘ ｙ ｚ Ａ Ｂ Ｃ Ｄ Ｅ Ｆ Ｇ Ｈ Ｉ Ｊ Ｋ Ｌ Ｍ Ｎ Ｏ Ｐ Ｑ Ｒ Ｓ Ｔ Ｕ Ｖ Ｗ Ｘ Ｙ Ｚ ０ １ ２ ３ ４ ５ ６ ７ ８ ９ ０

### `UNICODE_FANCY_ALPHABET_CURSED` (UFA_CUR)

a̹͑ b̸̘ͨ̃ͥ͢͞͝ ç̂̓ ḏ̸͍̈́̿̕ e̥ f̧ͩ̒ͨ̓ g̡̭̥ͣ̓̏̀́ h̽́ i̵͋͒ j͔̘́ k͔̒ͬ̇ͪ̚ l͕̠ͩͥ́͘ m̺ͥ̕ n͉̗ͭ͆ͨ̑ͅ o̵̩͔̾ͭͥ̓ p̳̊ͬ́ q̠̮ ŕ̡͖̘̭̯͔́ s͍̖̉ ţͩ u͏̮̃͊ v̜͔̀̈͋̚ͅ w̸̬̟ͦ̅̏̍͢ x̡͎̠̍͂͟ y̷̗͎ͨ z̧̨̗̮̗̙͢͡ A̋ B̦͖̬͂ C̣̙ D͔̗̻̩̿̀͠ͅ E̷͈̼̯̊͛̂ F̵̧͌̿͑ͭ G̡͓̣͊ͮ̐͡ H̛͇͈̟̑̌ Į̲̠̓͜͝ J̯ͨ͋ͯ́͝ K̠͇ͯ̒̓̎ͤ L̛͑̈́ M̨̱̍̋̓ Ņ̛̳̮̹̹͗̔ O̥ͤ̑̉ P̠̈ Q̴̪̘̽ͬͩ͝ Ṛ͉̹̻́ S̵̯̪̱̈ͅ T̖̞̜ͨ Ų̛̺̭ͭ V͚̐ W͍ͯ X͖̓̉ Y͏͈͚̩̕͟ Z͉̽ͨͮ͝ 0̸̖̲̓͛͠ 1̠͒̓ͦ̎ͫ̉ͩ 2̹̲̭̱̀͂̉ 3̖̣̳̃ͫͧ̕ͅ 4̗̹ 5͔̜̑ͪ̓̾̀̚ 6̳̀͡͞ 7̸̹͚͑ͨ͢ 8̘̬̃ͥ͝ 9̨̀͋ͬ 0̻̬̗͊̔͆̾

### `UNICODE_FANCY_ALPHABET_RANSOM` (UFA_RSM)

𝓪 𝚋 𝕔 𝒹 e f ℊ 🇭 🅘 𝖏 🇰 🅛 ⓜ ⓝ 𝚘 p̱͍̿ 𝒒 𝚛 s 𝑡 𝓾 𝓿 𝔀 𝔁 𝔶 𝖟 𝑨 𝔅 🇨 𝙳 𝓔 🄵 𝒢 𝙷 ℐ 🅹 𝕂 🅛 🅼 𝕹 𝕆 𝔓 Q 🆁 𝕾 𝔗 🆄 𝑉 𝚆 𝕏 𝕐 Z ⓿ 1 2̷̸̧̓͑ 𝟛 ④ ❺ 6 𝟽 ❽ 9

This alphabet uses characters from random other alphabets.

## Installation

[Install this module repository into your QMK code folder](../) and then add to your `keymap.json`:

```json
{
    "modules": [
        "stephen_ostermiller/unicode_fancy_alphabet"
    ]
}
```

You also need to [enable Unicode using any of the three supported methods](https://docs.qmk.fm/features/unicode#input-subsystems) and set up your Unicode input mode [enable Unicode using any of the three supported methods](https://docs.qmk.fm/features/unicode#input-modes).

## See also

This module is similar to [Drashna's Unicode Typing module](https://github.com/drashna/qmk_modules/tree/main/unicode_typing)


## License

 GNU General Public License Version 2. See the [LICENSE file](../LICENSE) for details.

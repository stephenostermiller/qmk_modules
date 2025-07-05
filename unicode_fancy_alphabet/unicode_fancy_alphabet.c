/* Copyright 2025 Stephen Ostermiller <https://ostermiller.org/contact.pl?regarding=qmk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "unicode.h"
#include "unicode_fancy_alphabet.h"
#include "progmem.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

static uint8_t unicode_fancy_alphabet_current = UNICODE_FANCY_ALPHABET_NONE;
static uint8_t unicode_fancy_alphabet_last = 1;

typedef struct {
    uint32_t zero;
    uint32_t one;
    uint32_t lower;
    uint32_t upper;
} unicode_fancy_alphabet_t;

const unicode_fancy_alphabet_t unicode_fancy_alphabets[] PROGMEM = {
    // Each fancy alphabet is specified with four
    // starting characters. Since these fancy chars
    // are typically defined together in alphabetical
    // order in unicode, other letters can be calculated
    // from these starting offsets
    [UNICODE_FANCY_ALPHABET_NONE] = {0, 0, 0, 0},
    [UNICODE_FANCY_ALPHABET_SCRIPT] = {
        0,
        0,
        0x1d4b6, // 𝒶
        0x1d49c, // 𝒜
    },
    [UNICODE_FANCY_ALPHABET_SCRIPT_BOLD] = {
        0,
        0,
        0x1d4ea, // 𝓪
        0x1d4d0, // 𝓐
    },
    [UNICODE_FANCY_ALPHABET_DOUBLE_STRUCK] = {
        0x1d7d8, // 𝟘
        0x1d7d9, // 𝟙
        0x1d552, // 𝕒
        0x1d538, // 𝔸
    },
    [UNICODE_FANCY_ALPHABET_WIDE] = {
        0xFF10, // ０
        0xFF11, // １
        0xFF41, // ａ
        0xFF21, // Ａ
    },
    [UNICODE_FANCY_ALPHABET_BOLD] = {
        0x1d7ce, // 𝟎
        0x1d7cf, // 𝟏
        0x1d41a, // 𝐚
        0x1d400, // 𝐀
    },
    [UNICODE_FANCY_ALPHABET_ITALIC] = {
        0,
        0,
        0x1d44e, // 𝑎
        0x1d434, // 𝐴
    },
    [UNICODE_FANCY_ALPHABET_BOLD_ITALIC] = {
        0,
        0,
        0x1d482, // 𝒂
        0x1d468, // 𝑨
    },
    [UNICODE_FANCY_ALPHABET_FRAKTUR] = {
        0,
        0,
        0x1d51e, // 𝔞
        0x1d504, // 𝔄
    },
    [UNICODE_FANCY_ALPHABET_FRAKTUR_BOLD] = {
        0,
        0,
        0x1d586, // 𝖆
        0x1d56c, // 𝕬
    },
    [UNICODE_FANCY_ALPHABET_REGIONAL] = {
        0,
        0,
        0x1f1e6, // 🇦
        0x1f1e6, // 🇦
    },
    [UNICODE_FANCY_ALPHABET_CIRCLED] = {
        0x24EA, // ⓪
        0x2460, // ①
        0x24D0, // ⓐ
        0x24B6, // Ⓐ
    },
    [UNICODE_FANCY_ALPHABET_NEGATIVE_CIRCLED] = {
        0x24ff, // ⓿
        0x2776, // ❶
        0x1f150, // 🅐
        0x1f150, // 🅐
    },
    [UNICODE_FANCY_ALPHABET_SQUARED] = {
        0,
        0,
        0x1f130, // 🄰
        0x1f130, // 🄰
    },
    [UNICODE_FANCY_ALPHABET_NEGATIVE_SQUARED] = {
        0,
        0,
        0x1f170, // 🅰
        0x1f170, // 🅰
    },
    [UNICODE_FANCY_ALPHABET_MONOSPACED] = {
        0x1d7f6, // 𝟶
        0x1d7f7, // 𝟷
        0x1d68a, // 𝚊
        0x1d670, // 𝙰
    },
};

void unicode_fancy_alphabet_cycle(void) {
    uint8_t next = unicode_fancy_alphabet_current + 1;
    if (unicode_fancy_alphabet_current == UNICODE_FANCY_ALPHABET_NONE) {
        next = unicode_fancy_alphabet_last;
    }
    if (next >= UNICODE_FANCY_ALPHABET_LAST) {
        next = 1;
    }
    unicode_fancy_alphabet_set(next);
}

__attribute__((weak)) void unicode_fancy_alphabet_set_user(uint8_t alphabet) {
}

void unicode_fancy_alphabet_set(uint8_t alphabet) {
    if (alphabet >= UNICODE_FANCY_ALPHABET_LAST) {
        return;
    }
    if (unicode_fancy_alphabet_current != UNICODE_FANCY_ALPHABET_NONE && alphabet == UNICODE_FANCY_ALPHABET_NONE) {
        unicode_fancy_alphabet_last = unicode_fancy_alphabet_current;
    }
    unicode_fancy_alphabet_current = alphabet;
    unicode_fancy_alphabet_set_user(alphabet);
}

uint8_t unicode_fancy_alphabet_get(void) {
    return unicode_fancy_alphabet_current;
}

bool _process_record_unicode_fancy_alphabet(uint16_t keycode, keyrecord_t *record) {
    int32_t unicode = 0;
    uint8_t alphabetIndex = unicode_fancy_alphabet_current;
    unicode_fancy_alphabet_t alphabet;
    if (alphabetIndex == UNICODE_FANCY_ALPHABET_RANSOM) {
        alphabetIndex = rand() % (UNICODE_FANCY_ALPHABET_RANSOM-1);
    }
    memcpy_P(&alphabet, &unicode_fancy_alphabets[alphabetIndex], sizeof(unicode_fancy_alphabet_t));

    switch(keycode) {
        case KC_0:
            unicode = alphabet.zero;
            break;
        case KC_1 ... KC_9:
            unicode = alphabet.one + keycode - KC_1;
            break;
        case KC_A ... KC_Z:
            unicode = ((host_keyboard_led_state().caps_lock || is_caps_word_on() || get_mods() & MOD_MASK_SHIFT) ? alphabet.upper : alphabet.lower) + keycode - KC_A;
            break;
    }

    if (unicode < 0x7F) {
        // Nothing fancy available
        // Fall back to regular keystroke processing
        return true;
    }

    // Some fancy letters don't live in the same block
    // with all the others. These were typically defined
    // as math symbols early in unicode history.
    // Their code point in the block with their peers is
    // reserved, but a special case is needed to
    // use the code point defined in another block.
    if (unicode == 0x1D4BA) {
        unicode = 0x212f; // ℯ
    } else if (unicode == 0x1D4BC) {
        unicode = 0x210A; // ℊ
    } else if (unicode == 0x1D4C4) {
        unicode = 0x2134; // ℴ
    } else if (unicode == 0x1D49D) {
        unicode = 0x212c; // ℬ
    } else if (unicode == 0x1D4A0) {
        unicode = 0x2130; // ℰ
    } else if (unicode == 0x1D4A1) {
        unicode = 0x2131; // ℱ
    } else if (unicode == 0x1D4A3) {
        unicode = 0x210b; // ℋ
    } else if (unicode == 0x1D4A4) {
        unicode = 0x2110; // ℐ
    } else if (unicode == 0x1D4A7) {
        unicode = 0x2112; // ℒ
    } else if (unicode == 0x1D4A8) {
        unicode = 0x2133; // ℳ
    } else if (unicode == 0x1D4AD) {
        unicode = 0x211b; // ℛ
    } else if (unicode == 0x1D53A) {
        unicode = 0x2102; // ℂ
    } else if (unicode == 0x1D53F) {
        unicode = 0x210d; // ℍ
    } else if (unicode == 0x1D545) {
        unicode = 0x2115; // ℕ
    } else if (unicode == 0x1D547) {
        unicode = 0x2119; // ℙ
    } else if (unicode == 0x1D548) {
        unicode = 0x211a; // ℚ
    } else if (unicode == 0x1D549) {
        unicode = 0x211d; // ℝ
    } else if (unicode == 0x1D551) {
        unicode = 0x2124; // ℤ
    } else if (unicode == 0x1D455) {
        unicode = 0x210e; // ℎ
    } else if (unicode == 0x1D506) {
        unicode = 0x212d; // ℭ
    } else if (unicode == 0x1D50B) {
        unicode = 0x210c; // ℌ
    } else if (unicode == 0x1D50C) {
        unicode = 0x2111; // ℑ
    } else if (unicode == 0x1D515) {
        unicode = 0x211c; // ℜ
    } else if (unicode == 0x1D51D) {
        unicode = 0x2128; // ℨ
    }

    register_unicode(unicode);
    return false;
}

bool process_record_unicode_fancy_alphabet(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_UNICODE_FANCY_ALPHABET_CYCLE:
            case KC_UNICODE_FANCY_ALPHABET_MOMENTARY:
                unicode_fancy_alphabet_cycle();
                return false;
            case KC_UNICODE_FANCY_ALPHABET_OFF:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_NONE);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_DOUBLE_STRUCK:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_DOUBLE_STRUCK);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_CIRCLED:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_CIRCLED);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_NEGATIVE_CIRCLED:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_NEGATIVE_CIRCLED);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_SQUARED:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_SQUARED);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_NEGATIVE_SQUARED:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_NEGATIVE_SQUARED);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_SCRIPT:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_SCRIPT);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_SCRIPT_BOLD:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_SCRIPT_BOLD);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_FRAKTUR:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_FRAKTUR);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_FRAKTUR_BOLD:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_FRAKTUR_BOLD);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_REGIONAL:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_REGIONAL);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_MONOSPACED:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_MONOSPACED);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_ITALIC:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_ITALIC);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_BOLD_ITALIC:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_BOLD_ITALIC);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_BOLD:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_BOLD);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_WIDE:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_WIDE);
                return false;
            case KC_UNICODE_FANCY_ALPHABET_RANSOM:
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_RANSOM);
                return false;
            case KC_ESC:
                if (unicode_fancy_alphabet_current == UNICODE_FANCY_ALPHABET_NONE) {
                    return true;
                }
                unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_NONE);
                return false;
            case KC_A ... KC_0:
                return _process_record_unicode_fancy_alphabet(keycode, record);
        }
    } else if (keycode == KC_UNICODE_FANCY_ALPHABET_MOMENTARY){
        unicode_fancy_alphabet_set(UNICODE_FANCY_ALPHABET_NONE);
        return false;
    }

    return true;
}

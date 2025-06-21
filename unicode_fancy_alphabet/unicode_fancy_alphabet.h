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
#include <stdint.h>

enum unicode_fancy_alphabet_enum {
    UNICODE_FANCY_ALPHABET_NONE,
    UNICODE_FANCY_ALPHABET_DOUBLE_STRUCK,
    UNICODE_FANCY_ALPHABET_CIRCLED,
    UNICODE_FANCY_ALPHABET_NEGATIVE_CIRCLED,
    UNICODE_FANCY_ALPHABET_SQUARED,
    UNICODE_FANCY_ALPHABET_NEGATIVE_SQUARED,
    UNICODE_FANCY_ALPHABET_SCRIPT,
    UNICODE_FANCY_ALPHABET_SCRIPT_BOLD,
	UNICODE_FANCY_ALPHABET_FRAKTUR,
	UNICODE_FANCY_ALPHABET_FRAKTUR_BOLD,
	UNICODE_FANCY_ALPHABET_REGIONAL,
	UNICODE_FANCY_ALPHABET_MONOSPACED,
	UNICODE_FANCY_ALPHABET_ITALIC,
	UNICODE_FANCY_ALPHABET_BOLD_ITALIC,
    UNICODE_FANCY_ALPHABET_BOLD,
	// Virtual alphabets come next to last
    UNICODE_FANCY_ALPHABET_RANSOM,
	// Keep this at the end of the list
    UNICODE_FANCY_ALPHABET_LAST,
};

void unicode_fancy_alphabet_cycle(void);
void unicode_fancy_alphabet_set(uint8_t alphabet);
uint8_t unicode_fancy_alphabet_get(void);

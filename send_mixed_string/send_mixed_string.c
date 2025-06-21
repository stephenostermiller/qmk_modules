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

#include "quantum.h"
#include "send_string.h"
#include "unicode.h"
#include "utf8.h"
#include "send_mixed_string.h"
#include "progmem.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

#ifdef KEY_OVERRIDE_ENABLE
    extern void clear_suppressed_override_mods(void);
#endif

void send_mixed_char(int32_t unicodeChar);

void send_mixed_char(int32_t unicodeChar) {
    if (unicodeChar >= 0) {
        switch(unicodeChar){
            case '\r': case '\n': case '\t': case ' ' ... '~':
                // Printable ASCII
                send_char((char)unicodeChar);
                break;
            default:
#               ifdef KEY_OVERRIDE_ENABLE
                    clear_suppressed_override_mods();
#               endif
                register_unicode(unicodeChar);
        }
    }
}

/**
 * Send keystrokes, possibly unicode strokes,
 * for a UTF-8 string.
 */
void send_mixed_string(const char *str) {
    if (!str) {
        return;
    }

    int32_t unicodeChar = 0;

    // While the string has contents
    while (*str) {
        // pick one unicode char off the front
        // and shorten the string to start after that char
        str = decode_utf8(str, &unicodeChar);
        send_mixed_char(unicodeChar);
    }
}

/**
 * Send keystrokes, possibly unicode strokes,
 * for a UTF-8 string stored in PROGMEM (flash memory).
 */
void send_mixed_string_P(const char *flashStr) {
    if (!flashStr) {
        return;
    }

    char buffer[5];
    char* bufferConsumed;
    int32_t unicodeChar = 0;

    // While the string has contents
    while (pgm_read_byte(flashStr)) {

        // Copy five bytes from the string
        // to the buffer. This may copy from beyond
        // the end of the flash string and that is OK.
        // It will include the termination null byte
        // in the middle in that case.
        // If the flash string is longer than 5 bytes,
        // the buffer may not be null terminated.
        // That is also OK because decoding utf-8
        // consumes at most 5 bytes.
        memcpy_P(buffer, flashStr, 5);

        // Pick one unicode char off the front
        // and get the pointer into the buffer from
        // after the bytes read from it.
        bufferConsumed = (char *)decode_utf8(buffer, &unicodeChar);

        // Advance the flash string pointer by the same
        // number of bytes that were read from the buffer
        flashStr += bufferConsumed - buffer;

        send_mixed_char(unicodeChar);
    }
}

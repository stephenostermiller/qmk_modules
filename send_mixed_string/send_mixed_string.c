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

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,1,0);

 void send_mixed_string(const char *str) {
    if (!str) {
        return;
    }

    // While the string has contents
    while (*str) {
        // pick one unicode char off the front
        // and shorten the string to start after that char
        int32_t unicodeChar = 0;
        str = decode_utf8(str, &unicodeChar);

        if (unicodeChar >= 0) {
            switch(unicodeChar){
                case '\r': case '\n': case '\t': case ' ' ... '~':
                    // Printable ASCII
                    send_char((char)unicodeChar);
                    break;
                default:
                    register_unicode(unicodeChar);
            }
        }
    }
}

#include "quantum.h"

// Use the callback for OS detection to set the unicode mode
bool process_detected_host_os_auto_unicode_os(os_variant_t detected_os) {

    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        default:
            break;
    }

    return true;
}

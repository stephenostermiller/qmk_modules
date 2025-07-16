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

#pragma once

// Get the mods from the keycode and create a mask with BOTH the left and right modifiers
#define EZOVRD_MODS_GET_MASK(kc) ((((kc) >> 8) & 0xF) | (((kc) >> 4) & 0xF0))

// Remove the bits from the mod_mask that match the modifiers on the keycode
#define EZOVRD_GET_SUPPRESS(mod_mask, replacement_key) (IS_QK_MODS((uint16_t)(replacement_key))?(mod_mask - (mod_mask & EZOVRD_MODS_GET_MASK(replacement_key))):mod_mask)

#define ezovrd_make_basic(mod_mask, trigger_key, replacement_key) \
    ((const key_override_t){.trigger_mods = mod_mask, .layers = ~0, .suppressed_mods = EZOVRD_GET_SUPPRESS(mod_mask, (replacement_key)), .options = ko_options_default, .negative_mod_mask = 0,\
    .custom_action  = ezovrd_key_event, .context = (void *)(replacement_key), .trigger = (trigger_key), .replacement = (replacement_key)})

bool ezovrd_key_event(bool pressed, void *context);

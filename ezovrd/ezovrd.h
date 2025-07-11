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

// Remove the mods from the keycode
#define EZOVRD_MODS_REMOVE(kc) (kc & 0xE0FF)

// Remove the bits from the mod_mask that match the modifiers on the keycode
#define EZOVRD_GET_SUPPRESS(trigger_key, replacement_key) (EZOVRD_MODS_GET_MASK(trigger_key) - (EZOVRD_MODS_GET_MASK(trigger_key) & EZOVRD_MODS_GET_MASK(replacement_key)))

#define ezovrd_make_basic(trigger_key, replacement_key) \
    ezovrd_make_with_layers(trigger_key, replacement_key, ~0)

#define ezovrd_make_with_layers(trigger_key, replacement_key, layers) \
    ezovrd_make_with_layers_and_negmods(trigger_key, replacement_key, layers, 0)

#define ezovrd_make_with_layers_and_negmods(trigger_key, replacement_key, layers, negative_mask) \
    ezovrd_make_with_layers_negmods_and_options(trigger_key, replacement_key, layers, negative_mask, ko_options_default)

#define ezovrd_make_with_layers_negmods_and_options(trigger_key, replacement_key, layer_mask, negative_mask, options_) \
    ((const key_override_t){.trigger_mods = EZOVRD_MODS_GET_MASK(trigger_key), .layers = (layer_mask), .suppressed_mods = EZOVRD_GET_SUPPRESS((trigger_key), (replacement_key)), .options = (options_), .negative_mod_mask = (negative_mask),\
    .custom_action  = (ezovrd_key_event), .context = (void *)(replacement_key), .trigger = EZOVRD_MODS_REMOVE(trigger_key), .replacement = (replacement_key)})

bool ezovrd_key_event(bool pressed, void *context);

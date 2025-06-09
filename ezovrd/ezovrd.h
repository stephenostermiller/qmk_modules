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

#define ezovrd_make_basic(trigger_mods, trigger_key, replacement_key) \
    ezovrd_make_with_layers(trigger_mods, trigger_key, replacement_key, ~0)

#define ezovrd_make_with_layers(trigger_mods, trigger_key, replacement_key, layers) \
    ezovrd_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, layers, 0)

#define ezovrd_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, layers, negative_mask) \
    ezovrd_make_with_layers_negmods_and_options(trigger_mods, trigger_key, replacement_key, layers, negative_mask, ko_options_default)


#define ezovrd_make_with_layers_negmods_and_options(trigger_mods_, trigger_key, replacement_key, layer_mask, negative_mask, options_) \
    ((const key_override_t){.trigger_mods = (trigger_mods_), .layers = (layer_mask), .suppressed_mods = (trigger_mods_), .options = (options_), .negative_mod_mask = (negative_mask),\
    .custom_action  = (ezovrd_key_event), .context = (void *)(replacement_key), .trigger = (trigger_key), .replacement = (replacement_key), .enabled = NULL})

bool ezovrd_key_event(bool pressed, void *context);

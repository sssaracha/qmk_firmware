/* Copyright 2019 imchipwood
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

#define _BASE     0
#define _SUB      1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
        BASE LAYER
   /-----------------------------------------------------`
   |             |   prv   |  play   |  next   |  stop   |
   |             |---------|---------|---------|---------|
   |             | LGAC_1  | LGAC_2  | LGAC_3  | LGAC_4  |
   |             |---------|---------|---------|---------|
   |             | LGAC_5  | LGAC_6  | LGAC_7  | LGAC_8  |
   |-------------|---------|---------|---------|---------|
   |     mute    | TT(SUB) | LGAC_9  | LGAC_0  | win-l   |
   \-----------------------------------------------------'
  */
  [_BASE] = LAYOUT(KC_LCTL, KC_TAB, KC_BSPC, KC_ESC, LCAG(KC_4), LCAG(KC_3), LCAG(KC_2), LCAG(KC_1), LCAG(KC_8), LCAG(KC_7), LCAG(KC_6), LCAG(KC_5), KC_MUTE, LGUI(KC_L), LCAG(KC_0), LCAG(KC_9), TT(1)),
  /*
        SUB LAYER
   /-----------------------------------------------------`
   |             | Trans   | Trans   | Trans   | Trans   |
   |             |---------|---------|---------|---------|
   |             | LGAC_A  | LGAC_B  | LGAC_C  | LGAC_D  |
   |             |---------|---------|---------|---------|
   |             | LGAC_E  | LGAC_F  | LGAC_G  | LGAC_H  |
   |-------------|---------|---------|---------|---------|
   |  Trans      | Trans   | LGAC_I  | LGAC_J  | Trans   |
   \-----------------------------------------------------'
  */
  [_SUB] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCAG(KC_D), LCAG(KC_C), LCAG(KC_B), LCAG(KC_A), LCAG(KC_H), LCAG(KC_G), LCAG(KC_F), LCAG(KC_E), KC_TRNS, KC_TRNS, LCAG(KC_J), LCAG(KC_I), KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
*/
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {
 
}

void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Cusotom behavior:
   *    main layer:
   *       CW: volume up
   *      CCW: volume down
   *    sub layer:
   *       CW: volume up
   *      CCW: volume down
   */
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        // main layer - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

      case _SUB:
        // sub layer - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

      default:
        // any other layer (shouldn't exist..) - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}

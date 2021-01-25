#include "ultipad.h"

#define _BASE     0
#define _SUB      1
#define _SUB2     2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
		KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, 
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_MUTE, 
		KC_P7, KC_P8, KC_P9, 
		KC_P4, KC_P5, KC_P6, KC_PPLS, 
		KC_P1, KC_P2, KC_P3, 
		KC_P0, KC_PDOT, KC_PENT, TT(1), TT(2)),

  [_SUB] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		LCAG(KC_1), LCAG(KC_2), LCAG(KC_3), 
		LCAG(KC_4), LCAG(KC_5), LCAG(KC_6), KC_TRNS, 
		LCAG(KC_7), LCAG(KC_8), LCAG(KC_9), 
		LCAG(KC_0), KC_TRNS, RESET, KC_TRNS, KC_TRNS),

  [_SUB2] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		LCAG(KC_A), LCAG(KC_B), LCAG(KC_C), 
		LCAG(KC_D), LCAG(KC_E), LCAG(KC_F), KC_TRNS, 
		LCAG(KC_G), LCAG(KC_H), LCAG(KC_I), 
		LCAG(KC_J), KC_TRNS, RESET, KC_TRNS, KC_TRNS),
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

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _BASE:
      writePinLow(LAYER_INDICATOR_LED_0);
      writePinLow(LAYER_INDICATOR_LED_1);
      break;
    case _SUB:
      writePinHigh(LAYER_INDICATOR_LED_1);
      break;
    case _SUB2:
      writePinHigh(LAYER_INDICATOR_LED_0);
      break;
  }
  return state;
}

void keyboard_post_init_user() {
  // Customise these values to desired behaviour
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
  setPinOutput(LAYER_INDICATOR_LED_0);
  setPinOutput(LAYER_INDICATOR_LED_1);
}

void shutdown_user() {
  
}


void matrix_init_user() {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {
    DDRB |= (1 << 3); 

    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTB |= (1 << 3);
    } else {
        PORTB &= ~(1 << 3);
    }
}


void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Cusotom behavior:
   *    main layer:
   *       CW: volume up
   *      CCW: volume down
   *    sub layer:
   *       CW: next media track
   *      CCW: prev media track
   *    debug layer:
   *       CW: brightness up
   *      CCW: brightness down
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
        // sub layer - next track (CW) and previous track (CCW)
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

      case _SUB2:
        // debug layer - brightness up (CW) and brightness down (CCW)
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

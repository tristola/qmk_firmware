#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_swedish.h"
#include "keymap_german.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

uint16_t parenthesis_open[2] = { KC_LSFT, KC_8 }; // (
uint16_t parenthesis_close[2] = { KC_LSFT, KC_9 }; // )
uint16_t curly_open[3] = { KC_RALT, KC_LSFT, KC_8 }; // {
uint16_t curly_close[3] = { KC_RALT, KC_LSFT, KC_9 }; // }

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};
enum {
  TD_OPEN = 0,
  TD_CLOSE
};

int REGISTER_CODES = 1;
int UNREGISTER_CODES = 2;

void handleCodes (uint16_t arr[], int size, int handler) {
  for (int i = 0; i < size; ++i) {
      if (handler == REGISTER_CODES) {
        register_code(arr[i]);
      }
      if (handler == UNREGISTER_CODES) {
        unregister_code(arr[i]);
      }
   }
}

void open_paren_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    handleCodes(parenthesis_open, 2, REGISTER_CODES );
  }
  if (state->count == 2) {
    handleCodes(curly_open, 3, REGISTER_CODES );
  }
}

void open_paren_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    handleCodes(parenthesis_open, 2, UNREGISTER_CODES );
  }
  if (state->count == 2) {
    handleCodes(curly_open, 3, UNREGISTER_CODES );
  }
}

void close_paren_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    handleCodes(parenthesis_close, 2, REGISTER_CODES );
  }
  if (state->count == 2) {
    handleCodes(curly_close, 3, REGISTER_CODES );
  }
}

void close_paren_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    handleCodes(parenthesis_close, 2, UNREGISTER_CODES );
  }
  if (state->count == 2) {
    handleCodes(curly_close, 3, UNREGISTER_CODES );
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_OPEN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, open_paren_finished, open_paren_reset),
  [TD_CLOSE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, close_paren_finished, close_paren_reset)
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |  >   |           |  ä   |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  {   |           |  }   |   Y  |   U  |   I  |   O  |   P  |   -    |
 * |--------+------+------+------+------+------|  (   |           |  )   |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  [   |           |  ]   |   N  |   M  |   ,  |   .  |  /   | LShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CMD  |  LAlt |  F5  |  F6  |  F11 |                                       | Left | Down |  Up  | Right|  RAlt  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  L1  | Prev |       | Vol+ |  L2  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Play |       | Vol- |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | Next |       | Mute |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_RBRACKET,
        KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TD(TD_OPEN),
        KC_LCTL,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   DE_LBRC,
        KC_LWIN,       KC_LALT,        KC_F5,  KC_F6,  KC_F11,
                                                   TG(SYMB),  KC_MPRV,
                                                              KC_MPLY,
                                               KC_SPC,KC_BSPC,KC_MNXT,
        // right hand
             KC_NONUS_BSLASH,         KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_EQL,
             TD(TD_CLOSE),  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_MINS,
                              KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),NO_AE,
             DE_RBRC,         KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_LSFT,
                              KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_RALT,
             KC_VOLU,        TG(MDIA),
             KC_VOLD,
             KC_MUTE,KC_TAB, KC_ENT

    ),
/* Keymap 1: Symbol Layer´´´`´≤<>≥<§•§
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  L1  |      |       |Toggle|  L2  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  DE_LCBR,DE_RCBR,DE_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, DE_LPRN,DE_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,DE_LBRC,DE_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       TG(SYMB),KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_PGUP, TG(MDIA),
       KC_PGDN,
       MEH(KC_PGUP), RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  MsUp    |  |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   MsLef   ||MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

/*
 * Har's 36 Key Layout
 * 4/26/2025
 *
 * Rebuilding from scratch
*/

#include QMK_KEYBOARD_H
#include "quantum/tap_dance.h"

// Define layers
#define Alpha   0
#define Sym     1
#define Fcn     2

// Define modifier row keys
#define KC_HSU  LGUI_T(KC_U)
#define KC_HSE  LSFT_T(KC_E)
#define KC_HSO  LCTL_T(KC_O)
#define KC_HSA  LALT_T(KC_A)

#define KC_HSH  LGUI_T(KC_H)
#define KC_HST  LSFT_T(KC_T)
#define KC_HSN  LCTL_T(KC_N)
#define KC_HSS  LALT_T(KC_S)

// Define thumb layer keys
#define KC_TB3L LT(MO(Fcn),KC_ESC)
#define KC_TB2L LT(MO(Sym),KC_BSPC)

#define KC_TB2R LT(MO(Sym),KC_SPC)
#define KC_TB3R LT(MO(Fcn),KC_CAPS)

#define HOMEROW_TAPPING_TERM 150

// Current semantic version number
const char* ver = "3.0.0";

// Create my own 'safe' keycode to run my script
enum custom_keycodes {
  KC_VER = SAFE_RANGE,
};

enum {
  TD_SEMI_COLON,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_COLN,KC_SCLN),
};

#define KC_HSSC TD(TD_SEMI_COLON)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Alpha] = LAYOUT_split_3x5_3(
    KC_QUOT,  KC_COMM,  KC_DOT,  KC_P,    KC_Y,                           KC_F,     KC_G,   KC_C,   KC_R,   KC_L,
    KC_HSA,   KC_HSO,   KC_HSE,  KC_HSU,  KC_I,                           KC_D,     KC_HSH, KC_HST, KC_HSN, KC_HSS,
    KC_HSSC,  KC_Q,     KC_J,    KC_K,    KC_X,                           KC_B,     KC_M,   KC_W,   KC_V,   KC_Z,
                                 KC_TB3L, KC_TB2L,  KC_ENT,     KC_TAB,   KC_TB2R,  KC_TB3R

  ),

    [Sym] = LAYOUT_split_3x5_3(
      KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_LPRN,                        KC_RPRN,  KC_7,   KC_8,   KC_9, KC_VER,
      KC_EQUAL,KC_DLR,  KC_PERC, KC_CIRC, KC_LBRC,                        KC_RBRC,  KC_4,   KC_5,   KC_6, KC_MINUS,
      KC_BSLS, KC_AMPR, KC_ASTR, KC_SLSH, KC_LCBR,                        KC_RCBR,  KC_1,   KC_2,   KC_3, KC_0,
                                 _______, _______, _______,    _______,   _______,  _______
  ),

    [Fcn] = LAYOUT_split_3x5_3(
      KC_PGUP, KC_HOME, KC_UP,   KC_END,   KC_INSERT,                      KC_VOLU, KC_F7,  KC_F8,  KC_F9, KC_F10,
      KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DELETE,                      KC_VOLD, KC_F4,  KC_F5,  KC_F6, KC_F11,
      KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,  XXXXXXX,                        KC_MUTE, KC_F1,  KC_F2,  KC_F3, KC_F12,
                                 _______, _______, _______,    _______,   _______,  _______
  )

};

// Customize tapping speed here
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Home row mods
        case KC_HSU:
        case KC_HSE:
        case KC_HSO:
        case KC_HSA:
        case KC_HSH:
        case KC_HST:
        case KC_HSN:
        case KC_HSS:
            return 150; // shorter tapping term for home row mods (in milliseconds)

        default:
            return TAPPING_TERM; // fallback to the default
    }
}

// Print the version number
int print_version(void) {
  int ctr = 0;
  for (int i = 0; ver[i] != '\0'; i++) {
    ctr++;
    char c = ver[i];

    switch(c) {
      case '0': tap_code16(KC_0); break;
      case '1': tap_code16(KC_1); break;
      case '2': tap_code16(KC_2); break;
      case '3': tap_code16(KC_3); break;
      case '4': tap_code16(KC_4); break;
      case '5': tap_code16(KC_5); break;
      case '6': tap_code16(KC_6); break;
      case '7': tap_code16(KC_7); break;
      case '8': tap_code16(KC_8); break;
      case '9': tap_code16(KC_9); break;
      case '.': tap_code16(KC_DOT); break;
      default: break;
    }

    wait_ms(50);
  }
  return ctr;
}

// Print a message
void show_version(void) {
  tap_code16(KC_CAPS);
  tap_code16(KC_H);
  tap_code16(KC_CAPS);
  tap_code16(KC_A);
  tap_code16(KC_R);
  tap_code16(KC_QUOT);
  tap_code16(KC_S);
  tap_code16(KC_SPC);
  tap_code16(KC_CAPS);
  tap_code16(KC_L);
  tap_code16(KC_CAPS);
  tap_code16(KC_A);
  tap_code16(KC_Y);
  tap_code16(KC_O);
  tap_code16(KC_U);
  tap_code16(KC_T);
  tap_code16(KC_SPC);
  tap_code16(KC_V);
  tap_code16(KC_E);
  tap_code16(KC_R);
  tap_code16(KC_COLON);
  tap_code16(KC_SPC);

  int digits = print_version();
  int total = 18 + digits;

  wait_ms(3000);

  // erase it all
  for (int i = 0; i < total; i++) {
    tap_code16(KC_BSPC);
    wait_ms(100);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case KC_VER:
        show_version();
        return false;
    }
  }
  return true;
}


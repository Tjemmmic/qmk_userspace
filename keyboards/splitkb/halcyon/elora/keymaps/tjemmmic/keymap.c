// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _LAYER_COUNT,  // Keep last: evaluates to the number of layers.
};

enum custom_keycodes {
    LAYER_UP = SAFE_RANGE,
    LAYER_DN,
    BOOTMENU,  // For holding to send F11 repeatedly (to access bootloader menu for dual-booting).
    BOOTHOLD,  // Must be held BOOT_ARM_MS before it enters the bootloader.
};

#define SYM      MO(_SYM)
#define NAV      TT(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_CAPS MT(MOD_LCTL, KC_CAPS)



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  `  ~  |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Enter |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Cap|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  '  "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | LGUI |Lay-Dn|  |Lay-Up|F-keys|   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | ESC  |Adjust| ALT  | Space| Nav  |  | Sym  | Space| [  { | ]  } |Delete|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_GRV  , KC_1 ,  KC_2   ,  KC_3  ,   KC_4 ,   KC_5 ,                                           KC_6   , KC_7   ,   KC_8  ,   KC_9  ,   KC_0 , KC_BSPC ,
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                           KC_Y   , KC_U   ,   KC_I  ,   KC_O  ,   KC_P , KC_ENT ,
     CTL_CAPS, KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                           KC_H   , KC_J   ,   KC_K  ,   KC_L  , KC_SCLN, KC_QUOT  ,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LGUI,LAYER_DN ,     LAYER_UP, FKEYS  , KC_N   , KC_M   , KC_COMM ,  KC_DOT , KC_SLSH, KC_RSFT ,
                                KC_ESC , ADJUST , KC_LALT, KC_SPC , NAV     ,     SYM     , KC_SPC , KC_LBRC, KC_RBRC, KC_DEL
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |VolUp |  End |   ↑  | Home | PgUp |                              | PgUp | Home |   ↑  | End  | VolUp| Enter  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |VolDn |  ←   |   ↓  |   →  | PgDn |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |VolMut|M Next|M Play|M Prev| Pause|      | LDN  |  | LUP  |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      KC_ESC , _______, _______, _______, _______, _______ ,                                              _______, _______, _______, _______, _______, _______,
      _______, KC_VOLU, KC_END , KC_UP  , KC_HOME, KC_PGUP ,                                              KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_VOLU, KC_ENT ,
      _______, KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN ,                                              KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS ,
      _______, KC_MUTE, KC_MNXT, KC_MPLY, KC_MPRV, KC_PAUSE, _______, LAYER_DN ,    LAYER_UP , _______ , KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______ , _______, _______  ,    _______  , _______ , _______ , _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   | LDN  |  | LUP  |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                              KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, LAYER_DN ,    LAYER_UP , KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______  ,    _______  , _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      | LDN  |  | LUP  |      |      |      |      |      |      | BTHLD  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______,LAYER_DN,LAYER_UP, _______, _______, _______, _______, _______, _______,BOOTHOLD,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |BTHLD |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |BT_MNU|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      | LDN  |  | LUP  |      |      | SAD  | HUD  | VAD  | RMOD |  XXX   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______,BOOTHOLD,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______,BOOTMENU, _______, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
      _______, _______, _______, _______, _______, _______,_______,LAYER_DN,LAYER_UP, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, XXXXXXX,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
//
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

#if defined (HALCYON_ENABLE)
const uint16_t left_halcyon_buttons[10][5] = {
    [_QWERTY] =     { KC_MUTE, _______, _______, _______, _______ },
    [_NAV] =        { _______, _______, _______, _______, _______ },
    [_SYM] =        { _______, _______, _______, _______, _______ },
    [_FUNCTION] =   { _______, _______, _______, _______, _______ },
    [_ADJUST] =     { _______, _______, _______, _______, _______ }
};

const uint16_t right_halcyon_buttons[10][5] = {
    [_QWERTY] =     { KC_MUTE, _______, _______, _______, _______ },
    [_NAV] =        { _______, _______, _______, _______, _______ },
    [_SYM] =        { _______, _______, _______, _______, _______ },
    [_FUNCTION] =   { _______, _______, _______, _______, _______ },
    [_ADJUST] =     { _______, _______, _______, _______, _______ }
};
#endif

// Boot menus often ignore USB auto-repeat, so the key has to be tapped rather
// than held. tap_code() alone will not do: TAP_CODE_DELAY defaults to 0, and a
// press with no measurable duration is frequently missed by firmware.
#define BOOT_KEY       KC_F11
#define BOOT_REPEAT_MS 60  // Gap between taps. Raise this first if it misses.
#define BOOT_HOLD_MS   15  // How long each tap is held down.

static bool     boot_spam  = false;
static uint16_t boot_timer = 0;

// Entering the bootloader takes a deliberate hold, so a stray press while a
// layer is locked cannot drop the keyboard offline mid-typing.
#define BOOT_ARM_MS 2000

static bool     boot_arming    = false;
static uint16_t boot_arm_timer = 0;

// Step the active layer forwards or backwards, wrapping at both ends.
// layer_move() leaves exactly one layer active, so transparent keys on the
// target layer resolve against the default layer.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Acts on both edges, so it sits above the press-only guard below.
    if (keycode == BOOTMENU) {
        boot_spam = record->event.pressed;
        if (boot_spam) {
            tap_code_delay(BOOT_KEY, BOOT_HOLD_MS);
            boot_timer = timer_read();
        }
        return false;
    }

    // Also both edges: releasing early must disarm it.
    if (keycode == BOOTHOLD) {
        boot_arming = record->event.pressed;
        if (boot_arming) {
            boot_arm_timer = timer_read();
        }
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    uint8_t current = get_highest_layer(layer_state | default_layer_state);

    switch (keycode) {
        case LAYER_UP:
            layer_move((current + 1) % _LAYER_COUNT);
            return false;
        case LAYER_DN:
            layer_move((current + _LAYER_COUNT - 1) % _LAYER_COUNT);
            return false;
    }
    return true;
}

// halcyon.c owns housekeeping_task_kb but calls through to this on its last
// line, so the repeat runs on every scan while BOOTMENU is held.
void housekeeping_task_user(void) {
    if (boot_spam && timer_elapsed(boot_timer) >= BOOT_REPEAT_MS) {
        tap_code_delay(BOOT_KEY, BOOT_HOLD_MS);
        boot_timer = timer_read();
    }

    if (boot_arming && timer_elapsed(boot_arm_timer) >= BOOT_ARM_MS) {
        boot_arming = false;  // Do not re-fire if the reset takes a moment.
        reset_keyboard();
    }
}

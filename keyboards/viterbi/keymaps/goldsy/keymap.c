#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _NUM_LYR 3
#define _FN4_LYR 4
#define _NAV_LYR 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAVLYR,
  FN4LYR,
  NUMLYR,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define ___x___ KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_NAV  NAVLYR
#define KC_FN4  FN4LYR
#define KC_NUM  NUMLYR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |   `  |   -  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   =  | Bksp |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Tab  |   [  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   ]  |   \  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Esc  |NavLyr|   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   '  |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   (  | Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  | Shift|   )  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl | FN4  | Hyper| GUI  | Alt  |LOWER |NumLyr|      |SPACE |RAISE | Alt  | GUI  | Hyper| Fn4  | Ctrl |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = KC_KEYMAP(
  //,--------+------+-------+----+----+----+----.    ,----+----+----+----+-------+------+--------.
     GRV     , MINS , 1     , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0     , EQL  , BSPC   ,
  //|--------+------+-------+----+----+----+----|    |----+----+----+----+-------+------+--------|
     TAB     , LBRC , Q     , W  , E  , R  , T  ,      Y  , U  , I  , O  , P     , RBRC , BSLS   ,
  //|--------+------+-------+----+----+----+----|    |----+----+----+----+-------+------+--------|
     ESC     , NAV  , A     , S  , D  , F  , G  ,      H  , J  , K  , L  , SCLN  , QUOT , ENT    ,
  //|--------+------+-------+----+----+----+----|    |----+----+----+----+-------+------+--------|
     LPRN    , LSFT , Z     , X  , C  , V  , B  ,      N  , M  ,COMM,DOT , SLSH  , RSFT , RPRN   ,
  //|--------+------+-------+----+----+----+----|    |----+----+----+----+-------+------+--------|
     LCTRL   , AJST , HYPR  ,LGUI,LALT,LOWR,NUM ,     SPC ,RASE,RALT,RGUI, HYPR  , AJST , RCTRL
  //`--------+------+-------+----+----+----+----'    `----+----+----+----+-------+------+--------'
  ),

/* LOWER
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  |      | DEL  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   !  |   @  |   #  |   $  |   %  |      |   ^  |   &  |   *  |   (  |   )  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   _  |   +  |   {  |   }  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | NEXT | VOL- | VOL+ | PLAY |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,TILD, F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,    ,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     UNDS,    ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PLUS,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,PLUS,LCBR,RCBR,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* RAISE
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F11 |  F12 |  F13 |  F14 |  F15 |      |  F16 |  F17 |  F18 |  F19 | F20  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   -  |   =  |   [  |   ]  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO # |ISO / |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | NEXT | VOL- | VOL+ | PLAY |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,TILD, F11, F12, F13, F14, F15,      F16, F17, F18, F19, F20,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     UNDS,    , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PLUS,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,PLUS,LBRC,RBRC,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,NUHS,NUBS,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* NUMBER PAD LAYER
 * ,--------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |   #   |   $  |   %   |      |   (   |   7  |   8  |   9  |   )   |   =  |      |
 * |------+------+------+------+-------+------+-------|      |-------+------+------+------+-------+------+------|
 * | TAB  |      |      |      |   E   |      |       |      |       |   4  |   5  |   6  |   -   |   /  |      |
 * |------+------+------+------+-------+------+-------|      |-------+------+------+------+-------+------+------|
 * | ESC  |      |  A   |      |   D   |   F  |       |      |       |   1  |   2  |   3  |   +   |   *  |      |
 * |------+------+------+------+-------+------+-------|      |-------+------+------+------+-------+------+------|
 * |      |      |      |      |   C   |      |   B   |      |       |   0  |   ,  |   .  | ENTER |      |      |
 * |------+------+------+------+-------+------+-------|      |-------+------+------+------+-------+------+------|
 * |      |      |      |      |       |      |       |      | SPACE |      |      |      |       |      |      |
 * `--------------------------------------------------'      `--------------------------------------------------'
 */
  [_NUM_LYR] = KC_KEYMAP(
  //,----+----+----+----+-------+------+-------.    ,-------+----+-------+------+-------+-------+----.
         ,    ,    ,    , HASH  , DLR  , PERC  ,      LPRN  , 7  ,   8   ,  9   , RPRN  , EQL   ,    ,
  //|----+----+----+----+-------+------+-------|    |-------+----+-------+------+-------+-------+----|
     TAB ,    ,    ,    ,   E   ,      ,       ,            , 4  ,   5   ,  6   , MINS  , SLSH  ,    ,
  //|----+----+----+----+-------+------+-------|    |-------+----+-------+------+-------+-------+----|
     ESC ,    , A  ,    ,   D   ,  F   ,       ,            , 1  ,   2   ,  3   , PLUS  , ASTR  ,    ,
  //|----+----+----+----+-------+------+-------|    |-------+----+-------+------+-------+-------+----|
         ,    ,    ,    ,   C   ,      ,   B   ,            , 0  , COMM  , DOT  , ENT   ,       ,    ,
  //|----+----+----+----+-------+------+-------|    |-------+----+-------+------+-------+-------+----|
         ,    ,    ,    ,       ,      , NUM   ,      SPC   ,    ,       ,      ,       ,       ,                       
  //`----+----+----+----+-------+------+-------'    `-------+----+-------+------+-------+-------+----'
  ),



  /* Directional navigation layer
   *
   *        Large movements -----/````````````````````\   /````````````````````\----- Vim-style arrow keys
   *          ,-----------------------------------------------------------------------------------.
   *          |     |     |     |     |     |     |     |     |     |     |     |     |     | Del |
   *          |-----------------------------------------------------------------------------------|
   *          |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
   *          |-----------------------------------------------------------------------------------|
   *          |     |     |     |Home |PgUp |PgDn | End |Left |Down | Up  |Right|     |     |     |
   *          |-----------------------------------------------------------------------------------|
   *          |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
   *          |-----------------------------------------------------------------------------------|
   *          |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
   *          `-----------------------------------------------------------------------------------'
   */
  [_NAV_LYR] = KEYMAP(
    ___x___,___x___,___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_DEL,
    ___x___,___x___,___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,
    _______, KC_NAV,_______, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, _______, _______, _______,
    _______,___x___,___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______,
    _______,___x___,_______, _______, _______, ___x___, ___x___, ___x___, ___x___, _______, _______, _______, ___x___, _______
  ),

  [_ADJUST] = KEYMAP(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
    _______, _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______, \
    _______, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
#endif
                persistent_default_layer_set(1UL<<_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
	case NUMLYR:
	    if (record->event.pressed) {
		    layer_on(_NUM_LYR);
		    update_tri_layer(_LOWER, _RAISE, _NUM_LYR);
	    } else {
		    layer_off(_NUM_LYR);
		    update_tri_layer(_LOWER, _RAISE, _NUM_LYR);
	    }
	    return false;
	    break;
	case NAVLYR:
	    if (record->event.pressed) {
		    layer_on(_NAV_LYR);
		    update_tri_layer(_LOWER, _RAISE, _NAV_LYR);
	    } else {
		    layer_off(_NAV_LYR);
		    update_tri_layer(_LOWER, _RAISE, _NAV_LYR);
	    }
	    return false;
	    break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}


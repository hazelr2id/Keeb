#include QMK_KEYBOARD_H
#include "LUFA/Drivers/USB/USB.h"

enum my_layers {
	_HAZEL,
	_QWERTY,
	_LOWER,
	_RAISE,
	_ADJUST,
};

enum my_keycodes {
	LANG1 = SAFE_RANGE,
	LANG2,
	L0CK,
};

#define LOWER LT(_LOWER, KC_SPC)
#define RAISE OSL(_RAISE)
#define DOTADJ LT(_ADJUST, KC_DOT)
#define ESCADJ LT(_ADJUST, KC_ESC)
#define TMUX C(KC_B)

static bool usb_detached = false;

static void usb_soft_detach(void) {
	cli();
	USB_Detach();
	USB_Disable();
	sei();
	wait_ms(1000);
	usb_detached = true;
}

static void usb_soft_attach(void) {
	cli();
	USB_Init();
	USB_Attach();
	sei();

	uint16_t t = 0;
	while (USB_DeviceState != DEVICE_STATE_Configured && t < 2000) {
		wait_ms(10);
		t += 10;
	}
	if (USB_DeviceState != DEVICE_STATE_Configured) {
		cli();
		USB_Disable();
		USB_Init();
		USB_Attach();
		sei();
	}
	usb_detached = false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_HAZEL] = LAYOUT(
			KC_X,    KC_F,    KC_U,    KC_B,    L0CK,                      L0CK,    KC_M,    KC_O,    KC_L,    KC_W,
			KC_A,    KC_T,    KC_I,    KC_N,    KC_K,                      KC_Q,    KC_S,    KC_E,    KC_R,    KC_C,
			KC_Z,    KC_V,    KC_Y,    KC_P,    LANG1,   _______, _______, LANG2,   KC_D,    KC_J,    KC_H,    KC_G,
			OS_LGUI, OS_LCTL, OS_LALT, KC_BSPC, LOWER,   _______, _______, RAISE,   OS_RSFT, OS_RALT, OS_RCTL, OS_RGUI
			),

	[_QWERTY] = LAYOUT(
			KC_Q,    KC_W,    KC_E,    KC_R,    L0CK,                      L0CK,    KC_Y,    KC_U,    KC_I,    KC_O,
			KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_T,    KC_H,    KC_J,    KC_K,    KC_L,
			KC_Z,    KC_X,    KC_C,    KC_V,    LANG1,   _______, _______, LANG2,   KC_B,    KC_N,    KC_M,    KC_P, 
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	[_LOWER] = LAYOUT(
			KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                   KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
			KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,                   KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
			KC_INS,  KC_CAPS, TMUX,    KC_TAB,  _______, _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_0,
			_______, _______, _______, _______, _______, _______, _______, DOTADJ,  CW_TOGG, _______, _______, _______
			),

	[_RAISE] = LAYOUT(
			KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_DLR,                    KC_CIRC, KC_BSLS, KC_QUOT, KC_DQT,  KC_PERC,
			KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_AMPR,                   KC_PIPE, KC_UNDS, KC_COMM, KC_DOT,  KC_ENT,
			KC_LT,   KC_SLSH, KC_MINS, KC_GT,   KC_EXLM, _______, _______, KC_QUES, KC_EQL,  KC_PLUS, KC_ASTR, KC_HASH,
			_______, _______, _______, KC_DEL,  ESCADJ,  _______, _______, _______, _______, _______, _______, _______
			),

	[_ADJUST] = LAYOUT(
			_______, _______, _______, _______, _______,                   KC_F15,  KC_F7,   KC_F8,   KC_F9,   KC_F12,
			KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, _______,                   KC_F14,  KC_F4,   KC_F5,   KC_F6,   KC_F11,
			_______, KC_BRID, KC_BRIU, KC_MPLY, _______, _______, _______, KC_F13,  KC_F1,   KC_F2,   KC_F3,   KC_F10,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(record->event.pressed) {
		switch(keycode) {
			case LANG1:
				tap_code16(C(KC_SPC));
			case LANG2:
				if (get_highest_layer(default_layer_state) == _HAZEL)
					set_single_persistent_default_layer(_QWERTY);
				else
					set_single_persistent_default_layer(_HAZEL);
				return false;
			case L0CK:
				if (!usb_detached) usb_soft_detach();
				else               usb_soft_attach();
				return false;
		}
	}
	return true;
}

const uint16_t PROGMEM combo1[] = {KC_QUOT, KC_DQT, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_SLSH, KC_MINS, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_PLUS, KC_ASTR, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo1, KC_GRV),
    COMBO(combo2, KC_TILDE),
    COMBO(combo3, KC_AT),
};

#pragma once

// -- external --
// cmap(inclusion(that is done later) does type definition)

// -- system --
#include <stdbool.h>
#include <stdint.h>

// - SDL code start -

/*
 * The following code has been taken from SDL and then repurposed for
 * Rodeo Kit. Many of the original comments have been kept. The following
 * notice was with the original code:
 */

/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \brief The SDL(now Rodeo Kit) keyboard scancode representation.
 *
 *  Values of this type are used to represent keyboard keys, among other places
 *  in the \link rodeo_input_Keysym::scancode key.keysym.scancode \endlink field of the
 *  rodeo_input_Event structure.
 *
 *  The values in this enumeration are based on the USB usage page standard:
 *  https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 */
typedef enum
{
    rodeo_input_binary_scancode_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    rodeo_input_binary_scancode_A = 4,
    rodeo_input_binary_scancode_B = 5,
    rodeo_input_binary_scancode_C = 6,
    rodeo_input_binary_scancode_D = 7,
    rodeo_input_binary_scancode_E = 8,
    rodeo_input_binary_scancode_F = 9,
    rodeo_input_binary_scancode_G = 10,
    rodeo_input_binary_scancode_H = 11,
    rodeo_input_binary_scancode_I = 12,
    rodeo_input_binary_scancode_J = 13,
    rodeo_input_binary_scancode_K = 14,
    rodeo_input_binary_scancode_L = 15,
    rodeo_input_binary_scancode_M = 16,
    rodeo_input_binary_scancode_N = 17,
    rodeo_input_binary_scancode_O = 18,
    rodeo_input_binary_scancode_P = 19,
    rodeo_input_binary_scancode_Q = 20,
    rodeo_input_binary_scancode_R = 21,
    rodeo_input_binary_scancode_S = 22,
    rodeo_input_binary_scancode_T = 23,
    rodeo_input_binary_scancode_U = 24,
    rodeo_input_binary_scancode_V = 25,
    rodeo_input_binary_scancode_W = 26,
    rodeo_input_binary_scancode_X = 27,
    rodeo_input_binary_scancode_Y = 28,
    rodeo_input_binary_scancode_Z = 29,

    rodeo_input_binary_scancode_1 = 30,
    rodeo_input_binary_scancode_2 = 31,
    rodeo_input_binary_scancode_3 = 32,
    rodeo_input_binary_scancode_4 = 33,
    rodeo_input_binary_scancode_5 = 34,
    rodeo_input_binary_scancode_6 = 35,
    rodeo_input_binary_scancode_7 = 36,
    rodeo_input_binary_scancode_8 = 37,
    rodeo_input_binary_scancode_9 = 38,
    rodeo_input_binary_scancode_0 = 39,

    rodeo_input_binary_scancode_RETURN = 40,
    rodeo_input_binary_scancode_ESCAPE = 41,
    rodeo_input_binary_scancode_BACKSPACE = 42,
    rodeo_input_binary_scancode_TAB = 43,
    rodeo_input_binary_scancode_SPACE = 44,

    rodeo_input_binary_scancode_MINUS = 45,
    rodeo_input_binary_scancode_EQUALS = 46,
    rodeo_input_binary_scancode_LEFTBRACKET = 47,
    rodeo_input_binary_scancode_RIGHTBRACKET = 48,
    rodeo_input_binary_scancode_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    rodeo_input_binary_scancode_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate rodeo_input_binary_scancode_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    rodeo_input_binary_scancode_SEMICOLON = 51,
    rodeo_input_binary_scancode_APOSTROPHE = 52,
    rodeo_input_binary_scancode_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    rodeo_input_binary_scancode_COMMA = 54,
    rodeo_input_binary_scancode_PERIOD = 55,
    rodeo_input_binary_scancode_SLASH = 56,

    rodeo_input_binary_scancode_CAPSLOCK = 57,

    rodeo_input_binary_scancode_F1 = 58,
    rodeo_input_binary_scancode_F2 = 59,
    rodeo_input_binary_scancode_F3 = 60,
    rodeo_input_binary_scancode_F4 = 61,
    rodeo_input_binary_scancode_F5 = 62,
    rodeo_input_binary_scancode_F6 = 63,
    rodeo_input_binary_scancode_F7 = 64,
    rodeo_input_binary_scancode_F8 = 65,
    rodeo_input_binary_scancode_F9 = 66,
    rodeo_input_binary_scancode_F10 = 67,
    rodeo_input_binary_scancode_F11 = 68,
    rodeo_input_binary_scancode_F12 = 69,

    rodeo_input_binary_scancode_PRINTSCREEN = 70,
    rodeo_input_binary_scancode_SCROLLLOCK = 71,
    rodeo_input_binary_scancode_PAUSE = 72,
    rodeo_input_binary_scancode_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    rodeo_input_binary_scancode_HOME = 74,
    rodeo_input_binary_scancode_PAGEUP = 75,
    rodeo_input_binary_scancode_DELETE = 76,
    rodeo_input_binary_scancode_END = 77,
    rodeo_input_binary_scancode_PAGEDOWN = 78,
    rodeo_input_binary_scancode_RIGHT = 79,
    rodeo_input_binary_scancode_LEFT = 80,
    rodeo_input_binary_scancode_DOWN = 81,
    rodeo_input_binary_scancode_UP = 82,

    rodeo_input_binary_scancode_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    rodeo_input_binary_scancode_KP_DIVIDE = 84,
    rodeo_input_binary_scancode_KP_MULTIPLY = 85,
    rodeo_input_binary_scancode_KP_MINUS = 86,
    rodeo_input_binary_scancode_KP_PLUS = 87,
    rodeo_input_binary_scancode_KP_ENTER = 88,
    rodeo_input_binary_scancode_KP_1 = 89,
    rodeo_input_binary_scancode_KP_2 = 90,
    rodeo_input_binary_scancode_KP_3 = 91,
    rodeo_input_binary_scancode_KP_4 = 92,
    rodeo_input_binary_scancode_KP_5 = 93,
    rodeo_input_binary_scancode_KP_6 = 94,
    rodeo_input_binary_scancode_KP_7 = 95,
    rodeo_input_binary_scancode_KP_8 = 96,
    rodeo_input_binary_scancode_KP_9 = 97,
    rodeo_input_binary_scancode_KP_0 = 98,
    rodeo_input_binary_scancode_KP_PERIOD = 99,

    rodeo_input_binary_scancode_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    rodeo_input_binary_scancode_APPLICATION = 101, /**< windows contextual menu, compose */
    rodeo_input_binary_scancode_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    rodeo_input_binary_scancode_KP_EQUALS = 103,
    rodeo_input_binary_scancode_F13 = 104,
    rodeo_input_binary_scancode_F14 = 105,
    rodeo_input_binary_scancode_F15 = 106,
    rodeo_input_binary_scancode_F16 = 107,
    rodeo_input_binary_scancode_F17 = 108,
    rodeo_input_binary_scancode_F18 = 109,
    rodeo_input_binary_scancode_F19 = 110,
    rodeo_input_binary_scancode_F20 = 111,
    rodeo_input_binary_scancode_F21 = 112,
    rodeo_input_binary_scancode_F22 = 113,
    rodeo_input_binary_scancode_F23 = 114,
    rodeo_input_binary_scancode_F24 = 115,
    rodeo_input_binary_scancode_EXECUTE = 116,
    rodeo_input_binary_scancode_HELP = 117,    /**< AL Integrated Help Center */
    rodeo_input_binary_scancode_MENU = 118,    /**< Menu (show menu) */
    rodeo_input_binary_scancode_SELECT = 119,
    rodeo_input_binary_scancode_STOP = 120,    /**< AC Stop */
    rodeo_input_binary_scancode_AGAIN = 121,   /**< AC Redo/Repeat */
    rodeo_input_binary_scancode_UNDO = 122,    /**< AC Undo */
    rodeo_input_binary_scancode_CUT = 123,     /**< AC Cut */
    rodeo_input_binary_scancode_COPY = 124,    /**< AC Copy */
    rodeo_input_binary_scancode_PASTE = 125,   /**< AC Paste */
    rodeo_input_binary_scancode_FIND = 126,    /**< AC Find */
    rodeo_input_binary_scancode_MUTE = 127,
    rodeo_input_binary_scancode_VOLUMEUP = 128,
    rodeo_input_binary_scancode_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     rodeo_input_binary_scancode_LOCKINGCAPSLOCK = 130,  */
/*     rodeo_input_binary_scancode_LOCKINGNUMLOCK = 131, */
/*     rodeo_input_binary_scancode_LOCKINGSCROLLLOCK = 132, */
    rodeo_input_binary_scancode_KP_COMMA = 133,
    rodeo_input_binary_scancode_KP_EQUALSAS400 = 134,

    rodeo_input_binary_scancode_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    rodeo_input_binary_scancode_INTERNATIONAL2 = 136,
    rodeo_input_binary_scancode_INTERNATIONAL3 = 137, /**< Yen */
    rodeo_input_binary_scancode_INTERNATIONAL4 = 138,
    rodeo_input_binary_scancode_INTERNATIONAL5 = 139,
    rodeo_input_binary_scancode_INTERNATIONAL6 = 140,
    rodeo_input_binary_scancode_INTERNATIONAL7 = 141,
    rodeo_input_binary_scancode_INTERNATIONAL8 = 142,
    rodeo_input_binary_scancode_INTERNATIONAL9 = 143,
    rodeo_input_binary_scancode_LANG1 = 144, /**< Hangul/English toggle */
    rodeo_input_binary_scancode_LANG2 = 145, /**< Hanja conversion */
    rodeo_input_binary_scancode_LANG3 = 146, /**< Katakana */
    rodeo_input_binary_scancode_LANG4 = 147, /**< Hiragana */
    rodeo_input_binary_scancode_LANG5 = 148, /**< Zenkaku/Hankaku */
    rodeo_input_binary_scancode_LANG6 = 149, /**< reserved */
    rodeo_input_binary_scancode_LANG7 = 150, /**< reserved */
    rodeo_input_binary_scancode_LANG8 = 151, /**< reserved */
    rodeo_input_binary_scancode_LANG9 = 152, /**< reserved */

    rodeo_input_binary_scancode_ALTERASE = 153,    /**< Erase-Eaze */
    rodeo_input_binary_scancode_SYSREQ = 154,
    rodeo_input_binary_scancode_CANCEL = 155,      /**< AC Cancel */
    rodeo_input_binary_scancode_CLEAR = 156,
    rodeo_input_binary_scancode_PRIOR = 157,
    rodeo_input_binary_scancode_RETURN2 = 158,
    rodeo_input_binary_scancode_SEPARATOR = 159,
    rodeo_input_binary_scancode_OUT = 160,
    rodeo_input_binary_scancode_OPER = 161,
    rodeo_input_binary_scancode_CLEARAGAIN = 162,
    rodeo_input_binary_scancode_CRSEL = 163,
    rodeo_input_binary_scancode_EXSEL = 164,

    rodeo_input_binary_scancode_KP_00 = 176,
    rodeo_input_binary_scancode_KP_000 = 177,
    rodeo_input_binary_scancode_THOUSANDSSEPARATOR = 178,
    rodeo_input_binary_scancode_DECIMALSEPARATOR = 179,
    rodeo_input_binary_scancode_CURRENCYUNIT = 180,
    rodeo_input_binary_scancode_CURRENCYSUBUNIT = 181,
    rodeo_input_binary_scancode_KP_LEFTPAREN = 182,
    rodeo_input_binary_scancode_KP_RIGHTPAREN = 183,
    rodeo_input_binary_scancode_KP_LEFTBRACE = 184,
    rodeo_input_binary_scancode_KP_RIGHTBRACE = 185,
    rodeo_input_binary_scancode_KP_TAB = 186,
    rodeo_input_binary_scancode_KP_BACKSPACE = 187,
    rodeo_input_binary_scancode_KP_A = 188,
    rodeo_input_binary_scancode_KP_B = 189,
    rodeo_input_binary_scancode_KP_C = 190,
    rodeo_input_binary_scancode_KP_D = 191,
    rodeo_input_binary_scancode_KP_E = 192,
    rodeo_input_binary_scancode_KP_F = 193,
    rodeo_input_binary_scancode_KP_XOR = 194,
    rodeo_input_binary_scancode_KP_POWER = 195,
    rodeo_input_binary_scancode_KP_PERCENT = 196,
    rodeo_input_binary_scancode_KP_LESS = 197,
    rodeo_input_binary_scancode_KP_GREATER = 198,
    rodeo_input_binary_scancode_KP_AMPERSAND = 199,
    rodeo_input_binary_scancode_KP_DBLAMPERSAND = 200,
    rodeo_input_binary_scancode_KP_VERTICALBAR = 201,
    rodeo_input_binary_scancode_KP_DBLVERTICALBAR = 202,
    rodeo_input_binary_scancode_KP_COLON = 203,
    rodeo_input_binary_scancode_KP_HASH = 204,
    rodeo_input_binary_scancode_KP_SPACE = 205,
    rodeo_input_binary_scancode_KP_AT = 206,
    rodeo_input_binary_scancode_KP_EXCLAM = 207,
    rodeo_input_binary_scancode_KP_MEMSTORE = 208,
    rodeo_input_binary_scancode_KP_MEMRECALL = 209,
    rodeo_input_binary_scancode_KP_MEMCLEAR = 210,
    rodeo_input_binary_scancode_KP_MEMADD = 211,
    rodeo_input_binary_scancode_KP_MEMSUBTRACT = 212,
    rodeo_input_binary_scancode_KP_MEMMULTIPLY = 213,
    rodeo_input_binary_scancode_KP_MEMDIVIDE = 214,
    rodeo_input_binary_scancode_KP_PLUSMINUS = 215,
    rodeo_input_binary_scancode_KP_CLEAR = 216,
    rodeo_input_binary_scancode_KP_CLEARENTRY = 217,
    rodeo_input_binary_scancode_KP_BINARY = 218,
    rodeo_input_binary_scancode_KP_OCTAL = 219,
    rodeo_input_binary_scancode_KP_DECIMAL = 220,
    rodeo_input_binary_scancode_KP_HEXADECIMAL = 221,

    rodeo_input_binary_scancode_LCTRL = 224,
    rodeo_input_binary_scancode_LSHIFT = 225,
    rodeo_input_binary_scancode_LALT = 226, /**< alt, option */
    rodeo_input_binary_scancode_LGUI = 227, /**< windows, command (apple), meta */
    rodeo_input_binary_scancode_RCTRL = 228,
    rodeo_input_binary_scancode_RSHIFT = 229,
    rodeo_input_binary_scancode_RALT = 230, /**< alt gr, option */
    rodeo_input_binary_scancode_RGUI = 231, /**< windows, command (apple), meta */

    rodeo_input_binary_scancode_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special rodeo_input_rodeo_input_keymod_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *  See https://usb.org/sites/default/files/hut1_2.pdf
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    rodeo_input_binary_scancode_AUDIONEXT = 258,
    rodeo_input_binary_scancode_AUDIOPREV = 259,
    rodeo_input_binary_scancode_AUDIOSTOP = 260,
    rodeo_input_binary_scancode_AUDIOPLAY = 261,
    rodeo_input_binary_scancode_AUDIOMUTE = 262,
    rodeo_input_binary_scancode_MEDIASELECT = 263,
    rodeo_input_binary_scancode_WWW = 264,             /**< AL Internet Browser */
    rodeo_input_binary_scancode_MAIL = 265,
    rodeo_input_binary_scancode_CALCULATOR = 266,      /**< AL Calculator */
    rodeo_input_binary_scancode_COMPUTER = 267,
    rodeo_input_binary_scancode_AC_SEARCH = 268,       /**< AC Search */
    rodeo_input_binary_scancode_AC_HOME = 269,         /**< AC Home */
    rodeo_input_binary_scancode_AC_BACK = 270,         /**< AC Back */
    rodeo_input_binary_scancode_AC_FORWARD = 271,      /**< AC Forward */
    rodeo_input_binary_scancode_AC_STOP = 272,         /**< AC Stop */
    rodeo_input_binary_scancode_AC_REFRESH = 273,      /**< AC Refresh */
    rodeo_input_binary_scancode_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    rodeo_input_binary_scancode_BRIGHTNESSDOWN = 275,
    rodeo_input_binary_scancode_BRIGHTNESSUP = 276,
    rodeo_input_binary_scancode_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    rodeo_input_binary_scancode_KBDILLUMTOGGLE = 278,
    rodeo_input_binary_scancode_KBDILLUMDOWN = 279,
    rodeo_input_binary_scancode_KBDILLUMUP = 280,
    rodeo_input_binary_scancode_EJECT = 281,
    rodeo_input_binary_scancode_SLEEP = 282,           /**< SC System Sleep */

    rodeo_input_binary_scancode_APP1 = 283,
    rodeo_input_binary_scancode_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    rodeo_input_binary_scancode_AUDIOREWIND = 285,
    rodeo_input_binary_scancode_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    rodeo_input_binary_scancode_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    rodeo_input_binary_scancode_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    rodeo_input_binary_scancode_CALL = 289, /**< Used for accepting phone calls. */
    rodeo_input_binary_scancode_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    rodeo_input_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
}
rodeo_input_binary_scancode_t;

#define mrodeo_input_binary_scancode_mask (1<<30)
#define mrodeo_input_binary_scancode_maskshift(X)  (X | mrodeo_input_binary_scancode_mask)

/*
typedef enum
{
    rodeo_input_binary_keycode_UNKNOWN = 0,

    rodeo_input_binary_keycode_RETURN = '\r',
    rodeo_input_binary_keycode_ESCAPE = '\x1B',
    rodeo_input_binary_keycode_BACKSPACE = '\b',
    rodeo_input_binary_keycode_TAB = '\t',
    rodeo_input_binary_keycode_SPACE = ' ',
    rodeo_input_binary_keycode_EXCLAIM = '!',
    rodeo_input_binary_keycode_QUOTEDBL = '"',
    rodeo_input_binary_keycode_HASH = '#',
    rodeo_input_binary_keycode_PERCENT = '%',
    rodeo_input_binary_keycode_DOLLAR = '$',
    rodeo_input_binary_keycode_AMPERSAND = '&',
    rodeo_input_binary_keycode_QUOTE = '\'',
    rodeo_input_binary_keycode_LEFTPAREN = '(',
    rodeo_input_binary_keycode_RIGHTPAREN = ')',
    rodeo_input_binary_keycode_ASTERISK = '*',
    rodeo_input_binary_keycode_PLUS = '+',
    rodeo_input_binary_keycode_COMMA = ',',
    rodeo_input_binary_keycode_MINUS = '-',
    rodeo_input_binary_keycode_PERIOD = '.',
    rodeo_input_binary_keycode_SLASH = '/',
    rodeo_input_binary_keycode_0 = '0',
    rodeo_input_binary_keycode_1 = '1',
    rodeo_input_binary_keycode_2 = '2',
    rodeo_input_binary_keycode_3 = '3',
    rodeo_input_binary_keycode_4 = '4',
    rodeo_input_binary_keycode_5 = '5',
    rodeo_input_binary_keycode_6 = '6',
    rodeo_input_binary_keycode_7 = '7',
    rodeo_input_binary_keycode_8 = '8',
    rodeo_input_binary_keycode_9 = '9',
    rodeo_input_binary_keycode_COLON = ':',
    rodeo_input_binary_keycode_SEMICOLON = ';',
    rodeo_input_binary_keycode_LESS = '<',
    rodeo_input_binary_keycode_EQUALS = '=',
    rodeo_input_binary_keycode_GREATER = '>',
    rodeo_input_binary_keycode_QUESTION = '?',
    rodeo_input_binary_keycode_AT = '@',

    // Skip uppercase letters

    rodeo_input_binary_keycode_LEFTBRACKET = '[',
    rodeo_input_binary_keycode_BACKSLASH = '\\',
    rodeo_input_binary_keycode_RIGHTBRACKET = ']',
    rodeo_input_binary_keycode_CARET = '^',
    rodeo_input_binary_keycode_UNDERSCORE = '_',
    rodeo_input_binary_keycode_BACKQUOTE = '`',
    rodeo_input_binary_keycode_A = 'a',
    rodeo_input_binary_keycode_B = 'b',
    rodeo_input_binary_keycode_C = 'c',
    rodeo_input_binary_keycode_D = 'd',
    rodeo_input_binary_keycode_E = 'e',
    rodeo_input_binary_keycode_F = 'f',
    rodeo_input_binary_keycode_G = 'g',
    rodeo_input_binary_keycode_H = 'h',
    rodeo_input_binary_keycode_I = 'i',
    rodeo_input_binary_keycode_J = 'j',
    rodeo_input_binary_keycode_K = 'k',
    rodeo_input_binary_keycode_L = 'l',
    rodeo_input_binary_keycode_M = 'm',
    rodeo_input_binary_keycode_N = 'n',
    rodeo_input_binary_keycode_O = 'o',
    rodeo_input_binary_keycode_P = 'p',
    rodeo_input_binary_keycode_Q = 'q',
    rodeo_input_binary_keycode_R = 'r',
    rodeo_input_binary_keycode_S = 's',
    rodeo_input_binary_keycode_T = 't',
    rodeo_input_binary_keycode_U = 'u',
    rodeo_input_binary_keycode_V = 'v',
    rodeo_input_binary_keycode_W = 'w',
    rodeo_input_binary_keycode_X = 'x',
    rodeo_input_binary_keycode_Y = 'y',
    rodeo_input_binary_keycode_Z = 'z',
 
    rodeo_input_binary_keycode_CAPSLOCK = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CAPSLOCK),
 
    rodeo_input_binary_keycode_F1 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F1),
    rodeo_input_binary_keycode_F2 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F2),
    rodeo_input_binary_keycode_F3 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F3),
    rodeo_input_binary_keycode_F4 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F4),
    rodeo_input_binary_keycode_F5 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F5),
    rodeo_input_binary_keycode_F6 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F6),
    rodeo_input_binary_keycode_F7 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F7),
    rodeo_input_binary_keycode_F8 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F8),
    rodeo_input_binary_keycode_F9 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F9),
    rodeo_input_binary_keycode_F10 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F10),
    rodeo_input_binary_keycode_F11 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F11),
    rodeo_input_binary_keycode_F12 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F12),
 
    rodeo_input_binary_keycode_PRINTSCREEN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PRINTSCREEN),
    rodeo_input_binary_keycode_SCROLLLOCK = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SCROLLLOCK),
    rodeo_input_binary_keycode_PAUSE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PAUSE),
    rodeo_input_binary_keycode_INSERT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_INSERT),
    rodeo_input_binary_keycode_HOME = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_HOME),
    rodeo_input_binary_keycode_PAGEUP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PAGEUP),
    rodeo_input_binary_keycode_DELETE = '\x7F',
    rodeo_input_binary_keycode_END = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_END),
    rodeo_input_binary_keycode_PAGEDOWN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PAGEDOWN),
    rodeo_input_binary_keycode_RIGHT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RIGHT),
    rodeo_input_binary_keycode_LEFT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_LEFT),
    rodeo_input_binary_keycode_DOWN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_DOWN),
    rodeo_input_binary_keycode_UP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_UP),
 
    rodeo_input_binary_keycode_NUMLOCKCLEAR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_NUMLOCKCLEAR),
    rodeo_input_binary_keycode_KP_DIVIDE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_DIVIDE),
    rodeo_input_binary_keycode_KP_MULTIPLY = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MULTIPLY),
    rodeo_input_binary_keycode_KP_MINUS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MINUS),
    rodeo_input_binary_keycode_KP_PLUS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_PLUS),
    rodeo_input_binary_keycode_KP_ENTER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_ENTER),
    rodeo_input_binary_keycode_KP_1 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_1),
    rodeo_input_binary_keycode_KP_2 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_2),
    rodeo_input_binary_keycode_KP_3 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_3),
    rodeo_input_binary_keycode_KP_4 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_4),
    rodeo_input_binary_keycode_KP_5 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_5),
    rodeo_input_binary_keycode_KP_6 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_6),
    rodeo_input_binary_keycode_KP_7 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_7),
    rodeo_input_binary_keycode_KP_8 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_8),
    rodeo_input_binary_keycode_KP_9 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_9),
    rodeo_input_binary_keycode_KP_0 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_0),
    rodeo_input_binary_keycode_KP_PERIOD = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_PERIOD),
 
    rodeo_input_binary_keycode_APPLICATION = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_APPLICATION),
    rodeo_input_binary_keycode_POWER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_POWER),
    rodeo_input_binary_keycode_KP_EQUALS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_EQUALS),
    rodeo_input_binary_keycode_F13 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F13),
    rodeo_input_binary_keycode_F14 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F14),
    rodeo_input_binary_keycode_F15 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F15),
    rodeo_input_binary_keycode_F16 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F16),
    rodeo_input_binary_keycode_F17 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F17),
    rodeo_input_binary_keycode_F18 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F18),
    rodeo_input_binary_keycode_F19 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F19),
    rodeo_input_binary_keycode_F20 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F20),
    rodeo_input_binary_keycode_F21 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F21),
    rodeo_input_binary_keycode_F22 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F22),
    rodeo_input_binary_keycode_F23 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F23),
    rodeo_input_binary_keycode_F24 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_F24),
    rodeo_input_binary_keycode_EXECUTE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_EXECUTE),
    rodeo_input_binary_keycode_HELP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_HELP),
    rodeo_input_binary_keycode_MENU = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_MENU),
    rodeo_input_binary_keycode_SELECT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SELECT),
    rodeo_input_binary_keycode_STOP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_STOP),
    rodeo_input_binary_keycode_AGAIN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AGAIN),
    rodeo_input_binary_keycode_UNDO = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_UNDO),
    rodeo_input_binary_keycode_CUT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CUT),
    rodeo_input_binary_keycode_COPY = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_COPY),
    rodeo_input_binary_keycode_PASTE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PASTE),
    rodeo_input_binary_keycode_FIND = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_FIND),
    rodeo_input_binary_keycode_MUTE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_MUTE),
    rodeo_input_binary_keycode_VOLUMEUP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_VOLUMEUP),
    rodeo_input_binary_keycode_VOLUMEDOWN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_VOLUMEDOWN),
    rodeo_input_binary_keycode_KP_COMMA = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_COMMA),
    rodeo_input_binary_keycode_KP_EQUALSAS400 =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_EQUALSAS400),
 
    rodeo_input_binary_keycode_ALTERASE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_ALTERASE),
    rodeo_input_binary_keycode_SYSREQ = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SYSREQ),
    rodeo_input_binary_keycode_CANCEL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CANCEL),
    rodeo_input_binary_keycode_CLEAR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CLEAR),
    rodeo_input_binary_keycode_PRIOR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_PRIOR),
    rodeo_input_binary_keycode_RETURN2 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RETURN2),
    rodeo_input_binary_keycode_SEPARATOR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SEPARATOR),
    rodeo_input_binary_keycode_OUT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_OUT),
    rodeo_input_binary_keycode_OPER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_OPER),
    rodeo_input_binary_keycode_CLEARAGAIN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CLEARAGAIN),
    rodeo_input_binary_keycode_CRSEL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CRSEL),
    rodeo_input_binary_keycode_EXSEL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_EXSEL),
 
    rodeo_input_binary_keycode_KP_00 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_00),
    rodeo_input_binary_keycode_KP_000 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_000),
    rodeo_input_binary_keycode_THOUSANDSSEPARATOR =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_THOUSANDSSEPARATOR),
    rodeo_input_binary_keycode_DECIMALSEPARATOR =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_DECIMALSEPARATOR),
    rodeo_input_binary_keycode_CURRENCYUNIT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CURRENCYUNIT),
    rodeo_input_binary_keycode_CURRENCYSUBUNIT =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CURRENCYSUBUNIT),
    rodeo_input_binary_keycode_KP_LEFTPAREN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_LEFTPAREN),
    rodeo_input_binary_keycode_KP_RIGHTPAREN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_RIGHTPAREN),
    rodeo_input_binary_keycode_KP_LEFTBRACE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_LEFTBRACE),
    rodeo_input_binary_keycode_KP_RIGHTBRACE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_RIGHTBRACE),
    rodeo_input_binary_keycode_KP_TAB = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_TAB),
    rodeo_input_binary_keycode_KP_BACKSPACE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_BACKSPACE),
    rodeo_input_binary_keycode_KP_A = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_A),
    rodeo_input_binary_keycode_KP_B = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_B),
    rodeo_input_binary_keycode_KP_C = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_C),
    rodeo_input_binary_keycode_KP_D = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_D),
    rodeo_input_binary_keycode_KP_E = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_E),
    rodeo_input_binary_keycode_KP_F = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_F),
    rodeo_input_binary_keycode_KP_XOR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_XOR),
    rodeo_input_binary_keycode_KP_POWER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_POWER),
    rodeo_input_binary_keycode_KP_PERCENT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_PERCENT),
    rodeo_input_binary_keycode_KP_LESS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_LESS),
    rodeo_input_binary_keycode_KP_GREATER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_GREATER),
    rodeo_input_binary_keycode_KP_AMPERSAND = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_AMPERSAND),
    rodeo_input_binary_keycode_KP_DBLAMPERSAND =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_DBLAMPERSAND),
    rodeo_input_binary_keycode_KP_VERTICALBAR =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_VERTICALBAR),
    rodeo_input_binary_keycode_KP_DBLVERTICALBAR =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_DBLVERTICALBAR),
    rodeo_input_binary_keycode_KP_COLON = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_COLON),
    rodeo_input_binary_keycode_KP_HASH = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_HASH),
    rodeo_input_binary_keycode_KP_SPACE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_SPACE),
    rodeo_input_binary_keycode_KP_AT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_AT),
    rodeo_input_binary_keycode_KP_EXCLAM = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_EXCLAM),
    rodeo_input_binary_keycode_KP_MEMSTORE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMSTORE),
    rodeo_input_binary_keycode_KP_MEMRECALL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMRECALL),
    rodeo_input_binary_keycode_KP_MEMCLEAR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMCLEAR),
    rodeo_input_binary_keycode_KP_MEMADD = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMADD),
    rodeo_input_binary_keycode_KP_MEMSUBTRACT =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMSUBTRACT),
    rodeo_input_binary_keycode_KP_MEMMULTIPLY =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMMULTIPLY),
    rodeo_input_binary_keycode_KP_MEMDIVIDE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_MEMDIVIDE),
    rodeo_input_binary_keycode_KP_PLUSMINUS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_PLUSMINUS),
    rodeo_input_binary_keycode_KP_CLEAR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_CLEAR),
    rodeo_input_binary_keycode_KP_CLEARENTRY = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_CLEARENTRY),
    rodeo_input_binary_keycode_KP_BINARY = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_BINARY),
    rodeo_input_binary_keycode_KP_OCTAL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_OCTAL),
    rodeo_input_binary_keycode_KP_DECIMAL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_DECIMAL),
    rodeo_input_binary_keycode_KP_HEXADECIMAL =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KP_HEXADECIMAL),
 
    rodeo_input_binary_keycode_LCTRL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_LCTRL),
    rodeo_input_binary_keycode_LSHIFT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_LSHIFT),
    rodeo_input_binary_keycode_LALT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_LALT),
    rodeo_input_binary_keycode_LGUI = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_LGUI),
    rodeo_input_binary_keycode_RCTRL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RCTRL),
    rodeo_input_binary_keycode_RSHIFT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RSHIFT),
    rodeo_input_binary_keycode_RALT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RALT),
    rodeo_input_binary_keycode_RGUI = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_RGUI),
 
    rodeo_input_binary_keycode_MODE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_MODE),
 
    rodeo_input_binary_keycode_AUDIONEXT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIONEXT),
    rodeo_input_binary_keycode_AUDIOPREV = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOPREV),
    rodeo_input_binary_keycode_AUDIOSTOP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOSTOP),
    rodeo_input_binary_keycode_AUDIOPLAY = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOPLAY),
    rodeo_input_binary_keycode_AUDIOMUTE = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOMUTE),
    rodeo_input_binary_keycode_MEDIASELECT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_MEDIASELECT),
    rodeo_input_binary_keycode_WWW = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_WWW),
    rodeo_input_binary_keycode_MAIL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_MAIL),
    rodeo_input_binary_keycode_CALCULATOR = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CALCULATOR),
    rodeo_input_binary_keycode_COMPUTER = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_COMPUTER),
    rodeo_input_binary_keycode_AC_SEARCH = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_SEARCH),
    rodeo_input_binary_keycode_AC_HOME = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_HOME),
    rodeo_input_binary_keycode_AC_BACK = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_BACK),
    rodeo_input_binary_keycode_AC_FORWARD = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_FORWARD),
    rodeo_input_binary_keycode_AC_STOP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_STOP),
    rodeo_input_binary_keycode_AC_REFRESH = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_REFRESH),
    rodeo_input_binary_keycode_AC_BOOKMARKS = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AC_BOOKMARKS),

    rodeo_input_binary_keycode_BRIGHTNESSDOWN =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_BRIGHTNESSDOWN),
    rodeo_input_binary_keycode_BRIGHTNESSUP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_BRIGHTNESSUP),
    rodeo_input_binary_keycode_DISPLAYSWITCH = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_DISPLAYSWITCH),
    rodeo_input_binary_keycode_KBDILLUMTOGGLE =
        mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KBDILLUMTOGGLE),
    rodeo_input_binary_keycode_KBDILLUMDOWN = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KBDILLUMDOWN),
    rodeo_input_binary_keycode_KBDILLUMUP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_KBDILLUMUP),
    rodeo_input_binary_keycode_EJECT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_EJECT),
    rodeo_input_binary_keycode_SLEEP = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SLEEP),
    rodeo_input_binary_keycode_APP1 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_APP1),
    rodeo_input_binary_keycode_APP2 = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_APP2),
 
    rodeo_input_binary_keycode_AUDIOREWIND = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOREWIND),
    rodeo_input_binary_keycode_AUDIOFASTFORWARD = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_AUDIOFASTFORWARD),
 
    rodeo_input_binary_keycode_SOFTLEFT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SOFTLEFT),
    rodeo_input_binary_keycode_SOFTRIGHT = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_SOFTRIGHT),
    rodeo_input_binary_keycode_CALL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_CALL),
    rodeo_input_binary_keycode_ENDCALL = mrodeo_input_binary_scancode_maskshift(rodeo_input_binary_scancode_ENDCALL)
}
rodeo_input_binary_keycode_t;
*/



/**
 * \brief Enumeration of valid key mods (possibly OR'd together).
 */

typedef
enum
{
    rodeo_input_keymod_NONE = 0x0000,
    rodeo_input_keymod_LSHIFT = 0x0001,
    rodeo_input_keymod_RSHIFT = 0x0002,
    rodeo_input_keymod_LCTRL = 0x0040,
    rodeo_input_keymod_RCTRL = 0x0080,
    rodeo_input_keymod_LALT = 0x0100,
    rodeo_input_keymod_RALT = 0x0200,
    rodeo_input_keymod_LGUI = 0x0400,
    rodeo_input_keymod_RGUI = 0x0800,
    rodeo_input_keymod_NUM = 0x1000,
    rodeo_input_keymod_CAPS = 0x2000,
    rodeo_input_keymod_MODE = 0x4000,
    rodeo_input_keymod_SCROLL = 0x8000,

    rodeo_input_keymod_CTRL = rodeo_input_keymod_LCTRL | rodeo_input_keymod_RCTRL,
    rodeo_input_keymod_SHIFT = rodeo_input_keymod_LSHIFT | rodeo_input_keymod_RSHIFT,
    rodeo_input_keymod_ALT = rodeo_input_keymod_LALT | rodeo_input_keymod_RALT,
    rodeo_input_keymod_GUI = rodeo_input_keymod_LGUI | rodeo_input_keymod_RGUI,

    rodeo_input_keymod_RESERVED = rodeo_input_keymod_SCROLL /* This is for source-level compatibility with SDL 2.0.0. */
}
rodeo_input_keymod_t;

typedef
enum
{
	rodeo_input_binary_mouseButton_INVALID = -1,
	rodeo_input_binary_mouseButton_LEFT    =  1,
	rodeo_input_binary_mouseButton_MIDDLE  =  2,
	rodeo_input_binary_mouseButton_RIGHT   =  3,
	rodeo_input_binary_mouseButton_X1      =  4,
	rodeo_input_binary_mouseButton_X2      =  5,
}
rodeo_input_binary_mouseButton_t;

typedef enum
{
    rodeo_input_binary_controllerButton_INVALID = -1,
    rodeo_input_binary_controllerButton_A,
    rodeo_input_binary_controllerButton_B,
    rodeo_input_binary_controllerButton_X,
    rodeo_input_binary_controllerButton_Y,
    rodeo_input_binary_controllerButton_BACK,
    rodeo_input_binary_controllerButton_GUIDE,
    rodeo_input_binary_controllerButton_START,
    rodeo_input_binary_controllerButton_LEFTSTICK,
    rodeo_input_binary_controllerButton_RIGHTSTICK,
    rodeo_input_binary_controllerButton_LEFTSHOULDER,
    rodeo_input_binary_controllerButton_RIGHTSHOULDER,
    rodeo_input_binary_controllerButton_DPAD_UP,
    rodeo_input_binary_controllerButton_DPAD_DOWN,
    rodeo_input_binary_controllerButton_DPAD_LEFT,
    rodeo_input_binary_controllerButton_DPAD_RIGHT,
    rodeo_input_binary_controllerButton_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
    rodeo_input_binary_controllerButton_PADDLE1,  /* Xbox Elite paddle P1 (upper left, facing the back) */
    rodeo_input_binary_controllerButton_PADDLE2,  /* Xbox Elite paddle P3 (upper right, facing the back) */
    rodeo_input_binary_controllerButton_PADDLE3,  /* Xbox Elite paddle P2 (lower left, facing the back) */
    rodeo_input_binary_controllerButton_PADDLE4,  /* Xbox Elite paddle P4 (lower right, facing the back) */
    rodeo_input_binary_controllerButton_TOUCHPAD, /* PS4/PS5 touchpad button */
    rodeo_input_binary_controllerButton_MAX
}
rodeo_input_binary_controllerButton_t;

// - SDL code end -

typedef
enum
{
	rodeo_input_positional_mouse_Invalid = -1,
	rodeo_input_positional_mouse_X,
	rodeo_input_positional_mouse_Y
}
rodeo_input_positional_mouse_t;

typedef
enum
{
	rodeo_input_boundedRange_controllerAxis_Invalid = -1,
	rodeo_input_boundedRange_controllerAxisLeft_X = 0,
	rodeo_input_boundedRange_controllerAxisLeft_Y = 1,
	rodeo_input_boundedRange_controllerAxisRight_X = 2,
	rodeo_input_boundedRange_controllerAxisRight_Y = 3,
	rodeo_input_boundedRange_controllerAxisTriggerLeft_X = 4,
	rodeo_input_boundedRange_controllerAxisTriggerRight_Y = 5,
}
rodeo_input_boundedRange_controllerAxis_t;

typedef
enum
{
	rodeo_input_unboundedRange_mouse_Invalid = 0,
	rodeo_input_unboundedRange_mouse_X = 1,
	rodeo_input_unboundedRange_mouse_Y = 2
}
rodeo_input_unboundedRange_mouse_t;

typedef
enum
{
	rodeo_input_type_Invalid = (1 << 0),
	rodeo_input_type_Binary  = (1 << 1),
	rodeo_input_type_Positional  = (1 << 2),
	rodeo_input_type_BoundedRange  = (1 << 3),
	rodeo_input_type_UnboundedRange  = (1 << 4),
}
rodeo_input_type_t ;

/*
 * needed for alternative registration
 * uncomment this for when that is being implemented
typedef
enum
{
	rodeo_input_binary_Invalid = 0,
	rodeo_input_binary_Scancode,
	rodeo_input_binary_Mouse
}
rodeo_input_binary_type_t;

typedef
enum
{
	rodeo_input_positional_Invalid = 0,
	rodeo_input_positional_Mouse
}
rodeo_input_positional_type_t;

typedef
enum
{
	rodeo_input_boundedRange_Invalid = 0,
	rodeo_input_boundedRange_Joystick
}
rodeo_input_boundedRange_type_t;

typedef
enum
{
	rodeo_input_unboundedRange_Invalid = 0,
	rodeo_input_unboundedRange_Mouse
}
rodeo_input_unboundedRange_type_t;
*/

typedef
enum
{
	rodeo_input_binary_state_Up = false,
	rodeo_input_binary_state_Down = true
}
rodeo_input_binary_state_t;

typedef int64_t rodeo_input_positional_state_t;

// ranges between -1.0 and +1.0
typedef float rodeo_input_boundedRange_state_t;

typedef float rodeo_input_unboundedRange_state_t;

typedef
struct
{
	union
	{
		rodeo_input_binary_state_t binary_state;
		rodeo_input_positional_state_t positional_state;
		rodeo_input_boundedRange_state_t bounded_range_state;
		rodeo_input_unboundedRange_state_t unbounded_range_state;
	}
	data;
	rodeo_input_type_t type;
}
rodeo_input_any_state_t;

typedef
void*
(*rodeo_input_callback_function)(
	rodeo_input_any_state_t *state,
	void *data
);

#define i_val rodeo_input_callback_function
#define i_tag input_callback_functions
#include <stc/cset.h>

#define i_val rodeo_input_binary_scancode_t
#define i_tag input_binary_scancodes
#include <stc/cset.h>

#define i_val rodeo_input_binary_mouseButton_t
#define i_tag input_binary_mouseButtons
#include <stc/cset.h>

#define i_val rodeo_input_positional_mouse_t
#define i_tag input_positional_mouse
#include <stc/cset.h>

#define i_val rodeo_input_boundedRange_controllerAxis_t
#define i_tag input_boundedRange_controllerAxis
#include <stc/cset.h>

#define i_val rodeo_input_unboundedRange_mouse_t
#define i_tag input_unboundedRange_mouse
#include <stc/cset.h>

#define i_val rodeo_input_binary_controllerButton_t
#define i_tag input_binary_controllerButton
#include <stc/cset.h>

typedef
struct
{
	uint32_t valid_types; // rodeo_input_type_t

	cset_input_callback_functions callbacks;

	struct
	{
		cset_input_binary_scancodes scancodes;
		cset_input_binary_mouseButtons mouse_buttons;
		cset_input_binary_controllerButton controller_buttons;
	}
	binary;

	struct
	{
		cset_input_positional_mouse mouse_axes;
	}
	positional;

	struct
	{
		cset_input_boundedRange_controllerAxis controller_axes;
	}
	bounded_range;
	
	struct
	{
		cset_input_unboundedRange_mouse mouse_axes;
	}
	unbounded_range;
	
}
rodeo_input_command_t;

#define i_val rodeo_input_command_t*
#define i_tag input_commands
#include <stc/cset.h>

typedef
struct
{
	cset_input_commands commands;
}
rodeo_input_scene_t;

// Video memory text mode colors
#ifndef __COLORS_H__
#define __COLORS_H__

#define FG_BACK          0b0000
#define FG_BLUE          0b0001
#define FG_GREEN         0b0010
#define FG_CYAN          0b0011
#define FG_RED           0b0100
#define FG_MAGENTA       0b0101
#define FG_BROWN         0b0110
#define FG_LIGHT_GRAY    0b0111
#define FG_DARK_GRAY     0b1000
#define FG_LIGHT_BLUE    0b1001
#define FG_LIGHT_GREEN   0b1010
#define FG_LIGHT_CYAN    0b1011
#define FG_LIGHT_RED     0b1100
#define FG_LIGHT_MAGENTA 0b1101
#define FG_YELLOW        0b1110
#define FG_WHITE         0b1111

// 7th bit does different things on different video cards
#define BG_BACK          0b0000000
#define BG_BLUE          0b0010000
#define BG_GREEN         0b0100000
#define BG_CYAN          0b0110000
#define BG_RED           0b1000000
#define BG_MAGENTA       0b1010000
#define BG_BROWN         0b1100000
#define BG_LIGHT_GRAY    0b1110000

#endif

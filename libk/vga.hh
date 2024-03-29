#pragma once
#include "int.hh"

enum vga_color {
  	VGA_COLOR_BLACK         = 0x0,
	VGA_COLOR_BLUE          = 0x1,
	VGA_COLOR_GREEN         = 0x2,
	VGA_COLOR_CYAN          = 0x3,
	VGA_COLOR_RED           = 0x4,
	VGA_COLOR_MAGENTA       = 0x5,
	VGA_COLOR_BROWN         = 0x6,
	VGA_COLOR_LIGHT_GREY    = 0x7,
	VGA_COLOR_DARK_GREY     = 0x8,
	VGA_COLOR_LIGHT_BLUE    = 0x9,
	VGA_COLOR_LIGHT_GREEN   = 0xA,
	VGA_COLOR_LIGHT_CYAN    = 0xB,
	VGA_COLOR_LIGHT_RED     = 0xC,
	VGA_COLOR_LIGHT_MAGENTA = 0xD,
	VGA_COLOR_YELLOW        = 0xE,
	VGA_COLOR_WHITE         = 0xF,
};

#ifdef __cplusplus
extern "C" {
#endif

inline __attribute__((always_inline)) auto vga_entry_color(vga_color const fg, vga_color const bg) -> u8 {
	return (fg | bg) << 4;
}

inline __attribute__((always_inline)) auto vga_entry(char const c, vga_color const fg, vga_color const bg) -> u16 {
	u16 const color = (bg << 4) | fg;
	return (color << 8) | c;
}

#ifdef __cplusplus
}
#endif

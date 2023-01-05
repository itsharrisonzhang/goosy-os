#include <../kernel/tty.hh>

namespace console {
    namespace {
        const size_t VGA_WIDTH = 80;
        const size_t VGA_HEIGHT = 25;
        const uint16_t VGA_MEMORY = 0xB8000;
        size_t    trow;
        size_t    tcolumn;
        uint8_t   tcolor;
        uint16_t* tbuffer;
    }

    void init () {
        trow = 0;
        tcolumn = 0;
        tcolor = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        tbuffer = (uint16_t*)VGA_MEMORY;
        for (auto i = 0; i != VGA_HEIGHT; ++i) {
            for (auto j = 0; j != VGA_WIDTH; ++j) {
                auto n = i*VGA_WIDTH + j;
                tbuffer[n] = vga_entry(' ', tcolor);
            }
        }
    }

    void setcolor (uint8_t color) {
        tcolor = color;
    }

    void putentryat (char c, uint8_t color, size_t x, size_t y) {
        auto i = y*VGA_WIDTH + x;
        tbuffer[i] = vga_entry(c, color);
    }

    void scroll () {
        for (auto i = 0; i != VGA_WIDTH; ++i) {
            for (auto j = 0; j != VGA_HEIGHT; ++j) {
                tbuffer[i*VGA_WIDTH+j] = tbuffer[(i+1)*VGA_WIDTH+j];
            }
        }
    }

    void newline () {
        tcolumn = 0;
        ++trow;
        if (trow == VGA_HEIGHT) {
            --trow;
            scroll();
        }
    }

    void putchar (char c) {
        putentryat((unsigned char)c, tcolor, tcolumn, trow);
        if (++tcolumn == VGA_WIDTH) {
            tcolumn = 0;
            if (++trow == VGA_HEIGHT) {
                for (auto i = 1; i != VGA_HEIGHT; ++i) {
                    scroll();
                }
                newline();
                trow = VGA_HEIGHT-1;
            }
        }
    }

    void write (const char* data, size_t size) {
        for (auto i = 0; i != size; ++i) {
            putchar(data[i]);
        }
    }

    void writestring (const char* str) {
        write(str, strlen(str));
    }
}
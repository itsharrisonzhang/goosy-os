#include "tty.hh"

console::Console C;
namespace console {

    void Console::scroll() {
        for (u16 i = 1; i < VGA_HEIGHT; ++i) {
            for (u16 j = 0; j < VGA_WIDTH; ++j) {
                _console_page[(i - 1) * VGA_WIDTH + j] = _console_page[i * VGA_WIDTH + j];
            }
        }
        for (u16 i = 0; i < VGA_WIDTH; ++i) {
            auto const n = (VGA_HEIGHT - 1) * VGA_WIDTH + i;
            _console_page[n] = vga_entry(' ', _fg, _bg);
        }
    }

    void Console::new_line() {
        _current_column = VGA_WIDTH - 1;
        if (_current_row >= VGA_HEIGHT) {
            _current_row = VGA_HEIGHT - 1;
            scroll();
        }
    }

    void Console::put_char(char const c) {
        if (c == '\n') {
            new_line();
            return;
        }
        auto const n = _current_row * VGA_WIDTH + _current_column;
        _console_page[n] = vga_entry(c, _fg, _bg);
    }

    void Console::update_pos(i8 const delta) {
        if (delta > 0) {
            _current_row += (_current_column + delta) / VGA_WIDTH;
            _current_column = (_current_column + delta) % VGA_WIDTH;
            if (_current_row >= VGA_HEIGHT) {
                _current_row = VGA_HEIGHT - 1;
                scroll();
            }
        }
        else if (delta == -1) {
            if (_current_column == 0) {
                _current_column = VGA_WIDTH - 1;
                if (_current_row > 0) {
                    --_current_row;
                }
            }
            else {
                --_current_column;
            }
        }
        else {
            for (auto i = delta; i < 0; ++i) {
                if (_current_column == 0) {
                _current_column = VGA_WIDTH - 1;
                if (_current_row > 0) {
                    --_current_row;
                }
                }
                else {
                    --_current_column;
                }
            }
        }
    }

    auto Console::num_digits(usize num, u8 base) -> u8 {
        u8 digits = 0;
        do {
            ++digits;
            num /= base;
        }
        while (num > 0);
        return digits;
    }

    void Console::put(void const* ptr) {
        auto num = reinterpret_cast<u32>(ptr);
        print("0x");
        auto const digits = num_digits(num, 16);
        update_pos(digits);
        do {
            auto const digit = static_cast<char>((num % 16 < 10) ? (num % 16 + '0') : (num % 16 + 'A' - 10));
            update_pos(-1);
            put_char(digit);
            num /= 16;
        }
        while (num > 0);
        update_pos(digits);
    }

    void Console::put(u32 num) {
        auto const digits = num_digits(num, 10);
        update_pos(digits);
        do {
            auto const digit = static_cast<char const>(num % 10 + '0');
            update_pos(-1);
            put_char(digit);
            num /= 10;
        }
        while (num > 0);
        update_pos(digits);
    }

    void Console::put(str const string) {
        for (auto const& c : string) {
            put_char(c);
            update_pos(1);
        }
    }

    void Console::print() {
        update_cursor(_current_row, _current_column);
    }

    void Console::clear() {
        for (u16 i = 0; i < VGA_HEIGHT; ++i) {
            for (u16 j = 0; j < VGA_WIDTH; ++j) {
                u16 const n = i * VGA_WIDTH + j;
                _console_page[n] = vga_entry(' ', DEFAULT_FG, DEFAULT_BG);
            }
        }
        _current_row = 0;
        _current_column = 0;
        update_cursor(_current_row, _current_column);
    }

    void Console::put(char const c) { put_char(c); }
    void Console::put(signed const& num) { put(u32(num)); }
    void Console::put(u16 const num) { put(u32(num)); }
    void Console::put(i16 const num) { put(u32(num)); }
    void Console::put(u8 const num) { put(u32(num)); }
    void Console::put(i8 const num) { put(u32(num)); }
}
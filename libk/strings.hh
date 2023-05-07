#pragma once
#include "int.hh"
#include "iterator.hh"

struct str {
    public :
        template<usize S>
        constexpr str(char const (&string)[S]) : tstr(string), tsize(S - 1) {}
        constexpr str(char const* string, usize size) : tstr(string), tsize(size - 1) {}

        auto constexpr len() const -> usize {
            return tsize;
        }

        auto constexpr begin() const -> iterator<char const> {
            return iterator<const char>(tstr);
        }

        auto constexpr end() const -> iterator<char const> {
            return iterator<const char>(tstr + tsize);
        }

        auto constexpr operator[](const usize i) const -> char const& {
            return tstr[i];
        }

    private:
        char const* tstr;
        usize tsize;
};
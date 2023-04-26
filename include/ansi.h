// #pragma once
//? #pragma once is not standard so i used a header guard
#ifndef _ansi_h
#define _ansi_h

namespace ansi_escape_codes
{
    #define ANSI_ESC "\x1b"

    enum Cursor : char
    {
        CURSOR_HOME = 'H',
        CURSOR_UP = 'A', CURSOR_DOWN, CURSOR_RIGHT, CURSOR_LEFT, CURSOR_BEGINNING_OF_NEXT_LINE, CURSOR_BEGINNING_OF_PREVIUS_LINE, CURSOR_COLUMN,
        CURSOR_LINE_UP_SCROLL = 'M',
        CURSOR_SAVE_POSITION = '7', CURSOR_RESTORE_POSITION
    };

    enum Clear : char
    {
        CLEAR_TO_END_OF_SCREEN, CLEAR_TO_BEGINNING_OF_SCREEN, CLEAR_SCREEN,
        CLEAR_TO_END_OF_LINE = 0, CLEAR_FROM_START_OF_LINE, CLEAR_LINE,
    };

    enum Mode : char
    {
        RESET, BOLD, FAINT, ITALIC, UNDERLINE, BLINKING, INVERSE = 7, HIDDEN, STRIKETHROUGH,
        RESET_BOLD = 22, RESET_FAINT = 22, RESET_ITALIC, RESET_UNDERLINE, RESET_BLINKING, RESET_INVERSE = 27, RESET_HIDDEN, RESET_STRIKETHROUGH,
    };

    enum Color : char
    {
        BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, DEFAULT = 39,
        BG_BLACK = 40, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE, BG_DEFAULT = 49,
    };

    inline void clear(const Clear type);
    inline void setMode(const Mode mode);
    inline void setColor(const Color color);
    inline void moveCursor(const Cursor action, const int amount);
    inline void moveCursor(const int row, const int column);
}

#endif

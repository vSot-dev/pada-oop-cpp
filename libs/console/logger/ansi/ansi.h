#ifndef _ansi_h
#define _ansi_h

#include <ostream>

namespace ansi_escape_codes
{
    #define ESC "\x1b"
    #define LESC L"\x1b"

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

    template <typename T>
    struct ansi_escape_code
    {
        explicit ansi_escape_code(T code);
        explicit ansi_escape_code(char code);

        ~ansi_escape_code();

        friend std::ostream& operator << (std::ostream& os, T code);
        friend std::ostream& operator << (std::ostream& os, ansi_escape_code<T>& code);

        friend std::wostream& operator << (std::wostream& os, T code);
        friend std::wostream& operator << (std::wostream& os, ansi_escape_code<T>& code);
    protected:
        char m_Code;
    };
    
    struct cursor : public ansi_escape_code<Cursor>
    {
        explicit cursor(Cursor code);
        explicit cursor(char code);
        explicit cursor(Cursor code, int row);
        explicit cursor(char code, int row);
        explicit cursor(int row, int column);

        using ansi_escape_code<Cursor>::~ansi_escape_code;

    private:
        int m_Row, m_Column;
    };

    struct clear : public ansi_escape_code<Clear>
    {
        explicit clear(Clear code);
        explicit clear(char code);

        using ansi_escape_code<Clear>::~ansi_escape_code;

    private:
        char m_Type;
    };

    struct mode : public ansi_escape_code<Mode>
    {
        using ansi_escape_code<Mode>::ansi_escape_code;
        using ansi_escape_code<Mode>::~ansi_escape_code;
    };

    struct color : public ansi_escape_code<Color>
    {
        using ansi_escape_code<Color>::ansi_escape_code;
        using ansi_escape_code<Color>::~ansi_escape_code;
    };
} // namespace ansi_escape_codes

#endif

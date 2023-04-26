#include "../include/ansi.h"

namespace ansi_escape_codes
{
    inline void clear(const Clear type)
    {
        if (type == CLEAR_TO_END_OF_SCREEN || CLEAR_TO_BEGINNING_OF_SCREEN || CLEAR_SCREEN)
            printf("%s[%dJ", ANSI_ESC, type);
        else if (type == CLEAR_TO_END_OF_LINE || CLEAR_FROM_START_OF_LINE || CLEAR_LINE)
            printf("%s[%dK", ANSI_ESC, type);
        
    }

    inline void setMode(const Mode mode)
    {
        printf("%s[%dm", ANSI_ESC, mode);
    }

    inline void setColor(const Color color)
    {
        printf("%s[%dm", ANSI_ESC, color);
    }

    inline void moveCursor(const Cursor action, const int amount = 1)
    {
        if (action == CURSOR_HOME)
            printf("%s[%c", ANSI_ESC, action);

        else if (action == CURSOR_UP || CURSOR_DOWN || CURSOR_RIGHT || CURSOR_LEFT || CURSOR_BEGINNING_OF_NEXT_LINE || CURSOR_BEGINNING_OF_PREVIUS_LINE || CURSOR_COLUMN)
            printf("%s[%d%c", ANSI_ESC, amount, action);
            
        else if (action == CURSOR_LINE_UP_SCROLL || CURSOR_SAVE_POSITION || CURSOR_RESTORE_POSITION)
            printf("%s %c", ANSI_ESC, action);
    }

    inline void moveCursor(const int row, const int column)
    {
        printf("%s[%d;%dH", ANSI_ESC, row, column);
    }
}

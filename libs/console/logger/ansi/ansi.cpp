#include "ansi.h"

namespace ansi_escape_codes
{

    template <typename T>
    ansi_escape_code<T>::ansi_escape_code(T code) : m_Code(code) {};

    template <typename T>
    ansi_escape_code<T>::ansi_escape_code(char code) : ansi_escape_code((T) code) {};
    
    template <typename T>
    ansi_escape_code<T>::~ansi_escape_code() {};

    clear::clear(Clear code) : ansi_escape_code(code)
    {
        if (m_Code == CLEAR_TO_END_OF_SCREEN || m_Code == CLEAR_TO_BEGINNING_OF_SCREEN || m_Code == CLEAR_SCREEN)
            m_Type = 'J'; 
        else if (m_Code == CLEAR_TO_END_OF_LINE || m_Code == CLEAR_FROM_START_OF_LINE || m_Code == CLEAR_LINE)
            m_Type = 'K';
    }

    clear::clear(char code) : clear::clear((Clear) code) {};

    cursor::cursor(Cursor code) : ansi_escape_code(code), m_Row(1) {};
    cursor::cursor(char code) : cursor::cursor((Cursor) code) {};

    cursor::cursor(Cursor code, int row) : ansi_escape_code(code), m_Row(row) {};
    cursor::cursor(char code, int row) : cursor::cursor((Cursor) code, row) {};

    cursor::cursor(int row, int column) : m_Row(row), m_Column(column), ansi_escape_code(0) {};
} // namespace ansi_escape_codes

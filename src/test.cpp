#include <iostream>

namespace ansi
{
#define ENTRY(name, code) \
	static inline struct name##_opcode {} name; \
	inline std::ostream& operator << (std::ostream& os, const name##_opcode&) \
	{ os << "\x1b[" #code "m"; return os; }
ENTRY(bold, 1)

#define COLOR_ENTRY(name, code) \
	static inline struct name##_color {} name; \
	inline std::ostream& operator << (std::ostream& os, const name##_color&) \
	{ os << "\x1b[" #code "m"; return os; }
    
COLOR_ENTRY(red,     31)
};

int main()
{
    std::cout << ansi:: << "afasf";
}
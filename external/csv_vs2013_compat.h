#if defined(_MSC_VER) && (_MSC_VER <= 1800)

#if !defined(constexpr)
#	define constexpr
#endif

#include <cstdarg>

namespace std {
	inline int snprintf(char* str, size_t size, const char* format, ...) {
		int count = -1;
		va_list ap;

		va_start(ap, format);
		
		if (size != 0)
			count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
		if (count == -1)
			count = _vscprintf(format, ap);
		
		va_end(ap);

		return count;
	}
}

#endif

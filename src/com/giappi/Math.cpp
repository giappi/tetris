
#include "com/giappi/Math.h"
#include <algorithm>

void StringUtils::copy(const char* source, UnsignedInteger n, char* target)
{
    NonNegInteger i = 0;
    std::copy(source, source + n, target);
    while(i < n && source[i] != CHAR_NULL)
    {
        target[i] = source[i];
        ++i;
    }
    target[i] = CHAR_NULL;
}

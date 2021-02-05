#include "cpp/lang/String.h"
#include <string>
#include <algorithm>
#include "utils/Debug.h"
#include "cpp/memory/Memory.h"

typedef std::string StdString;
const char CHAR_SPACE = ' ';
const char CHAR_TAB   = '\t';

#pragma region HELP_FUNCTIONS
inline void*                    CREATE_STRING(const char* __const_char_array)
{
    return Memory::allocate<StdString>(__const_char_array);
    //return (new StdString(__const_char_array));
}

inline void                     DELETE_STRING(void* __void_pointer)
{
    Memory::unallocate((StdString*)__void_pointer);
    //delete (StdString*)__void_pointer;
    __void_pointer = null;
}

inline StdString&               STRING(void* __void_pointer)
{
    return *((StdString*)__void_pointer);
}

inline boolean                  IS_WHITESPACE(char ch)
{
    return ch == CHAR_SPACE || ch == CHAR_TAB;
}
#pragma endregion HELP_FUNCTIONS

String::String() : length(_length)
{
    _value  = CREATE_STRING("");
    updateLength();
}

String::String(const char* str) : length(_length)
{
    _value  = CREATE_STRING(str);
    updateLength();
}

String::String(const String& str) : length(_length)
{
    _value   = CREATE_STRING(str.toCharArray());
    updateLength();
}

String::~String()
{
    DELETE_STRING(_value);
}

boolean String::equals(const String& __string2) const
{
    return STRING(_value) == STRING(__string2._value);
}


boolean String::exists(const char& ch)
{
    return (STRING(_value)).find(ch) != StdString::npos;
}

String& String::operator=(const String& another)
{
    if(&another != this)
    {
        this->_length = another._length;
        if(this->_value != null)
        {
            delete (StdString*)this->_value;
            this->_value = null;
        }
        this->_value  = new StdString((*(StdString*)another._value).c_str());
    }
    return *this;
}


String String::operator+(const String& __another) const
{
    return String((STRING(this->_value) + STRING(__another._value)).c_str());
}

char String::operator[](const usize index) const
{
    return STRING(_value)[index];
}


char& String::operator[](const usize index)
{
    return STRING(_value)[index];
}


String::operator const char*() const
{
    return (const char*) STRING(_value).c_str();
}


char String::charAt(const usize index) const
{
    return  index < this->getLength() ? STRING(_value)[index] : '\0';
}


usize String::indexOf(String str) const
{
    return this->indexOf(str, 0);
};

usize String::indexOf(String str, const usize fromIndex) const
{
    auto std_string_index = STRING(_value).find(str.toCharArray(), fromIndex);
    if(std_string_index == StdString::npos)
    {
        std_string_index = this->getLength();
    }
    return std_string_index;
}

usize String::indexOfEndString() const
{
    return this->getLength() - 1;
}


usize String::getLength() const
{
    return STRING(_value).length();
}


String String::replaceN(const String &__replaceFrom, const String &__replaceTo, const usize __n)
{
    String tmp    = *this;
    usize begin   = tmp.indexOf(__replaceFrom);
    usize length  = __replaceFrom.getLength();
    for(usize i = 0; i < __n && begin < tmp.getLength(); ++i)
    {
        STRING(tmp._value).replace(begin, length, __replaceTo.toCharArray()).c_str();
        begin  = tmp.indexOf(__replaceFrom);
    }
    return tmp;
}


String String::replaceAll(const String &__replaceFrom, const String &__replaceTo)
{
    return this->replaceN(__replaceFrom, __replaceTo, this->getLength());
}


String String::trim() const
{
    // trim from left
    usize index_begin = 0;
    while( IS_WHITESPACE(STRING(_value)[index_begin]))
    {
         index_begin += 1;
    }
    //trim from right
    usize index_end = this->indexOfEndString();
    while( IS_WHITESPACE(STRING(_value)[index_end]))
    {
        index_end -= 1;
    }
    return this->substring(index_begin, index_end);
};


String String::toLowerCase() const
{
    String str = *this;
    for (usize i = 0; i < str.getLength(); i++)
    {
        str[i] += STRING(_value)[i] > '@' && STRING(_value)[i] < '[' ? ('a'-'A') : 0;
    }
    return str;
};


String String::toUpperCase() const
{
    String str = *this;
    for (usize i = str.getLength(); i-- > 0;)
    {
        str[i] -= STRING(_value)[i] > '`' && STRING(_value)[i] < '{' ? ('a'-'A') : 0;
    }
    return str;
}

const byte* String::toByteArray() const
{
    return (const byte*)STRING(_value).c_str();
}

const char* String::toCharArray() const
{
    return (const char*)toByteArray();
}


String String::substr(const usize __begin, const usize __length) const
{
    return STRING(_value).substr(__begin, __length).c_str();
};

String String::substring(const usize __begin, const usize __end) const
{
    return this->substr(__begin, __end - __begin);
};

String String::substring(const usize __begin) const
{
    return this->substr(__begin, this->getLength());
}


String String::toString() const
{
    return *this;
}

void String::updateLength()
{
    _length = STRING(_value).length();
}

/*
 * File:   String.h
 * Author: Giappi
 * Description: class String, provide functions to process string
 */

#pragma once
#include "_typedef.h"
#include "Object.h"
#include "ArrayAccess.h"

/**
 * class String
 */
class String:
    public Object,
    public ArrayAccess<char>
{
public:

    /**
     * Default constructor
     */
    String();

    /**
     * Create String from char array
     * @param str
     */
    String(const char* str);

    /**
     * Destructor
     */
    virtual ~String();

    /**
     * Create String from another String (copy)
     * @param str
     */
    String(const String &str);

    /**
     * cast String to 'const char*'
     * @return array of 'const char'
     */
    virtual operator const char*() const;

    /**
     * Assignment Operator
     * @param another
     * @return
     */
    virtual String&     operator =(const String& another);

    /**
     * Get character in String at index
     * @param index index of a char in this String
     * @return the char at the index
     */
    virtual char        operator [](const usize index) const override;

    /**
     * Set character in String at index
     * @param index index of a char in this String
     * @return the char at the index
     */
    virtual char&       operator [](const usize index) override;

    /**
     * Concatenate two String into one String
     * @param str another String
     * @return a new String that has length equals to sum of two String
     */
    virtual String      operator+(const String& str) const;

    /**
     * Get character in String at index
     * @param index index of a char in this String
     * @return the char at the index
     */
    virtual char        charAt(const usize index) const;

    /**
     * Check if this String equals with another
     * @param str anotherString to compare
     * @return true if two String are the same
     */
    virtual boolean     equals(const String& str) const;

    /**
     * Check if a character exists in this String
     * @param ch the character need to check
     * @return true if exists, false otherwise
     */
    virtual boolean     exists(const char &ch) override;

    /**
     * Get length of this String
     * @return length of this String
     */
    virtual usize       getLength() const override;

    /**
     * get position of `str` in String, return length of this String if not found
     * @param str a text to search in this String
     * @return position of `str` in this String
     */
    virtual usize       indexOf(String str) const;

    /**
     * Get index of a substring in this String,
     * return length of this String if not found
     * @param str a text to search in this String
     * @param fromIndex the index from which to start the search
     * @return position of `str` in this String
     */
    virtual usize       indexOf(String str, const usize fromIndex) const;

    /**
     * Get index of last character in this String
     * @return index of last character, equivalent to (LENGTH - 1)
     */
    virtual usize       indexOfEndString() const;

    /**
     * Replace a substring by another string by first N matches
     * @param replaceFrom the substring need replace
     * @param replaceTo the string will be replace for 'replaceFrom'
     * @param n_times the number of occurrences
     * @return new replaced String
     */
    virtual String      replaceN(const String &replaceFrom, const String &replaceTo, const usize n_times);

    /**
     * Replace a substring by another string
     * @param replaceFrom the substring need replace
     * @param replaceTo the string will be replace for 'replaceFrom'
     * @param n_times the number of occurrences
     * @return new replaced String
     */
    virtual String      replaceAll(const String &replaceFrom, const String &replaceTo);

    /**
     * Return a new String with all extra whitespaces from beginning and ending removed
     * @return the trimmed String
     */
    virtual String      trim() const;

    /**
     * Convert this String to array of bytes
     * @return array of bytes
     */
    virtual const byte* toByteArray() const;

    /**
     * Convert this String to array of chars
     * @return array of chars
     */
    virtual const char* toCharArray() const;

    /**
     * Converts all of the characters in this String to lower case
     * @return the String that is converted to lowercase
     */
    virtual String      toLowerCase() const;

    /**
     * Converts all of the characters in this String to upper case
     * @return the String that is converted to uppercase
     */
    virtual String      toUpperCase() const;

    /**
     * Take a new string that is a substring of this string by first index and length of substring
     * @param from the position that is the beginning of substring
     * @param length the length of substring
     * @return the specified substring
     */
    virtual String      substr(const usize from, const usize length) const;

    /**
     * Take a new string that is a substring of this string by given index
     * @param begin The beginning index
     * @param end The ending index
     * @return the specified substring
     */
    virtual String      substring(const usize begin, const usize end) const;

    /**
     * Take a new string that is a substring of this string from given index to end of String
     * @param begin The beginning index
     * @return the specified substring
     */
    virtual String      substring(const usize begin) const;

    /**
     * Convert this String to String
     * @return String
     */
    virtual String      toString() const override;

private:
    /**
     * Update the variable that denote length of this String
     */
    virtual void        updateLength();

public:

    /**
     * property to get length of this String, equivalent to this.getLength()
     */
    const usize&        length;

private:

    /**
     * store length of this String
     */
    usize               _length = 0;

    /**
     * store data of this String
     */
    void*               _value = null;
};


/**
 * @TODO:
 * Implement method modify on this String
 * + toLowerCase() -> doLowerCase()
 * + toUpperCase() -> doUpperCase()
 */
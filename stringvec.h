/**
 * ===============================================================================================
 * @addtogroup string-vector
 * @{
 * ------------------------------------------------------------------------------------------------
 * @file    stringvec.h
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 * @p       <a href="https://www.raesangur.com/">https://www.raesangur.com/</a>
 *
 * @brief   A quick utility class, with some useful features:
 *           - Read a file into a vector of strings
 *           - Filter, order, transform, search and access strings
 *           - And more!
 *
 * ------------------------------------------------------------------------------------------------
 * @copyright Copyright (c) 2023 Pascal-Emmanuel Lachance | Raesangur
 *
 * @par License: <a href="https://opensource.org/license/mit/"> MIT </a>
 *               This project is released under the MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ------------------------------------------------------------------------------------------------
 * File History:
 * @version 0.1
 * 2024-02-14 - Raesangur
 *      - Project creation
 *      - Implementation of most class members
 *      - Creation of some unit tests, work remains to be done on unit tests
 *
 * @version 0.2
 * 2024-02-16 - Raesangur
 *      - Added the `transform` method
 *
 * @version 0.3
 * 2024-02-29 - Raesangur
 *      - Added an example to the documentation
 *      - Added the `remove_nth` method
 *      - Given an output stream parameter to the `print` method.
 *      - Various improvements
 *
 * @version 0.4
 * 2024-05-09 - Raesangur
 *      - Inlined all methods
 *      - Converted `std::string` arguments to `std::string_view`
 *      - Added the `begin`, `cbegin`, `end` and `cend` methods
 *      - Added the [] operator
 *      - Fixed bug in `transform`
 *
 * @version 0.5
 * 2024-05-20 - Raesangur
 *      - Added filter methods taking a function object
 *      - Added sorting algorithms
 *      - Added `find` and `rfind` methods
 *      - Added `reverse` method
 *      - Added `trim` method
 *      - Added member types iterators
 *
 * @version 0.6
 * 2024-05-29 - Raesangur
 *      - Added `split` method
 *
 * @version 0.7
 * 2024-06-02 - Raesangur
 *      - Added the `write_file` method
 *      - Added the == and != operators, as well as the <=> operator
 *
 * ------------------------------------------------------------------------------------------------
 * @code
 * // Example usage:
 *      StringVec sv;                    // Creating string vector
 *      sv.read_file("example.txt");     // Read the content of "example.txt"
 *      sv.filter_keep("^.*apple.*$");   // Filter all words containing "apple"
 *      sv.transform([](std::string& s)
 *                   {
 *                       return std::toupper(s);
 *                   });                 // Convert all strings to uppercase
 *      sv.remove_first();               // Remove first element
 *      sv.remove_last();                // Remove last element
 *      sv.print();                      // Print the filtered and transformed strings
 *
 * // With example.txt as:
 *      pineapple
 *      lorem
 *      ipsum
 *      dolor
 *      sit
 *      amet
 *      boneappletea
 *      pear
 *      Apple
 *      apple pie
 *
 * // Would print:
 *      BONEAPPLETEA
 *      APPLE
 *
 * @endcode
 * ===============================================================================================
 */
/* clang-format off */
#ifndef STRINGVEC_H
#define STRINGVEC_H


/** ===============================================================================================
 *  INCLUDES
 */
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <type_traits>
#include <vector>


/** ===============================================================================================
 *  CLASS DEFINITION
 *
 * @defgroup STRINGVEC_CLASS_DEF                 Class Definition
 * @{
 */

/** -----------------------------------------------------------------------------------------------
 * @class   stringvec
 *
 * @brief   Vector of string utility class.
 */
class stringvec
{
public:
    using iter   = std::vector<std::string>::iterator;
    using riter  = std::vector<std::string>::reverse_iterator;
    using citer  = std::vector<std::string>::const_iterator;
    using criter = std::vector<std::string>::const_reverse_iterator;

    // Constructors / Destructors
    ~stringvec()                 = default;
    stringvec()                  = default;
    stringvec(const stringvec&)  = default;
    stringvec(const stringvec&&) = delete;
    stringvec(const std::vector<std::string>& orig) : vec{orig} {};
    stringvec(const std::initializer_list<std::string>&& orig) : vec{orig} {};

    // Input / Output
    inline void read_file (const std::string& path);
    inline void write_file(const std::string& path, const std::string_view sep) const;
    inline void write_file(const std::string& path, char sep = '\n') const;

    inline void print(std::ostream& os = std::cout,
                      const std::string_view sep = "\n",
                      bool keep_last_sep = true) const;

    // Filtering
    inline void filter_remove(const std::function<bool(const std::string)> func);
    inline void filter_remove(const std::string& regex);
    inline void filter_keep  (const std::function<bool(const std::string)> func);
    inline void filter_keep  (const std::string& regex);
    inline void filter_empty (bool keep_whitespace = false);

    inline void remove_first();
    inline void remove_last();
    inline void remove_nth(std::size_t pos);

    // Transforming
    inline void transform(const std::function<std::string(const std::string)> func);
    inline void trim();
    inline void split(const std::string_view delimiter = " ");

    // Ordering
    inline void reverse();
    inline void sort(const std::function<bool(const std::string_view,
                                              const std::string_view)> func);
    inline void sort_alphabetically();
    inline void sort_length();

    // Searching
    inline  iter find     (const std::function<bool(const std::string&)> func);
    inline citer find     (const std::function<bool(const std::string&)> func) const;
    inline  iter rfind    (const std::function<bool(const std::string&)> func);
    inline citer rfind    (const std::function<bool(const std::string&)> func) const;
    inline  iter find     (const std::string_view s);
    inline citer find     (const std::string_view s) const;
    inline  iter rfind    (const std::string_view s);
    inline citer rfind    (const std::string_view s) const;
    inline  iter find_reg (const std::string& regex);
    inline citer find_reg (const std::string& regex) const;
    inline  iter rfind_reg(const std::string& regex);
    inline citer rfind_reg(const std::string& regex) const;
 
    // Accessing
    inline std::vector<std::string>&       get();
    inline const std::vector<std::string>& get() const;

    inline iter  begin();
    inline citer begin() const;
    inline citer cbegin() const;
    inline iter  end();
    inline citer end() const;
    inline citer cend() const;

    inline       std::string& operator[](std::size_t index);
    inline const std::string& operator[](std::size_t index) const;

    // Comparison
    inline bool operator== (const stringvec& other) const;
    inline bool operator!= (const stringvec& other) const;
    inline std::strong_ordering operator<=>(const stringvec& other) const;


private:
    std::vector<std::string> vec;
};

/**
 * @}
 */



/** ===============================================================================================
 *  METHOD DEFINITIONS
 *
 * @defgroup STRINGVEC_METHOD_DEF                 Method Definitions
 * @{
 */


/** -----------------------------------------------------------------------------------------------
 * @brief Read a file line by line, pushing each line into the vector of string.
 * @param path: File to read the lines from.
 */
inline void stringvec::read_file(const std::string& path)
{
    /* Check if file is valid and open it. */
    std::ifstream input(path);
    if(!input)
    {
        throw std::runtime_error("Couldn't open file: " + path);
    }

    /* Read all lines of file into the vector. */
    std::string line;
    while(std::getline(input, line))
    {
        vec.push_back(line);
    }
}

/** -----------------------------------------------------------------------------------------------
 * @brief Write to a file every string from the vector, separated by a specified string.
 * @param path: File to write the strings to.
 * @param sep:  Separator string between the strings in the vector when writing back to file.
 */
inline void stringvec::write_file(const std::string& path, const std::string_view sep) const
{
    /* Check if file is valid and open it. */
    std::ofstream output(path);
    if (!output)
    {
        throw std::runtime_error("Couldn't write to file: " + path);
    }

    print(output, sep, false);
}

inline void stringvec::write_file(const std::string& path, char sep) const
{
    char separator[2] = {sep, '\0'};
    return write_file(path, separator);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Print the vector of strings line by line, then flush the output buffer.
 */
inline void stringvec::print(std::ostream& os,
                             const std::string_view sep,
                             bool keep_last_sep) const
{
    /* Write all strings of vector into file. */
    for(citer it = begin(); it < end(); it++)
    {
        os << *it;
        if ((it != end() - 1) || keep_last_sep == true)
        {
            os << sep;
        }
    }
    os.flush();
}


/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided func, remove all strings that match.
 * @param func: Function object to check against
 */
inline void stringvec::filter_remove(const std::function<bool(const std::string)> func)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), func),
              vec.end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided regex, remove all strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
inline void stringvec::filter_remove(const std::string& regex)
{
    std::regex reg{regex};

    filter_remove([&reg](const std::string& s)
                  {
                      return std::regex_match(s, reg);
                  });
}

/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided func, keep only strings that match.
 * @param func: Function object to check against
 */
inline void stringvec::filter_keep(const std::function<bool(const std::string)> func)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), [func](const std::string& s)
                                                     {
                                                         return !func(s);
                                                     }),
              vec.end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided regex, keep only strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
inline void stringvec::filter_keep(const std::string& regex)
{
    std::regex reg{regex};

    filter_keep([&reg](const std::string& s)
                {
                    return std::regex_match(s, reg);
                });
}

/** -----------------------------------------------------------------------------------------------
 * @brief Remove all empty strings from the vector.
 * @param keep_whitespace: If true, keep strings containing only whitespace.
 */
inline void stringvec::filter_empty(bool keep_whitespace)
{
    if (keep_whitespace)
    {
        filter_remove([](const std::string& s)
                      {
                          return s.empty();
                      });
    }
    else
    {
        filter_remove("^\\s+$");
    }
}


/** -----------------------------------------------------------------------------------------------
 * @brief Remove first element from the vector.
 */
inline void stringvec::remove_first()
{
    vec.erase(begin());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Remove last element from the vector.
 */
inline void stringvec::remove_last()
{
    vec.erase(end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Remove an element from the vector from its index.
 */
inline void stringvec::remove_nth(std::size_t pos)
{
    if (begin() + pos >= end())
        return;

    vec.erase(begin() + pos);
}


/** -----------------------------------------------------------------------------------------------
 * @brief Apply a function to all the elements of the vector
 * @param func: Function to apply
 */
inline void stringvec::transform(const std::function<std::string(const std::string)> func)
{
    std::for_each(begin(), end(), [func](std::string& s) {
        s = func(s);
    });
}

/** -----------------------------------------------------------------------------------------------
 * @brief Trim trailing and leading whitespace from all strings in the vector, including newlines.
 */
inline void stringvec::trim()
{
    transform([](const std::string s){
        // https://cplusplus.com/forum/beginner/251052/
        constexpr std::string_view whitespace = " \t\v\r\n";

        std::size_t start = s.find_first_not_of(whitespace);
        std::size_t end = s.find_last_not_of(whitespace);

        return start == end ? std::string() : s.substr(start, end - start + 1);
    });
    
}

/** -----------------------------------------------------------------------------------------------
 * @brief Split all strings in-place with a specified delimiter string.
 *
 * @param delimiter: String to use as a separation point for the string.
 * 
 * @details The delimiter string is removed from each split.
 */
inline void stringvec::split(const std::string_view delimiter)
{
    const std::size_t delimiterLength = delimiter.length();
    std::vector<std::string> newStrings;
    for (const std::string& s : *this)
    {
        // https://stackoverflow.com/a/46931770
        std::size_t start = 0;
        std::size_t end;

        while ((end = s.find(delimiter, start)) != std::string::npos)
        {
            newStrings.emplace_back(s, start, end - start);
            start = end + delimiterLength;
        }
        newStrings.emplace_back(s, start);
    }

    vec = std::move(newStrings);
}


/** -----------------------------------------------------------------------------------------------
 * @brief Reverse the order of the vector's elements.
 */
inline void stringvec::reverse()
{
    std::reverse(begin(), end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Sort each string in the vector in O(N logN)
 * @param func: Comparison function
 */
inline void stringvec::sort(const std::function<bool(const std::string_view,
                                                     const std::string_view)> func)
{
    std::sort(begin(), end(), func);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Sort the vector alphabetically
 * 
 * @details The sort function defaults to using operator<.
 *          The default implementation of std::string provides an alphabetically-compared operator<
 */
inline void stringvec::sort_alphabetically()
{
    std::sort(begin(), end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Sort the vector by length of the strings
 */
inline void stringvec::sort_length()
{
    std::sort(begin(), end(), [](const std::string_view a, const std::string_view b)
                              {
                                  return a.length() < b.length();
                              });
}


/** -----------------------------------------------------------------------------------------------
 * @brief Find the first element matching the input function.
 * @param func: Function to match in the vector.
 */
inline stringvec::iter stringvec::find(const std::function<bool(const std::string&)> func)
{
    return std::find_if(begin(), end(), func);
}

inline stringvec::citer stringvec::find(const std::function<bool(const std::string&)> func) const
{
    return const_cast<stringvec*>(this)->find(func);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Find the last element matching the input function.
 * @param func: Function to match in the vector.
 */
inline stringvec::iter stringvec::rfind(const std::function<bool(const std::string&)> func)
{
    riter it = std::find_if(vec.rbegin(), vec.rend(), func);

    // https://stackoverflow.com/q/4407985
    if (it != vec.crend())
    {
        return iter{--(it.base())};
    }
    else
    {
        return vec.end();
    }
}

inline stringvec::citer stringvec::rfind(const std::function<bool(const std::string&)> func) const
{
    return const_cast<stringvec*>(this)->rfind(func);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Find the first element matching the input string.
 * @param s: String to find in the vector.
 */
inline stringvec::iter stringvec::find(const std::string_view s)
{
    return find([s](const std::string_view x){return x == s;});
}

inline stringvec::citer stringvec::find(const std::string_view s) const
{
    return const_cast<stringvec*>(this)->find(s);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Find the last element matching the input string.
 * @param s: String to find in the vector.
 */
inline stringvec::iter stringvec::rfind(const std::string_view s)
{
    return rfind([s](const std::string_view x){return x == s;});
}

inline stringvec::citer stringvec::rfind(const std::string_view s) const
{
    return const_cast<stringvec*>(this)->rfind(s);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Find the first element matching the input regex.
 * @param regex: Regex to match in the vector.
 */
inline stringvec::iter stringvec::find_reg(const std::string& regex)
{
    std::regex reg{regex};

    return find([&reg](const std::string& s)
                {
                    return std::regex_match(s, reg);
                });
}

inline stringvec::citer stringvec::find_reg(const std::string& regex) const
{
    return const_cast<stringvec*>(this)->find_reg(regex);
}

/** -----------------------------------------------------------------------------------------------
 * @brief Find the last element matching the input regex.
 * @param regex: Regex to match in the vector.
 */
inline stringvec::iter stringvec::rfind_reg(const std::string& regex)
{
    std::regex reg{regex};

    return rfind([&reg](const std::string& s)
                {
                    return std::regex_match(s, reg);
                });
}

inline stringvec::citer stringvec::rfind_reg(const std::string& regex) const
{
    return const_cast<stringvec*>(this)->rfind_reg(regex);
}


/** -----------------------------------------------------------------------------------------------
 * @brief Get the vector of strings.
 */
inline std::vector<std::string>& stringvec::get()
{
    return vec;
}

inline const std::vector<std::string>& stringvec::get() const
{
    return vec;
}


/** -----------------------------------------------------------------------------------------------
 * @brief Get an iterator to the first element of the vector.
 */
inline stringvec::iter stringvec::begin()
{
    return vec.begin();
}

inline stringvec::citer stringvec::begin() const
{
    return vec.cbegin();
}

inline stringvec::citer stringvec::cbegin() const
{
    return begin();
}

/** -----------------------------------------------------------------------------------------------
 * @brief Get an iterator to the last element of the vector.
 */
inline stringvec::iter stringvec::end()
{
    return vec.end();
}

inline stringvec::citer stringvec::end() const
{
    return vec.cend();
}

inline stringvec::citer stringvec::cend() const
{
    return end();
}


/** -----------------------------------------------------------------------------------------------
 * @brief Get the string at position `index`.
 */
inline std::string& stringvec::operator[](std::size_t index)
{
    return vec[index];
}

inline const std::string& stringvec::operator[](std::size_t index) const
{
    return vec[index];
}



inline bool stringvec::operator== (const stringvec& other) const
{
    return vec == other.vec;
}

inline bool stringvec::operator!= (const stringvec& other) const
{
    return !(*this == other);
}

inline std::strong_ordering stringvec::operator<=>(const stringvec& other) const
{
    return vec <=> other.vec;
}



/**
 * @}
 */


#endif        // STRINGVEC_H
/* clang-format on */
/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */

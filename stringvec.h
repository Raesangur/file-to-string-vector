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
 *           - Filter strings
 *           - Apply transformations to all the strings
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
 *      - Added the `begin`, `cbegin`, `end` and `cend` methods
 *      - Added the [] operator
 *      - Fixed bug in `transform`
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
    ~stringvec()                 = default;
    stringvec()                  = default;
    stringvec(const stringvec&)  = default;
    stringvec(const stringvec&&) = delete;
    stringvec(const std::vector<std::string>& orig) : vec{orig} {};

    inline void read_file(const std::string_view path);

    inline void filter_remove(const std::string_view regex);
    inline void filter_keep(const std::string_view regex);

    inline void transform(const std::function<std::string(const std::string_view)> func);

    inline void remove_first();
    inline void remove_last();
    inline void remove_nth(std::size_t pos);

    inline std::vector<std::string>&       get();
    inline const std::vector<std::string>& get() const;

    inline std::vector<std::string>::iterator begin();
    inline std::vector<std::string>::const_iterator begin() const;
    inline std::vector<std::string>::const_iterator cbegin() const;
    inline std::vector<std::string>::iterator end();
    inline std::vector<std::string>::const_iterator end() const;
    inline std::vector<std::string>::const_iterator cend() const;

    inline std::string& operator[](std::size_t index);
    inline const std::string& operator[](std::size_t index) const;

    inline void print(std::ostream& os = std::cout) const;

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
 * @param path File to read the line from.
 */
inline void stringvec::read_file(const std::string_view path)
{
    std::string pathString{path};
    /* Check if file is valid and open it. */
    std::ifstream input(pathString);
    if(!input)
    {
        throw std::runtime_error("Couldn't open file: " + pathString);
    }

    /* Read all lines of file into the vector. */
    std::string line;
    while(std::getline(input, line))
    {
        vec.push_back(line);
    }
}


/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided regex, remove all strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
inline void stringvec::filter_remove(const std::string_view regex)
{
    std::regex reg{std::string{regex}};

    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [&reg](const std::string& s) {
                                 return std::regex_match(s, reg);
                             }),
              vec.end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided regex, keep only strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
inline void stringvec::filter_keep(const std::string_view regex)
{
    std::regex reg{std::string{regex}};

    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [&reg](const std::string& s) {
                                 return !std::regex_match(s, reg);
                             }),
              vec.end());
}


/** -----------------------------------------------------------------------------------------------
 * @brief Apply a function to all the elements of the vector
 * @param func: Function to apply
 */
inline void stringvec::transform(const std::function<std::string(const std::string_view)> func)
{
    std::for_each(begin(), end(), [func](std::string& s) {
        s = func(s);
    });
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
inline std::vector<std::string>::iterator stringvec::begin()
{
    return vec.begin();
}

inline std::vector<std::string>::const_iterator stringvec::begin() const
{
    return begin();
}

inline std::vector<std::string>::const_iterator stringvec::cbegin() const
{
    return begin();
}

/** -----------------------------------------------------------------------------------------------
 * @brief Get an iterator to the last element of the vector.
 */
inline std::vector<std::string>::iterator stringvec::end()
{
    return vec.end();
}

inline std::vector<std::string>::const_iterator stringvec::end() const
{
    return end();
}

inline std::vector<std::string>::const_iterator stringvec::cend() const
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
    return this->operator[](index);
}


/** -----------------------------------------------------------------------------------------------
 * @brief Print the vector of strings line by line, then flush the output buffer.
 */
inline void stringvec::print(std::ostream& os) const
{
    for(const std::string& s : vec)
    {
        os << s << '\n';
    }

    // Add new line and flush output buffer
    os << std::endl;
}


/**
 * @}
 */



#endif        // STRINGVEC_H
/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */

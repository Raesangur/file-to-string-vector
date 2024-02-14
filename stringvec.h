/**
 * ===============================================================================================
 * @addtogroup string-vector
 * @{
 * ------------------------------------------------------------------------------------------------
 * @file    stringvec.h
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
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
 * ===============================================================================================
 */
#ifndef STRINGVEC_H
#define STRINGVEC_H

/** ===============================================================================================
 *  INCLUDES
 */
#include <algorithm>
#include <iostream>
#include <fstream>
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
 * @class   STRINGVEC
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
    stringvec(const std::vector<std::string>& orig);

    void read_file(const std::string& path);

    void filter_remove(const std::string& regex);
    void filter_keep(const std::string& regex);

    void remove_first();
    void remove_last();

    const std::vector<std::string>& get() const;
    std::vector<std::string>&       get();

    void print() const;

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
 * @brief Vector of string copy constructor.
 *
 * @param orig: Vector of string to copy.
 */
stringvec::stringvec(const std::vector<std::string>& orig)
{
    vec = orig;
}


/** -----------------------------------------------------------------------------------------------
 * @brief Read a file line by line, pushing each line into the vector of string.
 * @param path File to read the line from.
 */
void stringvec::read_file(const std::string& path)
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
 * @brief Check all strings against a provided regex, remove all strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
void stringvec::filter_remove(const std::string& regex)
{
    std::regex reg{regex};

    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [&](const std::string& s) {
                                 return std::regex_match(s, reg);
                             }),
              vec.end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Check all strings against a provided regex, keep only strings that match the regex.
 * @param regex: Regular Expression to check against.
 */
void stringvec::filter_keep(const std::string& regex)
{
    std::regex reg{regex};

    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [&](const std::string& s) {
                                 return !std::regex_match(s, reg);
                             }),
              vec.end());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Remove first element from the vector.
 */
void stringvec::remove_first()
{
    vec.erase(vec.begin());
}

/** -----------------------------------------------------------------------------------------------
 * @brief Remove last element from the vector.
 */
void stringvec::remove_last()
{
    vec.erase(vec.end());
}


/** -----------------------------------------------------------------------------------------------
 * @brief Get the vector of strings.
 */
std::vector<std::string>& stringvec::get()
{
    return vec;
}

/** -----------------------------------------------------------------------------------------------
 * @brief Get the vector of strings.
 */
const std::vector<std::string>& stringvec::get() const
{
    return vec;
}

/** -----------------------------------------------------------------------------------------------
 * @brief Print the vector of strings line by line, then flush the output buffer.
 */
void stringvec::print() const
{
    for(const std::string& s : vec)
    {
        std::cout << s << '\n';
    }
    std::cout << std::endl;
}


/**
 * @}
 */

#endif        // STRINGVEC_H
/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */

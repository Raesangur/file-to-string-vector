/**
* ===============================================================================================
* @addtogroup string-vector
* @{
* ------------------------------------------------------------------------------------------------
* @file    test.cpp
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
* ------------------------------------------------------------------------------------------------
* File History:
* @version 0.1
* 2024-02-14 - Raesangur
* - Creation of the repo and the class.
* - Implementation of some basic functions.
* - Starting writing tests.
* ===============================================================================================
*/

/** ===============================================================================================
 *  INCLUDES
 */
#include "stringvec.h"


/** ===============================================================================================
 *  FUNCTION DEFINITIONS
 */

int main()
{
    stringvec sv;

    sv.read_file("input_test.txt");
    sv.remove_first();
    sv.filter_remove(".*[Aa]pple.*");
    sv.print();
    sv.filter_keep(".*berry");
    sv.print();
}


/**
 * ===============================================================================================
 * @}
 */

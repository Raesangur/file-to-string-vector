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
 *  TYPE DEFINITIONS
 */
using err_t = int;

/** ===============================================================================================
 *  CONSTANTS DEFINITIONS
 */
constexpr err_t TEST_SUCCESS = 0;
constexpr err_t TEST_ERROR   = -1;

/** ===============================================================================================
 *  FUNCTION DECLARATIONS
 */
err_t comparison_test();
err_t remove_test();

err_t integration_test();


static std::pair<stringvec, stringvec> load_test(const std::string& path);


/** ===============================================================================================
 *  FUNCTION DEFINITIONS
 */

err_t comparison_test()
{
    stringvec sv  = {"aaa", "bbb", "ccc"};
    stringvec sv2 = {"aaa", "bbb", "ccc"};
    stringvec sv3 = {"aaa", "bbb"};
    stringvec sv4 = {"aaa", "bbb", "aaa"};

    if(sv != sv2)
    {
        return TEST_ERROR;
    }

    if(sv == sv3)
    {
        return TEST_ERROR;
    }

    if(sv == sv4)
    {
        return TEST_ERROR;
    }

    return TEST_SUCCESS;
}

err_t remove_test()
{
    stringvec sv       = {"aaa", "bbb", "ccc", "ddd", "eee"};
    stringvec sv_first = {"bbb", "ccc", "ddd", "eee"};
    stringvec sv_last  = {"bbb", "ccc", "ddd"};
    stringvec sv_2nd   = {"bbb", "ddd"};

    sv.remove_first();
    if(sv != sv_first)
    {
        return TEST_ERROR;
    }

    sv.remove_last();
    if(sv != sv_last)
    {
        return TEST_ERROR;
    }

    sv.remove_nth(1);
    if(sv != sv_2nd)
    {
        return TEST_ERROR;
    }

    return TEST_SUCCESS;
}

err_t integration_test()
{
    const stringvec valid = {"Raspberry", "Blueberry"};
    stringvec       sv;

    sv.read_file("input_test.txt");
    sv.remove_first();
    sv.split();
    sv.filter_remove(".*[Aa]pple.*");
    // sv.print();
    sv.filter_keep(".*berry");
    // sv.print();
    sv.write_file("output_test.txt");

    if(sv != valid)
    {
        return TEST_ERROR;
    }
    return TEST_SUCCESS;
}



/* ------------------------------------------- */
int main()
{
    if(comparison_test() == TEST_ERROR)
    {
        std::cout << "FAIL" << std::endl;
        return TEST_ERROR;
    }

    if(remove_test() == TEST_ERROR)
    {
        std::cout << "FAIL" << std::endl;
        return TEST_ERROR;
    }


    if(integration_test() == TEST_ERROR)
    {
        std::cout << "FAIL" << std::endl;
        return TEST_ERROR;
    }

    std::cout << "SUCCESS" << std::endl;
    return TEST_SUCCESS;
}


/** ===============================================================================================
 *  PRIVATE FUNCTION DEFINITIONS
 */

static std::pair<stringvec, stringvec> load_test(const std::string& path)
{
    stringvec input;
    stringvec answer;
    input.read_file(path);
    answer.read_file(path + "-answer");

    return {input, answer};
}



/**
 * ===============================================================================================
 * @}
 */

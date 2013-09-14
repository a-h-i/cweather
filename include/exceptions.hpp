/*
* The MIT License (MIT)
*
* Copyright (c) 2013 Ahmed H. Ismail
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <stdexcept>

namespace cweather
{
namespace exceptions
{


struct CWeatherException : public std::runtime_error
{

    CWeatherException( const std::string& what ): runtime_error( what ) {}

};

/**
 *@brief currently indicates an error from libcurl.
 */
struct NetworkException : public CWeatherException
{
    NetworkException( const std::string& what ) : CWeatherException( what ) {}
};

/**
 *@brief thrown by parsers, usually when they encounter unexpected formats.
 */
struct DataFormatException : public CWeatherException
{
    DataFormatException( const std::string& what ) : CWeatherException( what ) {}
};


}
} // cweather::exceptions


#endif

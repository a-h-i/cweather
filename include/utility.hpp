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
#ifndef UTILITY_HPP
#define UTILITY_HPP

/**
 *@file
 */
#include "exceptions.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include <boost/regex.hpp>
#pragma GCC diagnostic pop
#include <string>

namespace cweather
{
namespace utility
{


extern const boost::regex HTML_ENTITIY_REGEX;
extern const std::string HTML_ENTITIY_FMT;
extern const boost::regex HTML_HEADER_REGEX;
extern const boost::regex HTML_DATA_SPACE_REPLACE_REGEX;
extern const std::string HTML_DATA_SPACE_REPLACE_FMT;



/**
 * @brief translates html entities such as &lt.
 */
template <class MutableBidirItr, class OutputTtr>
OutputTtr decode_html_entities( OutputTtr out, MutableBidirItr begin,
                                MutableBidirItr end )
{
    return boost::regex_replace( out, begin, end, HTML_ENTITIY_REGEX,
                                 HTML_ENTITIY_FMT, boost::match_default | boost::format_all );
}

/**
 *@brief replaces spaces with '+'.
 */
template <class OutputItr, class InputItr>
OutputItr encode_space( OutputItr out, InputItr begin, InputItr  end)
{
    return boost::regex_replace(out, begin, end, HTML_DATA_SPACE_REPLACE_REGEX, HTML_DATA_SPACE_REPLACE_FMT
                                , boost::match_default | boost::format_all);
}



/**
 * @brief performs a blocking HTTP GET request using libcurl.
 * @return http response body as processed by provided call back.
 * @param callback provided call back function for processing response body. param actual types (const char * original_body, std::size_t body_length, std::string *to_fill )
 * @param request HTTP request to send.
 * @throws cweather::exceptions::NetworkException if an error occured while performing the request.
 * @sa cweather::exceptions::NetworkException
 */
std::string curl_perform( std::string request,
                          std::size_t ( *callback ) ( void *, std::size_t, std::size_t, void * ) );


} // utility
} // cweather

#endif  // UTILITY_HPP
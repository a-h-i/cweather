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
#include "utility.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include <curl/curl.h>
#pragma GCC diagnostic pop
#include <boost/scope_exit.hpp>

const boost::regex
cweather::utility::HTML_ENTITIY_REGEX( "(&amp;)|(&quot;)|(&lt;)|(&gt;)|(&apos;)",
                                       boost::regex::optimize );
const std::string
cweather::utility::HTML_ENTITIY_FMT( "(?1&)(?2\")(?3<)(?4>)(?5')" );
const boost::regex cweather::utility::HTML_HEADER_REGEX(
    R"delim((.+\w\r\n)|\r\n)delim", boost::regex::optimize );

const boost::regex cweather::utility::HTML_DATA_SPACE_REPLACE_REGEX
( "( )", boost::regex::optimize );
const std::string cweather::utility::HTML_DATA_SPACE_REPLACE_FMT( "(?1+)" );

std::string cweather::utility::curl_perform( std::string request,
        std::size_t ( *callback ) ( void *, std::size_t,
                                    std::size_t, void * ) )
{
    using cweather::exceptions::NetworkException;
    CURL * curl = curl_easy_init(); // init curl
    char error_buffer[CURL_ERROR_SIZE];
    if( curl == nullptr )
        {
            throw NetworkException( "Failed to init CURL handle." );
        }
    BOOST_SCOPE_EXIT( &curl )
    {
        curl_easy_cleanup( curl );
    }
    BOOST_SCOPE_EXIT_END
    auto ec = curl_easy_setopt( curl, CURLOPT_ERRORBUFFER, error_buffer );
    if( ec != CURLE_OK )
        {
            throw NetworkException( "Failed to enable CURL error strings." );
        }
    ec = curl_easy_setopt( curl, CURLOPT_URL, request.c_str() ); // URL
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to set CURL URL. CURL Error Code : " ) + std::to_string(
                    static_cast<int>( ec ) ) +
                ". CURL Error Message : " + std::string( curl_easy_strerror( ec ) ) );
        }
    ec = curl_easy_setopt( curl, CURLOPT_TCP_KEEPALIVE, 0 );
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to set CURL TCP_KEEP_ALIVE option. CURL Error Code : " ) +
                std::to_string( static_cast<int>( ec ) )
                + ". CURL Error Message : "  + std::string( curl_easy_strerror( ec ) ) );
        }
    std::string response;
    ec = curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, callback ); // callback
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to set CURLOPT_WRITEFUNCTION option. CURL Error Code : " )
                + std::to_string( static_cast<int>( ec ) )
                + ". CURL Error Message : " + std::string( curl_easy_strerror( ec ) ) );
        }
    ec = curl_easy_setopt( curl, CURLOPT_WRITEDATA,
                           reinterpret_cast<void *> ( &response ) );
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to set CURLOPT_WRITEDATA option. CURL Error Code : " ) +
                std::to_string( static_cast<int>( ec ) )
                + ". CURL Error Message : " + std::string( curl_easy_strerror( ec ) ) );
        }
    ec = curl_easy_setopt( curl, CURLOPT_WRITEHEADER, nullptr );
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to set CURLOPT_WRITEHEADER option. CURL Error Code : " ) +
                std::to_string( static_cast<int>( ec ) )
                + ". CURL Error Message : " + std::string( curl_easy_strerror( ec ) ) );
        }
    ec = curl_easy_perform( curl ); // send request
    if( ec != CURLE_OK )
        {
            throw NetworkException(
                std::string( "Failed to perform CURL request. CURL Error Code : " ) +
                std::to_string( static_cast<int>( ec ) )
                + ". CURL Error Message : " + std::string( curl_easy_strerror( ec ) ) );
        }
    return response;
}
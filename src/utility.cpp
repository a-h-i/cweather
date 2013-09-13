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

const boost::regex
cweather::utility::HTML_ENTITIY_REGEX( "(&amp;)|(&quot;)|(&lt;)|(&gt;)|(&apos;)",
                                       boost::regex::optimize );
const std::string
cweather::utility::HTML_ENTITIY_FMT( "(?1&)(?2\")(?3<)(?4>)(?5')" );
const boost::regex cweather::utility::HTML_HEADER_REGEX(
    R"delim((.+\w\r\n)|\r\n)delim", boost::regex::optimize );


std::string cweather::utility::curl_perform( std::string request,
        std::size_t ( *callback ) ( void *, std::size_t,
                                    std::size_t, void * ) )
{
    CURL * curl = curl_easy_init(); // init curl
    curl_easy_setopt( curl, CURLOPT_URL, request.c_str() ); // URL
    curl_easy_setopt( curl, CURLOPT_TCP_KEEPALIVE, 0 );
    std::string response;
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, callback ); // callback
    curl_easy_setopt( curl, CURLOPT_WRITEDATA,
                      reinterpret_cast<void *> ( &response ) );
    curl_easy_setopt( curl, CURLOPT_WRITEHEADER, nullptr );
    CURLcode ec = curl_easy_perform( curl ); // send request
    curl_easy_cleanup( curl );
    if( ec != CURLE_OK )
        {
            // TODO: throw stuff
        }
    return response;
}
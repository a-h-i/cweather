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
#include "parsers.hpp"

const boost::regex cweather::service::parsers::WebServiceXParser::temperature_regex
 (R"del((([0-9]+\.[0-9]+)|([0-9]+)) C)del", boost::regex::optimize);

const boost::regex cweather::service::parsers::WebServiceXParser::pressure_regex
 (R"del((([0-9]+\.[0-9]+])|([0-9]+)) hPa)del", boost::regex::optimize);

const boost::regex cweather::service::parsers::WebServiceXParser::visibility_regex
(R"del([0-9]+)del", boost::regex::optimize);

const boost::regex cweather::service::parsers::WebServiceXParser::wind_direction_regex
(R"del([0-9]+ degrees)del", boost::regex::optimize);

const boost::regex cweather::service::parsers::WebServiceXParser::wind_speed_regex
(R"del((([0-9]+)|([0-9]+\.[0-9]+)) MPH)del", boost::regex::optimize);

const boost::regex cweather::service::parsers::WebServiceXParser::humidity_regex
(R"del((([0-9]+)|([0-9]+\.[0-9]+))%)del", boost::regex::optimize);


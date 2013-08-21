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

#include "weather_service.hpp"
#include "utility.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

// initalize static constants
const std::string cweather::service::WebServiceXWeatherService::HOST = "www.webservicex.net";
const std::string cweather::service::WebServiceXWeatherService::COUNTRY_TOKEN = "COUNTRY";
const std::string cweather::service::WebServiceXWeatherService::CITY_TOKEN = "CITY";
const boost::regex cweather::service::WebServiceXWeatherService::CITY_REQUEST_REGEX(
    std::string( "(" ) + CITY_TOKEN + ")|(" + COUNTRY_TOKEN + ")", boost::regex::optimize );
const std::string cweather::service::WebServiceXWeatherService::CITY_REQUEST =
    std::string( "GET /globalweather.asmx/GetWeather?CityName=" ) + CITY_TOKEN + "&CountryName=" + COUNTRY_TOKEN +
    " HTTP/1.1\r\nHost: www.webservicex.net\r\n\r\n";


cweather::service::WebServiceXWeatherService::WebServiceXWeatherService(): WeatherService(new TCPConnecter(HOST))
{

}

cweather::service::WebServiceXWeatherService::~WebServiceXWeatherService()
{

}

cweather::WeatherData cweather::service::WebServiceXWeatherService::get_weather_data(const std::string &country, const std::string &city)
{
   
    auto reply = get_xml(country, city);
   // std::copy(reply.begin(), reply.end(), std::ostream_iterator<char>(std::cout));
    return {0,0,0.0f,0.0f};
    
}

void cweather::service::WebServiceXWeatherService::send_request_helper(const std::string & country, const std::string &city, boost::system::error_code &ec)
{
    std::vector<char> request(CITY_REQUEST.size() + country.size() + city.size());
    const std::string fmt = std::string("(?1") + city + ")(?2" + country + ")";
    auto new_end = utility::apply_regex(request.begin(), CITY_REQUEST.cbegin(), CITY_REQUEST.cend(), CITY_REQUEST_REGEX, fmt);
    request.erase(new_end, request.end());
    conn->send_data(request, ec);
}


std::vector<char> cweather::service::WebServiceXWeatherService::get_xml(const std::string &country, const std::string &city)
{

    

    return {42,42,42};
}
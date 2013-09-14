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
#include "parsers.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "tinyxml2/tinyxml2.h"
#pragma GCC diagnostic pop
#include <vector>
#include <iterator>
#include <iostream>
// initalize static constants
const std::string cweather::service::WebServiceXWeatherService::HOST =
    "http://www.webservicex.net";
const std::string cweather::service::WebServiceXWeatherService::COUNTRY_TOKEN =
    "COUNTRY";
const std::string cweather::service::WebServiceXWeatherService::CITY_TOKEN =
    "CITY";
const boost::regex
cweather::service::WebServiceXWeatherService::CITY_REQUEST_REGEX(
    std::string( "(" ) + CITY_TOKEN + ")|(" + COUNTRY_TOKEN + ")",
    boost::regex::optimize );
const std::string cweather::service::WebServiceXWeatherService::CITY_REQUEST =
    HOST +
    "/globalweather.asmx/GetWeather?CityName=" + CITY_TOKEN + "&CountryName=" +
    COUNTRY_TOKEN;



cweather::service::WebServiceXWeatherService::WebServiceXWeatherService():
    WeatherService()
{
}

cweather::service::WebServiceXWeatherService::~WebServiceXWeatherService()
{
}

/**
 *@brief callback for libcurl
 */
static std::size_t handle_response( void * ptr, size_t size, size_t count,
                                    void * string )
{
    if( string != nullptr )
        {
            const char * cstr = reinterpret_cast<const char *>( ptr );
            std::string * str = reinterpret_cast<std::string *>( string );
            for( size_t i = 0; i < count; i++ )
                {
                    *str += cstr[i];
                }
        }
    return count;
}




std::string cweather::service::WebServiceXWeatherService::get_xml_helper(
    const std::string& country,
    const std::string& city )
{
    std::string encoded_country;
    utility::encode_space(std::back_inserter(encoded_country), country.cbegin(), country.cend());
    std::string encoded_city;
    utility::encode_space(std::back_inserter(encoded_city), city.cbegin(), city.cend());

    std::vector<char> temp( CITY_REQUEST.size() + encoded_country.size() + encoded_city.size() );
    const std::string fmt = std::string( "(?1" ) + encoded_city + ")(?2" + encoded_country + ")";
    auto new_end =  boost::regex_replace( temp.begin(), CITY_REQUEST.cbegin(),
                                          CITY_REQUEST.cend(), CITY_REQUEST_REGEX, fmt,
                                          boost::match_default | boost::format_all );
    std::string request_str( temp.begin(),
                             new_end ); // this string contains a valid URL
    std::cout << encoded_country << std::endl;
    auto response = utility::curl_perform( request_str, handle_response );
    std::string clean_response; // after replacing entities
    clean_response.reserve( response.size() );
    auto str_end = utility::decode_html_entities( clean_response.begin(),
                   response.begin(), response.end() );
    clean_response.erase( str_end, clean_response.end() );
    return clean_response;
}


cweather::WeatherData
cweather::service::WebServiceXWeatherService::get_weather_data(
    const std::string& country,
    const std::string& city )
{
    std::string response = get_xml_helper( country, city );
    if( response.find( "Data Not Found" ) != std::string::npos )
        {
            throw cweather::exceptions::IncorrectLocationException(
                std::string( "Country : " ) + country  + " City : " + city );
        }
    tinyxml2::XMLDocument doc;
    doc.Parse( response.c_str() );
    parsers::WebServiceXParser parser( &doc );
    WeatherData data;
    data.temperature = parser.get_temp_celcius();
    data.pressure = parser.get_pressure_pascal();
    data.visibility = parser.get_visibility_kilometers();
    data.wind_speed = parser.get_wind_speed_kph();
    data.wind_direction = parser.get_wind_direction_degrees();
    data.humidity = parser.get_humidity();
    return data;
}




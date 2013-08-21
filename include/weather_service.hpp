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

#ifndef WEATHER_SERVICE_HPP
#define WEATHER_SERVICE_HPP
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "tinyxml2/tinyxml2.h"
#include <boost/regex.hpp>
#pragma GCC diagnostic pop
#include <memory>

namespace cweather
{

struct WeatherData
{

    unsigned short wind_speed; // SI
    unsigned short wind_direction_degrees; // SI
    float humidity; // SI
    float temperature;// SI
    //boost::locale::date_time time;
};

namespace service
{


class WeatherService
{
public:
    WeatherService(){}
    virtual ~WeatherService(){};
    virtual WeatherData get_weather_data(const std::string &country, const std::string &city) = 0;
protected:
    WeatherData data;
};

class WebServiceXWeatherService : public WeatherService
{
public:
    WebServiceXWeatherService();
    ~WebServiceXWeatherService();
    WeatherData get_weather_data(const std::string &country, const std::string &city) override;
private:
    static const std::string HOST;
    static const std::string COUNTRY_TOKEN;
    static const std::string CITY_TOKEN;
    static const boost::regex CITY_REQUEST_REGEX;
    static const std::string CITY_REQUEST;
    static std::string get_xml_helper(const std::string &country, const std::string &city);
    tinyxml2::XMLDocument doc;
};




} // service
} // cweather

#endif // WEATHER_SERVICE_HPP
